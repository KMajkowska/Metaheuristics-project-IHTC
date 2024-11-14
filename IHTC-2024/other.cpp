#include "other.h"


void writeToFile(const std::string& filename, const std::string& data)
{
    std::ofstream file(filename);

    if (!file) 
    {
        return;
    }

    file << data;

    file.close();
}

std::mt19937 createRandomGenerator()
{
    std::random_device r;
    std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
    std::mt19937 mt(seed);

    return mt;
}

std::pair<int, int> findTwoDifferentNumbersBetween(int lowLimit, int highLimit, std::mt19937& generator)
{
    std::uniform_int_distribution<int> distrib(lowLimit, highLimit);

    int firstIndex = distrib(generator);
    int secondIndex;
    do
    {
        secondIndex = distrib(generator);
    } while (secondIndex == firstIndex);

    if (secondIndex < firstIndex)
    {
        int temp = firstIndex;
        firstIndex = secondIndex;
        secondIndex = temp;
    }

    return std::make_pair(firstIndex, secondIndex);
}

std::string getFileNameWithoutExtension(const std::string& filePath)
{
    std::filesystem::path path(filePath);
    return path.stem().string();
}

std::string getLoggerFileName(const std::string filePath)
{
    
    return LOG_FILE + getFileNameWithoutExtension(filePath) + ".csv";
}


