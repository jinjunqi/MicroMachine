#pragma once

#include "Common.h"
#include "MicroManager.h"
#include "UCTCDAction.h"

class CCBot;

class RangedManager : public MicroManager
{
public:

    RangedManager(CCBot & bot);
	void setHarassMode(bool harass) { m_harassMode = harass; }
    void setTargets(const std::vector<Unit> & targets);
    void executeMicro();
	bool isTargetRanged(const sc2::Unit * target);

private:
	void RunBehaviorTree(sc2::Units &rangedUnits, sc2::Units &rangedUnitTargets);

	void setNextCommandFrameAfterAttack(const sc2::Unit* unit);
	void HarassLogic(sc2::Units &rangedUnits, sc2::Units &rangedUnitTargets);
	bool ShouldSkipFrame(const sc2::Unit * rangedUnit) const;
	void ExecuteBansheeCloakLogic(const sc2::Unit * rangedUnit, sc2::Units & threats) const;
	bool ExecuteVikingMorphLogic(const sc2::Unit * viking, float squaredDistanceToGoal, const sc2::Unit* target);
	bool MoveToGoal(const sc2::Unit * rangedUnit, sc2::Units & threats, const sc2::Unit * target, CCPosition & goal, float squaredDistanceToGoal);
	bool ShouldAttackTarget(const sc2::Unit * rangedUnit, const sc2::Unit * target, sc2::Units & threats) const;
	CCPosition GetDirectionVectorTowardsGoal(const sc2::Unit * rangedUnit, const sc2::Unit * target, CCPosition goal, bool targetInAttackRange) const;
	bool ExecuteThreatFightingLogic(const sc2::Unit * rangedUnit, sc2::Units & rangedUnits, sc2::Units & threats);
	bool CanUseKD8Charge(const sc2::Unit * rangedUnit) const;
	bool ExecuteKD8ChargeLogic(const sc2::Unit * rangedUnit, const sc2::Unit * threat, const CCPosition& fleeVec);
	CCPosition GetFleeVectorFromThreat(const sc2::Unit * rangedUnit, const sc2::Unit * threat, CCPosition fleeVec, float distance, float threatRange) const;
	void AdjustSummedFleeVec(CCPosition & summedFleeVec) const;
	CCPosition GetRepulsionVectorFromFriendlyReapers(const sc2::Unit * reaper, sc2::Units & rangedUnits) const;
	CCPosition GetAttractionVectorToFriendlyHellions(const sc2::Unit * reaper, sc2::Units & rangedUnits) const;
	bool MoveUnitWithDirectionVector(const sc2::Unit * rangedUnit, CCPosition & directionVector, CCPosition & outPathableTile) const;

	CCTilePosition FindSafestPathWithInfluenceMap(const sc2::Unit * rangedUnit, const std::vector<const sc2::Unit *> & threats);
	float getAttackPriority(const sc2::Unit * rangedUnit, const sc2::Unit * target);
	const sc2::Unit * getTarget(const sc2::Unit * rangedUnit, const std::vector<const sc2::Unit *> & targets);
	const std::vector<const sc2::Unit *> getThreats(const sc2::Unit * rangedUnit, const std::vector<const sc2::Unit *> & targets);
	void UCTCD(std::vector<const sc2::Unit *> rangedUnits, std::vector<const sc2::Unit *> rangedUnitTargets);
	void AlphaBetaPruning(std::vector<const sc2::Unit *> rangedUnits, std::vector<const sc2::Unit *> rangedUnitTargets);
    std::vector<const sc2::Unit *> lastUnitCommand;
    std::map<const sc2::Unit *, UCTCDAction> command_for_unit;
	std::map<const sc2::Unit *, uint32_t> nextCommandFrameForUnit;
	std::map<const sc2::Unit *, uint32_t> nextAvailableKD8ChargeFrameForReaper;
    bool isCommandDone = false;
	bool m_harassMode = false;
};
