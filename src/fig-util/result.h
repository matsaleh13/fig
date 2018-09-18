#pragma once

namespace fig {
namespace util {

template <typename T, typename E>
class Result {
public:
  Result(const T& value) : m_value(value) {}
  Result(const E& error) : m_error(error) {}

  const T& value() const;
  const E& error() const;

private:
    T m_value;
    E m_error;
};

template <typename T, typename E>
inline const T& Result<T, E>::value() const {
  return m_value;
}

template <typename T, typename E>
inline const E& Result<T, E>::error() const {
  return m_error;
}

} // namespace util
} // namespace fig