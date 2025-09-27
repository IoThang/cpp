//
// Created by TUO8HC on 9/24/2025.
//

#include "Cure.h"

#include <iostream>
#include <ostream>

Cure::Cure() : AMateria("cure") {
    std::cout << "Cure::Cure ctor" << std::endl;
}

Cure::~Cure() {
    std::cout << "Cure::~Cure dtor" << std::endl;
}


std::unique_ptr<AMateria> Cure::clone() const {
    return std::make_unique<Cure>(*this);
}

void Cure::use(ICharacter& target) {
    std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}