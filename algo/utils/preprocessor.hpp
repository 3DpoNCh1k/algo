#pragma once

#define AS_SINGLE_ARGUMENT(...) __VA_ARGS__

#define _AS_STRING_EXPANDED(input) #input

#define AS_STRING(input) _AS_STRING_EXPANDED(AS_SINGLE_ARGUMENT(input))

#define _CONCAT_EXPANDED(x, y) x##y
#define CONCAT(x, y) \
  _CONCAT_EXPANDED(AS_SINGLE_ARGUMENT(x), AS_SINGLE_ARGUMENT(y))
