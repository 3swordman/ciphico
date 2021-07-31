#pragma once

#ifndef BASE_CPP
#define BASE_CPP
#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DISABLE_PERFCRIT_LOCKS 1
#include <list>
#include <deque>
#include <string>
#include <string_view>
#include <unordered_set>
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

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include "is_something.cpp"
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define ON_WINDOWS
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#else
#include <thread>
#endif
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
static const std::string EOL = "_Endl";

#if defined(__GNUC__)
#define assume_unreachable() __builtin_unreachable()
#elif defined(_MSC_VER)
#define assume_unreachable() __assume(0)
#else
// Well, it's better than nothing.
#define assume_unreachable() std::abort()
#endif

/**
 * @brief Print error message and quit, the exit code is 1
 * 
 * @param str error message
 */
#if defined(__GNUC__) || defined(__clang__)
[[ noreturn, gnu::always_inline ]] inline
#elif defined(_MSC_VER)
[[ noreturn ]] __forceinline
#else
[[ noreturn ]] inline
#endif
void make_error(std::string_view str) noexcept {
    std::fprintf(stderr, "%.*s\n", static_cast<int>(str.size()), str.data());
    std::exit(1);
}
using namespace std::literals;
using ssize_t = std::make_signed_t<size_t>;
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