//
// Created by TUO8HC on 9/21/2025.
//

#include "Cat.h"

Cat::Cat() : Animal("Cat"), brain_(std::make_unique<Brain>()) {
    std::cout << "Cat::Cat()" << std::endl;
}

Cat::~Cat() {
    std::cout << "Cat::~Cat()" << std::endl;
}

Cat::Cat(Cat const& other) : Animal(other), brain_(std::make_unique<Brain>(*other.brain_)) {
    std::cout << "Cat::Cat(Cat const &)" << std::endl;
}

Cat& Cat::operator=(Cat const& other) {
    std::cout << "Cat::operator=(Cat const &)" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        brain_ = std::make_unique<Brain>(*other.brain_);
    }
    return *this;
}


void Cat::setIdea(std::string const& idea) {
    std::cout << "Cat::setIdea()" << std::endl;
    if (brain_) brain_->setIdea(idea);
}

const std::string Cat::getIdea() const noexcept {
    if (brain_) return brain_->getIdea();
    return "";
}

void Cat::makeSound() const noexcept {
    std::cout << "Meo meo" << std::endl;
}

std::unique_ptr<Animal> Cat::clone() const {
    std::cout << "Cat::clone()" << std::endl;
    return std::make_unique<Cat>(*this);
}
