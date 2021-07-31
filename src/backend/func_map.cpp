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
    using func_type = object(*)(std::pmr::vector<std::unique_ptr<ast::tree>>&&) noexcept;
    /**
     * @brief a map that contains diffrent type of function
     */
    static const std::pmr::unordered_map<std::string, func_type> func_map {
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
        {"nothing", lib::nothing},
        {"sleep", lib::sleep},
        {"get", lib::get},
        {"int", lib::int_},
        {"str", lib::str_},
        {"del", lib::del_},
        {"_getitem", lib::getitem},
        {"_make_array_index", lib::make_array_index}
    };
};
#endif