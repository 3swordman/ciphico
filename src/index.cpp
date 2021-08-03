#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4710 4464 4668 4514 5039 5105 4711)
#endif
#include "base.cpp"
#include "lexer.cpp"
#include "translate.cpp"
#include "ast.cpp"
#include "backend/index.cpp"
/**
 * @brief Init the program
 */
inline void init() noexcept {
    // TODO: add your code here
    #ifdef _WIN32
    _configthreadlocale(_ENABLE_PER_THREAD_LOCALE);
    #endif
    std::setvbuf(stdout, nullptr, _IOFBF, BUFSIZ);
}

constexpr auto help_message = R"(Ciphico v0.1,
Use "ciphico [filename]" to run the phico code.)";
/**
 * @brief Main function
 */
int main(int argc, char *argv[]) {
    // TODO: make it faster
    if (expect_true_with_probability(argc == 2, 0.99)) {
        init();
        auto d = std::chrono::high_resolution_clock::now();
        auto file = std::fopen(argv[1], "rb");
        std::pmr::list<std::string> lexer_content;
        lexer::parse(lexer_content, file);
        fclose(file);
        translation::parse(lexer_content);
        auto ast_tree = ast::parse(std::move(lexer_content));
        backend::execute(std::move(ast_tree));
        auto e = std::chrono::high_resolution_clock::now();
        std::printf("%lldus", (e - d) / 1us); // Don't change this
        std::exit(0);
    } else {
        std::fputs(help_message, stderr);
        std::exit(1);
    }
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif
