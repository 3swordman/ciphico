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
    [[ nodiscard ]] func_type get_func(object&& obj) noexcept {
        obj.reload();
        try {
            if (obj.extra_content) {
                return std::any_cast<func_type>(*obj.extra_content);
            } else {
                throw std::bad_any_cast{};
            }
        } catch (const std::bad_any_cast&) {
            try {
                if (object(*obj.data()).extra_content) {
                    return std::any_cast<func_type>(*object(*obj.data()).extra_content);
                } else {
                    throw std::bad_any_cast{};
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
    #if defined(__clang__) || defined(__GNUC__)
    [[ gnu::pure ]]
    #endif
    [[ nodiscard ]] ast::tree tree_copy(ast::tree& tree) noexcept {
        ast::tree result;
        result.content = tree.content;
        result.childs.reserve(tree.childs.size());
        for (size_t i = 0;i < tree.childs.size();++i) {
            result.childs.emplace_back(std::make_unique<ast::tree>(tree_copy(*tree.childs[i])));
        }
        return result;
    }
    /**
     * @brief Execute using the ast tree
     * @param ast_tree Ast tree
     */
    inline void _execute(ast::tree& ast_tree) noexcept {
        // TODO: add support for if/while
        if (is_end(ast_tree)) {
            return;
        // } else if (*ast_tree.content.data() == "_func") {
        //     object temp;
        //     auto&& func = [tree_ = tree_copy(ast_tree)]([[ maybe_unused ]] std::pmr::vector<std::unique_ptr<ast::tree>>&& args) {
        //         return object{};
        //     };
        //     temp.func_ptr = std::make_shared<void>(
        //         func_type(std::move(func))
        //     );
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