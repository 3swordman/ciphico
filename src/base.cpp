#pragma once

#ifndef BASE_CPP
#define BASE_CPP
// Disable warning
#define _CRT_SECURE_NO_WARNINGS 1
// Disable lock
#define _CRT_DISABLE_PERFCRIT_LOCKS 1
// Include files
#pragma region include_files
#include <list>
#include <deque>
#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <utility>
#include <functional>
#include <type_traits>
#include <any>
#include <array>
#include <chrono>
#include <memory_resource>
#include <map>
#include <filesystem>
#include <random>
#include <sstream>
#include <set>
#include <thread>
// Inclue C files
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <stdio.h>
// Windows
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define ON_WINDOWS
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#endif
// Simd
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
// Useful file
#include "is_something.cpp"
#pragma endregion include_files
// The end of line
static const std::string EOL = "_Endl";
// Define something unreachable
#if defined(__GNUC__) || defined(__clang__)
#define assume_unreachable() __builtin_unreachable()
#elif defined(_MSC_VER)
#define assume_unreachable() __assume(0)
#else
// Well, it's better than nothing.
#define assume_unreachable() std::abort()
#endif
// Symbols
constexpr auto left_temp_symbol = ':';
constexpr auto right_temp_symbol = ';';
constexpr auto left_symbol = '{';
constexpr auto right_symbol = '}';
// Useful macros
#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)
/**
 * @brief Print error message and quit, the exit code is 1
 * 
 * @param str_ error message
 */
#define make_error(str_) do {std::string_view CONCAT(str, __LINE__) = std::move(str_);std::fprintf(stderr, "Error: %.*s\n", static_cast<int>(CONCAT(str, __LINE__).size()), CONCAT(str, __LINE__).data());std::exit(1);} while (false)
using namespace std::literals;
#if defined(__GNUC__) || defined(__clang__)
#define expect_false_with_probability(things, probability) __builtin_expect_with_probability(!!(things), false, (probability))
#define expect_true_with_probability(things, probability) __builtin_expect_with_probability(!!(things), true, (probability))
#define prefetch_memory(...) __builtin_prefetch(__VA_ARGS__)
#else
#define expect_false_with_probability(things, probability) (!!(things))
#define expect_true_with_probability(things, probability) (!!(things))
#define prefetch_memory(...) 0
#endif
#endif