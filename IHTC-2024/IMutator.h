#pragma once

class CIndividual;

class IMutator
{
public:
	virtual void mutate(CIndividual& individual) const = 0;
};