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
    class 
    #ifndef NDEBUG
    alignas(16) 
    #endif
    object {
        std::shared_ptr<std::string> raw_string = std::make_shared<std::string>();
    public:
        std::shared_ptr<std::any> extra_content = std::make_shared<std::any>();
        object& reload() noexcept {
            try {
                auto& data_ = variable_map.at(*raw_string);
                raw_string = data_->raw_string;
                extra_content = data_->extra_content;
            } catch (const std::exception& e) {}
            return *this;
        }
        std::string& get_str_from_raw_string() noexcept {
            auto& str = *raw_string;
            try {
                return *variable_map.at(str)->data();
            } catch (const std::exception& e) {
                return str;
            }
        }
        object() noexcept = default;
        object(const object&) noexcept = default;
        object(object&&) noexcept = default;
        template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        object(T&& number) noexcept {
            raw_string = std::make_shared<std::string>(std::to_string(std::forward<T>(number)));
        }
        object(const std::string& str) noexcept {
            raw_string = std::make_shared<std::string>(str);
        }
        object(std::string&& str) noexcept {
            raw_string = std::make_shared<std::string>(std::move(str));
        }
        object& operator=(const object&) noexcept = default;
        object& operator=(object&&) noexcept = default;
        ~object() = default;
        #if defined(__GNUC__) || defined(__clang__)
        [[ gnu::pure, gnu::always_inline ]] inline
        #elif defined(_MSC_VER)
        __forceinline
        #else
        inline
        #endif
        std::shared_ptr<std::string>& data() noexcept {
            return raw_string;
        }
        std::string to_string() noexcept {
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
    void set_value(T1&& arg1, T2&& arg2) noexcept {
        variable_map.insert_or_assign(std::forward<T1>(arg1), std::forward<T2>(arg2));
    }
};
#endif