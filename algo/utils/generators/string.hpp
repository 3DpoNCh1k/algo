#pragma once

#include <string>

#include <algo/utils/generators/random.hpp>

namespace algo::utils::generators {

namespace details {
struct StringGenerator {
  RandomGenerator& random;
  explicit StringGenerator(RandomGenerator& random, char from, char to)
      : random(random),
        from_(from),
        to_(to) {
  }

  std::string Get(int len) {
    std::string s;
    for (int i = 0; i < len; ++i) {
      s.push_back(random.GetChar(from_, to_));
    }
    return s;
  }

 private:
  char from_, to_;
};

}  // namespace details

struct StringGenerator {
  virtual std::string Get(int len) = 0;
};

struct AsciiStringGenerator : StringGenerator {
  explicit AsciiStringGenerator(RandomGenerator& random)
      : generator_(random, 0, char(255)) {
  }

  std::string Get(int len) override {
    return generator_.Get(len);
  }

 private:
  details::StringGenerator generator_;
};

struct AsciiLowercaseStringGenerator : StringGenerator {
  explicit AsciiLowercaseStringGenerator(RandomGenerator& random)
      : generator_(random, 97, 122) {
  }

  std::string Get(int len) override {
    return generator_.Get(len);
  }

 private:
  details::StringGenerator generator_;
};

struct AsciiUppercaseStringGenerator : StringGenerator {
  explicit AsciiUppercaseStringGenerator(RandomGenerator& random)
      : generator_(random, 65, 90) {
  }

  std::string Get(int len) override {
    return generator_.Get(len);
  }

 private:
  details::StringGenerator generator_;
};

}  // namespace algo::utils::generators
