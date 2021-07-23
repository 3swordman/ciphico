#pragma once
#ifndef BACKEND_LIB_TYPES_CPP
#define BACKEND_LIB_TYPES_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 */
namespace backend::lib {
    object int_(std::deque<std::shared_ptr<ast::tree>>&& args) {
        return args[0]->content.to_string();
    }
    object str_(std::deque<std::shared_ptr<ast::tree>>&& args) {
        return "\"" + args[0]->content.to_string() + "\"";
    }
};
#endif