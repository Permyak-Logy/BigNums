#include "../BigInt.h"

BigInt operator+(const BigInt &a, const BigInt &other) { // NOLINT(misc-no-recursion)
  if (!a._negative && other._negative) {
	return a - -other;
  }

  if (a._negative && !other._negative) {
	return other - -a;
  }

  digits_t res_digits(a._digits.size());
  std::copy(a._digits.begin(), a._digits.end(), res_digits.begin());

  int carry = 0;
  for (size_t i = 0; i < std::max(a._digits.size(), other._digits.size()) || carry; ++i) {
	if (i == a._digits.size()) res_digits.push_back(0);

	res_digits[i] += carry + (i < other._digits.size() ? other._digits[i] : 0);
	carry = res_digits[i] >= BigInt::BASE;
	if (carry) res_digits[i] -= BigInt::BASE;
  }

  BigInt r(res_digits, a._negative);
  return r;
}
BigInt operator-(const BigInt &a, const BigInt &other) { // NOLINT(misc-no-recursion)
  if (!a._negative && other._negative) {
	return a + -other;
  }
  if (a._negative && !other._negative) {
	BigInt tmp = -a + other;
	tmp._negative = true;
	return tmp;
  }

  if (BigInt::abs(a) < BigInt::abs(other)) {
	BigInt result = (BigInt::abs(other) - BigInt::abs(a));
	result._negative = !a._negative;
	return result;
  }

  digits_t res_digits(a._digits.size());
  std::copy(a._digits.begin(), a._digits.end(), res_digits.begin());

  int carry = 0;
  for (size_t i = 0; i < other._digits.size() || carry; ++i) {
	res_digits[i] -= carry + (i < other._digits.size() ? other._digits[i] : 0);
	carry = res_digits[i] < 0;
	if (carry) res_digits[i] += BigInt::BASE;
  }

  BigInt result(res_digits, a._negative);
  result.fixup();
  return result;
}
BigInt operator*(const BigInt &a, const BigInt &other) {
  digits_t res_digits(a._digits.size() + other._digits.size());
  for (size_t i = 0; i < a._digits.size(); ++i)
	for (int j = 0, carry = 0; j < (int)other._digits.size() || carry; ++j) {
	  long long cur =
		  res_digits[i + j] + a._digits[i] * 1ll * (j < (int)other._digits.size() ? other._digits[j] : 0) + carry;
	  res_digits[i + j] = int(cur % BigInt::BASE);
	  carry = int(cur / BigInt::BASE);
	}

  while (res_digits.size() > 1 && res_digits.back() == 0)
	res_digits.pop_back();
  BigInt result(res_digits, !(res_digits.size() == 1 && res_digits[0] == 0) && (a._negative ^ other._negative));
  return result;
}
BigInt operator/(const BigInt &a, const BigInt &other) {
  return a.div_mod(other).first;
}
BigInt operator%(const BigInt &a, const BigInt &other) {
  return a.div_mod(other).second;
}
BigInt BigInt::operator-() const {
  if (*this == 0) return 0;
  BigInt result = BigInt(this->_digits, !this->_negative);
  return result;
}

BigInt &operator+=(BigInt &a, const BigInt &other) {
  return a = a + other;
}
BigInt &operator-=(BigInt &a, const BigInt &other) {
  return a = a - other;
}
BigInt &operator*=(BigInt &a, const BigInt &other) {
  return a = a * other;
}
BigInt &operator/=(BigInt &a, const BigInt &other) {
  return a = a / other;
}
BigInt &operator%=(BigInt &a, const BigInt &other) {
  return a = a % other;
}

std::pair<BigInt, BigInt> BigInt::div_mod(const BigInt &other) const {
  if (other == 0) {
	throw std::runtime_error("Zero is specified as the divisor.");
  }

  if (abs(*this) < abs(other)) {
	std::pair<BigInt, BigInt> result(0, (*this < 0) ? *this + other : *this);
	return result;
  }

  BigInt abs_other = abs(other);
  BigInt div_result, remainder;
  div_result._digits.clear();
  remainder._digits.clear();
  div_result._digits.resize(this->_digits.size());
  for (long long i = (long long)(this->_digits.size()) - 1; i >= 0; --i) {
	remainder._shift_right();
	remainder._digits[0] = this->_digits[i];
	remainder.fixup();
	int x = 0, l = 0, r = BASE;
	while (l <= r) {
	  int m = (l + r) / 2;
	  BigInt t = abs_other * m;
	  if (t <= remainder) {
		x = m;
		l = m + 1;
	  } else {
		r = m - 1;
	  }
	}
	div_result._digits[i] = x;
	remainder -= abs_other * x;

  }
  div_result._negative = this->_negative ^ other._negative;
  div_result.fixup();
  std::pair<BigInt, BigInt> result(div_result, remainder);
  return result;
}
BigInt BigInt::abs(const BigInt &n) {
  BigInt result = n;
  result._negative = false;
  return result;
}
BigInt BigInt::gcd(const BigInt& a, const BigInt& b) {
  BigInt a_ = abs(a);
  BigInt b_ = abs(b);

  while (a_ != 0 && b_ != 0) {
	if (a_ > b_) {
	  a_ = a_ % b_;
	} else {
	  b_ = b_ % a_;
	}
  }
  return a_ + b_;
}