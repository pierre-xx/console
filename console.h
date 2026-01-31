#pragma once
#include <iostream>
#include <windows.h>
#include <optional>
#include <mutex>
#include <sstream>

inline std::mutex log_mtx;

namespace console {
	inline HANDLE handle;

	enum class level {
		INFO,
		WARN,
		ERR
	};

	inline const char* lvl_names[] = {
		"INFO",
		"WARNING",
		"ERR"
	};

	void init(const std::string& title) {
		AllocConsole();
		FILE* f;
		freopen_s(&f, "CONOUT$", "w", stdout);
		freopen_s(&f, "CONIN$", "r", stdin);
		SetConsoleTitleA(title.c_str());
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void set_color(WORD col) {
		SetConsoleTextAttribute(handle, col);
	}

	template<typename T>
	void log(const T& val, std::optional<level> lvl = std::nullopt) {
		std::lock_guard<std::mutex> lock(log_mtx);

		std::ostringstream oss;
		oss << val;

		set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		time_t now = time(nullptr);
		tm lt{};
		localtime_s(&lt, &now);

		if (lvl) {
			const char* prefix = lvl_names[static_cast<int>(lvl.value())];

			printf("[%02d:%02d:%02d] [%s]: ", lt.tm_hour, lt.tm_min, lt.tm_sec, prefix);
		}
		else {
			printf("[%02d:%02d:%02d]: ", lt.tm_hour, lt.tm_min, lt.tm_sec);
		}

		set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		printf("%s\n", oss.str().c_str());
	}
}
