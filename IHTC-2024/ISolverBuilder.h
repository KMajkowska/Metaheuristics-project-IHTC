#pragma once
#include <type_traits>
#include "IHTCSolver.h"

template <typename T>
concept DerivedFromIHTCSolver = std::is_base_of_v<IHTCSolver, T>;

template <DerivedFromIHTCSolver T>
class IHTCSolverBuilder
{
public:
	ISolverBuilder() = default;
	virtual ~ISoverBuilder() = default;

	virtual IHTCSolver build() const = 0;

protected:
	bool isReadyToBuild = false;

};