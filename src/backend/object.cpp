#pragma once
#ifndef BACKEND_OBJECT_CPP
#define BACKEND_OBJECT_CPP
#include "../base.cpp"
/**
 * @author 3swordman
 * @copyright 3swordman
 */
namespace backend {
    class object;
    static const std::unordered_map<std::string, object> variable_map;
    class object {
        std::shared_ptr<std::string> raw_string = std::make_shared<std::string>();
    public:
        object() = default;
        object(const object&) = default;
        object(object&&) = default;
        template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        object(T&& number) {
            raw_string = std::make_shared<std::string>(std::to_string(std::forward<T>(number)));
        }
        object(const std::string& str) {
            raw_string = std::make_shared<std::string>(str);
        }
        object& operator=(const object&) = default;
        object& operator=(object&&) = default;
        ~object() = default;
        std::shared_ptr<std::string>& data() {
            return raw_string;
        }
        std::string to_string() {
            if (raw_string->empty()) {
                return "";
            } else if ((std::isdigit(raw_string->front()) || raw_string->front() == '-')) {
                return *raw_string;
            } else if (raw_string->front() == '"') {
                auto temp = raw_string->substr(1, raw_string->size() - 2);
                return temp;
            } else {
                make_error("it is not anything");
            }
        }
    };
};
#endif