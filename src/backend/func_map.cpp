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
        {"print", [](std::deque<std::shared_ptr<ast::tree>>&& args) -> std::string {
            for (auto&& i : args) {
                std::printf("%.*s ", static_cast<int>(i->content.to_string().size()), i->content.to_string().data());
            }
            std::printf("\n");
            return "0"s;
        }},
        {"system", [](std::deque<std::shared_ptr<ast::tree>>&& args) -> std::string {
            return std::to_string(std::system(args[0]->content.to_string().c_str()));
        }}
    };
};
#endif