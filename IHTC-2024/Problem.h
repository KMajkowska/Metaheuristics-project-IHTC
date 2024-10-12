#pragma once
#include "ISelector.h"

class Problem
{
public:
	void select(ISelector selector);
	void eval();
};