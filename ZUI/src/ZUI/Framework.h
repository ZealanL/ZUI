#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <format>
#include <cmath>
#include <cassert>
#include <mutex>

#define ZUI_FMT(s, ...) std::format(s, ##__VA_ARGS__)
#define ZUI_ASSERT(e) assert(e)

#ifndef ZUI_NO_STD_EXCEPTIONS
#define ZUI_ERROR(msg) ZUI_ASSERT(false && msg); throw std::exception(msg)
#else
#define ZUI_ERROR(msg) ZUI_ASSERT(false && msg)
#endif

#define ZUI_STATICASSERT(e, msg) static_assert(e, msg)

#ifdef _DEBUG
#define ZUI_DLOG(s, ...) { std::cout << std::format(s, ##__VA_ARGS__) << std::endl; }
#else
#define ZUI_DLOG {}
#endif

namespace ZUI {
	typedef uint8_t byte;
	using std::string;
	using std::vector;
	using std::pair;

	template<typename T>
	T Min(T a, T b) {
		return a < b ? a : b;
	}

	template<typename T>
	T Max(T a, T b) {
		return a > b ? a : b;
	}

	template<typename T>
	T Clamp(T val, T min, T max) {
		return val > max ? max : (val < min ? min : val);
	}
}