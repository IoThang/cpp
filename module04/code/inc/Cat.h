//
// Created by TUO8HC on 9/21/2025.
//

#ifndef EX01_CAT_H
#define EX01_CAT_H
#include "Animal.h"
#include "Brain.h"

// Concrete products.
class Cat : public Animal{
public:
    Cat();
    ~Cat();

    Cat(Cat const&);
    Cat& operator=(Cat const&);

    void makeSound() const noexcept override;
    std::unique_ptr<Animal> clone() const override;

    // Brain accessors for testing deep copy
    void setIdea(std::string const& idea);
    const std::string getIdea() const noexcept;
private:
    std::unique_ptr<Brain> brain_;
};


#endif //EX01_CAT_H