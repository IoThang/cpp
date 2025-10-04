#include <ClapTrap.h>

ClapTrap::ClapTrap(){
    std::cout << this->GetName() << "Default constructor called\n";
}

ClapTrap::ClapTrap(std::string my_name) : name_(my_name), hit_points_(10), energy_points_(10), attack_damage_(0) 
{
    std::cout << this->GetName() << "Explicit constructor for ClapTrap called\n";
}

ClapTrap::ClapTrap(ClapTrap const& obj) : name_(obj.name_), hit_points_(obj.hit_points_), energy_points_(obj.energy_points_), attack_damage_(obj.attack_damage_){
    std::cout << this->GetName() << "Copy constructor called\n";
}

ClapTrap& ClapTrap::operator = (ClapTrap const& obj){
    std::cout << this->GetName() << "Copy assignment called\n";
    this->name_ = obj.name_;
    this->hit_points_ = obj.hit_points_;
    this->energy_points_ = obj.energy_points_;
    this->attack_damage_ = obj.attack_damage_;
    return *this;
}

ClapTrap::~ClapTrap(){
    std::cout << this->GetName() << "Default deconstructor called\n";
}

// =========================================================

std::string ClapTrap::GetName(void) const
{
    return name_;
}

void ClapTrap::SetName(std::string const& name)
{
    this->name_ = name;
}

points ClapTrap::GetHitPoints(void) const
{
    return hit_points_;
}

void ClapTrap::SetHitPoints(points amount)
{
    this->hit_points_ = amount;
}

points ClapTrap::GetAttackDamage(void) const {
    return this->attack_damage_;
}

void ClapTrap::SetEnergyPoints(points amount){
    this->energy_points_ = amount;
}

points ClapTrap::GetEnergyPoints(void) const {
    return this->energy_points_;
}

sClapTrapState ClapTrap::getState(void) const{
    return state_;
}

void ClapTrap::SetState(sClapTrapState const& state){
    this->state_ = state;
}

void ClapTrap::SetAttackDamage(points amount){
    this->attack_damage_ = amount;
}


bool isBlocked(points hit_pts, points energy_pts){
    if(!hit_pts && !energy_pts)
        return true;
    return false;
}

// ========================================================

void ClapTrap::attack(ClapTrap& target)
{
    if(getState() == sClapTrapState::OutOfEnergy){
        std::cout << this->GetName() << "Out of energy point. Can not attack\n";
    }
    else if(getState() == sClapTrapState::OutOfHealth){
        std::cout << this->GetName() << "You're already died before, can not do anything \n";
    }
    else{
        std::cout << "ClapTrap " << this->name_ << " attacks " << target.name_ <<" causing " << this->attack_damage_ << " points of damage! \n";
        // decrement energy point for this attack
        this->energy_points_--;
        target.TakeDamage(this->attack_damage_);
    }

}

void ClapTrap::TakeDamage(points amount){
    if(getState() != sClapTrapState::OutOfHealth){
        if(ClapTrap::hit_points_ > amount){
            hit_points_ -= amount;
        }
        else{
            hit_points_ = 0;
            SetState(sClapTrapState::OutOfHealth);
            std::cout << "Die\n";
        }
    }
}

void ClapTrap::BeRepaired(points amount){
    if(getState() != sClapTrapState::OutOfEnergy){
        hit_points_ += amount;
        energy_points_--;
    }
    else{
        std::cout << "Don't enough energy point to repair\n";
    }
}