#pragma once

#include <ostream>
#include <vector>

template<typename T>
static std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);