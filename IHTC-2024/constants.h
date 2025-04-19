#pragma once

#include <string>
#include <random>

#include "other.h"

/**
 * @brief IP address used for games (localhost)
 */
const std::string IP{ "127.0.0.1" };

/**
 * @brief Port used for establishing connection (sessions are sent and received on here)
 */
const int SESSION_PEER_TO_PEER_PORT{ 12345 };

const std::string DEFAULT_PROBLEM_FILE{ "../datasets/ihtc2024_test_dataset/test01.json" };
const std::string DEFAULT_PARAMS_FILE{ "./params.json" };