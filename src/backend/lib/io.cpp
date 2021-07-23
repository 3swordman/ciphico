#pragma once
#ifndef BACKEND_LIB_IO_CPP
#define BACKEND_LIB_IO_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 */
namespace backend::lib {
    /**
     * @brief Print the args to the stdout
     * 
     * @param args things you want to print to the stdout
     * @return null
     */
    object print(std::deque<std::shared_ptr<ast::tree>>&& args) {
        for (auto&& i : args) {
            std::printf("%.*s ", static_cast<int>(i->content.to_string().size()), i->content.to_string().data());
        }
        std::printf("\n");
        return object{0};
    }
    object get(std::deque<std::shared_ptr<ast::tree>>&& args) {
        std::string return_value;
        std::getline(std::cin, return_value);
        return "\"" + return_value + "\"";
    }
};
#endif