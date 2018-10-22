#pragma once

#include <string>
#include "string_helpers.h"
#include "error.h"


#define FORMAT_STRING(msg, ...) \
  (fig::util::string_format(msg, __VA_ARGS__))

