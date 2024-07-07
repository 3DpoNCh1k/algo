#pragma once

#include <string>

struct Dummy {};

struct DummyWithToString {
  std::string ToString() const {
    return "I'm DummyWithToString!";
  }
};
