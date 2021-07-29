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
     * @return null
     */
    object print(std::pmr::deque<std::shared_ptr<ast::tree>>&& args) noexcept {
        if (args.empty()) return 0;
        std::stringstream result;
        for (auto&& i : args) {
            if (*i->content.data() == "nothing") {
                continue;
            }
            result << i->content.to_string();
            result << " ";
        }
        auto str = result.str();
        std::printf("%.*s \n", static_cast<int>(str.size()), str.data());
        return 0;
    }
    /**
     * @brief Get the string from stdin
     * 
     * @return object 
     */
    object get(std::pmr::deque<std::shared_ptr<ast::tree>>&&) noexcept {
        static char c_str[256];
        if (expect_false_with_probability(!std::fgets(c_str, 255, stdin), 0.9)) {
            make_error("Some errors about io have been happened");
        }
        std::string return_value{c_str};
        return_value.erase(return_value.size() - 1);
        return "\"" + return_value + "\"";
    }
};
#endif