#pragma once
#ifndef LEXER_CPP
#define LEXER_CPP
#include "base.cpp"
#include "is_something.cpp"
/**
 * @author 3swordman
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
     * @exception when there are some error, the function will call make_lexer_error, and the program's exit code will be 1
     */
    void parse(std::pmr::list<std::string>& lexer_content, std::FILE *file) noexcept {
        char_type type_of_i = char_type::unknown;
        std::string word = "";
        static std::array<char, 32> buf;
        size_t char_need_to_read = 32;
        size_t already_read = 32;
        bool should_stop = false;
        bool is_eof = false;
        char i;
        while (true) {
            if (should_stop) {
                break;
            }
            // For an example, the content of file is "test", the i will be "t", "e", "s", "t" and " "
            if (already_read == char_need_to_read) {
                if (std::fgetc(file) != EOF) {
                    std::fseek(file, -1, SEEK_CUR);
                    size_t size = std::fread(buf.data(), sizeof(char), 32, file);
                    if (size == char_need_to_read) {
                        i = buf[0];
                        already_read = 1;
                    } else {
                        if (char_need_to_read != 32) {
                            i = ' ';
                            should_stop = true;
                        } else {
                            char_need_to_read = size;
                            i = buf[0];
                            already_read = 1;
                        }
                    }
                } else {
                    i = ' ';
                    should_stop = true;
                }
            } else {
                i = buf[already_read];
                ++already_read;
            }
            // Main code
            restart:
            switch (type_of_i) {
                case char_type::unknown:
                    if (i == '#') {
                        // The variable i is '#', it means there are some comment after it
                        type_of_i = char_type::comment;
                        break;
                    } else if (is_operator(i)) {
                        // The variable i is an operator, it means there are some other thing like number and string after it
                        // We don't know what is it, so type_of_i is still char_type::unknown
                        lexer_content.emplace_back(i + ""s);
                        break;
                    } else if (maybe_operator(i)) {
                        // The variable i might be an operator, might be a part of operator
                        type_of_i = char_type::symbol;
                    } else if (std::isdigit(i)) {
                        // The variable i is a digit, there are also some digit after it
                        type_of_i = char_type::number;
                    } else if (i == '"') {
                        // The variable i is the beginning of a string
                        type_of_i = char_type::string;
                    } else if (i == '\n') {
                        // The variable i is the end of line
                        lexer_content.emplace_back(EOL);
                        break;
                    } else if (std::isspace(i)) {
                        // The variable i is some useless thing like space
                        break;
                    } else {
                        // The variable i is a word, the content of it may be a function or a variable
                        type_of_i = char_type::word;
                    }
                    word += i;
                    break; 
                case char_type::comment:
                    // It's the comment, so we ignore it
                    if (expect_false_with_probability(i == '\n', 0.95)) {
                        type_of_i = char_type::unknown;
                        goto restart;
                    }
                    break;
                case char_type::number:
                    if (std::isdigit(i)) {
                        // The variable i is a digit, so put it into the word
                        word += i;
                    } else {
                        // It isn't the digit, it's the end of the number
                        lexer_content.emplace_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    }
                    break;
                case char_type::string:
                    if (expect_false_with_probability(i == '"', 0.8)) {
                        // It is the end of a string
                        lexer_content.emplace_back(std::move(word) + "\"");
                        word = "";
                        type_of_i = char_type::unknown;
                    } else {
                        // It is the part of the string
                        word += i;
                    }
                    break;
                case char_type::symbol:
                    if (i == '\n' || i == '"' || std::isalnum(i)) { 
                        // There is a newline between the words
                        lexer_content.emplace_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else if (i == ' ') {
                        // There is a space between the symbols
                        lexer_content.emplace_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        break;
                    } else if (is_operator(word + i)) {
                        // this is a operator
                        word += i;
                        lexer_content.emplace_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        break;
                    } else {
                        make_error("unknown operator: " + word + i);
                    }
                case char_type::word:
                    if (i == '\n' || i == ' ' || maybe_operator(i)) {
                        // It is the end of a word
                        lexer_content.emplace_back(std::move(word));
                        word = "";
                        type_of_i = char_type::unknown;
                        goto restart;
                    } else {
                        // It is still a part of the worf
                        word += i;
                    }
                    break;
                default:
                    assume_unreachable();
            }
        }
    }
}
#endif