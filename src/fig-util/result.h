#pragma once

namespace fig {
namespace util {

template <typename T, typename E>
class Result {
public:
  constexpr explicit Result(const T& value);
  constexpr explicit Result(const E& error);
  Result() = delete;

  constexpr explicit operator bool() const;

  constexpr const T& value() const;
  constexpr const E& error() const;

private:
  constexpr void ensure_checked() const;

  union {
    const T m_value;
    const E m_error;
  };

  const bool m_isError;
  mutable bool m_checked = false;
};

template <typename T, typename E>
constexpr Result<T, E>::Result(const T& value)
    : m_value(value), m_isError(false), m_checked(false) {}

template <typename T, typename E>
constexpr Result<T, E>::Result(const E& error)
    : m_error(error), m_isError(true), m_checked(false) {}

template <typename T, typename E>
inline constexpr Result<T, E>::operator bool() const {
  m_checked = true;
  return (m_isError == false);
}

template <typename T, typename E>
inline constexpr const T& Result<T, E>::value() const {
  assert(m_checked);
  ensure_checked();

  assert(!m_isError);
  return m_value;
}

template <typename T, typename E>
inline constexpr const E& Result<T, E>::error() const {
  assert(m_checked);
  ensure_checked();

  assert(m_isError);
  return m_error;
}

template <typename T, typename E>
inline constexpr void Result<T, E>::ensure_checked() const {
  if (!m_checked) throw ResultNotCheckedError("Result is not checked; call Result::operator bool() before calling accessors.");
}

} // namespace util
} // namespace fig