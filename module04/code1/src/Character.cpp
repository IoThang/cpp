//
// Created by TUO8HC on 9/24/2025.
//

#include "../inc/Character.h"

#include <iostream>
#include <ostream>

#include "AMateria.h"

Character::Character(std::string name) : name_(std::move(name)), inventory_(), dropped_() {
    std::cout << "Character::Character(\"" << name_ << "\")\n";
    inventory_.reserve(kMaxSlots);
}

Character::Character(Character const &other) : name_(other.name_) {
    inventory_.reserve(kMaxSlots);
    dropped_.reserve(other.dropped_.size());

    // deep copy inventory
    for (const auto& mptr : other.inventory_) {
        if (mptr) inventory_.push_back(mptr->clone());
        else inventory_.push_back(nullptr);
    }

    // deep copy dropped/floor
    for (const auto& mptr : other.dropped_)
        dropped_.push_back(mptr ? mptr->clone() : nullptr);

    std::cout << "[Character] copy-ctor name=" << name_ << "\n";
}

Character& Character::operator=(Character const &other) {
    if (this == &other) return *this;

    // clone-and-swap-like: build temporary copies then assign
    std::vector<std::unique_ptr<AMateria>> newInv;
    newInv.reserve(kMaxSlots);
    for (const auto& mptr : other.inventory_) newInv.push_back(mptr ? mptr->clone() : nullptr);

    std::vector<std::unique_ptr<AMateria>> newDropped;
    newDropped.reserve(other.dropped_.size());
    for (const auto& mptr : other.dropped_) newDropped.push_back(mptr ? mptr->clone() : nullptr);

    name_ = other.name_;
    inventory_.swap(newInv);
    dropped_.swap(newDropped);
    std::cout << "[Character] copy-assign name=" << name_ << "\n";
    return *this;
}

Character::~Character() {
    std::cout << "[Character] dtor name=" << name_ << " (cleaning inventory and dropped)\n";
    // unique_ptr will delete resources automatically
}

std::string const& Character::getName() const {
    std::cout << "Character::getName()\n";
    return name_;
}

void Character::equip(std::unique_ptr<AMateria> m) {
    if (!m) return;
    // find first empty slot
    if (inventory_.size() < static_cast<size_t>(kMaxSlots)) {
        inventory_.push_back(std::move(m));
        std::cout << "[Character] " << name_ << " equipped materia type=" << inventory_.back()->getType() << "\n";
    } else {
        // inventory full: follow assignment instructions: "don't do anything"
        // To avoid memory leak of passed unique_ptr, we decide to keep it on floor (dropped_).
        dropped_.push_back(std::move(m));
        std::cout << "[Character] " << name_ << " inventory full. Materia placed on the floor.\n";
    }
}

void Character::unequip(int const idx) {
    if (idx < 0 || idx >= static_cast<int>(inventory_.size())) {
        std::cout << "[Character] " << name_ << " unequip invalid idx=" << idx << "\n";
        return;
    }
    // move the materia to dropped_ (floor) — do NOT delete it
    dropped_.push_back(std::move(inventory_[idx]));
    inventory_.erase(inventory_.begin() + idx);
    std::cout << "[Character] " << name_ << " unequipped slot " << idx << " (moved to floor)\n";
}

void Character::use(int const idx, ICharacter &target) {
    if (idx < 0 || idx >= static_cast<int>(inventory_.size()) || !inventory_[idx]) {
        std::cout << "[Character] " << name_ << " use invalid idx=" << idx << "\n";
        return;
    }
    inventory_[idx]->use(target);
}
