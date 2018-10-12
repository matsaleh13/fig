#pragma once

#include <memory>
#include <string>
#include <cctype>

namespace fig {
namespace util {

constexpr static const size_t MIN_BUF_SIZE = 1024;

/**
 * @brief Sprintf-style formatting for C++ strings.
 * Gratefully inspired from: https://stackoverflow.com/a/26221725/5548101.
 *
 * @tparam MinBufSize=MIN_BUF_SIZE Starting size of static buffer for internal
 * use.
 * @tparam Args Variadic template parmeter for format string arguments.
 * @param format sprintf-style format string encapsulated in a std::string.
 * @param args Format string arguments.
 * @return std::string Formatted string.
 */
template <size_t MinBufSize = MIN_BUF_SIZE, typename... Args>
constexpr static std::string string_format(const std::string& format,
                                           Args... args) {
  char buf[MinBufSize];
  const size_t buf_size =
      std::snprintf(buf, MinBufSize, format.c_str(), args...) + 1;

  if (buf_size < MinBufSize) {
    return {buf, buf + buf_size - 1};
  } else {
    // Need bigger buffer, so now we allcate.
    std::unique_ptr<char[]> buf_ptr(new char[buf_size]);
    std::snprintf(buf_ptr.get(), buf_size, format.c_str(), args...);
    return {buf_ptr.get(), buf_ptr.get() + buf_size - 1};
  }
}

/**
 * @brief Simple sprintf-style formatting for C++ strings.
 * This implementation uses array size template deduction to allow use of
 * stack-based buffer and avoid allocations. Used with const literal format
 * strings.
 *
 * @tparam N Character buffer size.
 * @tparam MinBufSize=MIN_BUF_SIZE Starting size of static buffer for internal
 * use.
 * @tparam Args Variadic template parmeter for format string arguments.
 * @param format sprintf-style format string encapsulated in a std::string.
 * @param args Format string arguments.
 * @return std::string Formatted string.
 */
template <size_t N, size_t MinBufSize = MIN_BUF_SIZE, typename... Args>
constexpr static std::string string_format(const char (&format)[N],
                                           Args... args) {
  constexpr const size_t buf_size = std::max(N * 2, MinBufSize);
  char buf[buf_size];
  const size_t actual_size = std::snprintf(nullptr, 0, format, args...) + 1;
  std::snprintf(buf, actual_size, format, args...);
  return {buf, buf + actual_size - 1};
}

/**
 * @brief Convert all characters of string s to lower case.
 *
 * TODO: Configurable locale support.
 *
 * @tparam TChar Type of character to use.
 * @param s String to be converted (IN/OUT)
 */
template <typename TChar>
constexpr static void tolower(std::basic_string<TChar>& s) {
  std::transform(s.begin(), s.end(), s.begin(), std::tolower );
}

/**
 * @brief Convert all characters of string s to lower case.
 *
 * TODO: Configurable locale support.
 *
 * @tparam TChar Type of character to use.
 * @param s String to be converted.
 * @return Converted string.
 */
template <typename TChar>
constexpr static std::basic_string<TChar> tolower(const std::basic_string<TChar>& s) {
  std::basic_string<TChar> temp(s);
  std::transform(temp.begin(), temp.end(), temp.begin(), std::tolower );
  return temp;
}


} // namespace util
} // namespace fig