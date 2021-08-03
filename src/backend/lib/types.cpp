#pragma once
#ifndef BACKEND_LIB_TYPES_CPP
#define BACKEND_LIB_TYPES_CPP
#include "../object.cpp"
#include "../../ast.cpp"
/**
 * @author 3swordman
 */
namespace backend::lib {
    object int_(std::pmr::vector<std::unique_ptr<ast::tree>>&& args) noexcept {
        return args[0]->content.to_string();
    }
    object str_(std::pmr::vector<std::unique_ptr<ast::tree>>&& args) noexcept {
        return "\"" + args[0]->content.to_string() + "\"";
    }
    object getitem(std::pmr::vector<std::unique_ptr<ast::tree>>&& args) noexcept {
        auto temp = args[1]->content.data().find('`');
        if (temp == std::string::npos) {
            auto a = std::stoull(args[1]->content.to_string()) - 1;
            object return_value{"\""s + args[0]->content.to_string().at(a) + "\""s};
            return_value.content->extra_content = std::make_any<std::pair<std::string, size_t>>(
                std::make_pair(
                    args[0]->content.data(), 
                    a
                )
            );
            return return_value;
        } else {
            return args[0]->content.to_string().substr(
                std::stoull(args[1]->content.data().substr(0, temp)) - 1, 
                std::stoull(args[1]->content.data().substr(temp + 1, args[1]->content.data().size() - 2))
            );
        }
    }
    object del_(std::pmr::vector<std::unique_ptr<ast::tree>>&& args) noexcept {
        auto data = std::any_cast<std::pair<std::string, size_t>>(args[0]->content.reload().content->extra_content);
        auto temp = object(data.first).to_string();
        // std::cout << "\n" << *data.first << " " << temp << " " << data.second << std::endl;
        temp.erase(data.second, 1);
        set_value(data.first, object("\""s + temp + "\""s).content);
        // std::cout << temp << std::endl;
        return "0"s;
    }
};
#endif