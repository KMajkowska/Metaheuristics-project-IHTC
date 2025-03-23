#include "IHTCSolverBuilder.h"

IHTCSolverBuilder::IHTCSolverBuilder(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
	_problemData(problemData),
	_randGenerator(randGenerator),
	_consumer(consumer)
{}

std::shared_ptr<IHTCSolver> IHTCSolverBuilder::build() const
{
	auto builtSolverOpt{ prepareForBuild() };

	if (!builtSolverOpt)
	{
		throw std::invalid_argument("Invalid build params, cannot create solver");
	}

	return builtSolverOpt.value();
}