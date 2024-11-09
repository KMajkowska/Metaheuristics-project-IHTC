#pragma once

#include <functional>
#include <queue>

#include "IMutator.h"

std::function<IMutator(int iteration, int numberOfNeigbours)> mutatorOrchestratorQueue(const std::vector<IMutator>& mutators);

std::function<IMutator(int iteration, int numberOfNeigbours)> mutatorOrchestratorSimplex(const std::vector<IMutator>& mutators);