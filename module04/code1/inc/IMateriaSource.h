//
// Created by TUO8HC on 9/24/2025.
//

#ifndef EX01_IMATERIALSOURCE_H
#define EX01_IMATERIALSOURCE_H

#include "AMateria.h"

class IMateriaSource {
public:
    virtual ~IMateriaSource() {}
    virtual void learnMateria(std::unique_ptr<AMateria>) = 0;
    virtual std::unique_ptr<AMateria> createMateria(std::string const & type) = 0;
};


#endif //EX01_IMATERIALSOURCE_H