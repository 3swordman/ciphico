#pragma once
#ifndef IS_SOMETHING_CPP
#define IS_SOMETHING_CPP
#include <string>
#include <unordered_set>
/**
 * @author 3swordman
 */
namespace is_something_datas {
    /**
     * @brief A list which contains keywords
     */
    static const std::unordered_set<std::string> keyword_list {
        "if",
        "while",
        "else",
        "for",
        "not",
        "let",
        "var",
        "and",
        "or"
    };

    /**
     * @brief A list which contains operators
     */
    static const std::unordered_set<std::string> truely_operator_list {
        ".",
        ",",
        "(",
        ")",
        "^",
        "~",
        "`",
        ",",
        ":",
        ";",
        "[",
        "]",
        "{",
        "}",
        "<=",
        ">=",
        "==",
        "&&",
        "||",
        "!=",
        "+=",
        "-=",
        "*=",
        "/=",
        "%="
    };

    /**
     * @brief A list which contains things maybe operator, maybe a part of operator
     */
    static const std::unordered_set<char> maybe_operator_list {
        '+',
        '-',
        '*',
        '/',
        '%',
        '&',
        '<',
        '>',
        '!',
        '=',
        '|'
    };

};
/**
 * @brief Tell you if the arg is a keyword
 * 
 * @param keyword_string Something you don't sure if it is a keyword
 * @return if the arg is a keyword
 */
#if defined(__GNUC__) || defined(__clang__)
[[ gnu::always_inline, gnu::pure ]] inline
#elif defined(_MSC_VER)
__forceinline
#else 
inline
#endif
bool is_keyword(const std::string& keyword_string) noexcept {
    return is_something_datas::keyword_list.count(keyword_string);
}

/**
 * @brief Tell you if the arg is an operator
 * 
 * @param character A character you don't sure if it is an operator
 * @return If the arg must be an operator
 */
#if defined(__GNUC__) || defined(__clang__)
[[ gnu::always_inline, gnu::pure ]] inline
#elif defined(_MSC_VER)
__forceinline
#else 
inline
#endif
bool is_operator(char character) noexcept {
    return is_something_datas::truely_operator_list.count(std::string("") + character);
}
/**
 * @brief Tell you if the arg is an operator
 * 
 * @param str A string you don't sure if it is an operator
 * @return If the arg must be an operator
 */
#if defined(__GNUC__) || defined(__clang__)
[[ gnu::always_inline, gnu::pure ]] inline
#elif defined(_MSC_VER)
__forceinline
#else 
inline
#endif
bool is_operator(const std::string& str) noexcept {
    return is_something_datas::truely_operator_list.count(str);
}
/**
 * @brief Tell you if the arg might be an operator
 * 
 * @param character A character you don't sure if it is an operator
 * @return If the arg might be a operator
 */
#if defined(__GNUC__) || defined(__clang__)
[[ gnu::always_inline, gnu::pure ]] inline
#elif defined(_MSC_VER)
__forceinline
#else 
inline
#endif
bool maybe_operator(char character) noexcept {
    return is_something_datas::maybe_operator_list.count(character) || is_operator(character);
}

#endif
