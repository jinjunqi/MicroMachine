#include "Unit.h"
#include "CCBot.h"

Unit::Unit()
    : m_bot(nullptr)
    , m_unit(nullptr)
    , m_unitID(0)
{

}

#ifdef SC2API
Unit::Unit(const sc2::Unit * unit, CCBot & bot)
    : m_bot(&bot)
    , m_unit(unit)
    , m_unitID(unit->tag)
    , m_unitType(unit->unit_type, bot)
{
    
}

const sc2::Unit * Unit::getUnitPtr() const
{
    return m_unit;
}

const sc2::UnitTypeID & Unit::getAPIUnitType() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
    return m_unit->unit_type;
}

#else
Unit::Unit(const BWAPI::Unit unit, CCBot & bot)
    : m_bot(&bot)
    , m_unit(unit)
    , m_unitID(unit->getID())
    , m_unitType(unit->getType(), bot)
{
    
}

const BWAPI::Unit Unit::getUnitPtr() const
{
    return m_unit;
}

const BWAPI::UnitType & Unit::getAPIUnitType() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
    return m_unit->getType();
}

#endif
bool Unit::operator < (const Unit & rhs) const
{
    return m_unit < rhs.m_unit;
}

bool Unit::operator == (const Unit & rhs) const
{
    return m_unit == rhs.m_unit;
}

const UnitType & Unit::getType() const
{
    return m_unitType;
}


CCPosition Unit::getPosition() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->pos;
#else
    return m_unit->getPosition();
#endif
}

CCTilePosition Unit::getTilePosition() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return Util::GetTilePosition(m_unit->pos);
#else
    return m_unit->getTilePosition();
#endif
}

CCHealth Unit::getHitPoints() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->health;
#else
    return m_unit->getHitPoints();
#endif
}

CCHealth Unit::getShields() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->shield;
#else
    return m_unit->getShields();
#endif
}

CCHealth Unit::getEnergy() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->energy;
#else
    return m_unit->getEnergy();
#endif
}

float Unit::getBuildPercentage() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->build_progress;
#else
    if (getType().isBuilding()) { return m_unit->getRemainingBuildTime() / (float)getType().getAPIUnitType().buildTime(); }
    else { return m_unit->getRemainingTrainTime() / (float)getType().getAPIUnitType().buildTime(); }
#endif
}

CCPlayer Unit::getPlayer() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    if (m_unit->alliance == sc2::Unit::Alliance::Self) { return 0; }
    else if (m_unit->alliance == sc2::Unit::Alliance::Enemy) { return 1; }
    else { return 2; }
#else
    if (m_unit->getPlayer() == BWAPI::Broodwar->self()) { return 0; }
    else if (m_unit->getPlayer() == BWAPI::Broodwar->enemy()) { return 1; }
    else { return 2; }
#endif
}

sc2::Tag Unit::getTag() const
{
	return m_unit->tag;
}

CCUnitID Unit::getID() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    CCUnitID id = m_unit->tag;
#else
    CCUnitID id = m_unit->getID();
#endif

    BOT_ASSERT(id == m_unitID, "Unit ID changed somehow");
    return id;
}

int Unit::getIDAsInt() const
{
	BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
	int id = m_unit->tag;
#else
	int id = m_unit->getID();
#endif

	return id;
}

bool Unit::canAttackAir() const
{
	return Util::CanUnitAttackAir(m_unit, *m_bot);
}

bool Unit::canAttackGround() const
{
	return Util::CanUnitAttackGround(m_unit, *m_bot);
}

bool Unit::isCompleted() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->build_progress >= 1.0f;
#else
    return m_unit->isCompleted();
#endif
}

bool Unit::isTraining() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->orders.size() > 0;
#else
    return m_unit->isTraining();
#endif
}


bool Unit::isAddonTraining() const
{
	BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
	return m_unit->orders.size() > 1;
	
#else
	return false;
#endif
}

bool Unit::isBeingConstructed() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return !isCompleted() && m_unit->build_progress > 0.0f;
#else
    return m_unit->isBeingConstructed();
#endif
}

sc2::Tag Unit::getAddonTag() const
{
	BOT_ASSERT(isValid(), "Unit is not valid");
	return m_unit->add_on_tag;
}

int Unit::getWeaponCooldown() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return (int)m_unit->weapon_cooldown;
#else
    return std::max(m_unit->getGroundWeaponCooldown(), m_unit->getAirWeaponCooldown());
#endif
}

bool Unit::isCloaked() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->cloak;
#else
    return m_unit->isCloaked();
#endif
}

bool Unit::isFlying() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->is_flying;
#else
    return m_unit->isFlying();
#endif
}

bool Unit::isAlive() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->is_alive;
#else
    return m_unit->getHitPoints() > 0;
#endif
}

bool Unit::isPowered() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->is_powered;
#else
    return m_unit->isPowered();
#endif
}

bool Unit::isIdle() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->orders.empty();
#else
    return m_unit->isIdle() && !m_unit->isMoving() && !m_unit->isGatheringGas() && !m_unit->isGatheringMinerals();
#endif
}

bool Unit::isBurrowed() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    return m_unit->is_burrowed;
#else
    return m_unit->isBurrowed();
#endif
}

bool Unit::isValid() const
{
    return m_unit != nullptr;
}

bool Unit::isVisible() const
{
	return m_unit->display_type == sc2::Unit::DisplayType::Visible;
}

void Unit::stop() const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::STOP);
#else
    m_unit->stop();
#endif
}

void Unit::attackUnit(const Unit & target) const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
    BOT_ASSERT(target.isValid(), "Target is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::ATTACK, target.getUnitPtr());
#else
    m_unit->attack(target.getUnitPtr());
#endif
}

void Unit::attackMove(const CCPosition & targetPosition) const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::ATTACK, targetPosition);
#else
    m_unit->attack(targetPosition);
#endif
}

void Unit::move(const CCPosition & targetPosition) const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::MOVE, targetPosition);
#else
    m_unit->move(targetPosition);
#endif
}

void Unit::move(const CCTilePosition & targetPosition) const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::MOVE, CCPosition((float)targetPosition.x, (float)targetPosition.y));
#else
    m_unit->move(CCPosition(targetPosition));
#endif
}

void Unit::rightClick(const Unit & target) const
{
	BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
	m_bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::SMART, target.getUnitPtr());
#else
	m_unit->rightClick(target.getUnitPtr());
#endif
}

void Unit::repair(const Unit & target) const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, sc2::ABILITY_ID::EFFECT_REPAIR, target.getUnitPtr());
#else
    rightClick(target);
#endif
}

void Unit::build(const UnitType & buildingType, CCTilePosition pos) const
{
    //BOT_ASSERT(m_bot->Map().isConnected(getTilePosition(), pos), ("Error: Build Position is not connected to worker (build pos:[" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + "], unit pos:[" + std::to_string(getTilePosition().x) + ", " + std::to_string(getTilePosition().y) + "], building type:" + buildingType.getName() + ")").c_str());
	
	BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, m_bot->Data(buildingType).buildAbility, Util::GetPosition(pos));
#else
    m_unit->build(buildingType.getAPIUnitType(), pos);
#endif
}

void Unit::buildTarget(const UnitType & buildingType, const Unit & target) const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, m_bot->Data(buildingType).buildAbility, target.getUnitPtr());
#else
    BOT_ASSERT(false, "buildTarget shouldn't be called for BWAPI bots");
#endif
}

void Unit::train(const UnitType & type) const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, m_bot->Data(type).buildAbility);
#else
    m_unit->train(type.getAPIUnitType());
#endif
}

void Unit::morph(const UnitType & type) const
{
    BOT_ASSERT(isValid(), "Unit is not valid");
#ifdef SC2API
    m_bot->Actions()->UnitCommand(m_unit, m_bot->Data(type).buildAbility);
#else
    m_unit->morph(type.getAPIUnitType());
#endif
}

sc2::AvailableAbilities Unit::getAbilities() const
{
	return m_bot->Query()->GetAbilitiesForUnit(m_unit);
}

/*
 * This method queries the game to check if the ability is available.
 * Since queries are slow, this method should not be used on every frame.
 */
bool Unit::useAbility(const sc2::ABILITY_ID abilityId) const
{
	BOT_ASSERT(isValid(), "Unit is not valid");

	if (abilityId == sc2::ABILITY_ID::EFFECT_STIM)
	{
		sc2::BUFF_ID stimpack = m_unitType.getAPIUnitType() == sc2::UNIT_TYPEID::TERRAN_MARINE ? sc2::BUFF_ID::STIMPACK : sc2::BUFF_ID::STIMPACKMARAUDER;
		if(std::find(m_unit->buffs.begin(), m_unit->buffs.end(), stimpack) != m_unit->buffs.end())
		{
			// Stimpack already in use
			return false;
		}
	}

	auto query = m_bot->Query();
	auto abilities = m_bot->Observation()->GetAbilityData();
	sc2::AvailableAbilities available_abilities = query->GetAbilitiesForUnit(m_unit);
	for (const sc2::AvailableAbility & available_ability : available_abilities.abilities)
	{
		if (available_ability.ability_id >= abilities.size()) { continue; }
		const sc2::AbilityData & ability = abilities[available_ability.ability_id];
		if (ability.ability_id == abilityId) {
			m_bot->Actions()->UnitCommand(m_unit, ability.ability_id);
			return true;
		}
	}

	return false;
}

bool Unit::isConstructing(const UnitType & type) const
{
#ifdef SC2API
	BOT_ASSERT(isValid(), "Cannot check if unit is constructing because unit ptr is null");

    sc2::AbilityID buildAbility = m_bot->Data(type).buildAbility;
    return (getUnitPtr()->orders.size() > 0) && (getUnitPtr()->orders[0].ability_id == buildAbility);
#else
    return m_unit->isConstructing();
#endif
}

bool Unit::isConstructingAnything() const
{
#ifdef SC2API
	BOT_ASSERT(isValid(), "Cannot check if unit is constructing because unit ptr is null");

	return (getUnitPtr()->orders.size() > 0);
#else
	return m_unit->isConstructing();
#endif
}