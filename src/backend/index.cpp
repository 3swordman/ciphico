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
    #if defined(__GNUC__) || defined(__clang__)
    __attribute__(( always_inline )) inline
    #elif defined(_MSC_VER )
    __forceinline
    #else 
    inline
    #endif
    void _execute(ast::tree&& ast_tree) noexcept {
        std::deque<ast::tree *> stack_tree{&ast_tree};
        std::deque<size_t> stack_number{0};
        while (!stack_number.empty()) {
            restart:;
            auto& stack_number_back = stack_number.back();
            auto& stack_tree_back = stack_tree.back();
            for (size_t i = stack_number_back;i < stack_tree_back->childs.size();++i) {
                if (expect_true_with_probability(!is_end(*stack_tree_back->childs[i]), 0.7)) {
                    stack_number_back = i + 1;
                    stack_number.push_back(0);
                    stack_tree.push_back(&*stack_tree_back->childs[i]);
                    goto restart;
                }
            }
            try {
                stack_tree_back->content = func_map.at(*stack_tree_back->content.data())(std::move(stack_tree_back->childs));
            } catch (const std::exception& err) {
                std::fprintf(stderr, "%s", err.what());
                exit(1);
            }
            stack_tree_back->childs.clear();
            stack_number.pop_back();
            stack_tree.pop_back();
        }
    }
    /**
     * @brief Execute using the ast trees
     * @param ast_tree Ast trees
     */
    #if defined(__GNUC__) || defined(__clang__)
    __attribute__(( always_inline )) inline
    #elif defined(_MSC_VER)
    __forceinline
    #else 
    inline
    #endif
    void execute(std::deque<ast::tree>&& ast_tree) noexcept {
        for (auto&& i : ast_tree) {
            _execute(std::move(i));
        }
    }
};
#endif