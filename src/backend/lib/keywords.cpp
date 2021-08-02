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
        /**
         * @brief Print the args to the stdout
         * 
         * @return null
         */
        object if_(std::pmr::vector<std::unique_ptr<ast::tree>>&& args) noexcept {
            if (bool(get_func(std::move(args[0]->content))({}))) {
                return get_func(std::move(args[1]->content))({});
            }
            return 0;
        }
    };
};
#endif