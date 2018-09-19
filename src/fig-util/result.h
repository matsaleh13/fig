#pragma once

namespace fig {
namespace util {

template <typename T, typename E>
class Result {
public:
  Result(const T& value);
  Result(const E& error);
  explicit operator bool() const;

  const T& value() const;
  const E& error() const;

private:
  union {
    T m_value;
    E m_error;
  } m_data;

  bool m_isError = false;
};

template <typename T, typename E>
Result<T, E>::Result(const T& value) : m_data{value}, m_isError(false) {}

template <typename T, typename E>
Result<T, E>::Result(const E& error) : m_data{error}, m_isError(true) {}

template <typename T, typename E>
inline Result<T,E>::operator bool() const
{
  return (m_isError == false);
}

template <typename T, typename E>
inline const T& Result<T, E>::value() const {
  return m_data.m_value;
}

template <typename T, typename E>
inline const E& Result<T, E>::error() const {
  return m_data.m_error;
}

} // namespace util
} // namespace fig