#pragma once
#include <type_traits>

#include "IHTCSolver.h"
#include "Params.h"

template <typename T>
concept DerivedFromIHTCSolver = std::is_base_of_v<IHTCSolver, T>;

template <DerivedFromIHTCSolver T>
class IHTCSolverBuilder
{
public:
	IHTCSolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);
	virtual ~IHTCSolverBuilder() = default;

	T build() const;

protected:
	virtual std::optional<T> prepareForBuild() const = 0;

	const Params& _params;
	const ProblemData& _problemData;
	std::mt19937& _randGenerator;
	ICIndividualConsumer& _consumer;
};

template<DerivedFromIHTCSolver T>
inline IHTCSolverBuilder<T>::IHTCSolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
	_params(params),
	_problemData(problemData),
	_randGenerator(randGenerator),
	_consumer(consumer)
{}

template<DerivedFromIHTCSolver T>
inline T IHTCSolverBuilder<T>::build() const
{
	auto builtSolverOpt { prepareForBuild() };

	if (!builtSolverOpt)
	{
		throw std::invalid_argument("Invalid build params, cannot create solver");
	}
	
	return std::move(builtSolverOpt.value());
}
