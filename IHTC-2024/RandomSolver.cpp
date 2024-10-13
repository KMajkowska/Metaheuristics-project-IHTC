#include "RandomSolver.h"

RandomSolver::RandomSolver(std::mt19937& randGenerator) : 
    randGenerator(randGenerator)
{
}

CIndividual RandomSolver::solve(const ProblemData& problemData, const IProblem& problem) const
{
    const auto& problemPatients = problemData.getPatients();
    const auto& problemRooms = problemData.getRooms();
    const auto& problemNurses = problemData.getNurses();
    const auto& problemOperatingTheaters = problemData.getOperatingTheaters();

    std::uniform_int_distribution<int> roomDistrib(0, static_cast<int>(problemRooms.size()) - 1);
    std::uniform_int_distribution<int> otDistrib(0, static_cast<int>(problemOperatingTheaters.size()) - 1);
    std::uniform_int_distribution<int> _0to100Distrib(0, 100);

    std::vector<Patient> solutionPatients;
    solutionPatients.reserve(problemPatients.size());

    for (const auto& patient : problemPatients)
    {
        std::uniform_int_distribution<int> distrib(
            patient.getSurgeryReleaseDay(),
            patient.getSurgeryDueDay() == INT_MAX ? problemData.getDays() : patient.getSurgeryDueDay()
        );

        solutionPatients.push_back(
            Patient(
                distrib(randGenerator), 
                problemRooms[roomDistrib(randGenerator)].getId(), 
                problemOperatingTheaters[otDistrib(randGenerator)].getId()
            )
        );
    }

    std::vector<std::vector<Assignment>> solutionAssignments;
    solutionAssignments.reserve(problemNurses.size());

    for (const auto& nurse : problemNurses)
    {
        std::vector<Assignment> assignments;

        for (const auto& shift : nurse.getWorkingShifts())
        {
            std::vector<std::string> assignedRooms;

            while (_0to100Distrib(randGenerator) >= 50)
            {
                int i = roomDistrib(randGenerator);
                assignedRooms.push_back(problemRooms[i].getId());
            }

            assignments.push_back(
                Assignment(
                    shift.getDay(),
                    shift.getShift(),
                    assignedRooms
                )
            );
        }

        solutionAssignments.push_back(assignments);
    }

    return CIndividual(solutionPatients, solutionAssignments);
}
