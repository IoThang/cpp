#include "MateriaSource.h"
#include "Character.h"
#include "Ice.h"
#include "Cure.h"
#include <iostream>

int main() {
    std::cout << "=== Setup MateriaSource ===\n";
    MateriaSource src;
    src.learnMateria(std::make_unique<Ice>());
    src.learnMateria(std::make_unique<Cure>());

    std::cout << "\n=== Create Characters ===\n";
    Character alice("Alice");
    Character bob("Bob");

    std::cout << "\n=== Create materias and equip ===\n";
    auto m1 = src.createMateria("ice");
    auto m2 = src.createMateria("cure");
    alice.equip(std::move(m1));
    alice.equip(std::move(m2));

    std::cout << "\n=== Alice use materia ===\n";
    alice.use(0, bob); // ice -> shoots at Bob
    alice.use(1, bob); // cure -> heals Bob

    std::cout << "\n=== unequip slot 0 (to floor) ===\n";
    alice.unequip(0);

    std::cout << "\n=== deep copy Character ===\n";
    Character copyAlice = alice; // deep copy
    std::cout << "copyAlice uses slot 0: \n";
    copyAlice.use(0, bob); // should work if slot exists

    std::cout << "\n=== MateriaSource create unknown ===\n";
    auto m3 = src.createMateria("fire");
    if (!m3) std::cout << "createMateria returned nullptr for 'fire'\n";

    std::cout << "\n=== End main ===\n";
    return 0;
}
