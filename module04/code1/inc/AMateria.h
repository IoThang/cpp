//
// Created by TUO8HC on 9/24/2025.
//

#ifndef EX01_AMATERIA_H
#define EX01_AMATERIA_H

#include <string>
#include "ICharacter.h"

class ICharacter;

class AMateria {
private:
    std::string type_;
public:
    explicit AMateria(std::string const & type);
    virtual ~AMateria();
    std::string const& getType() const noexcept { return type_; }    virtual std::unique_ptr<AMateria> clone() const = 0;
    virtual void use(ICharacter& target);
};


#endif //EX01_AMATERIA_H