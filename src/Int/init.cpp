#include "../BigInt.h"

BigInt::BigInt(long long n) {
  _digits.clear();
  if (n < 0) {
	_negative = true;
	n = -n;
  } else {
	_negative = false;
  }

  do {
	_digits.push_back((int)(n % BASE));
	n /= BASE;
  } while (n);
}

BigInt::BigInt(unsigned long long n) {
  _digits.clear();
  _negative = false;
  do {
	_digits.push_back((int)(n % BASE));
	n /= BASE;
  } while (n);
}

BigInt::BigInt(const std::string &s) {
  if (s.empty() or (s.size() == 1 and s[0] == '-'))
	throw std::runtime_error("String does not contain a number.");
  for (size_t i = 1; i < s.size(); ++i)
	if (s[i] < '0' || '9' < s[i])
	  throw std::runtime_error("String does not contain a integer.");
  _digits.clear();
  _negative = s[0] == '-';
  for (int i = (int)s.length(); i > _negative; i -= BASE_LENGTH)
	if (i < BASE_LENGTH)
	  _digits.push_back(std::stoi(s.substr(_negative, i - _negative)));
	else
	  _digits.push_back(std::stoi(s.substr(i - BASE_LENGTH, BASE_LENGTH)));
  fixup();
}
