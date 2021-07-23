#pragma once
#ifndef BACKEND_OBJECT_CPP
#define BACKEND_OBJECT_CPP
#include "../base.cpp"
/**
 * @author 3swordman
 */
namespace backend {
    class object;
    static std::unordered_map<std::string, std::shared_ptr<object>> variable_map;
    class alignas(alignof(std::shared_ptr<std::string>)) object {
        std::shared_ptr<std::string> raw_string = std::make_shared<std::string>();
    public:
        std::string get_str_from_raw_string() {
            auto& str = *raw_string;
            try {
                return *variable_map.at(str)->data();
            } catch (const std::exception& e) {
                return str;
            }
        }
        object() = default;
        object(const object& other) {
            *raw_string = *other.raw_string;
        }
        object(object&& other) {
            *raw_string = std::move(*other.raw_string);
        }
        template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        object(T&& number) {
            raw_string = std::make_shared<std::string>(std::to_string(std::forward<T>(number)));
        }
        object(const std::string& str) {
            raw_string = std::make_shared<std::string>(str);
        }
        object& operator=(const object& other) {
            *raw_string = *other.raw_string;
            return *this;
        }
        object& operator=(object&& other) {
            *raw_string = std::move(*other.raw_string);
            return *this;
        }
        ~object() = default;
        std::shared_ptr<std::string>& data() {
            return raw_string;
        }
        std::string to_string() {
            auto str = get_str_from_raw_string();
            if (str.empty()) {
                return "";
            } else if ((std::isdigit(str.front()) || str.front() == '-')) {
                return str;
            } else if (str.front() == '"') {
                auto temp = str.substr(1, str.size() - 2);
                return temp;
            } else {
                make_error("it is not anything");
            }
        }
    };
    template <typename T1, typename T2>
    void set_value(T1&& arg1, T2&& arg2) {
        variable_map.insert_or_assign(std::forward<T1>(arg1), std::forward<T2>(arg2));
    }
};
#endif