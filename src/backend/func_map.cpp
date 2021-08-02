#pragma once
#ifndef BACKEND_FUNC_MAP_CPP
#define BACKEND_FUNC_MAP_CPP
#include "../ast.cpp"
#include "lib/io.cpp"
#include "lib/keywords.cpp"
#include "lib/operators.cpp"
#include "lib/stdlib.cpp"
#include "lib/types.cpp"
/**
 * @author 3swordman
 */
namespace backend {
    using func_type = std::function<object(std::pmr::vector<std::unique_ptr<ast::tree>>&&)>;
    /**
     * @brief a map that contains diffrent type of function
     */
    static const std::pmr::unordered_map<std::string_view, func_type> func_map {
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
        {"_bit_and", lib::bit_and},
        {"_bit_or", lib::bit_or},
        {"_bit_xor", lib::bit_xor},
        {"_if", lib::if_},
        {"nothing", lib::nothing},
        {"sleep", lib::sleep},
        {"get", lib::get},
        {"int", lib::int_},
        {"str", lib::str_},
        {"del", lib::del_},
        {"_getitem", lib::getitem}
    };
};
#endif