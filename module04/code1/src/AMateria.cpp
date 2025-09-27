//
// Created by TUO8HC on 9/24/2025.
//

#include "../inc/AMateria.h"
#include "ICharacter.h"

#include <iostream>
#include <ostream>

AMateria::AMateria(std::string const &type) : type_(std::move(type)) {
    std::cout << "Amateria::AMateria()" << std::endl;
}

AMateria::~AMateria() {
    std::cout << "Amateria::~AMateria()" << std::endl;
}
void AMateria::use(ICharacter& /*target*/) {
    // Default behavior: nothing specific
    std::cout << "* uses materia of type " << type_ << " *\n";
}