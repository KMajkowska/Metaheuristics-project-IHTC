#include "RandomSolver.h"

RandomSolver::RandomSolver(const ProblemData& problemData, std::mt19937& randGenerator) :
    ISolver(problemData, randGenerator)
{}

CIndividual RandomSolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
    const auto& ots = problemData.getEmptyOperatingTheaters();
    const auto& problemPatients = problemData.getPatients();
    const auto& problemRooms = problemData.getRooms();
    const auto& problemNurses = problemData.getNurses();

    std::uniform_int_distribution<int> roomDistrib(0, static_cast<int>(problemRooms.size()) - 1);
    std::uniform_int_distribution<int> _0to100Distrib(0, 100);

    std::vector<Patient> solutionPatients;
    solutionPatients.reserve(problemPatients.size());

    for (const auto& patient : problemPatients)
    {
        std::uniform_int_distribution<int> distrib(
            patient.getSurgeryReleaseDay(),
            patient.getSurgeryDueDay() == INT_MAX ? problemData.getDays() : patient.getSurgeryDueDay()
        );

        const int admissionDay = distrib(randGenerator);

        if (admissionDay >= problemData.getDays())
        { 
            solutionPatients.push_back(
                Patient(
                    patient.getId(),
                    admissionDay,
                    problemRooms[roomDistrib(randGenerator)].getId(),
                    ""
                )
            );
        }
        else 
        {
            std::uniform_int_distribution<int> otDistrib(0, static_cast<int>(ots.at(admissionDay).size()) - 1);
            auto it = ots.at(admissionDay).begin();
            std::advance(it, otDistrib(randGenerator));

            solutionPatients.push_back(
                Patient(
                    patient.getId(),
                    admissionDay,
                    problemRooms[roomDistrib(randGenerator)].getId(),
                    it -> first
                )
            );
        }
    }

    std::vector<std::vector<Assignment>> solutionAssignments;
    solutionAssignments.reserve(problemNurses.size());

    for (const auto& nurse : problemNurses)
    {
        std::vector<Assignment> assignments;

        for (const auto& shift : nurse.getWorkingShifts())
        {
            std::set<std::string> assignedRooms;

            while (_0to100Distrib(randGenerator) >= 50)
            {
                int i = roomDistrib(randGenerator);
                assignedRooms.insert(problemRooms[i].getId());
            }

            assignments.push_back(
                Assignment(
                    shift.getDay(),
                    shift.getShift(),
                    std::vector<std::string>(assignedRooms.begin(), assignedRooms.end())
                )
            );
        }

        solutionAssignments.push_back(assignments);
    }

    return CIndividual(solutionPatients, solutionAssignments);
}
