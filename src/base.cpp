#pragma once
#ifndef BASE_CPP
#define BASE_CPP
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <format>

#include <cstddef>
#include <cstdlib>
#include <cstdio>

#include "is_something.cpp"
static const std::string EOL = "..";
/**
 * @brief Print error message and quit, the exit code is 1
 * 
 * @param str error message
 */
[[ noreturn ]] void make_error(const std::string& str) {
    std::cerr << str << std::endl;
    std::exit(1);
}
using namespace std::literals;
#if defined(__GNUC__) || defined(__clang__)
#define expect_false(things) __builtin_expect(!!(things), 0)
#define expect_true(things) __builtin_expect(!!(things), 1)
#else
#define expect_false(things) (!!(things))
#define expect_true(things) (!!(things))
#endif
#endif