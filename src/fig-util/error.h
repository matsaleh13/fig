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

} // namespace util
} // namespace fig


#define FIG_ERROR(msg) \
{ \
  fig::util::Error(msg, __FILE__, __LINE__); \
};