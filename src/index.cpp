#include "base.cpp"
#include "lexer.cpp"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        auto file = std::fopen(argv[1], "r");
        std::list<std::string> lexer_content;
        lexer::parse(lexer_content, file);
        for (auto&& i : lexer_content) {
            std::cout << i << " ";
        }
    }
}