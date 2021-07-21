#pragma once
#ifndef AST_CPP
#define AST_CPP
#include "base.cpp"
namespace ast {
    /**
     * @brief The map contains operators
     */
    static std::unordered_map<std::string, std::string> operator_map {
        {"==", "_equals"},
        {"<=", "_less_equals"},
        {">=", "_greater_equals"},
        {"<", "_less"},
        {">", "_greater"},
        {"&&", "_and"},
        {"||", "_or"},
        {"!=", "_not_equals"},
        {"+=", "_add_to"},
        {"-=", "_minus_to"},
        {"*=", "_mul_to"},
        {"/=", "_div_to"},
        {"+", "_add"},
        {"-", "_minus"},
        {"*", "_mul"},
        {"/", "_div"},
        {"&", "_bit_and"},
        {"|", "_bit_or"},
        {"!", "_not"},
        {"=", "_set"}
    };
    /**
     * @brief The abstract lexer tree
     */
    struct tree {
        std::string content = "";
        std::deque<std::shared_ptr<tree>> childs;
    };
    /**
     * @brief Parse the lexer content, change it into an ast tree
     * @bug (a) is correct but not be allowed
     * 
     * @param lexer_content The output of lexer
     * @return Some ast tree
     */
    std::deque<tree> parse(const std::list<std::string>& lexer_content) noexcept {
        std::deque<tree> result{tree{}};
        tree *lexer_expr = &result[0];
        std::vector<tree *> stack{lexer_expr};
        long line_number{1};
        long char_number{0};
        for (std::string i : lexer_content) {
            char_number += i.size();
            if (i == "(") {
                // Put the thing to the stack
                lexer_expr->childs.push_back(std::make_shared<tree>());
                stack.push_back(&*lexer_expr->childs.back());
                lexer_expr = stack.back();
            } else if (i == ")") {
                // Pop the stack
                if (stack.size() < 2) {
                    // Only one? what the fucking program he make!
                    make_error("unexpected \")\" at line "s + std::to_string(line_number) + " char "s + std::to_string(char_number));
                }
                stack.pop_back();
                lexer_expr = stack.back();
            } else if (i.empty()) {
                // There is some error, but we ignore it
                continue;
            } else if (i == EOL) {
                // It is the end of the line
                if (stack.size() != 1) {
                    make_error("unexpected \")\" at line "s + std::to_string(line_number) + " char "s + std::to_string(char_number));
                }
                result.emplace_back();
                lexer_expr = &result.back();
                stack = { lexer_expr };
                ++line_number;
                char_number = 0;
            } else if (isdigit(i[0])) {
                // It is a number
                lexer_expr->content = i;
            } else if (i == ",") {
                // Pop from stack and push
                stack.pop_back();
                lexer_expr = stack.back();
                lexer_expr->childs.push_back(std::make_shared<tree>());
                lexer_expr = &*lexer_expr->childs.back();
                stack.push_back(lexer_expr);
            } else if (i[0] == '"') {
                if (i.back() != '"') {
                    // There are some error
                    make_error("unexpected \" at line "s + std::to_string(line_number) + " char "s + std::to_string(char_number));
                }
                // It is a string
                lexer_expr->content = i;
            } else if (std::isalpha(i[0]) || i[0] == '_') {
                // It is a variable or a func
                lexer_expr->content = i;
            } else if (is_operator(i) || maybe_operator(i[0])) {
                // It is a operator
                // Get the name of operator
                auto& content = operator_map.find(i)->second;
                auto tree_now = std::move(*lexer_expr);
                lexer_expr->content = content;
                lexer_expr->childs = {
                    std::make_shared<tree>(std::move(tree_now)), 
                    std::make_shared<tree>()
                };
                stack.push_back(&*lexer_expr->childs.back());
                lexer_expr = stack.back();

            } else {
                // It isn't anything, make an error
                make_error("unexpected \""s + i + "\" at line "s + std::to_string(line_number) + " char "s + std::to_string(char_number));
            }
        }
        return result;
    }
};
#endif