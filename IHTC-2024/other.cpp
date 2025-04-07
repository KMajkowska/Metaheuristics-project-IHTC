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

double calcAverage(const std::vector<double>& data)
{
    double sum = 0.0;

    for (double wartosc : data) 
    {
        sum += wartosc;
    }

    return sum / data.size();
}

double calcStdDev(const std::vector<double>& data)
{
    double avg = calcAverage(data);

    double res = 0.0;

    for (double val : data) 
    {
        res += std::pow(val - avg, 2);
    }

    return std::sqrt(res / data.size());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "{";

    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];

        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }

    os << "}\n";

    return os;
}