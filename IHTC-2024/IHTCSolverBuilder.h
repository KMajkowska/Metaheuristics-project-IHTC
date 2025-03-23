#pragma once
#include <type_traits>

#include "IHTCSolver.h"
#include "Params.h"
#include "ICIndividualConsumer.h"

/**
 * @brief Used for building complex solvers
 */
class IHTCSolverBuilder
{
public:
	IHTCSolverBuilder(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);
	virtual ~IHTCSolverBuilder() = default;

	/**
	 * @brief Build the solver with data gathered in the builder properties
	 * @return instance of a solver 
	 */
	std::shared_ptr<IHTCSolver> build() const;

protected:
	virtual std::optional<std::shared_ptr<IHTCSolver>> prepareForBuild() const = 0;

	const ProblemData& _problemData;
	std::mt19937& _randGenerator;
	ICIndividualConsumer& _consumer;
};
