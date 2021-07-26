#pragma once
#ifndef BACKEND_INDEX_CPP
#define BACKEND_INDEX_CPP
#include "../ast.cpp"
#include "func_map.cpp"
#include "object.cpp"
/**
 * @author 3swordman
 */
namespace backend {
    /**
     * @brief Execute using the ast tree
     * @todo don't use goto
     * @param ast_tree Ast tree
     */
    inline void _execute(ast::tree& ast_tree) noexcept {
        if (is_end(ast_tree)) {
            return;
        } else {
            for (auto i = std::begin(ast_tree.childs);i != std::end(ast_tree.childs);++i) {
                _execute(**i);
            }
            try {
                ast_tree.content = func_map.at(*ast_tree.content.data())(std::move(ast_tree.childs));
            } catch (const std::exception& err) {
                std::fprintf(stderr, "%s", err.what());
                exit(1);
            }
        }
    }
    /**
     * @brief Execute using the ast trees
     * @param ast_tree Ast trees
     */
    #if defined(__GNUC__) || defined(__clang__)
    [[ gnu::always_inline ]] inline
    #elif defined(_MSC_VER)
    __forceinline
    #else 
    inline
    #endif
    void execute(std::pmr::deque<ast::tree>&& ast_tree) noexcept {
        for (auto&& i : ast_tree) { 
            _execute(i);
        }
    }
};
#endif