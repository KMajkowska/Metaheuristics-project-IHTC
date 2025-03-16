#pragma once

#include "IMutator.h"

class IHTCMutatorDay : public IMutator
{
public:
	IHTCMutatorDay(std::mt19937& randGenerator, const ProblemData& problemData, double newDayShuffleProbability);

	bool mutate(CIndividual& individual) const override;

	std::string mutatorName() const override;

private:
	int randomDay(int min, int max) const;

	bool checkCorrectAdmissionDay(int admissionDay, const std::string& surgeonId, const std::string& otId) const;
};