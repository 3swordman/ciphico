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
        set_value(*args[0]->content.data(), std::make_shared<object>(args[1]->content));
        return *args[0]->content.data();
    }
    object add(std::deque<std::shared_ptr<ast::tree>>&& args) {
        if (std::isdigit((args[0]->content.get_str_from_raw_string()).back()) && std::isdigit((args[1]->content.get_str_from_raw_string()).back())) {
            return std::stol(args[0]->content.get_str_from_raw_string()) + std::stol(args[1]->content.get_str_from_raw_string());
        } else {
            return "\""s + args[0]->content.to_string() + args[1]->content.to_string() + "\""s;
        }
    }
    object minus(std::deque<std::shared_ptr<ast::tree>>&& args) {
        return std::stol(args[0]->content.get_str_from_raw_string()) - std::stol(args[1]->content.get_str_from_raw_string());
    }
    object mul(std::deque<std::shared_ptr<ast::tree>>&& args) {
        return std::stol(args[0]->content.get_str_from_raw_string()) * std::stol(args[1]->content.get_str_from_raw_string());
    }
    object div(std::deque<std::shared_ptr<ast::tree>>&& args) {
        return std::stol(args[0]->content.get_str_from_raw_string()) / std::stol(args[1]->content.get_str_from_raw_string());
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
    object make_array_index(std::deque<std::shared_ptr<ast::tree>>&& args) {
        return *args[0]->content.data() + "`"s + *args[1]->content.data();
    }
};
#endif