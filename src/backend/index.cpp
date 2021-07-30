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
    func_type get_func(object&& obj) noexcept {
        obj.reload();
        try {
            if (obj.extra_content) {
                return std::any_cast<func_type>(*obj.extra_content);
            } else {
                return std::any_cast<func_type>(std::make_any<int>(1));
            }
        } catch (const std::bad_any_cast&) {
            try {
                if (object(*obj.data()).extra_content) {
                    return std::any_cast<func_type>(*object(*obj.data()).extra_content);
                } else {
                    return std::any_cast<func_type>(std::make_any<int>(1));
                }
            } catch (const std::bad_any_cast&) {
                try {
                    return func_map.at(*obj.data());
                } catch (const std::exception&) {
                    make_error("unknown function: " + *obj.data());
                }
            }
        }

    }
    /**
     * @brief Execute using the ast tree
     * @todo don't use goto
     * @param ast_tree Ast tree
     */
    inline void _execute(ast::tree& ast_tree) noexcept {
        if (is_end(ast_tree)) {
            return;
        } else {
            for (auto&& i : ast_tree.childs) {
                _execute(*i);
            }
            try {
                ast_tree.content = get_func(std::move(ast_tree.content))(std::move(ast_tree.childs));
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
    void execute(std::pmr::vector<ast::tree>&& ast_tree) noexcept {
        for (auto&& i : ast_tree) { 
            _execute(i);
        }
    }
};
#endif