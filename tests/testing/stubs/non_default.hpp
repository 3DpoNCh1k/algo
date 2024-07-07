#pragma once

struct NonDefault {
  template<typename T>
  explicit NonDefault(T&&) {}
};
