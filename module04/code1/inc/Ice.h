//
// Created by TUO8HC on 9/24/2025.
//

#ifndef EX01_ICE_H
#define EX01_ICE_H
#include "AMateria.h"


class Ice : public AMateria {
public:
    Ice();
    ~Ice() override;
    std::unique_ptr<AMateria> clone() const override;
    void use(ICharacter& target) override;
};


#endif //EX01_ICE_H