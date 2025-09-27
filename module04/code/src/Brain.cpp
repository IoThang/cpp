//
// Created by TUO8HC on 9/22/2025.
//

#include "Brain.h"

#include <memory>

#include "Animal.h"

Brain::Brain() : idea_("") {
    // initialize with empty strings (already default-initialized)
}

Brain::Brain(std::string const& idea) : idea_(idea) {
    std::cout << "[Brain] explicit-ctor\n";
}

Brain::Brain(Brain const& other) : idea_(other.idea_) {
    std::cout << "[Brain] copy-ctor\n";
}

Brain& Brain::operator=(Brain const& other) {
    if (this != &other) {
        idea_ = other.idea_;
    }
    std::cout << "[Brain] copy-assign\n";
    return *this;
}

void Brain::setIdea(std::string const &idea) {
    idea_ = (idea);
}

const std::string Brain::getIdea() const noexcept {
    return idea_;
}
