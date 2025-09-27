//
// Created by TUO8HC on 9/24/2025.
//

#ifndef EX01_CURE_H
#define EX01_CURE_H
#include "AMateria.h"


class Cure : public AMateria {
public:
    Cure();
    ~Cure() override;
    std::unique_ptr<AMateria> clone() const override;
    void use(ICharacter& target) override;
};

#endif //EX01_CURE_H