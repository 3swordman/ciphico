#pragma once
#ifndef BACKEND_LIB_STDLIB_CPP
#define BACKEND_LIB_STDLIB_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 */
namespace backend::lib {
    /**
     * @brief abort the program
     * 
     * @param args it don't need any argument
     * @return null
     */
    [[ noreturn ]] object abort(std::pmr::deque<std::shared_ptr<ast::tree>>&& args) noexcept {
        std::abort();
    }
    /**
     * @brief exit the program
     * 
     * @param args the error code
     * @return null
     */
    [[ noreturn ]] object exit(std::pmr::deque<std::shared_ptr<ast::tree>>&& args) noexcept {
        std::exit(std::stoi(args[0]->content.to_string()));
    }
};
#endif