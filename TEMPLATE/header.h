// Copyright 2025 Your Organization. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// File-level comment describing the purpose of this header.
// This header provides abstractions for managing example data, including
// a struct for data storage, an enum for error codes, and a class for
// processing. It is intended for use in data processing pipelines.

#ifndef PROJECT_EXAMPLE_H_
#define PROJECT_EXAMPLE_H_

// Include related header (if this header is not the primary one for a .cc file).
#include "project/related_header.h"

// Blank line.

// C system headers (in angle brackets, with .h extension, alphabetical).
#include <sys/types.h>
#include <unistd.h>

// Blank line.

// C++ standard library headers (no extension, in angle brackets, alphabetical).
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

// Blank line.

// Third-party library headers (in quotes or angles as required, alphabetical).
#include "absl/strings/string_view.h"
#include "third_party/other_lib.h"

// Blank line.

// Project-specific headers (in quotes, relative to project root, alphabetical).
#include "project/another_header.h"
#include "project/yet_another_header.h"

// Conditional includes for system-specific code (after other includes).
#ifdef _WIN32
#include <windows.h>
#endif  // _WIN32

// Namespace to prevent name collisions; follows snake_case naming.
namespace project_namespace {

// Forward declarations (minimized to avoid hidden dependencies; include headers instead when possible).
class Dependency;  // Only if necessary for compilation speed.

// Type alias for clarity; documents intent and compatibility.
using DataPoint = int;  // Alias for int; guaranteed to remain int-compatible.

// Constant for use in API; follows kCamelCase naming.
constexpr int kMaxItems = 100;  // Maximum number of items allowed.

// Static constant with trivial destructor; safe for header as per Google style.
const int kDefaultTimeoutMs = 5000;  // Default timeout in milliseconds.

// Enum class for type safety and clear scoping; follows kCamelCase for enumerators.
enum class ErrorCode {
  kOk = 0,           // Success.
  kInvalidInput,     // Input validation failed.
  kOutOfMemory,      // Memory allocation failed.
};

// Struct for passive data storage; public members with no invariants.
struct DataRecord {
  std::string name;    // Descriptive name of the record.
  int value;           // Associated value.
  static Pool<DataRecord>* pool;  // Static member for resource management.
};

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
class ExampleProcessor {
 public:
  // Default constructor; initializes to safe empty state.
  ExampleProcessor() = default;

  // Parameterized constructor; explicit to prevent implicit conversions.
  explicit ExampleProcessor(const std::string& config_name)
      : config_name_(config_name) {
    if (config_name.empty()) {
      throw std::invalid_argument("Config name cannot be empty");
    }
  }

  // Copy and move operations (Rule of Zero since using standard containers).
  ExampleProcessor(const ExampleProcessor&) = default;
  ExampleProcessor& operator=(const ExampleProcessor&) = default;
  ExampleProcessor(ExampleProcessor&&) noexcept = default;
  ExampleProcessor& operator=(ExampleProcessor&&) noexcept = default;

  // Destructor; trivial and noexcept.
  ~ExampleProcessor() noexcept = default;

  // Public methods; const and noexcept where appropriate.
  /**
   * @brief Adds a DataRecord to the collection.
   * @param record The record to add.
   * @throws std::invalid_argument if record is invalid.
   * @throws std::length_error if adding exceeds kMaxItems.
   */
  void AddRecord(const DataRecord& record);

  /**
   * @brief Returns the number of records.
   * @return Size of the record collection.
   */
  size_t GetRecordCount() const noexcept {
    return record_list_.size();
  }

  /**
   * @brief Checks if a record with the given name exists.
   * @param name The name to search for.
   * @return True if the record exists, false otherwise.
   */
  bool HasRecord(absl::string_view name) const noexcept;

  // Inline function (short, <10 lines, ODR-safe in class body).
  int GetDefaultTimeout() const noexcept { return kDefaultTimeoutMs; }

 private:
  // Private data members; snake_case with trailing underscore.
  std::vector<DataRecord> record_list_;  // Stores DataRecords.
  std::string config_name_;              // Configuration identifier.

  // Static data member; trivially destructible.
  static const int kMaxRetries = 3;  // Max retry attempts.

  // Private helper method; internal implementation detail.
  bool ValidateRecord(const DataRecord& record) const noexcept;

  // Dependency (composition over inheritance).
  std::unique_ptr<Dependency> dependency_;
};

// Implementation details only below here.

// Longer inline or template function definitions (ODR-safe with 'inline').
inline bool ExampleProcessor::HasRecord(absl::string_view name) const noexcept {
  return std::find_if(record_list_.begin(), record_list_.end(),
                      [&name](const DataRecord& record) {
                        return record.name == name;
                      }) != record_list_.end();
}

}  // namespace project_namespace

#endif  // PROJECT_EXAMPLE_H_
```