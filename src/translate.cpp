#pragma once
#ifndef TRANSLATE_CPP
#define TRANSLATE_CPP
#include "base.cpp"
#include "backend/object.cpp"
/**
 * @author 3swordman 
 */
namespace translation {
    void translate(std::list<std::string>& lexer_content) noexcept {
        auto begin = lexer_content.begin(), end = lexer_content.end();
        size_t bracket_number{};
        for (;begin != end;++begin) {
            if (*begin == "["s) {
                lexer_content.insert(std::prev(begin), {
                    "("s,
                    "_getitem"s,
                    "("s
                });
                *begin = ",";
                bracket_number = 1;
                auto right = std::find_if(std::next(begin), end, [&bracket_number](const std::string& str) {
                    if (str == "["s) ++bracket_number;
                    if (str == "]"s) {
                        --bracket_number;
                        if (bracket_number == 0) {
                            return true;
                        }
                    }
                    return false;
                });
                *right = ")"s;
                lexer_content.insert(std::next(right), ")");
            }
        }
    }
};
#endif