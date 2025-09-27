//
// Created by TUO8HC on 9/21/2025.
//

#ifndef CPP_ANIMAL_H
#define CPP_ANIMAL_H

#include <iostream>
#include <string>
#include <memory>

// Abstract base class (Product interface).
class Animal {
public:
    Animal();
    explicit Animal(std::string name);
    Animal(Animal const&) = default;
    Animal& operator=(Animal const&) = default;
    ~Animal() noexcept;

    virtual void makeSound() const noexcept = 0;

    const std::string getType() const noexcept;

    // Prototype: polymorphic clone
    virtual std::unique_ptr<Animal> clone() const = 0;

protected:
    std::string type_;
};


#endif //CPP_ANIMAL_H