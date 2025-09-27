//
// Created by TUO8HC on 9/26/2025.
//

#include "../inc/MateriaSource.h"

#include <iostream>

MateriaSource::MateriaSource() {
    std::cout << "MateriaSource::MateriaSource()" << std::endl;
    materias_.reserve(kMaxSlots);
}
MateriaSource::~MateriaSource() {
    std::cout << "MateriaSource::~MateriaSource()" << std::endl;
}

MateriaSource::MateriaSource(MateriaSource const &other) {
    std::cout << "MateriaSource::MateriaSource(MateriaSource const &other)" << std::endl;
    for (const auto& p : other.materias_) materias_.push_back(p ? p->clone() : nullptr);
}

MateriaSource &MateriaSource::operator=(MateriaSource const &other) {
    if (this == &other) return *this;
    std::vector<std::unique_ptr<AMateria>> tmp;
    tmp.reserve(kMaxSlots);
    for (const auto& p : other.materias_) tmp.push_back(p ? p->clone() : nullptr);
    materias_.swap(tmp);
    std::cout << "[MateriaSource] copy-assign\n";
    return *this;
}

void MateriaSource::learnMateria(std::unique_ptr<AMateria> m) {
    if (!m) return;
    if (static_cast<int>(materias_.size()) >= kMaxSlots) {
        std::cout << "[MateriaSource] cannot learn more prototypes (full)\n";
        return;
    }
    materias_.push_back(std::move(m));
    std::cout << "[MateriaSource] learned materia type=" << materias_.back()->getType() << "\n";
}

std::unique_ptr<AMateria> MateriaSource::createMateria(std::string const &type) {
    for (const auto& proto : materias_) {
        if (proto && proto->getType() == type) {
            std::cout << "[MateriaSource] creating materia type=" << type << "\n";
            return proto->clone();
        }
    }
    std::cout << "[MateriaSource] unknown type=" << type << "\n";
    return nullptr;
}
