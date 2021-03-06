#pragma once
#include <vector>

#include <chrono>
#include "UCTCDMove.h"
#include "UCTCDState.h"
#include "UCTCDNode.h"
#include "UCTCDUnit.h"

class UCTConsideringDurations {
public:
    float k;
    size_t max_traversals;
    size_t time_limit;
    std::chrono::high_resolution_clock::time_point start;

    bool attack_closest;
    bool attack_weakest;
    bool attack_priority;

    std::map<const sc2::Unit *, UCTCDAction> command_for_unit;

    UCTConsideringDurations(float pk, size_t pmax_traversals, size_t time, std::map<const sc2::Unit *, UCTCDAction> pcommand_for_unit);
    UCTCDMove doSearch(std::vector<UCTCDUnit> max, std::vector<UCTCDUnit> min, bool pclosest, bool pweakest, bool ppriority, bool pconsiderDistance, bool punitOwnAgent);

    // stats for nerdz
    size_t nodes_explored;
    int win_value;
    size_t traversals;
    std::chrono::milliseconds time_spent;

private:
    UCTCDMove UCTCD(UCTCDState state);
    int traverse(UCTCDNode & n, UCTCDState & s);
    UCTCDNode & selectNode(UCTCDNode & n);
    void UpdateState(UCTCDNode & n, UCTCDState & s, bool leaf);
    void generateChildren(UCTCDState & s, UCTCDNode & n);
};