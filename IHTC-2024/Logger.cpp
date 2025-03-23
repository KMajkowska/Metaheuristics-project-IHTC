#include "Logger.h"


void Logger::log(auto log)
{
	if (DEBUG)
	{
		std::cout << std::to_string(log) << std::endl;
	}
}
