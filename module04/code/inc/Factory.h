//
// Created by TUO8HC on 9/21/2025.
//

#ifndef EX01_FACTORY_H
#define EX01_FACTORY_H

#include <Animal.h>
#include "Brain.h"
#include <Cat.h>
#include <Dog.h>
#include <memory>

enum class AnimalType { Dog, Cat };
// Creator
class AnimalFactory {
public:
    static std::unique_ptr<Animal> createAnimal(AnimalType type);
};

#endif //EX01_FACTORY_H