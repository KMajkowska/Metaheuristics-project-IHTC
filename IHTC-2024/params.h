#pragma once

#include <string>

static const std::string DEFAULT_PROBLEM_FILE = "../datasets/competition_instances/i01.json";

static constexpr double HARD_RESTRICTION_WEIGHT = 100;

static constexpr double MUTATION_PROBABILITY = 1;
static constexpr int NEIGHBOUR_NUMBER = 18;
static constexpr int MAX_ITERATION = 250;

static constexpr double STARTING_TEMPERATURE = 10000;
static constexpr double STOP_TEMPERATURE = 1;
static constexpr double SIMPLEX_COOLING_MULTIPLIER = 0.999;

static constexpr int SOLVER_REPETITION_AMOUNT = 1;
