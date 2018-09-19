#pragma once

namespace fig {
namespace util {

template <typename T, typename E>
class Result {
public:
  explicit Result(const T& value);
  explicit Result(const E& error);
  constexpr explicit operator bool() const;

  constexpr const T& value() const;
  constexpr const E& error() const;

private:
  union {
    const T m_value;
    const E m_error;
  };

  const bool m_isError;
  mutable bool m_checked = false;
};

template <typename T, typename E>
Result<T, E>::Result(const T& value)
    : m_value(value), m_isError(false), m_checked(false) {}

template <typename T, typename E>
Result<T, E>::Result(const E& error)
    : m_error(error), m_isError(true), m_checked(false) {}

template <typename T, typename E>
inline constexpr Result<T, E>::operator bool() const {
  m_checked = true;
  return (m_isError == false);
}

template <typename T, typename E>
inline constexpr const T& Result<T, E>::value() const {
  assert(m_checked);
  assert(!m_isError);
  return m_value;
}

template <typename T, typename E>
inline constexpr const E& Result<T, E>::error() const {
  assert(m_checked);
  assert(m_isError);
  return m_error;
}

} // namespace util
} // namespace fig