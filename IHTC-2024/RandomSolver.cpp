#include "RandomSolver.h"

RandomSolver::RandomSolver(const ProblemData& problemData, std::mt19937& randGenerator, ICIndividualConsumer& consumer) :
    IHTCSolver(problemData, randGenerator, consumer)
{}

CIndividual RandomSolver::solve(const IProblem& problem, const CIndividual& startingIndividual) const
{
    const auto& ots = _problemData.getEmptyOperatingTheaters();
    const auto& problemPatients = _problemData.patients();
    const auto& problemRooms = _problemData.rooms();
    const auto& problemNurses = _problemData.nurses();

    std::uniform_int_distribution<int> roomDistrib(0, static_cast<int>(problemRooms.size()) - 1);
    std::uniform_int_distribution<int> _0to100Distrib(0, 100);

    std::vector<Patient> solutionPatients;
    solutionPatients.reserve(problemPatients.size());

    for (const auto& patient : problemPatients)
    {
        std::uniform_int_distribution<int> distrib(
            patient.getSurgeryReleaseDay(),
            patient.getSurgeryDueDay() == INT_MAX ? _problemData.days() : patient.getSurgeryDueDay()
        );

        const int admissionDay = distrib(_randGenerator);

        if (admissionDay >= _problemData.days() || ots.at(admissionDay).size() <= 0)
        { 
            solutionPatients.push_back(
                Patient(
                    patient.id(),
                    admissionDay,
                    problemRooms.at(roomDistrib(_randGenerator)).id(),
                    ""
                )
            );
        }
        else 
        {
            std::uniform_int_distribution<int> otDistrib(0, static_cast<int>(ots.at(admissionDay).size()) - 1);
            auto it = ots.at(admissionDay).begin();
            std::advance(it, otDistrib(_randGenerator));

            solutionPatients.push_back(
                Patient(
                    patient.id(),
                    admissionDay,
                    problemRooms.at(roomDistrib(_randGenerator)).id(),
                    it -> first
                )
            );
        }
    }

    std::unordered_map<std::string, std::vector<Assignment>> solutionAssignments;
    solutionAssignments.reserve(problemNurses.size());

    for (const auto& nurse : problemNurses)
    {
        std::vector<Assignment> assignments;

        for (const auto& shift : nurse.workingShifts())
        {
            std::set<std::string> assignedRooms;

            while (_0to100Distrib(_randGenerator) >= 50)
            {
                int i = roomDistrib(_randGenerator);
                assignedRooms.insert(problemRooms.at(i).id());
            }

            assignments.push_back(
                Assignment(
                    shift.day(),
                    shift.shift(),
                    std::vector<std::string>(assignedRooms.begin(), assignedRooms.end())
                )
            );
        }
       solutionAssignments[nurse.id()] = assignments;
    }

    CIndividual res(solutionPatients, solutionAssignments);

    res.setFitness(problem.eval(res));

    return res;
}
