#pragma once
#ifndef BACKEND_OBJECT_CPP
#define BACKEND_OBJECT_CPP
#include "../base.cpp"
/**
 * @author 3swordman
 */
namespace backend {
    struct object_value;
    static std::pmr::unordered_map<std::string, std::shared_ptr<object_value>> variable_map;
    struct alignas(16) object_value : public std::enable_shared_from_this<object_value> {
        std::string raw_string;
        std::any extra_content;
    };
    class object {
        template <typename T>
        struct false_t {
            enum {
                value = false
            };
        };
    public:
        std::shared_ptr<object_value> content = std::make_shared<object_value>();
        object& reload() noexcept {
            try {
                content = variable_map.at(content->raw_string);
            } catch (const std::exception&) {}
            return *this;
        }
        [[ nodiscard ]] std::string get_str_from_raw_string() noexcept {
            auto& str = content->raw_string;
            try {
                return variable_map.at(str)->raw_string;
            } catch (const std::exception&) {
                return str;
            }
        }
        object() noexcept  = default;
        object(const object&) noexcept = default;
        object(object&&) noexcept = default;
        template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        object(T&& number) noexcept {
            content->raw_string = std::to_string(std::forward<T>(number));
        }
        object(const std::string& str) noexcept {
            content->raw_string = str;
        }
        object(std::string&& str) noexcept {
            content->raw_string = std::move(str);
        }
        object& operator=(const object&) noexcept = default;
        object& operator=(object&&) noexcept = default;
        ~object() = default;
        template <typename T>
        operator T() {
            if constexpr (std::is_same_v<T, long>) {
                return std::stol(get_str_from_raw_string());
            } else if constexpr (std::is_same_v<T, int>) {
                return std::stoi(get_str_from_raw_string());
            } else if constexpr (std::is_same_v<T, long long>) {
                return std::stoll(get_str_from_raw_string());
            } else if constexpr (std::is_same_v<T, float>) {
                return std::stof(get_str_from_raw_string());
            } else if constexpr (std::is_same_v<T, double>) {
                return std::stod(get_str_from_raw_string());
            } else if constexpr (std::is_same_v<T, long double>) {
                return std::stold(get_str_from_raw_string());
            } else if constexpr (std::is_same_v<T, bool>) {
                auto my_str = get_str_from_raw_string();
                return !(my_str == "0" || my_str == "\"\"");
            } else {
                static_assert(false_t<T>::value, "??? what are you doing");
            }
        }
        #if defined(__GNUC__) || defined(__clang__)
        [[ gnu::pure, gnu::always_inline, nodiscard ]] inline
        #elif defined(_MSC_VER)
        [[ nodiscard ]] __forceinline
        #else
        [[ nodiscard ]] inline
        #endif
        std::string& data() noexcept {
            return content->raw_string;
        }
        [[ nodiscard ]] inline std::string to_string() noexcept {
            auto str = get_str_from_raw_string();
            if (expect_false_with_probability(str.empty(), 0.9)) {
                return "";
            } else if (expect_true_with_probability(std::isdigit(str.front()) || str.front() == '-', 0.6)) {
                return str;
            } else if (str.front() == '"') {
                return str.substr(1, str.size() - 2);
            } else {
                make_error("it is not anything");
            }
        }
    };
    template <typename T1, typename T2>
    #if defined(__GNUC__) || defined(__clang__)
    [[ gnu::always_inline ]] inline
    #elif defined(_MSC_VER)
    __forceinline
    #else
    inline
    #endif
    void set_value(T1&& arg1, T2&& arg2) noexcept {
        variable_map.insert_or_assign(std::forward<T1>(arg1), std::forward<T2>(arg2));
    }
};
#endif