#ifndef SCAV_TRAP_H_
#define SCAV_TRAP_H_

#include <ClapTrap.h>

class ScavTrap : public ClapTrap{
public:
    ScavTrap(std::string);

    ScavTrap(ScavTrap const&);
    ScavTrap& operator = (ScavTrap const&);

    ~ScavTrap();

    void guardGate();

};

#endif 

