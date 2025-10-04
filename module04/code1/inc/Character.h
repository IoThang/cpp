//
// Created by TUO8HC on 9/26/2025.
//

#ifndef EX01_CHARACTER_H
#define EX01_CHARACTER_H

#include "ICharacter.h"
#include <vector>

class Character final : public ICharacter {
public:
    Character(std::string name);
    Character(Character const& other);
    Character& operator=(Character const& other);
    ~Character() override;

    std::string const& getName() const override;
    void equip(std::unique_ptr<AMateria> m) override;
    void unequip(int idx) override;
    void use(int const idx, ICharacter& target) override;
private:
    std::string name_;
    static constexpr int kMaxSlots = 4;
    std::vector<std::unique_ptr<AMateria>> inventory_; // Size up to 4
    std::vector<std::unique_ptr<AMateria>> dropped_;   // materias left on the floor (we keep them to avoid leak)
};

#endif //EX01_CHARACTER_H