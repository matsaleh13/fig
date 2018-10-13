#pragma once

#include <functional>
#include <string>

#include "string_helpers.h"

namespace fig {
namespace core {

/**
 * @brief Responsible for describing a unique identifier that supports path-like
 * semantics and unique hashing.
 *
 * NOTE: FigKey names are case-insensitive by default.
 *
 */
template <typename TString = std::string>
class FigKey {
public:
  constexpr explicit FigKey(const TString& name);
  FigKey() = delete;

  constexpr const TString& name() const { return m_name; }

  constexpr bool operator==(const FigKey<TString>& other) const;
  constexpr bool operator<(const FigKey<TString>& other) const;

private:
  TString m_name;
};

template <typename TString>
constexpr FigKey<TString>::FigKey(const TString& name)
    : m_name(fig::util::tolower(name)) {}

template <typename TString>
constexpr bool FigKey<TString>::operator==(const FigKey<TString>& other) const {
  return m_name == other.m_name;
}

template <typename TString>
constexpr bool FigKey<TString>::operator<(const FigKey<TString>& other) const {
  return m_name < other.m_name;
}

} // namespace core
} // namespace fig

namespace std {

template <typename TString>
struct hash<fig::core::FigKey<TString>> {
  size_t operator()(const fig::core::FigKey<TString>& k) const {
    return std::hash<TString>()(k.name());
  }
};

} // namespace std