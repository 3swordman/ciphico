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
            if (obj.content->extra_content.has_value()) {
                return std::any_cast<func_type>(obj.content->extra_content);
            } else {
                throw std::bad_any_cast{};
            }
        } catch (const std::bad_any_cast&) {
            try {
                return func_map.at(obj.data());
            } catch (const std::exception&) {
                make_error("unknown function: " + obj.data());
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
        for (auto& i : tree.childs) {
            result.childs.emplace_back(std::make_unique<ast::tree>(tree_copy(*i)));
        }
        return result;
    }
    /**
     * @brief Execute using the ast tree
     * @param ast_tree Ast tree
     */
    #if defined(_MSC_VER) && !defined(__clang__)
    #pragma inline_depth(2)
    #endif
    inline void _execute(ast::tree& ast_tree) noexcept {
        // TODO: add support for while
        if (is_end(ast_tree)) {
            return;
        } else if (expect_false_with_probability(ast_tree.content.data() == "_func", 0.6)) {
            object temp{""s};
            temp.content->extra_content = std::make_any<func_type>(
                [tree_ = std::make_shared<ast::tree>(tree_copy(ast_tree))]([[ maybe_unused ]] std::pmr::vector<std::unique_ptr<ast::tree>>&& args) {
                    auto tree = tree_copy(*tree_);
                    std::for_each(tree.childs.begin(), std::prev(tree.childs.end()), [](std::unique_ptr<ast::tree>& i) {
                        _execute(*i);
                    });
                    ast::tree temp_tree;
                    temp_tree.content = "_set"s;
                    temp_tree.childs.emplace_back(std::make_unique<ast::tree>());
                    temp_tree.childs[0]->content = "_return"s;
                    temp_tree.childs.emplace_back(std::move(tree_->childs.back()));
                    _execute(temp_tree);
                    return object("_return"s);
                }
            );
            ast_tree.content = std::move(temp);
            ast_tree.childs.clear();
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