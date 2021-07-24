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
        char *c_str = static_cast<char *>(std::malloc(16 * sizeof(char)));
        gets_s(c_str, 15);
        std::string return_value{c_str};
        std::free(c_str);
        return "\"" + return_value + "\"";
    }
};
#endif