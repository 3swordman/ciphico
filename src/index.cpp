#include "base.cpp"
#include "lexer.cpp"
#include "ast.cpp"
#include "backend/index.cpp"
/**
 * @brief Init the program
 */
void init() {
    std::ios::sync_with_stdio(false);
}

/**
 * @brief Main function
 */
int main(int argc, char *argv[]) {
    if (argc == 2) {
        init();
        auto file = std::fopen(argv[1], "r");
        std::list<std::string> lexer_content;
        lexer::parse(lexer_content, file);
        auto ast_tree = ast::parse(lexer_content);
        backend::execute(std::move(ast_tree));
    }
}