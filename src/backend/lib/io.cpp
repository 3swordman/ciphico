#pragma once
#ifndef BACKEND_LIB_IO_CPP
#define BACKEND_LIB_IO_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace backend::lib {
    object print(std::deque<std::shared_ptr<ast::tree>>&& args) {
        for (auto&& i : args) {
            std::printf("%.*s ", static_cast<int>(i->content.to_string().size()), i->content.to_string().data());
        }
        std::printf("\n");
        return object{0};
    }
};
#endif