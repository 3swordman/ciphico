#pragma once
#ifndef BACKEND_FUNC_MAP_CPP
#define BACKEND_FUNC_MAP_CPP
#include "../ast.cpp"
#include "lib/io.cpp"
#include "lib/operators.cpp"
#include "lib/stdlib.cpp"
#include "lib/types.cpp"
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
        {"_minus", lib::minus},
        {"_mul", lib::mul},
        {"_div", lib::div},
        {"_mod", lib::mod},
        {"nothing", lib::nothing},
        {"get", lib::get},
        {"int", lib::int_},
        {"str", lib::str_},
        {"del", lib::del_},
        {"_getitem", lib::getitem},
        {"_make_array_index", lib::make_array_index}
    };
};
#endif