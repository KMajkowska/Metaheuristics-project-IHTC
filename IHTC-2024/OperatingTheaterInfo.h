#pragma once

#include <string>

class OperatingTheaterInfo
{
public:
	OperatingTheaterInfo(int max, int current, const std::string& id);

	void setMax(int max);
	void setCurrent(int current);
	void setId(const std::string& id);

	int max() const;
	int current() const;
	std::string id() const;

private:
	int _max;
	int _current;
	std::string _id;
};