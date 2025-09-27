#include <ScavTrap.h>

ScavTrap::ScavTrap(std::string name) {
    std::cout << "ScavTrap constructor called\n";
    SetName(name);
    SetHitPoints(100);
    SetEnergyPoints(50);
    SetAttackDamage(20);
}

ScavTrap::ScavTrap(ScavTrap const& obj){
    std::cout << this->GetName() << "ScavTrap copy constructor called\n";
    SetName(obj.GetName());
    SetHitPoints(obj.GetHitPoints());
    SetEnergyPoints(obj.GetEnergyPoints());
    SetAttackDamage(obj.GetAttackDamage());
}

ScavTrap& ScavTrap::operator=(ScavTrap const& obj){
    std::cout << this->GetName() << " ScavTrap copy assignment called\n";
    SetName(obj.GetName());
    SetHitPoints(obj.GetHitPoints());
    SetEnergyPoints(obj.GetEnergyPoints());
    SetAttackDamage(obj.GetAttackDamage());
    return *this;
}

void ScavTrap::guardGate(void){
    std::cout << this->GetName() << " ScavTrap is now in Gate keeper mode\n";
}


ScavTrap::~ScavTrap() {
    std::cout << this->GetName() << " ScavTrap constructor called\n";
}