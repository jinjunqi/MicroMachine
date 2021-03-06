#pragma once

#include "Common.h"
#include "BuildOrder.h"
#include "Condition.h"

typedef std::pair<UnitType, size_t> UnitPair;
typedef std::vector<UnitPair>       UnitPairVector;

class CCBot;

struct Strategy
{
    std::string m_name;
    CCRace      m_race;
    int         m_wins;
    int         m_losses;
    BuildOrder  m_buildOrder;
    Condition   m_scoutCondition;
    Condition   m_attackCondition;

    Strategy();
    Strategy(const std::string & name, const CCRace & race, const BuildOrder & buildOrder, const Condition & scoutCondition, const Condition & attackCondition);
};

struct StrategyPostBuildOrder {
	const static int NO_STRATEGY = -1;
	const static int TERRAN_REAPER = 0;
	const static int TERRAN_ANTI_SPEEDLING = 1;//Also plans towards mutalisk
	const static int TERRAN_MARINE_MARAUDER = 2;
	const static int WORKER_RUSH_DEFENSE = 3;
	const static int TERRAN_ANTI_ADEPT = 4;
	const static int TERRAN_ANTI_AIR = 5;
};

class StrategyManager
{
    CCBot & m_bot;

    CCRace                          m_selfRace;
    CCRace                          m_enemyRace;
    std::map<std::string, Strategy> m_strategies;
    int                             m_totalGamesPlayed;
    const BuildOrder                m_emptyBuildOrder;
	bool m_workerRushed = false;
	bool m_shouldProduceAntiAir = false;
	bool m_enemyHasInvisible = false;
	bool m_enemyHasMetabolicBoost = false;
	bool m_enemyHasFlyingCombatUnit = false;
	bool m_focusBuildings = false;
	bool m_bansheeCloakCompleted = false;

    bool  shouldExpandNow() const;
    const UnitPairVector getProtossBuildOrderGoal() const;
    const UnitPairVector getTerranBuildOrderGoal() const;
    const UnitPairVector getZergBuildOrderGoal() const;

public:

    StrategyManager(CCBot & bot);

    const Strategy & getCurrentStrategy() const;
	const int & getCurrentStrategyPostBuildOrder() const;
    bool scoutConditionIsMet() const;
    bool attackConditionIsMet() const;
    void onStart();
    void onFrame();
    void onEnd(const bool isWinner);
    void addStrategy(const std::string & name, const Strategy & strategy);
    const UnitPairVector getBuildOrderGoal() const;
    const BuildOrder & getOpeningBookBuildOrder() const;
    void readStrategyFile(const std::string & str);
	bool isWorkerRushed() const { return m_workerRushed; }
	void setIsWorkerRushed(bool workerRushed) { m_workerRushed = workerRushed; }
	bool shouldProduceAntiAir() const { return m_shouldProduceAntiAir; }
	void setShouldProduceAntiAir(bool shouldProduceAntiAir) { m_shouldProduceAntiAir = shouldProduceAntiAir; }
	bool enemyHasInvisible() const { return m_enemyHasInvisible; }
	void setEnemyHasInvisible(bool enemyHasInvisible) { m_enemyHasInvisible = enemyHasInvisible; }
	bool enemyHasMetabolicBoost() const { return m_enemyHasMetabolicBoost; }
	void setEnemyHasMetabolicBoost(bool enemyHasMetabolicBoost) { m_enemyHasMetabolicBoost = enemyHasMetabolicBoost; }
	bool shouldFocusBuildings() const { return m_focusBuildings; }
	void setFocusBuildings(bool focusBuildings) { m_focusBuildings = focusBuildings; }
	bool isBansheeCloakCompleted() const { return m_bansheeCloakCompleted; }
	void setBansheeCloakCompleted(bool bansheeCloakCompleted) { m_bansheeCloakCompleted = bansheeCloakCompleted; }
};
