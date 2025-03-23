#pragma once

#include <string>
#include <iostream>

static const bool DEBUG = true;

/**
 * @brief Class that logs to wanted stream.
 */
class Logger
{
public:
	static const Logger& instance()
	{
		static Logger instance;
		return instance;
	}
	
	/**
	 * @brief Logs to given stream.
	 * @param log Param that can be std::to_string'ed.
	 */
	static void log(auto log);

private:
	Logger();
};