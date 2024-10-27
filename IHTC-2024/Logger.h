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

	std::vector<std::string> getLogs() const;

	void flushToFile();

private:
	std::string filename;
	std::vector<std::string> buffer;
	std::mutex mutex;

};