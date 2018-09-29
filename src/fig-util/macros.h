#pragma once

#include <string>
#include "string_helpers.h"
#include "error.h"


// #define FORMAT_STRING(msg, ...) \
//   (fig::util::string_format(msg, __VA_OPT__(,) __VA_ARGS__));

#define FORMAT_STRING(msg, ...) \
  (fig::util::string_format(msg, __VA_ARGS__))

// #define FIG_ERROR(msg, ...) \
//   (fig::util::Error(FORMAT_STRING(msg, __VA_OPT__(,) __VA_ARGS__), __FILE__, __LINE__));

#define FIG_ERROR(msg, ...) \
  (fig::util::Error(FORMAT_STRING(msg, __VA_ARGS__), __FILE__, __LINE__))