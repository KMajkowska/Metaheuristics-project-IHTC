#pragma once

#include "IMutator.h"

/**
 * @brief Mutator which randomly (normal distribution) assign day for our patient.
 * For mandatory patients day are choosen in given time period. For optional is choosen from their release day since not defined day
 * shuffling is happening with given probavility (for SA ut is 1)
*/
class IHTCMutatorDay : public IMutator
{
public:
	IHTCMutatorDay(std::mt19937& randGenerator, const ProblemData& problemData, double newDayShuffleProbability);

	bool mutate(CIndividual& individual) const;

	std::string getMutatorName() const;

private:
	int randomDay(int min, int max) const;

	bool checkCorrectAdmissionDay(int admissionDay, const std::string& surgeonId, const std::string& otId) const;

	double dayShuffleProbability;
};