#pragma once

#include "error.h"
#include "result.h"

#include <string>

namespace fig {
namespace core {

using namespace fig::util;

/**
 * @brief Provides access to a single value.
 *
 * @tparam TValue Native type of the value to be retrieved; assumed to be
 * std::basic_string<X>
 */
template <typename TValue>
class FigValue {
public:
  using value_type = TValue;

  constexpr FigValue(const value_type& value) noexcept;
  constexpr FigValue() noexcept = default;

  constexpr const value_type& get() const noexcept { return m_value; };

  template <typename TRValue>
  constexpr TRValue get() const;

  template <typename TRValue>
  constexpr Result<TRValue, Error> get_safe() const noexcept;

private:
  value_type m_value;
};

template <typename TValue>
constexpr FigValue<TValue>::FigValue(const TValue& value) noexcept
    : m_value(value) {}

template <typename TValue>
template <typename TRValue>
constexpr TRValue FigValue<TValue>::get() const {
  return FigValueConverter<TValue, TRValue>::convert(m_value);
}

template <typename TValue>
template <typename TRValue>
constexpr Result<TRValue, Error> FigValue<TValue>::get_safe() const noexcept {
  return FigValueConverter<TValue, TRValue>::convert_safe(m_value);
}

/**
 * @brief Utility for converting a native value to another type.
 *
 * @tparam TValue Type of the value to be converted.
 * @tparam TRValue Returned (converted) value.
 */
template <typename TValue, typename TRValue>
struct FigValueConverter {

  constexpr static TRValue convert(const TValue& value);

  // Exception safe version.
  constexpr static Result<TRValue, Error>
  convert_safe(const TValue& value) noexcept {
    try {
      return convert<TRValue>(value);
    } catch (...) {
      return FIG_ERROR("Invalid conversion of value.");
    }
  }
};

//
// Template specializations of FigValueConverter.
//

template <typename TValue>
struct FigValueConverter<TValue, int> {
  constexpr static int convert(const TValue& value) { return std::stoi(value); }
};

template <typename TValue>
struct FigValueConverter<TValue, long> {
  constexpr static long convert(const TValue& value) {
    return std::stol(value);
  }
};

template <typename TValue>
struct FigValueConverter<TValue, long long> {
  constexpr static long long convert(const TValue& value) {
    return std::stoll(value);
  }
};

template <typename TValue>
struct FigValueConverter<TValue, unsigned int> {
  constexpr static unsigned long convert(const TValue& value) {
    auto temp = std::stoul(value);
    if (temp > std::numeric_limits<unsigned>::max()) {
      throw std::out_of_range("unsigned int");
    }
    return static_cast<unsigned int>(temp);
  }
};

template <typename TValue>
struct FigValueConverter<TValue, unsigned long> {
  constexpr static unsigned long convert(const TValue& value) {
    return std::stoul(value);
  }
};

template <typename TValue>
struct FigValueConverter<TValue, unsigned long long> {
  constexpr static unsigned long long convert(const TValue& value) {
    return std::stoull(value);
  }
};

template <typename TValue>
struct FigValueConverter<TValue, float> {
  constexpr static float convert(const TValue& value) {
    return std::stof(value);
  }
};

template <typename TValue>
struct FigValueConverter<TValue, double> {
  constexpr static double convert(const TValue& value) {
    return std::stod(value);
  }
};

template <typename TValue>
struct FigValueConverter<TValue, long double> {
  constexpr static long double convert(const TValue& value) {
    return std::stold(value);
  }
};

} // namespace core
} // namespace fig