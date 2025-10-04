//
// Created by TUO8HC on 9/24/2025.
//

#include "Ice.h"

#include <iostream>
#include <ostream>

Ice::Ice() : AMateria("ice") {
    std::cout << "Ice::Ice ctor" << std::endl;
}

Ice::~Ice() {
    std::cout << "Ice::~Ice dtor" << std::endl;
}


std::unique_ptr<AMateria> Ice::clone() const {
    return std::make_unique<Ice>(*this);
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at" << target.getName() << "*" << std::endl;
}