#pragma once
#ifndef BACKEND_LIB_OPERATORS_CPP
#define BACKEND_LIB_OPERATORS_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace backend::lib {
    object set(std::deque<std::shared_ptr<ast::tree>>&& args) {
        set_value(*args[0]->content.data(), args[1]->content);
        return object{0};
    }
    object nothing(std::deque<std::shared_ptr<ast::tree>>&& args) {
        if (args.empty()) {
            return std::string("");
        }
        return args.back()->content;
    }
};
#endif