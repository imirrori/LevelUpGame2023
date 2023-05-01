//
// Created by Dmitry Morozov on 1/5/23.
//
#include "logtest.hpp"

#include "spdlog/spdlog.h"

void LogTest() {

	spdlog::warn("Easy padding in numbers like {:08d}", 12);
	spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	spdlog::info("Support for floats {:03.2f}", 1.23456);
	spdlog::info("Positional args are {1} {0}..", "too", "supported");
	spdlog::info("{:>8} aligned, {:<8} aligned", "right", "left");

	// Runtime log levels
	spdlog::set_level(spdlog::level::info); // Set global log level to info
	spdlog::debug("This message should not be displayed!");
	spdlog::set_level(spdlog::level::trace); // Set specific logger's log level
	spdlog::debug("This message should be displayed..");

	// Customize msg format for all loggers
	spdlog::set_pattern("[%H:%M:%S %z] [%^%L%$] [thread %t] %v");
	spdlog::info("This an info message with custom format");
	spdlog::set_pattern("%+"); // back to default format
	spdlog::set_level(spdlog::level::info);

}