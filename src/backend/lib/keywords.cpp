#pragma once
#ifndef BACKEND_LIB_KEYWORDS_CPP
#define BACKEND_LIB_KEYWORDS_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 */
namespace backend {
    [[ nodiscard ]] std::function<object(std::pmr::vector<std::unique_ptr<ast::tree>>&&)> get_func(object&& obj) noexcept;
    namespace lib {
        object if_(std::pmr::vector<std::unique_ptr<ast::tree>>&& args) noexcept {
            auto a = get_func(std::move(args[0]->content))({});
            if (bool(a)) {
                return get_func(std::move(args[1]->content))({});
            }
            return 0;
        }
        object async_(std::pmr::vector<std::unique_ptr<ast::tree>>&& args) noexcept {
            std::thread a{[func = get_func(std::move(args[0]->content))] {
                func({});
            }};
            a.detach();
            return 0;
        }
    };
};
#endif