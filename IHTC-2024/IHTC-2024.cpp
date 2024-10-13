#include <iostream>
#include <vector>
#include "IHTCProblemIO.h"

static const std::string PROBLEM_FILE = "../toy/toy.json";

template<typename T>
static std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	os << "{";

	for (size_t i = 0; i < vec.size(); ++i)
	{
		os << vec[i];

		if (i != vec.size() - 1)
		{
			os << ", ";
		}
	}

	os << "}\n";

	return os;
}

int main(int argc, char* argv[])
{
	const std::string problemFilepath = argc > 1 ? argv[0] : PROBLEM_FILE;

	IHTCProblemIO problemReader;

	try
	{
		ProblemData problemData = problemReader.parseFromJSON(problemFilepath);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

}
