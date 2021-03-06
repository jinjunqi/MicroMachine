#pragma once
#include "Common.h"
#include "Unit.h"

class CCBot;

namespace WorkerJobs
{
    enum { Minerals, Gas, Build, Combat, Idle, Repair, Move, Scout, None, Num };
}

class WorkerData
{
    CCBot & m_bot;

    std::set<Unit>          m_workers;
    std::set<Unit>          m_depots;
    std::map<int, int>      m_workerJobCount;
    std::map<Unit, int>     m_workerJobMap;
    std::map<Unit, int>     m_refineryWorkerCount;
    std::map<Unit, int>     m_depotWorkerCount;
    std::map<Unit, Unit>    m_workerRefineryMap;
    std::map<Unit, Unit>    m_workerDepotMap;
    std::map<Unit, std::set<Unit>>    m_workerRepairing;
    std::map<Unit, Unit>    m_workerRepairTarget;

    void clearPreviousJob(const Unit & unit);
    std::set<Unit> getWorkerRepairingThatTarget(const Unit & unit);
    void GetBestMineralInList(const std::vector<Unit> & unitsToTest, const Unit & worker, Unit & bestMineral, double & bestDist) const;

public:

    WorkerData(CCBot & bot);

    void    workerDestroyed(const Unit & unit);
    void    updateAllWorkerData();
    void    updateWorker(const Unit & unit);
    void    setWorkerJob(const Unit & unit, int job, Unit jobUnit = Unit(), bool mineralWorkerTargetJobUnit = false);
    void    drawDepotDebugInfo();
    size_t  getNumWorkers() const;
    int     getWorkerJobCount(int job) const;
    int     getNumAssignedWorkers(const Unit & unit);
    int     getWorkerJob(const Unit & unit) const;
	int		getCountWorkerAtDepot(Unit & depot) const;
    Unit    getMineralToMine(const Unit & unit) const;
    Unit    getWorkerDepot(const Unit & unit) const;
    const char * getJobCode(const Unit & unit);
    const std::set<Unit> & getWorkers() const;
    Unit getWorkerRepairTarget(const Unit & unit) const; 
    const std::set<Unit> getWorkerRepairingThatTargetC(const Unit & unit) const;
    void WorkerStoppedRepairing(const Unit & unit);
};