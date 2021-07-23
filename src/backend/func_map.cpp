#pragma once
#ifndef BACKEND_FUNC_MAP_CPP
#define BACKEND_FUNC_MAP_CPP
#include "../ast.cpp"
#include "lib/io.cpp"
#include "lib/operators.cpp"
#include "lib/stdlib.cpp"
/**
 * @author 3swordman
 */
namespace backend {
    /**
     * @brief a map that contains diffrent type of function
     */
    static std::unordered_map<std::string, std::function<object(std::deque<std::shared_ptr<ast::tree>>&&)>> func_map {
        {"print", lib::print},
        {"out", lib::print},
        {"exit", lib::exit},
        {"abort", lib::abort},
        {"_set", lib::set},
        {"_add", lib::add},
        {"nothing", lib::nothing}
    };
};
#endif