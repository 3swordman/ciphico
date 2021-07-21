#pragma once
#ifndef BACKEND_INDEX_CPP
#define BACKEND_INDEX_CPP
#include "../ast.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace backend {
    /**
     * @brief Execute using the ast tree
     * @todo make it work
     * @warning don't use recursion
     * @param ast_tree Ast trees
     */
    void _execute(ast::tree&& ast_tree) {
        // Enter your code here
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