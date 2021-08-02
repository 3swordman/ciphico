#pragma once
#ifndef AST_CPP
#define AST_CPP
#include "base.cpp"
#include "backend/object.cpp"
/**
 * @author 3swordman 
 */
namespace ast {
    /**
     * @brief The map contains operators
     */
    const static std::pmr::unordered_map<std::string, std::string> operator_map {
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
        {"%", "_mod"},
        {"&", "_bit_and"},
        {"|", "_bit_or"},
        {"^", "_bit_xor"},
        {"!", "_not"},
        {"=", "_set"}
    };
    /**
     * @brief The abstract lexer tree
     */
    struct alignas(16) tree {
        backend::object content = "nothing"s;
        std::pmr::vector<std::unique_ptr<tree>> childs{};
    };
    /**
     * @brief Parse the lexer content, change it into an ast tree
     * @bug (a) is correct but not be allowed
     * 
     * @param lexer_content The output of lexer
     * @return Some ast tree
     */
    auto parse(std::pmr::list<std::string>&& lexer_content) noexcept {
        std::pmr::vector<tree> result{};
        result.emplace_back();
        tree *lexer_expr = &result[0];
        std::pmr::vector<tree *> stack{lexer_expr};
        long line_number{1};
        size_t frozen{};
        std::pmr::unordered_set<size_t> frozen_list{};
        lexer_content.emplace_back(EOL);
        for (std::string& i : lexer_content) {
            if (i == "(") {
                // Put the thing to the stack
                lexer_expr->childs.emplace_back(std::make_unique<tree>());
                stack.emplace_back(&*lexer_expr->childs.back());
                lexer_expr = stack.back();
            } else if (i == ")" || i[0] == right_temp_symbol) {
                if (frozen) {
                    if (frozen_list.count(stack.size())) {
                        frozen_list.erase(stack.size());
                        stack.pop_back();
                        lexer_expr = stack.back();
                    }
                    --frozen;
                }
                // Pop the stack
                if (expect_false_with_probability(stack.size() < 2, 0.9)) {
                    // Only one? what the fucking program he make!
                    make_error("unexpected \")\" at line "s + std::to_string(line_number));
                }
                stack.pop_back();
                lexer_expr = stack.back();
                if (frozen_list.count(stack.size())) {
                    frozen_list.erase(stack.size());
                    stack.pop_back();
                    lexer_expr = stack.back();
                }
            } else if (i[0] == left_temp_symbol) {
                // name it _func and put it into the stack
                lexer_expr->content = "_func"s;
                lexer_expr->childs.emplace_back(std::make_unique<tree>());
                stack.emplace_back(&*lexer_expr->childs.back());
                lexer_expr = stack.back();
            } else if (i.empty()) {
                // There is some error, but we ignore it
                continue;
            } else if (i == EOL) {
                if (frozen) {
                    if (frozen_list.count(stack.size())) {
                        frozen_list.erase(stack.size());
                        stack.pop_back();
                        lexer_expr = stack.back();
                    }
                    --frozen;
                }
                // It is the end of the line
                if (stack.size() != 1) {
                    make_error("unexpected \")\" at line "s + std::to_string(line_number));
                }
                result.emplace_back();
                lexer_expr = &result.back();
                stack = { lexer_expr };
                ++line_number;
            } else if (isdigit(i[0])) {
                // It is a number
                lexer_expr->content = i;
                if (frozen_list.count(stack.size())) {
                    frozen_list.erase(stack.size());
                    stack.pop_back();
                    lexer_expr = stack.back();
                }
            } else if (i == ",") {
                // Pop from stack and push
                stack.pop_back();
                lexer_expr = stack.back();
                lexer_expr->childs.emplace_back(std::make_unique<tree>());
                lexer_expr = &*lexer_expr->childs.back();
                stack.emplace_back(lexer_expr);
            } else if (i[0] == '"') {
                if (expect_true_with_probability(i.back() != '"', 0.9)) {
                    // There are some error
                    make_error("unexpected \" at line "s + std::to_string(line_number));
                }
                // It is a string
                lexer_expr->content = i;
                if (frozen_list.count(stack.size())) {
                    frozen_list.erase(stack.size());
                    stack.pop_back();
                    lexer_expr = stack.back();
                }
            } else if (std::isalpha(i[0]) || i[0] == '_') {
                // It is a variable or a func
                lexer_expr->content = i;
                ++frozen;
            } else if (is_operator(i) || maybe_operator(i[0])) {
                // It is a operator
                // Get the name of operator
                auto tree_now = std::move(*lexer_expr);
                lexer_expr->content = operator_map.find(i)->second;
                lexer_expr->childs.clear();
                lexer_expr->childs.emplace_back(std::make_unique<tree>(std::move(tree_now)));
                lexer_expr->childs.emplace_back(std::make_unique<tree>());
                stack.emplace_back(&*lexer_expr->childs.back());
                lexer_expr = stack.back();
                frozen_list.emplace(stack.size());

            } else {
                // It isn't anything, make an error
                make_error("unexpected \""s + i + "\" at line "s + std::to_string(line_number));
            }
        }
        return result;
    }
};
/**
 * @brief 
 * 
 * @param ast_tree 
 * @return true 
 * @return false 
 */
#if defined(__GNUC__) || defined(__clang__)
[[ gnu::pure, gnu::always_inline ]] inline
#elif defined(_MSC_VER)
__forceinline
#else
inline
#endif
bool is_end(const ast::tree& ast_tree) noexcept {
    return ast_tree.childs.empty();
}
#endif