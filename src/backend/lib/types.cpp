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
    object getitem(std::deque<std::shared_ptr<ast::tree>>&& args) {
        auto temp = args[1]->content.data()->find('`');
        if (temp == std::string::npos) {
            auto a = std::stoll(args[1]->content.to_string()) - 1;
            object return_value{"\""s + args[0]->content.to_string().at(a) + "\""s};
            return_value.extra_content = std::make_shared<std::any>(
                std::make_any<std::pair<std::shared_ptr<std::string>, size_t>>(
                    std::make_pair(
                        args[0]->content.data(), 
                        a
                    )
                )
            );
            return return_value;
        } else {
            return args[0]->content.to_string().substr(std::stoll(args[1]->content.data()->substr(0, temp)) - 1, std::stoll(args[1]->content.data()->substr(temp + 1, args[1]->content.data()->size() - 2)));
        }
    }
    object del_(std::deque<std::shared_ptr<ast::tree>>&& args) {
        auto data = std::any_cast<std::pair<std::shared_ptr<std::string>, size_t>>(*args[0]->content.reload().extra_content);
        auto temp = object(*data.first).to_string();
        // std::cout << "\n" << *data.first << " " << temp << " " << data.second << std::endl;
        temp.erase(data.second, 1);
        set_value(*data.first, std::make_shared<object>(object("\""s + temp + "\""s)));
        // std::cout << temp << std::endl;
        return "0"s;
    }
};
#endif