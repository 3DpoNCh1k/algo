#pragma once

#include <string>

struct MoveOnly {
  MoveOnly() = default;

  MoveOnly(MoveOnly&& that) = default;
  MoveOnly(const MoveOnly& that) = delete;

  MoveOnly& operator=(const MoveOnly& that) = delete;
  MoveOnly& operator=(MoveOnly&& that) = delete;
};

struct MoveOnlyWithToString : MoveOnly {
  std::string ToString() const {
    return "I'm MoveOnlyWithToString!";
  }
};
