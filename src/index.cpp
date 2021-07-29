#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4710 4464 4668 4514 5039 5105)
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
        auto d = std::chrono::high_resolution_clock::now();
        init();
        auto file = std::fopen(argv[1], "rb");
        std::pmr::list<std::string> lexer_content;
        lexer::parse(lexer_content, file);
        #ifdef _WIN32
        _fclose_nolock(file);
        #else
        std::fclose(file);
        #endif
        translation::parse(lexer_content);
        auto ast_tree = ast::parse(std::move(lexer_content));
        backend::execute(std::move(ast_tree));
        auto e = std::chrono::high_resolution_clock::now();
        std::printf("%lld", (e - d) / 1us);
        return 0;
    } else {
        std::fputs(help_message, stderr);
        return 1;
    }
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif