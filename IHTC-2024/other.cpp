#include "other.h"


void writeToFile(const std::string& filename, const std::string& data)
{
    std::ofstream file(filename);

    if (!file) {
        return;
    }

    file << data;

    file.close();
}

std::mt19937& createRandomGenerator()
{
    std::random_device r;
    std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
    std::mt19937 mt(seed);

    return mt;
}
