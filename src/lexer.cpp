#pragma once
#ifndef LEXER_CPP
#define LEXER_CPP
#include "base.cpp"
#include "is_something.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace lexer {
    /**
     * @brief The state of parseing content
     */
    enum class char_type : unsigned char {
        unknown = 0,
        word = 1,
        number = 2,
        string = 3,
        symbol = 4,
        comment = 5
    };

    /**
     * @brief Parse the file to a list
     * @todo Make the code shorter
     * 
     * @param lexer_content The output of this function
     * @param file The phico source file
     * @exception nothing when there are some error, the function will call make_lexer_error, and the program's exit code will be 1
     */
    void parse(std::list<std::string>& lexer_content, std::FILE *file) noexcept {
        char_type type_of_i = char_type::unknown;
        std::string word = "";
        int _i;
        char i;
        bool has_more_char{};
        while (true) {
            // For an example, the content of file is "test", the i will be "t", "e", "s", "t" and " "
            if (expect_true(!has_more_char)) {
                _i = std::fgetc(file);
                if (expect_false(_i == EOF)) {
                    has_more_char = true;
                    _i = ' ';
                }
                i = char(_i);
            } else {
                break;
            }
            // Main code
            restart:
            switch (type_of_i) {
                case char_type::unknown:
                    if (i == '#') {
                        // The variable i is '#', it means there are some comment after it
                        type_of_i = char_type::comment;
                    } else if (is_operator(i)) {
                        // The variable i is an operator, it means there are some other thing like number and string after it
                        // We don't know what is it, so type_of_i is still char_type::unknown
                        std::string temp;
                        temp += i;
                        lexer_content.push_back(std::move(temp));
                    } else if (maybe_operator(i)) {
                        // The variable i might be an operator, might be a part of operator
                        type_of_i = char_type::symbol;
                        word += i;
                    } else if (std::isdigit(i)) {
                        // The variable i is a digit, there are also some digit after it
                        type_of_i = char_type::number;
                        word += i;
                    } else if (i == '"') {
                        // The variable i is the beginning of a string
                        type_of_i = char_type::string;
                        word += i;
                    } else if (i == ' ' || i == '\r') {
                        // The variable i is some useless thing like space
                        break;
                    } else if (i == '\n') {
                        // The variable i is the end of line
                        lexer_content.push_back(EOL);
                    } else {
                        // The variable i is a word, the content of it may be a function or a variable
                        type_of_i = char_type::word;
                        word += i;
                    } 
                    break;
                case char_type::comment:
                    // It's the comment, so we ignore it
                    if (i == '\n') {
                        type_of_i = char_type::unknown;
                        goto restart;
                    }
                    break;
                case char_type::number:
                    if (!std::isdigit(i)) {
                        // It isn't the digit, it's the end of the number
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else {
                        // The variable i is a digit, so put it into the word
                        word += i;
                    }
                    break;
                case char_type::string:
                    if (i == '"') {
                        // It is the end of a string
                        lexer_content.push_back(std::move(word) + "\"");
                        word = "";
                        type_of_i = char_type::unknown;
                    } else {
                        // It is the part of the string
                        word += i;
                    }
                    break;
                case char_type::symbol:
                    if (i == '\n') { 
                        // There is a newline between the words
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else if (i == ' ') {
                        // There is a space between the symbols
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        break;
                    } else if (i == '"') {
                        // There is a space between the symbols
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else if (is_operator(word + i)) {
                        // this is a operator
                        word += i;
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        break;
                    } else if (std::isdigit(i) || std::isalpha(i)) {
                        // the beginning of it is an operator
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else {
                        make_error("unknown operator: " + word + i);
                    }
                case char_type::word:
                    if (i == '\n') {
                        // It is the end of a word
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else if (i == ' ') {
                        // It is the end of a word
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        break;
                    } else if (maybe_operator(i)) {
                        // It is the end of a word
                        lexer_content.push_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else {
                        // It is still a part of the worf
                        word += i;
                    }
                    break;
            }
        }
    }
}
#endif