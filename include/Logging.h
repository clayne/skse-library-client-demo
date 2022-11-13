#pragma once

#include <format>
#include <RE/C/ConsoleLog.h>
#include <spdlog/sinks/basic_file_sink.h>

template <class... Types>
void Log(const std::string text, const Types&... args) {
	std::string result = std::format(text, args...);
	logger::info("{}", result);
	RE::ConsoleLog::GetSingleton()->Print(std::format("[SkyrimScripting] {}", result).c_str());
};

