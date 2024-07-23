#pragma once

#include <string>

#include <algo/utils/generators/random.hpp>

namespace algo::utils::generators {

namespace details {
struct StringGenerator {
  RandomGenerator& random;
  char from, to;
  explicit StringGenerator(RandomGenerator& random, char from, char to)
      : random(random),
        from(from),
        to(to) {
  }

  std::string Get(int len) {
    std::string s;
    for (int i = 0; i < len; ++i) {
      s.push_back(random.GetChar(from, to));
    }
    return s;
  }
};

}  // namespace details

struct StringGenerator {
  virtual std::string Get(int len) = 0;
};

struct AsciiStringGenerator : StringGenerator {
  details::StringGenerator generator;
  explicit AsciiStringGenerator(RandomGenerator& random)
      : generator(random, 0, char(255)) {
  }

  std::string Get(int len) override {
    return generator.Get(len);
  }
};

struct AsciiLowercaseStringGenerator : StringGenerator {
  details::StringGenerator generator;
  explicit AsciiLowercaseStringGenerator(RandomGenerator& random)
      : generator(random, 97, 122) {
  }

  std::string Get(int len) override {
    return generator.Get(len);
  }
};

struct AsciiUppercaseStringGenerator : StringGenerator {
  details::StringGenerator generator;
  explicit AsciiUppercaseStringGenerator(RandomGenerator& random)
      : generator(random, 65, 90) {
  }

  std::string Get(int len) override {
    return generator.Get(len);
  }
};

}  // namespace algo::utils::generators
