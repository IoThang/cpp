//
// Created by TUO8HC on 9/22/2025.
//

#ifndef EX01_BRAIN_H
#define EX01_BRAIN_H

#include <iostream>
#include <string>

class Brain {
public:
    Brain();
    explicit Brain(std::string const &idea);
    Brain(Brain const&);
    Brain& operator=(Brain const&);
    ~Brain() = default;

    void setIdea(std::string const& idea);
    const std::string getIdea() const noexcept;

private:
    std::string idea_;
};


#endif //EX01_BRAIN_H