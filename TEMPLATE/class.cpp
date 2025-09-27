// Include necessary headers
#include <vector>      // For standard containers
#include <string>      // For strings
#include <utility>     // For std::move, std::swap
#include <stdexcept>   // For exceptions

// Forward declarations (minimize includes)
class Dependency;      // If needed for composition

/**
 * @brief Brief description of the class purpose.
 * 
 * Invariants: [List key invariants, e.g., data_ is always sorted].
 * Exception Safety: [e.g., Strong guarantee for addItem()].
 */
class MySafeEfficientClass {
public:
    // Constructors
    /**
     * @brief Default constructor.
     * Initializes to a safe empty state.
     */
    MySafeEfficientClass() = default;

    /**
     * @brief Parameterized constructor.
     * @param param Description of param.
     * @throws std::invalid_argument if param invalid.
     */
    explicit MySafeEfficientClass(const std::string& param)
        : data_(), name_(param) {
        if (param.empty()) {
            throw std::invalid_argument("Param cannot be empty");
        }
        // Additional initialization
    }

    // Copy and Move Operations (Rule of Zero/Five)
    MySafeEfficientClass(const MySafeEfficientClass&) = default;
    MySafeEfficientClass& operator=(const MySafeEfficientClass&) = default;
    MySafeEfficientClass(MySafeEfficientClass&&) noexcept = default;
    MySafeEfficientClass& operator=(MySafeEfficientClass&&) noexcept = default;

    // Destructor
    /**
     * @brief Destructor.
     * Releases resources safely.
     */
    ~MySafeEfficientClass() noexcept = default;  // Or custom if needed

    // Public Member Functions
    /**
     * @brief Getter example.
     * @return Const reference to avoid copies.
     */
    const std::string& getName() const noexcept {
        return name_;
    }

    /**
     * @brief Setter example with validation.
     * @throws std::invalid_argument on invalid input.
     */
    void setName(const std::string& newName) {
        if (newName.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        name_ = newName;
    }

    /**
     * @brief Operation example with strong exception safety.
     * Uses copy-and-swap for safety.
     */
    void addItem(const std::string& item) {
        auto temp = data_;  // Copy for strong guarantee
        temp.push_back(item);
        swap(temp);         // Noexcept swap
    }

    /**
     * @brief Const-correct query function.
     * @return Size without modifying state.
     */
    size_t size() const noexcept {
        return data_.size();
    }

    // Swap for exception safety (non-member friend if needed)
    void swap(MySafeEfficientClass& other) noexcept {
        using std::swap;
        swap(data_, other.data_);
        swap(name_, other.name_);
    }

private:
    // Private Data Members (encapsulated)
    std::vector<std::string> data_;  // Managed container
    std::string name_ = "default";   // In-class initializer

    // Private Helper Functions (if needed)
    void internalHelper() noexcept {
        // Implementation details hidden
    }

    // Composition Example
    std::unique_ptr<Dependency> dep_;  // Owned resource
};

// Non-Member Functions (for symmetry, e.g., swap)
void swap(MySafeEfficientClass& a, MySafeEfficientClass& b) noexcept {
    a.swap(b);
}

// Usage Example (outside class)
int main() {
    MySafeEfficientClass obj("example");
    obj.addItem("item1");
    return 0;
}