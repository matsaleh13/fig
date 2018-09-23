#pragma once

#include <memory>
#include <string>

namespace fig {
namespace util {

constexpr static const size_t MIN_BUF_SIZE = 2048;

/**
 * @brief Sprintf-style formatting for C++ strings.
 * Gratefully inspired from: https://stackoverflow.com/a/26221725/5548101.
 *
 * @tparam Args
 * @param format sprintf-style format string encapsulated in a std::string.
 * @param args
 * @return std::string
 */
template <typename... Args>
constexpr static std::string string_format(const std::string& format,
                                           Args... args) {
  char buf[MIN_BUF_SIZE];
  const size_t buf_size =
      std::snprintf(buf, MIN_BUF_SIZE, format.c_str(), args...) +
      1; // Extra space for '\0'

  if (buf_size < MIN_BUF_SIZE) {
    return {buf, buf + buf_size - 1}; // We don't want the '\0' inside
  } else {
    // Need bigger buffer, so now we allcate.
    std::unique_ptr<char[]> buf_ptr(new char[buf_size]);
    std::snprintf(buf_ptr.get(), buf_size, format.c_str(), args...);
    return {buf_ptr.get(),
            buf_ptr.get() + buf_size - 1}; // We don't want the '\0' inside
  }
}

/**
 * @brief Simple sprintf-style formatting for C++ strings.
 * This implementation uses array size template deduction to allow use of
 * stack-based buffer and avoid allocations. Used with const literal format
 * strings.
 *
 * @tparam N
 * @tparam Args
 * @param args
 * @return constexpr std::string
 */
template <size_t N, typename... Args>
constexpr static std::string string_format(const char (&format)[N],
                                           Args... args) {
  constexpr const size_t buf_size = std::max(N * 2, MIN_BUF_SIZE);
  char buf[buf_size];
  const size_t actual_size =
      std::snprintf(nullptr, 0, format, args...) + 1; // Extra space for '\0'
  std::snprintf(buf, actual_size, format, args...);
  return {buf, buf + actual_size - 1}; // We don't want the '\0' inside
}

} // namespace util
} // namespace fig