#pragma once
#ifndef LEXER_CPP
#define LEXER_CPP
#include "base.cpp"
#include "is_something.cpp"
namespace lexer {
    enum class char_type : unsigned char {
        unknown = 0,
        word = 1,
        number = 2,
        string = 3,
        symbol = 4,
        comment = 5
    };

    void parse(std::list<std::string>& lexer_content, std::FILE *file) noexcept {
        char_type type_of_i = char_type::unknown;
        std::string word = "";
        int _i;
        char i;
        bool has_more_char{};
        while (true) {
            if (!has_more_char) {
                _i = std::fgetc(file);
                if (_i == EOF) {
                    has_more_char = true;
                    _i = ' ';
                }
                i = char(_i);
            } else {
                break;
            }
            restart:
            switch (type_of_i) {
                case char_type::comment:
                    if (i == '\n') {
                        type_of_i = char_type::unknown;
                        goto restart;
                    }
                    break;
                case char_type::number:
                    if (!isdigit(i)) {
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else {
                        word += i;
                    }
                    break;
                    // oh, this character isn't digit, maybe there is a operator
                case char_type::string:
                    if (i == '"') {
                        // end of a string
                        lexer_content.push_back(std::move(word) + "\"");
                        word = "";
                        type_of_i = char_type::unknown;
                    } else {
                        // still in a string
                        word += i;
                    }
                    break;
                case char_type::symbol:
                    if (i == '\n') { 
                        // there is a newline between the words
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else if (i == ' ') {
                        // there is a space between the symbols
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        break;
                    } else if (i == '"') {
                        // there is a space between the symbols
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else if (is_operator(word + i)) {
                        word += i;
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        break;
                    } else if (isdigit(i) || isalpha(i)) {
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else if (is_operator(word)) {
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else {
                        make_lexer_error("unknown operator: " + word + i);
                    }
                case char_type::word:
                    if (i == '\n') {
                        // there is a space between the words
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else if (i == ' ') {
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        break;
                    } else if (maybe_operator(i)) {
                        // end of a word
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else {
                        word += i;
                    }
                    break;
                case char_type::unknown:
                    if (i == '#') {
                        type_of_i = char_type::comment;
                    } else if (is_operator(i)) {
                        std::string temp;
                        temp += i;
                        lexer_content.push_back(std::move(temp));
                    } else if (maybe_operator(i)) {
                        word += i;
                        type_of_i = char_type::symbol;
                    } else if (std::isdigit(i)) {
                        // i is a digit
                        if (type_of_i == char_type::unknown) {
                            type_of_i = char_type::number;
                        }
                        word += i;
                        // wait until next letter is not digit
                    } else if (i == '"') {
                        // begin of a string
                        word += "\"";
                        type_of_i = char_type::string;
                    } else if (i == ' ' || i == '\r') {
                        break;
                    } else if (i == '\n') {
                        lexer_content.push_back(EOL);
                    } else {
                        word += i;
                        type_of_i = char_type::word;
                    }
                    break;
            }
        }
    }
}
#endif