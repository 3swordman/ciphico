#pragma once
#ifndef TRANSLATE_CPP
#define TRANSLATE_CPP
#include "base.cpp"
#include "backend/object.cpp"
/**
 * @author 3swordman 
 */
namespace translation {
    void remove_empty_line(std::pmr::list<std::string>& syntax_content) noexcept {
        size_t lines = 1;
        syntax_content.remove_if([&lines](const std::string& str) {
            if (str == EOL) {
                if (lines == 1) {
                    return true;
                } else {
                    lines = 1;
                }
            } else {
                lines = 0;
            }
            return false;
        });
    }

    void keyword_to_func(std::pmr::list<std::string>& syntax_content) noexcept {
        auto i = syntax_content.begin(), end = syntax_content.end();
        for (;i != end;++i) {
            if (is_something_datas::keyword_list.count(*i)) {
                auto left = std::find_if(i, end, [](const std::string& str) {
                    if (str == EOL) return false; // make_error("there aren't \":\" after keyword {}" + *i);
                    return str[0] == left_symbol;
                });
                if (left == end) return; // make_error("there aren't \":\" after keyword {}" + *i);
                long number{1};
                auto right = std::find_if(std::next(left), end, [&number](const std::string& str) {
                    if (str[0] == left_symbol) ++number;
                    if (str[0] == right_symbol) {
                        --number;
                        if (number == 0) {
                            return true;
                        }
                    }
                    return false;
                });
                if (right == end) return; // make_error("there aren't \";\" after keyword " + *i);
                *i = "_" + *i;
                syntax_content.insert(std::next(i), { "(", (std::string("") + left_temp_symbol) });
                *left = (std::string("") + left_temp_symbol);
                *right = std::string("") + right_temp_symbol;
                syntax_content.insert(left, { (std::string("") + right_temp_symbol), "," });
                syntax_content.insert(std::next(right), ")");

            }
        }
    }

    void process_func_which_have_args(std::pmr::list<std::string>& syntax_content) noexcept {
        auto i = syntax_content.begin(), end = syntax_content.end();
        for (;i != end;++i) {
            if (*i == "func") {
                auto left = std::find_if(i, end, [](const std::string& str) {
                    if (str == EOL) return false; // make_error("there aren't \":\" after keyword {}" + *i);
                    return str[0] == left_symbol;
                });
                auto func_name = *std::next(i);
                syntax_content.insert(i, { "_set", "(", func_name, "," });
                syntax_content.erase(std::next(i), std::next(i, 3));
                if (left == end) return; // make_error("there aren't \":\" after keyword {}" + *i);
                long number{};
                auto right = std::find_if(left, end, [&number](const std::string& str) {
                    if (str[0] == left_symbol) ++number;
                    if (str[0] == right_symbol) {
                        --number;
                        if (number == 0) {
                            return true;
                        }
                    }
                    return false;
                });
                if (right == end) return; // make_error("there aren't \";\" after keyword " + *i);
                syntax_content.erase(std::prev(left, 1));
                *i = "_make_func_with_args";
                syntax_content.insert(std::next(i), "(");
                *left = (std::string("") + left_temp_symbol);
                *right = (std::string("") + right_temp_symbol);
                syntax_content.insert(left, ",");
                syntax_content.insert(std::next(right), { ")", ")" });

            }
        }
    }


    void make_func_better(std::pmr::list<std::string>& syntax_content) noexcept {
        auto iter = std::find(syntax_content.begin(), syntax_content.end(), (std::string("") + left_temp_symbol));
        auto end_pos = std::find(syntax_content.rbegin(), std::pmr::list<std::string>::reverse_iterator(iter), (std::string("") + right_temp_symbol)).base();
        std::replace(iter, end_pos, EOL, ","s);
        bool is_bracket = false;
        syntax_content.remove_if([&is_bracket](const std::string& str) {
            if (is_bracket && (str == "," || str == EOL)) {
                is_bracket = false;
                return true;
            }
            if (str[0] == left_temp_symbol || str == "(") {
                is_bracket = true;
            } else {
                is_bracket = false;
            }
            return false;
        });
        syntax_content.erase(syntax_content.begin(), std::remove_if(syntax_content.rbegin(), syntax_content.rend(), [&is_bracket](const std::string& str) {
            if (is_bracket && (str == "," || str == EOL)) {
                is_bracket = false;
                return true;
            }
            if (str[0] == right_temp_symbol || str == ")") {
                is_bracket = true;
            } else {
                is_bracket = false;
            }
            return false;
        }).base());
        iter = syntax_content.begin();
        bool frozen{};
        std::pmr::vector<bool> func_lambda_stack{}; // true: lambda, false: function arg
        size_t s{};
        for (;iter != syntax_content.end();++iter,++s) {
            switch ((*iter)[0]) {
                case '(':
                    if (!frozen) {
                        func_lambda_stack.emplace_back(false);
                    } else {
                        frozen = false;
                    }
                    break;
                case ')':
                    func_lambda_stack.pop_back();
                    break;
                case '{':
                    func_lambda_stack.emplace_back(true);
                    frozen = true;
                    syntax_content.insert(std::next(iter), "(");
                    break;
                case '}':
                    func_lambda_stack.pop_back();
                    syntax_content.insert(iter, ")");
                    break;
                case ',':
                    if (!func_lambda_stack.empty() && func_lambda_stack.back() == true) {
                        syntax_content.insert(iter, ")");
                        syntax_content.insert(std::next(iter), "(");
                        frozen = true;
                    }
                    break;
                default:;
            }
        }
    }
    void translate(std::pmr::list<std::string>& lexer_content) noexcept {
        auto begin = lexer_content.begin(), end = lexer_content.end();
        size_t bracket_number{};
        for (;begin != end;++begin) {
            if (expect_false_with_probability(*begin == "["s, 0.7)) {
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
    
    void parse(std::pmr::list<std::string>& syntax_content) noexcept {
        syntax_content.remove("var"s);
        remove_empty_line(syntax_content);
        translate(syntax_content);
        keyword_to_func(syntax_content);
        process_func_which_have_args(syntax_content);
        make_func_better(syntax_content);
    }
};
#endif