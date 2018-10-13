#pragma once

#include "result.h"
#include "error.h"

#include <string>

namespace fig {
namespace core {

template <typename TValue>
class FigValue {
public:
  constexpr explicit FigValue(const TValue& value);

  constexpr const TValue& get() const { return m_value; };

  template <typename TRValue>
  constexpr const TRValue& get() const;

private:
  TValue m_value;
};

template <typename TValue, typename TRValue>
constexpr TRValue get() {
  return static_cast<TRValue>(m_value); // hey, it could work.
}

//
// Template specializations of get().
//

template <typename TChar>
template <>
constexpr int get<std::basic_string<TChar>, int>() {
  return std::stoi(m_value);
}

template <typename TChar>
constexpr long get<std::basic_string<TChar>, long>() {
  return std::stol(m_value);
}

template <typename TChar>
constexpr long long get<std::basic_string<TChar>, long long>() {
  return std::stoll(m_value);
}

template <typename TChar>
constexpr unsigned long get<std::basic_string<TChar>, unsigned long>() {
  return std::stoul(m_value);
}

template <typename TChar>
constexpr unsigned long long
get<std::basic_string<TChar>, unsigned long long>() {
  return std::stoull(m_value);
}

template <typename TChar>
constexpr float get<std::basic_string<TChar>, float>() {
  return std::stof(m_value);
}

template <typename TChar>
constexpr double get<std::basic_string<TChar>, double>() {
  return std::stod(m_value);
}

template <typename TChar>
constexpr long double get<std::basic_string<TChar>, long double>() {
  return std::stold(m_value);
}

// Safe error handling version.
template <typename TChar, typename TRValue>
constexpr fig::util::Result<TRValue, fig::util::Error>
get<std::basic_string<TChar>, fig::util::Result<TRValue, fig::util::Error>>() {
  try {
    return get<TRValue>();
  } catch (...) {
    return FIG_ERROR("Invalid conversion of value.");
  }
}

} // namespace core
} // namespace fig