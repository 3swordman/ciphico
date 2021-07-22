#pragma once
#ifndef IS_SOMETHING_CPP
#define IS_SOMETHING_CPP
#include <string>
#include <unordered_set>
/**
 * @author 3swordman
 * @copyright 3swordman
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
        "%",
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
        "/="
    };

    /**
     * @brief A list which contains things maybe operator, maybe a part of operator
     */
    static std::unordered_set<char> maybe_operator_list {
        '+',
        '-',
        '*',
        '/',
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
inline bool is_keyword(const std::string& keyword_string) noexcept {
    return is_something_datas::keyword_list.find(keyword_string) != is_something_datas::keyword_list.end();
}

/**
 * @brief Tell you if the arg is an operator
 * 
 * @param character A character you don't sure if it is an operator
 * @return If the arg must be an operator
 */
inline bool is_operator(char character) noexcept {
    return is_something_datas::truely_operator_list.find(std::string("") + character) != is_something_datas::truely_operator_list.end();
}
/**
 * @brief Tell you if the arg is an operator
 * 
 * @param str A string you don't sure if it is an operator
 * @return If the arg must be an operator
 */
inline bool is_operator(const std::string& str) noexcept {
    return is_something_datas::truely_operator_list.find(str) != is_something_datas::truely_operator_list.end();
}
/**
 * @brief Tell you if the arg might be an operator
 * 
 * @param character A character you don't sure if it is an operator
 * @return If the arg might be a operator
 */
inline bool maybe_operator(char character) noexcept {
    return is_something_datas::maybe_operator_list.find(character) != is_something_datas::maybe_operator_list.end() || is_operator(character);
}

#endif
