#include "../../base.cpp"
#include "../../lexer.cpp"
#include "../../translate.cpp"
#include "../../ast.cpp"
namespace compiler {
    static const std::string lib_str = R"(
        #include <iostream>
        #include <type_traits>
        #include <cstdio>
        inline namespace detail {
            double _add(double a, double b) {
                return a + b;
            }
            double _minus(double a, double b) {
                return a + b;
            }
            double _mul(double a, double b) {
                return a * b;
            }
            double _div(double a, double b) {
                return a / b;
            }
            double _mod(double a, double b) {
                return static_cast<long>(a) % static_cast<long>(b);
            }
            template <typename T>
            void _print(T&& arg) {
                std::cout << std::forward<T>(arg);
            }
            template <typename T, typename ...Ts>
            void _print(T&& arg, Ts&& ...args) {
                _print<T>(std::forward<T>(arg));
                _print<Ts...>(std::forward<Ts>(args)...);
            }
            template <typename ...Ts>
            int print(Ts&& ...args) {
                _print<Ts...>(std::forward<Ts>(args)...);
                _print("\n");
                return 0;
            }
        }
    )";
    size_t biggest_num{};
    inline std::string add_code(ast::tree& tree, std::string& content) noexcept {
        std::vector<std::string> str_list;
        std::stringstream my_str;
        if (is_end(tree)) {
            return tree.content.data();
        }
        for (auto&& i : tree.childs) {
            str_list.emplace_back(add_code(*i, content));
        }
        my_str << "auto e";
        ++biggest_num;
        my_str << biggest_num;
        my_str << " = ";
        my_str << tree.content.data();
        my_str << "( ";
        my_str << str_list[0] << " ";
        std::for_each(str_list.begin() + 1, str_list.end(), [&my_str](std::string& str) {
            my_str << ", ";
            my_str << str;
        });
        my_str << " );";
        content += my_str.str();
        return "e" + std::to_string(biggest_num);
    }
    /**
     * @brief Main function
     */
    void main(int, char *argv[]) {
        // TODO: make it faster
        std::pmr::vector<ast::tree> ast_trees;
        {
            auto file = std::fopen(argv[2], "rb");
            std::pmr::list<std::string> lexer_content;
            lexer::parse(lexer_content, file);
            fclose(file);
            translation::parse(lexer_content);
            ast_trees = ast::parse(std::move(lexer_content));
        }
        std::string file_name = "temp" + std::to_string(std::random_device{}()) + ".cpp";
        std::FILE *file = std::fopen(file_name.c_str(), "w");
        std::string file_content = lib_str;
        file_content += "int main() {";
        for (auto&& i : ast_trees) {
            add_code(i, file_content);
        }
        file_content += "}";
        std::fprintf(file, "%.*s", static_cast<int>(file_content.size()), file_content.data());
        fclose(file);
        std::system(("clang -O3 -fpermissive -std=c++17 -o a.exe " + file_name).c_str());
        std::remove(file_name.c_str());
        exit(0);
    }
};