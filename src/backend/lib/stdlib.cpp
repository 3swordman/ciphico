#pragma once
#ifndef BACKEND_LIB_STDLIB_CPP
#define BACKEND_LIB_STDLIB_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace backend::lib {
    object abort(std::deque<std::shared_ptr<ast::tree>>&& args) {
        std::abort();
    }
    object exit(std::deque<std::shared_ptr<ast::tree>>&& args) {
        std::exit(std::stoi(args[0]->content.to_string()));
    }
};
#endif