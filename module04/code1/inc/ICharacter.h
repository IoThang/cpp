//
// Created by TUO8HC on 9/24/2025.
//

#ifndef EX01_ICHARACTER_H
#define EX01_ICHARACTER_H

#include <memory>

class AMateria;

class ICharacter {
public:
    virtual ~ICharacter() {}
    virtual std::string const & getName() const = 0;
    virtual void equip(std::unique_ptr<AMateria> m) = 0;
    virtual void unequip(int idx) = 0;
    virtual void use(int idx, ICharacter& target) = 0;
};


#endif //EX01_ICHARACTER_H