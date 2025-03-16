#pragma once

#include <random>

#include "CIndividual.h"
#include "ProblemData.h"

/**
 * @brief Modification for SA algorithm. It has a problem with genderMix restriction so this modification change the patients to different room. 
 * Used everytime when genderMix is broken in any room and is used after given number of iterations.
*/
class GenderGrouper
{
public:
	GenderGrouper(int perIterAmountFix, const ProblemData& problemData, std::mt19937& randGenerator);

	/**
	 * @brief Using greedy algoritm, we assign the patiens, which broke our genderMix restriction, to different room. We choose the patients by choosing the patient which 
	 * are in the minority. E.g. if we have 5 men and 3 women, we assign women to different rooms.
	 * @param individual 
	*/
	void greedyGroupGenders(CIndividual& individual) const;

	int iter() const;


private:
	int _perIterAmountFix { 0 };

	const ProblemData& _problemData;
	std::mt19937& _randGenerator;
};