#pragma once
#ifndef BACKEND_INDEX_CPP
#define BACKEND_INDEX_CPP
#include "../ast.cpp"
#include "func_map.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace backend {
    #if defined(__GNUC__) || defined(__clang__)
    __attribute__(( pure ))
    #endif
    inline bool is_end(const ast::tree& ast_tree) {
        return ast_tree.childs.empty();
    }
    /**
     * @brief Execute using the ast tree
     * @todo don't use goto
     * @param ast_tree Ast tree
     */
    void _execute(ast::tree&& ast_tree) {
        // Enter your code here
        std::deque<ast::tree *> stack_tree{&ast_tree};
        std::deque<size_t> stack_number{0};
        while (!stack_number.empty()) {
            for (size_t i = stack_number.back();i < stack_tree.back()->childs.size();++i) {
                stack_number.back() = i;
                if (!is_end(*stack_tree.back()->childs[i])) {
                    stack_number.back() = i + 1;
                    stack_number.push_back(0);
                    stack_tree.push_back(&*stack_tree.back()->childs[i]);
                    goto restart;
                }
            }
            stack_tree.back()->content = func_map.at(stack_tree.back()->content)(std::move(stack_tree.back()->childs));
            stack_tree.back()->childs.clear();
            stack_number.pop_back();
            stack_tree.pop_back();
            restart:;
        }
    }
    /**
     * @brief Execute using the ast trees
     * @todo make it work
     * @param ast_tree Ast trees
     */
    void execute(std::deque<ast::tree>&& ast_tree) {
        for (auto&& i : ast_tree) {
            _execute(std::move(i));
        }
    }
};
#endif