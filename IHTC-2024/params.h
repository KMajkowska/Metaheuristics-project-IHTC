#pragma once

#include <string>

static const std::string DEFAULT_PROBLEM_FILE = "../datasets/competition_instances/i01.json";

static constexpr double HARD_RESTRICTION_WEIGHT = 100;

static constexpr double MUTATION_PROBABILITY = 1;
static constexpr int NEIGHBOUR_NUMBER = 15;
static constexpr int MAX_ITERATION = 250;

static constexpr double STARTING_TEMPERATURE = 600;
static constexpr double STOP_TEMPERATURE = 0.01;

static constexpr int SOLVER_REPETITION_AMOUNT = 1;
