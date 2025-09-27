
#ifndef PHONEBOOK_H_
#define PHONEBOOK_H_

// Include related header (if this header is not the primary one for a .cc file).
#include "Contact.h"

// C system headers (in angle brackets, with .h extension, alphabetical).
#include <sys/types.h>

// C++ standard library headers (no extension, in angle brackets, alphabetical).
#include <cstddef>
#include <string>
#include <vector>

#define MAX_OF_CONTACTS     8

// Forward declarations (minimized to avoid hidden dependencies; include headers instead when possible).
class Contact;  // Only if necessary for compilation speed.

// Class for active data processing; follows PascalCase naming.
/**
 * @brief Manages a collection of DataRecords with processing capabilities.
 * 
 * This class handles a collection of DataRecords, providing methods to add,
 * query, and process them. It ensures thread-safety for read operations but
 * requires external synchronization for write operations.
 * 
 * Example usage:
 *   ExampleProcessor processor;
 *   processor.AddRecord({"item1", 42});
 *   int count = processor.GetRecordCount();
 * 
 * Invariants:
 * - record_list_ is never null.
 * - record_list_ size does not exceed kMaxItems.
 * Exception Safety: Strong guarantee for AddRecord(), basic for others.
 */
class PhoneBook {
public:
    // Default constructor; initializes to safe empty state.
    PhoneBook()
    {
        contact_list_.reserve(MAX_OF_CONTACTS);
    };

    // Copy and move operations (Rule of Zero since using standard containers).
    PhoneBook(const PhoneBook&) = default;
    PhoneBook& operator=(const PhoneBook&) = default;
    PhoneBook(PhoneBook&&) noexcept = default;
    PhoneBook& operator=(PhoneBook&&) noexcept = default;

    // Destructor; trivial and noexcept.
    ~PhoneBook() noexcept = default;

  // Public methods; const and noexcept where appropriate.
  /**
   * @brief Adds a DataRecord to the collection.
   * @param record The record to add.
   * @throws std::invalid_argument if record is invalid.
   * @throws std::length_error if adding exceeds kMaxItems.
   */
    void Add(Contact& cont_element);
    void Display(int idx);

 private:
    // Private data members; snake_case with trailing underscore.
    std::vector<Contact> contact_list_;    // Stores DataRecords.

    void getInput(Contact& cont_element);

};


#endif  // PHONEBOOK_H_