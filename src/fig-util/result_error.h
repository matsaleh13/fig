#pragma once

#include <stdexcept>

namespace fig {
namespace util {

class ResultNotCheckedError : public std::runtime_error {
public:
  explicit ResultNotCheckedError(const std::string& what_arg) : runtime_error(what_arg) {}
  explicit ResultNotCheckedError(const char* what_arg) : runtime_error(what_arg) {}
};

} // namespace util
} // namespace fig