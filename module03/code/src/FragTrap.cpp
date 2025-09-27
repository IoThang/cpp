#include <FragTrap.h>

FragTrap::FragTrap(std::string name)
{
    SetName(name);
    SetHitPoints(100);
    SetEnergyPoints(100);
    SetAttackDamage(30);
    std::cout << this->GetName() << " FragTrap constructor called\n";
}

FragTrap::FragTrap(FragTrap const& obj)
{
    SetName(obj.GetName());
    SetHitPoints(obj.GetHitPoints());
    SetEnergyPoints(obj.GetEnergyPoints());
    SetAttackDamage(obj.GetAttackDamage());
    std::cout << this->GetName() << "FragTrap copy constructor called\n";
}

FragTrap& FragTrap::operator = (FragTrap const& obj)
{
    SetName(obj.GetName());
    SetHitPoints(obj.GetHitPoints());
    SetEnergyPoints(obj.GetEnergyPoints());
    SetAttackDamage(obj.GetAttackDamage());
    std::cout << this->GetName() << "FragTrap copy assignment called\n";
    return *this;    
}

FragTrap::~FragTrap()
{
    std::cout << this->GetName() << " FragTrap deconstructor called\n";
}