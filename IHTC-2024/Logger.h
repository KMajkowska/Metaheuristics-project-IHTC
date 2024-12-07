#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>

class Logger
{
public:
	Logger(const std::string& filename);
	Logger(const Logger& other) = default;
	~Logger();

	void log(const std::string& logStr);

	void flushToFile();

private:
	std::ofstream logFile;
	std::vector<std::string> buffer;
	std::mutex mutex;

	static constexpr size_t MAX_BUFFER_SIZE = 16384;

};