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
    static const std::unordered_map<std::string, std::function<object(std::deque<std::shared_ptr<ast::tree>>&&)>> func_map {
        {"print", lib::print},
        {"exit", lib::exit},
        {"abort", lib::abort},
        {"_set", lib::set},
        {"nothing", lib::nothing}
    };
};
#endif