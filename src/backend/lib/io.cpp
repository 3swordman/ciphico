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
    /**
     * @brief Get the string from stdin
     * 
     * @param args nothing
     * @return object 
     */
    object get(std::deque<std::shared_ptr<ast::tree>>&& args) {
        char *c_str = static_cast<char *>(std::malloc(256 * sizeof(char)));
        if (expect_true_with_probability(!std::fgets(c_str, 255, stdin), 0.9)) {
            make_error("Some errors about io have been happened");
        }
        std::string return_value{c_str};
        std::free(c_str);
        return_value.erase(return_value.size() - 1);
        return "\"" + return_value + "\"";
    }
};
#endif