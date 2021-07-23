#pragma once
#ifndef BACKEND_LIB_STDLIB_CPP
#define BACKEND_LIB_STDLIB_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 */
namespace backend {
    namespace lib {
        /**
         * @brief abort the program
         * 
         * @param args it don't need any argument
         * @return null
         */
        object abort(std::deque<std::shared_ptr<ast::tree>>&& args) {
            std::abort();
        }
        /**
         * @brief exit the program
         * 
         * @param args the error code
         * @return null
         */
        object exit(std::deque<std::shared_ptr<ast::tree>>&& args) {
            std::exit(std::stoi(args[0]->content.to_string()));
        }
        #if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
        void dll_deleter(HINSTANCE *x) {
            FreeLibrary(*x);
        }
        static std::unordered_map<std::string, std::shared_ptr<HINSTANCE>> modules;
        /**
         * @brief import module
         * 
         * @param args the name of module
         * @return nothing
         */
        object import_(std::deque<std::shared_ptr<ast::tree>>&& args) {
            using func_type = object(*)(std::deque<std::shared_ptr<ast::tree>>&&);
            HINSTANCE *dll_instance;
            func_type instance;
            if (!modules.count(*args[0]->content.data())) {
                modules.insert_or_assign(*args[0]->content.data(), std::shared_ptr<HINSTANCE>(new HINSTANCE{::LoadLibraryA(args[0]->content.data()->c_str())}, dll_deleter));
            }
            dll_instance = &*modules.find(*args[0]->content.data())->second;
            return "0"s;
        }
        #endif
    }    
};
#endif