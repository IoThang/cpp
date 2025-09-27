
#ifndef CLAP_TRAP_H_
#define CLAP_TRAP_H_

#include <iostream>
#include <string>

// Type alias for clarity; documents intent and compatibility.
using points = unsigned int;  // Alias for int; guaranteed to remain int-compatible.

enum class sClapTrapState{
    Normal = 0,
    OutOfHealth = 1,
    OutOfEnergy = 2,
    Blocked = 3
};

class ClapTrap{
public:
    // Rule of five
    ClapTrap();

    // Explicit constructor with name arg
    explicit ClapTrap(std::string);

    ClapTrap(ClapTrap const&);
    ClapTrap& operator = (ClapTrap const&);

    ClapTrap(ClapTrap &&) noexcept = default;
    ClapTrap& operator = (ClapTrap&&) noexcept = default; 

    ~ClapTrap() noexcept;

    void attack(ClapTrap& name);
    void TakeDamage(points amount);
    void BeRepaired(points amount);

    std::string GetName(void) const;
    void SetName(std::string const&);

    points GetHitPoints(void) const;
    void SetHitPoints(points amount);

    void SetAttackDamage(points);
    points GetAttackDamage(void) const;

    void SetEnergyPoints(points);
    points GetEnergyPoints(void) const;

    sClapTrapState getState(void) const;
    void SetState(sClapTrapState const&);

private:
    std::string name_;
    points hit_points_;
    points energy_points_;
    points attack_damage_;

    // Additional attribute to track the state
    sClapTrapState state_ = sClapTrapState::Normal;
};

#endif  // CLAP_TRAP_H_
