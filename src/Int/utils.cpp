#include "../BigInt.h"

std::string BigInt::to_string() const {
  std::string result = _negative ? "-" : "";

  result += std::to_string(_digits.empty() ? 0 : _digits.back());
  for (int i = (int)_digits.size() - 2; i >= 0; --i) {
	std::string tmp = std::to_string(_digits[i]);
	for (int j = 0; j < BASE_LENGTH - tmp.size(); ++j) result.append("0");
	result += tmp;
  }
  return result;
}

std::ostream &operator<<(std::ostream &ostream, const BigInt &number) {
  std::string string = number.to_string();
  for (long long i = 0; i < string.size(); i = i + 1) {
	ostream.put(string[i]);
  }
  return ostream;
}

BigInt BigInt::abs(const BigInt &n) {
  BigInt r(n._digits);
  return r;
}

void BigInt::fixup() {
  while (_digits.size() > 1 && _digits.back() == 0) _digits.pop_back();

  if (_digits.size() == 1 && _digits[0] == 0) _negative = false;
}

BigInt BigInt::gcd(BigInt a, BigInt b) {
  a = abs(a);
  b = abs(b);

  while (a != 0 && b != 0) {
	if (a > b) {
	  a %= b;
	} else {
	  b %= a;
	}
  }
  return a + b;
}

void BigInt::_shift_right() {
  if (_digits.empty()) {
	_digits.push_back(0);
	return;
  }
  _digits.push_back(_digits[_digits.size() - 1]);
  for (size_t i = _digits.size() - 2; i > 0; --i)
	_digits[i] = _digits[i - 1];
  _digits[0] = 0;
}