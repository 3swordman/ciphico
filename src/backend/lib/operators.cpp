#pragma once
#ifndef BACKEND_LIB_OPERATORS_CPP
#define BACKEND_LIB_OPERATORS_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 */
namespace backend::lib {
    /**
     * @brief set the variable
     * 
     * @param args The name of variable and the value of variable
     * @return The name of varible
     */
    object set(std::deque<std::shared_ptr<ast::tree>>&& args) {
        set_value(*args[0]->content.data(), args[1]->content);
        return *args[0]->content.data();
    }
    /**
     * @brief do nothing
     * 
     * @param args A group of things
     * @return The value of the one of args, if there aren't any arg, return null
     */
    object nothing(std::deque<std::shared_ptr<ast::tree>>&& args) {
        if (args.empty()) {
            return "0"s;
        }
        return args.back()->content;
    }
};
#endif