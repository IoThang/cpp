//
// Created by TUO8HC on 9/21/2025.
//

#include "../inc/Dog.h"

Dog::Dog() : Animal("Dog"), brain_(std::make_unique<Brain>()) {
    std::cout << "Dog::Dog()" << std::endl;
}

Dog::~Dog() {
    std::cout << "Dog::~Dog()" << std::endl;
}

// deep copy
Dog::Dog(Dog const & other) : Animal(other), brain_(std::make_unique<Brain>(*other.brain_)) {
    std::cout << "[Dog] copy-ctor\n";
}

Dog& Dog::operator=(Dog const & other) {
    std::cout << "Dog::operator=()" << std::endl;
    if (this != &other) {
        Animal::operator=(other);
        brain_ = std::make_unique<Brain>(*other.brain_);
    }
    return *this;
}

void Dog::makeSound() const noexcept {
    std::cout << "Gau gau" << std::endl;
}

std::unique_ptr<Animal> Dog::clone() const {
    return std::make_unique<Dog>(*this); // uses copy ctor -> deep copy
}

void Dog::setIdea(std::string const& idea) {
    if (brain_) brain_->setIdea(idea);
}

const std::string Dog::getIdea() const noexcept {
    if (brain_) return brain_->getIdea();
    return "";
}
