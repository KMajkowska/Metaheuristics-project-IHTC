#include "strings.h"

std::string tolowercase(const std::string& str)
{
    std::string copy = str;

    std::transform(copy.begin(), copy.end(), copy.begin(),
        [](unsigned char c)
        {
            return std::tolower(c);
        }
    );

    return copy;
}
