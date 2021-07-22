#pragma once
#ifndef BASE_CPP
#define BASE_CPP
#define _CRT_SECURE_NO_WARNINGS
#include <list>
#include <deque>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <utility>
#include <functional>
#include <type_traits>

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#define noexcept
#include "is_something.cpp"
static const std::string EOL = "_Endl";
/**
 * @brief Print error message and quit, the exit code is 1
 * 
 * @param str error message
 */
[[ noreturn ]] inline void make_error(const std::string& str) noexcept {
    std::fprintf(stderr, "%.*s\n", static_cast<int>(str.size()), str.data());
    std::exit(1);
}
using namespace std::literals;
using ssize_t = std::make_signed_t<size_t>;
#if defined(__GNUC__) || defined(__clang__)
#define expect_false(things) __builtin_expect(!!(things), 0)
#define expect_true(things) __builtin_expect(!!(things), 1)
#else
#define expect_false(things) (!!(things))
#define expect_true(things) (!!(things))
#endif
#endif