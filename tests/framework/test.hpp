#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace tests::framework::test {
struct ITest {
  virtual std::string Name() const = 0;
  virtual void Run() = 0;
};

using ITestPtr = std::shared_ptr<ITest>;
using TestList = std::vector<ITestPtr>;

static TestList tests;

void AddTest(ITestPtr test) {
  tests.push_back(test);
}
TestList ListAllTests() {
  return tests;
}
};  // namespace tests::framework::test

#define TEST(name)                                                       \
  struct Test##name : tests::framework::test::ITest {                    \
    std::string Name() const override {                                  \
      return #name;                                                      \
    }                                                                    \
    void Run() override;                                                 \
    struct Registrar {                                                   \
      Registrar() {                                                      \
        tests::framework::test::AddTest(std::make_shared<Test##name>()); \
      }                                                                  \
    };                                                                   \
  };                                                                     \
  static Test##name::Registrar test##name##registrar;                    \
  void Test##name::Run()

#define RUN_ALL_TESTS()                                        \
  int main() {                                                 \
    for (auto test : tests::framework::test::ListAllTests()) { \
      std::cout << test->Name() << " is running" << std::endl; \
      test->Run();                                             \
    }                                                          \
  }
