#pragma once
#include<vector>

class CIndividual;

class ISelector
{
public:
	virtual std::vector<CIndividual> select(std::vector<CIndividual> population) const = 0;
};