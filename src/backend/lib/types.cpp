#pragma once
#ifndef BACKEND_LIB_TYPES_CPP
#define BACKEND_LIB_TYPES_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 */
namespace backend::lib {
    object int_(std::deque<std::shared_ptr<ast::tree>>&& args) {
        return args[0]->content.to_string();
    }
    object str_(std::deque<std::shared_ptr<ast::tree>>&& args) {
        return "\"" + args[0]->content.to_string() + "\"";
    }
    object getitem_(std::deque<std::shared_ptr<ast::tree>>&& args) {
        auto a = std::stol(args[1]->content.to_string()) - 1;
        object return_value{"\""s + args[0]->content.to_string()[a] + "\""s};
        return_value.extra_content = std::make_shared<std::any>(
            std::make_any<std::pair<std::shared_ptr<std::string>, size_t>>(
                std::make_pair(
                    args[0]->content.data(), 
                    a
                )
            )
        );
        return return_value;
    }
    object del_(std::deque<std::shared_ptr<ast::tree>>&& args) {
        std::cout << "\n" << args[0]->content.reload().extra_content->has_value() << "\n";
        auto data = std::any_cast<std::pair<std::shared_ptr<std::string>, size_t>>(*args[0]->content.reload().extra_content);
        data.first->erase(data.second + 1, 1);
        return "0"s;
    }
};
#endif