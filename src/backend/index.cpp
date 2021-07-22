#pragma once
#ifndef BACKEND_INDEX_CPP
#define BACKEND_INDEX_CPP
#include "../ast.cpp"
#include "func_map.cpp"
#include "object.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace backend {
    #if defined(__GNUC__) || defined(__clang__)
    __attribute__(( pure ))
    #endif
    inline bool is_end(const ast::tree& ast_tree) noexcept {
        return ast_tree.childs.empty();
    }
    /**
     * @brief Execute using the ast tree
     * @todo don't use goto
     * @param ast_tree Ast tree
     */
    void _execute(ast::tree&& ast_tree) noexcept {
        std::deque<ast::tree *> stack_tree{&ast_tree};
        std::deque<size_t> stack_number{0};
        while (!stack_number.empty()) {
            restart:;
            auto& stack_number_back = stack_number.back();
            auto& stack_tree_back = stack_tree.back();
            for (size_t i = stack_number_back;i < stack_tree_back->childs.size();++i) {
                if (!is_end(*stack_tree_back->childs[i])) {
                    stack_number_back = i + 1;
                    stack_number.push_back(0);
                    stack_tree.push_back(&*stack_tree_back->childs[i]);
                    goto restart;
                }
            }
            stack_tree_back->content = func_map.at(std::move(*stack_tree_back->content.data()))(std::move(stack_tree_back->childs));
            stack_tree_back->childs.clear();
            stack_number.pop_back();
            stack_tree.pop_back();
        }
    }
    /**
     * @brief Execute using the ast trees
     * @param ast_tree Ast trees
     */
    void execute(std::deque<ast::tree>&& ast_tree) noexcept {
        for (auto&& i : ast_tree) {
            _execute(std::move(i));
        }
    }
};
#endif