#pragma once

#include <string>

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
