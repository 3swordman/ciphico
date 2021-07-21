#pragma once
#ifndef BACKEND_FUNC_MAP_CPP
#define BACKEND_FUNC_MAP_CPP
#include "../ast.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace backend {
    static const std::unordered_map<std::string, std::function<std::string(std::deque<std::shared_ptr<ast::tree>>&&)>> func_map {
        {"a", [](std::deque<std::shared_ptr<ast::tree>>&& args) -> std::string {
            for (auto&& i : args) {
                std::cout << i->content << " ";
            }
            return "0"s;
        }}
    };
};
#endif