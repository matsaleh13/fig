#pragma once

#include <string>

#include "string_helpers.h"

namespace fig {
namespace util {

/**
 * @brief Encapsulates actionable details about an error for later reporting.
 *
 */
class Error {
public:
  constexpr explicit Error(const std::string& what, const std::string& file,
                           uint32_t line);
  Error() = delete;
  ~Error() {}

  constexpr const std::string& what() const { return m_what; }
  constexpr const std::string& file() const { return m_file; }
  constexpr uint32_t line() const { return m_line; }

private:
  const std::string m_what;
  const std::string m_file;
  const uint32_t m_line;
};

constexpr Error::Error(const std::string& what, const std::string& file,
                       uint32_t line)
    : m_what(what), m_file(file), m_line(line) {}


} // namespace util
} // namespace fig


#define FIG_ERROR(msg, ...) \
  (fig::util::Error(FORMAT_STRING(msg, __VA_ARGS__), __FILE__, __LINE__))

