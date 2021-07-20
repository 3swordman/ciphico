#pragma once
#ifndef IS_SOMETHING_CPP
#define IS_SOMETHING_CPP
#include <string>
#include <unordered_set>
namespace is_something_datas {
    static std::unordered_set<std::string> keyword_list {
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

    // emmm, it is something useful
    static std::unordered_set<std::string> truely_operator_list {
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

bool is_keyword(const std::string& keyword_string) noexcept {
    return is_something_datas::keyword_list.find(keyword_string) != is_something_datas::keyword_list.end();
}



bool is_operator(char character) noexcept {
    return is_something_datas::truely_operator_list.find(std::string("") + character) != is_something_datas::truely_operator_list.end();
}

bool is_operator(const std::string& str) noexcept {
    return is_something_datas::truely_operator_list.find(str) != is_something_datas::truely_operator_list.end();
}

bool maybe_operator(char character) noexcept {
    return is_something_datas::maybe_operator_list.find(character) != is_something_datas::maybe_operator_list.end() || is_operator(character);
}

#endif
