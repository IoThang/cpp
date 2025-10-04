//
// Created by TUO8HC on 9/21/2025.
//

#include <Factory.h>

std::unique_ptr<Animal> AnimalFactory::createAnimal(AnimalType type) {
    switch (type) {
        case AnimalType::Dog:
            return std::make_unique<Dog>();
        case AnimalType::Cat:
            return std::make_unique<Cat>();
        default:
            throw std::invalid_argument("Unknown AnimalType");
    }
}


// // Abstract factory interface.
// class ShapeFactory {
// public:
//     virtual ~ShapeFactory() noexcept = default;
//
//     // Factory method.
//     virtual std::unique_ptr<Shape> CreateShape(const std::string& type,
//                                                double param) const = 0;
// };
//
// // Concrete factory.
// class ConcreteShapeFactory : public ShapeFactory {
// public:
//     std::unique_ptr<Shape> CreateShape(const std::string& type,
//                                        double param) const override {
//         if (type == "circle") {
//             return std::make_unique<Circle>(param);
//         } else if (type == "square") {
//             return std::make_unique<Square>(param);
//         } else {
//             throw std::invalid_argument("Unknown shape type: " + type);
//         }
//     }
// };