#pragma once

#include "result_error.h"

namespace fig {
namespace util {

template <typename TValue, typename TError>
class Result {
public:
  using value_type = TValue;
  using error_type = TError;

  constexpr Result(const value_type& value);
  constexpr Result(const error_type& error);
  Result() = delete;
  ~Result() {}

  constexpr explicit operator bool() const;

  constexpr const value_type& value() const;
  constexpr const error_type& error() const;

private:
  constexpr void ensure_checked() const;

  union {
    const value_type m_value;
    const error_type m_error;
  };

  const bool m_isError;
  mutable bool m_checked = false;
};

template <typename TValue, typename TError>
constexpr Result<TValue, TError>::Result(const TValue& value)
    : m_value(value), m_isError(false), m_checked(false) {}

template <typename TValue, typename TError>
constexpr Result<TValue, TError>::Result(const TError& error)
    : m_error(error), m_isError(true), m_checked(false) {}

template <typename TValue, typename TError>
inline constexpr Result<TValue, TError>::operator bool() const {
  m_checked = true;
  return (m_isError == false);
}

template <typename TValue, typename TError>
inline constexpr const TValue& Result<TValue, TError>::value() const {
  assert(m_checked);
  ensure_checked();

  assert(!m_isError);
  return m_value;
}

template <typename TValue, typename TError>
inline constexpr const TError& Result<TValue, TError>::error() const {
  assert(m_checked);
  ensure_checked();

  assert(m_isError);
  return m_error;
}

template <typename TValue, typename TError>
inline constexpr void Result<TValue, TError>::ensure_checked() const {
  if (!m_checked) throw ResultNotCheckedError("Result is not checked; call Result::operator bool() before calling accessors.");
}

} // namespace util
} // namespace fig