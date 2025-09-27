//
// Created by TUO8HC on 9/21/2025.
//

#include "../inc/Animal.h"

Animal::Animal() {
    std::cout << "Animal::Animal constructor" << std::endl;
}

Animal::Animal(std::string name) : type_(std::move(name)) {
    std::cout << "Animal::Animal explicit constructor" << std::endl;
}

Animal::~Animal() noexcept {
    std::cout << "Animal::~Animal destructor" << std::endl;
}

const std::string Animal::getType() const noexcept {
    return type_;
}
