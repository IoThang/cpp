#ifndef FRAG_TRAP_H_
#define FRAG_TRAP_H_

#include <ClapTrap.h>

class FragTrap : public ClapTrap{
public:
    FragTrap(std::string);
    FragTrap(FragTrap const&);
    FragTrap& operator = (FragTrap const&);
    ~FragTrap();
    
    void highFivesGuys(void);

};

#endif
