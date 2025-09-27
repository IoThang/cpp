#include "Factory.h"
#include <iostream>
#include <cassert>

int main(int argc, char *argv[]) {
    auto Chihuahua = AnimalFactory::createAnimal(AnimalType::Dog);
    auto cat = AnimalFactory::createAnimal(AnimalType::Cat);

    auto dog = std::move(Chihuahua);

    auto husky = dog->clone();

    assert(Chihuahua == nullptr);

    std::cout << dog->getType() << std::endl;
    std::cout << cat->getType() << std::endl;

    cat->makeSound();
    dog->makeSound();

    /**
     * There are two ways to change the parent type to child type
     * 1. Dynamic cast -> Drawback: Complex to use due to casting
     * 2. Create a pure abstract interface for supper class, and subclasses have a specific implementation
     */
    dynamic_cast<Cat*>(cat.get())->setIdea("Hello from cat");
    std::cout << dynamic_cast<Cat*>(cat.get())->getIdea() << std::endl;

    dynamic_cast<Dog*>(dog.get())->setIdea("Hello from dog");
    std::cout << dynamic_cast<Dog*>(dog.get())->getIdea() << std::endl;


    return 0;
}
