#pragma once

#include "error.h"
#include "result.h"
#include "string_helpers.h"
#include "string_converter.h"

#include <string>
#include <cwchar>

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
  return StringConverter<TValue, TRValue>::convert(m_value);
}

template <typename TValue>
template <typename TRValue>
constexpr Result<TRValue, Error> FigValue<TValue>::get_safe() const noexcept {
  return StringConverter<TValue, TRValue>::convert_safe(m_value);
}





} // namespace core
} // namespace fig