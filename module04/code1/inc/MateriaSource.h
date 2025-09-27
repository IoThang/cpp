//
// Created by TUO8HC on 9/26/2025.
//

#ifndef EX01_MATERIASOURCE_H
#define EX01_MATERIASOURCE_H

#include <vector>

#include "IMateriaSource.h"

class MateriaSource : public IMateriaSource {
public:
    MateriaSource();
    MateriaSource(MateriaSource const& other);
    MateriaSource& operator=(MateriaSource const& other);
    ~MateriaSource() override;

    void learnMateria(std::unique_ptr<AMateria> m) override;
    std::unique_ptr<AMateria> createMateria(std::string const & type) override;
private:
    static constexpr int kMaxSlots = 4;
    std::vector<std::unique_ptr<AMateria>> materias_;
};


#endif //EX01_MATERIASOURCE_H