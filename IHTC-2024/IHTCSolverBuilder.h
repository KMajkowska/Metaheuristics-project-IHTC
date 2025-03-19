#pragma once
#include <type_traits>

#include "IHTCSolver.h"
#include "Params.h"
#include "ICIndividualConsumer.h"


/**
 * @brief Accepts only classed that derive from IHTCSolver
 */
template <typename T>
concept DerivedFromIHTCSolver = std::is_base_of_v<IHTCSolver, T>;

/**
 * @brief Used for building complex solvers
 * @tparam T class type that derives from IHTCSolver
 */
template <DerivedFromIHTCSolver T>
class IHTCSolverBuilder
{
public:
	IHTCSolverBuilder(const Params& params, const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer);
	virtual ~IHTCSolverBuilder() = default;

	/**
	 * @brief Build the solver with data gathered in the builder properties
	 * @return instance of a solver 
	 */
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
