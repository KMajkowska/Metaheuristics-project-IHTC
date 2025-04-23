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

/**
 * @brief Paths to files with problems
 */

/**
 * @brief Path to the default problem file for testing.
 */
const std::string DEFAULT_PROBLEM_FILE{ "../datasets/ihtc2024_test_dataset/test01.json" };

/**
 * @brief Path to the easy-level problem file.
 */
const std::string EASY_PROBLEM_FILE{ "../datasets/ihtc2024_test_dataset/test01.json" };

/**
 * @brief Path to the medium - level problem file.
 */
const std::string MEDIUM_PROBLEM_FILE{ "../datasets/ihtc2024_test_dataset/test05.json" };

/**
 * @brief Path to the hard - level problem file.
 */
const std::string HARD_PROBLEM_FILE{ "../datasets/ihtc2024_test_dataset/test08.json" };

/**
 * @brief Path to the default parameters configuration file.
 */
const std::string DEFAULT_PARAMS_FILE{ "./params.json" };

