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

#include <cstddef>
#include <cstdlib>
#include <cstdio>

#include "is_something.cpp"
static const std::string EOL = "..";
[[ noreturn ]] void make_lexer_error(const std::string& str) {
    std::cerr << str << std::endl;
    std::exit(1);
}
#endif