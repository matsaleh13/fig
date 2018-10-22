#pragma once

#include "result.h"
#include "error.h"

#include <stdexcept>
#include <string>

namespace fig {
namespace util {

/**
 * @brief Utility for converting a string value to another type.
 *
 * @tparam TValue Type of the value to be converted.
 * @tparam TRValue Returned (converted) value.
 */
template <typename TValue, typename TRValue>
class StringConverter {
public:
  constexpr static TRValue convert(TValue value);
  
  // Exception safe version.
  constexpr static Result<TRValue, Error> convert_safe(TValue value) noexcept {
    try {
      return Result<TRValue, Error>(convert<TRValue>(value));
    } catch (std::exception e) {
      return FIG_ERROR("Invalid conversion of value: [%s]", e.what());
    }
  }
};


//
// Template specializations of StringConverter.
//

template <typename TValue>
struct StringConverter<TValue, int> {
  constexpr static int convert(const TValue& value) { return std::stoi(value); }
  constexpr static Result<int, Error> convert_safe(TValue value) noexcept {
    try {
      return Result<int, Error>(convert<int>(value));
    } catch (std::exception e) {
      return FIG_ERROR("Invalid conversion of value: [%s]", e.what());
    }
  }
};

template <typename TValue>
struct StringConverter<TValue, long> {
  constexpr static long convert(const TValue& value) {
    return std::stol(value);
  }
};

template <typename TValue>
struct StringConverter<TValue, long long> {
  constexpr static long long convert(const TValue& value) {
    return std::stoll(value);
  }
};

template <typename TValue>
struct StringConverter<TValue, unsigned int> {
  constexpr static unsigned long convert(const TValue& value) {
    auto temp = std::stoul(value);
    if (temp > std::numeric_limits<unsigned>::max()) {
      throw std::out_of_range("unsigned int");
    }
    return static_cast<unsigned int>(temp);
  }
};

template <typename TValue>
struct StringConverter<TValue, unsigned long> {
  constexpr static unsigned long convert(const TValue& value) {
    return std::stoul(value);
  }
};

template <typename TValue>
struct StringConverter<TValue, unsigned long long> {
  constexpr static unsigned long long convert(const TValue& value) {
    return std::stoull(value);
  }
};

template <typename TValue>
struct StringConverter<TValue, float> {
  constexpr static float convert(const TValue& value) {
    return std::stof(value);
  }
};

template <typename TValue>
struct StringConverter<TValue, double> {
  constexpr static double convert(const TValue& value) {
    return std::stod(value);
  }
};

template <typename TValue>
struct StringConverter<TValue, long double> {
  constexpr static long double convert(const TValue& value) {
    return std::stold(value);
  }
};

template <typename TValue>
struct StringConverter<TValue, std::string> {
  constexpr static std::string convert(const TValue& value) {
    return fig::util::wstring_to_string(value);
  }
};

template <typename TValue>
struct StringConverter<TValue, std::wstring> {
  constexpr static std::wstring convert(const TValue& value) {
    return fig::util::string_to_wstring(value);
  }
};

// No-op / pass-through
template <>
struct StringConverter<std::string, std::string> {
  constexpr static const std::string& convert(const std::string& value) {
    return value;
  }
};

// No-op / pass-through
template <>
struct StringConverter<std::wstring, std::wstring> {
  constexpr static const std::wstring& convert(const std::wstring& value) {
    return value;
  }
};


}
} // namespace fig