#pragma once
#ifndef IS_SOMETHING_CPP
#define IS_SOMETHING_CPP
#include <algorithm>
#include <string>
#include <string_view>
#include <memory_resource>
#include <vector>
/**
 * @author 3swordman
 */
namespace is_something_datas {
    /**
     * @brief A list which contains keywords
     */
    static std::pmr::vector<std::string_view> keyword_list {
        "if",
        "while"
    };
    static std::pmr::vector<std::string_view> one_keyword_list {
        "async"
    };

    /**
     * @brief A list which contains operators
     */
    static std::pmr::vector<std::string_view> truely_operator_list {
        "!=",
        "%=",
        "&&",
        "(",
        ")",
        "*=",
        "+=",
        ",",
        "-=",
        ".",
        "/=",
        ":",
        ";",
        "<<",
        "<=>",
        "==",
        ">=",
        ">>",
        "[",
        "]",
        "^",
        "`",
        "{",
        "||",
        "}",
        "~"
    };

    /**
     * @brief A list which contains things maybe operator, maybe a part of operator
     */
    static std::pmr::vector<char> maybe_operator_list {
        '!',
        '%',
        '&',
        '*',
        '+',
        '-',
        '/',
        '<',
        '=',
        '>',
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
bool is_keyword(std::string_view keyword_string) noexcept {
    return std::binary_search(is_something_datas::keyword_list.begin(), is_something_datas::keyword_list.end(), keyword_string);
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
    return std::binary_search(is_something_datas::truely_operator_list.begin(), is_something_datas::truely_operator_list.end(), (std::string("") + character));
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
bool is_operator(std::string_view str) noexcept {
    return std::binary_search(is_something_datas::truely_operator_list.begin(), is_something_datas::truely_operator_list.end(), str);
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
    return std::binary_search(is_something_datas::maybe_operator_list.begin(), is_something_datas::maybe_operator_list.end(), character) || is_operator(character);
}

#endif
