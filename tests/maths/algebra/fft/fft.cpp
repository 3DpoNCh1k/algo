#include <iostream>
#include <vector>

#include <algo/maths/algebra/fft.hpp>
#include <algo/utils/debug.hpp>

// NOLINTBEGIN
using ld = long double;
using clx = std::complex<ld>;
// NOLINTEND

struct Number {
  std::vector<clx> coefs;
  int sign = 1;

  void Normalize() {
    for (int i = 0; i < coefs.size() - 1; ++i) {
      int value = coefs[i].real() + 0.5;
      coefs[i + 1] += value / 10;
      coefs[i] = value % 10;
    }
  }

  std::string ToString() {
    std::string s;
    if (sign == -1) {
      s.push_back('-');
    }
    int start = coefs.size() - 1;
    while (start >= 0 && int(coefs[start].real()) == 0) {
      start--;
    }
    for (int i = start; i >= 0; --i) {
      int value = coefs[i].real();
      assert(value >= 0 && value <= 9);
      s.push_back('0' + value);
    }
    if (start == -1) {
      return "0";
    }
    return s;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string first, second;
  std::cin >> first >> second;

  auto get_number = [](std::string const& s) {
    auto number = Number();
    int start = 0;
    if (s[0] == '-') {
      number.sign = -1;
      start = 1;
    }
    number.coefs.resize(algo::maths::algebra::FFT::mxN);
    for (int i = s.size() - 1; i >= start; --i) {
      int j = s.size() - 1 - i;
      number.coefs[j] = s[i] - '0';
    }
    return number;
  };

  auto first_number = get_number(first);
  auto second_number = get_number(second);

  auto fft = algo::maths::algebra::FFT();

  std::vector<clx> first_values(fft.mxN);
  std::vector<clx> second_values(fft.mxN);

  fft.DoFFT(first_values, first_number.coefs);
  fft.DoFFT(second_values, second_number.coefs);

  std::vector<clx> result_values(fft.mxN);
  for (int i = 0; i < result_values.size(); ++i) {
    result_values[i] = first_values[i] * second_values[i];
  }

  auto result_number = Number();
  result_number.coefs.resize(fft.mxN);
  result_number.sign = first_number.sign * second_number.sign;
  fft.DoInverseFFT(result_number.coefs, result_values);

  result_number.Normalize();
  std::cout << result_number.ToString() << std::endl;
}
