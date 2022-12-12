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
BigInt &BigInt::operator=(const BigInt &other) {
  _digits.resize(other._digits.size());
  std::copy(other._digits.begin(), other._digits.end(), _digits.begin());
  _negative = other._negative;
  return *this;
}

void BigInt::fixup() {
  while (_digits.size() > 1 && _digits.back() == 0) _digits.pop_back();

  if (_digits.size() == 1 && _digits[0] == 0) _negative = false;
}