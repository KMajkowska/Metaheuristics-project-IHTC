#include "mutators.h"

std::function<IMutator(int iteration, int numberOfNeigbours)> mutatorOrchestratorQueue(const std::vector<IMutator>& mutators)
{
    std::queue<IMutator> mutQueue;
    
    for (const auto& mutator : mutators)
    {
        mutQueue.push(mutator);
    }

    std::function<IMutator(int, int)> mutatorFunc 
    {
        [mutQueue](int iteration, int numberOfNeigbours) mutable
        {
            auto mut = mutQueue.front();
            mutQueue.pop();

            mutQueue.push(mut);

            return mut;
        } 
    };

    return mutatorFunc;
}

std::function<const IMutator(int iteration, int numberOfNeigbours)> mutatorOrchestratorSimplex(const std::vector<IMutator>& mutators)
{
    return std::function<IMutator(int iteration, int numberOfNeigbours)>();
}
