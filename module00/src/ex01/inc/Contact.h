#ifndef CONTACT_H_
#define CONTACT_H_

// C system headers (in angle brackets, with .h extension, alphabetical).
#include <sys/types.h>

// C++ standard library headers (no extension, in angle brackets, alphabetical).
#include <cstddef>
#include <string>

class Contact {
public:
  // Default constructor; initializes to safe empty state.
    Contact() = default;

  // Parameterized constructor; explicit to prevent implicit conversions.
    explicit Contact(const std::string& firstName,
                    const std::string& lastName,
                    const std::string& nickName,
                    const std::string& phoneNumber,
                    const std::string& darkestSecret)
    : firstName_(firstName) {
        if (firstName.empty()) {
            // throw std::invalid_argument("This field can't have empty");
        }
    }

    // Copy and move operations (Rule of Zero since using standard containers).
    Contact(const Contact&) = default;
    Contact& operator=(const Contact&) = default;
    Contact(Contact&&) noexcept = default;
    Contact& operator=(Contact&&) noexcept = default;

  // Destructor; trivial and noexcept.
    ~Contact() noexcept = default;

  // Public methods; const and noexcept where appropriate.
  /**
   * @brief Adds a DataRecord to the collection.
   * @param record The record to add.
   * @throws std::invalid_argument if record is invalid.
   * @throws std::length_error if adding exceeds kMaxItems.
   */
    void SET_firstName(const std::string& firstName);
    void SET_lastName(const std::string& lastName);
    void SET_nickName(const std::string& nickName);
    void SET_phoneNumber(const std::string& phoneNumber);
    void SET_DarkestSecret(const std::string& DarkestSecret);

    std::string GET_firstName(void) const;
    std::string GET_lastName(void) const;
    std::string GET_nickName(void) const;
    std::string GET_phoneNumber(void) const;
    std::string GET_DarkestSecret(void) const;

private:
  // Private data members; snake_case with trailing underscore.
    std::string firstName_;              // Configuration identifier.
    std::string lastName_;              // Configuration identifier.
    std::string nickName_;              // Configuration identifier.
    std::string phoneNumber_;              // Configuration identifier.
    std::string darkestSecret_;              // Configuration identifier.

};



#endif  // CONTACT_H_