#include "base.cpp"
#include "lexer.cpp"
#include "translate.cpp"
#include "ast.cpp"
#include "backend/index.cpp"
/**
 * @brief Init the program
 */
inline void init() noexcept {
    // Your code here
}

constexpr auto help_message = R"(Ciphico v0.1,
Use "ciphico [filename]" to run the phico code.)";

/**
 * @brief Main function
 */
int main(int argc, char *argv[]) {
    if (expect_true_with_probability(argc == 2, 0.99)) {
        auto d = std::chrono::high_resolution_clock::now();
        init();
        auto file = std::fopen(argv[1], "rb");
        std::pmr::list<std::string> lexer_content;
        lexer::parse(lexer_content, file);
        std::fclose(file);
        translation::parse(lexer_content);
        auto ast_tree = ast::parse(std::move(lexer_content));
        backend::execute(std::move(ast_tree));
        auto e = std::chrono::high_resolution_clock::now();
        std::cout << (e - d) / 1us << std::endl;
        return 0;
    } else {
        std::puts(help_message);
        return 1;
    }
}