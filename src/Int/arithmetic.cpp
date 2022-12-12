#include "../BigInt.h"

BigInt BigInt::operator+(const BigInt &other) const {
  if (!this->_negative && other._negative) {
	return *this - -other;
  }

  if (this->_negative && !other._negative) {
	return other - -*this;
  }

  lnum res_digits(this->_digits.size());
  std::copy(this->_digits.begin(), this->_digits.end(), res_digits.begin());

  int carry = 0;
  for (size_t i = 0; i < std::max(this->_digits.size(), other._digits.size()) || carry; ++i) {
	if (i == this->_digits.size()) res_digits.push_back(0);

	res_digits[i] += carry + (i < other._digits.size() ? other._digits[i] : 0);
	carry = res_digits[i] >= BigInt::BASE;
	if (carry) res_digits[i] -= BigInt::BASE;
  }

  BigInt r(res_digits, _negative);
  return r;
}
BigInt BigInt::operator+=(const BigInt &other) {
  return *this = *this + other;
}

// TODO: fixup result
BigInt BigInt::operator-(const BigInt &other) const {
  if (!this->_negative && other._negative) {
	return *this + -other;
  }
  if (this->_negative && !other._negative) {
	BigInt tmp = -*this + other;
	tmp._negative = true;
	return tmp;
  }

  if (abs(*this) < abs(other)) {
	BigInt result = (abs(other) - abs(*this));
	result._negative = !this->_negative;
	return result;
  }

  lnum res_digits(this->_digits.size());
  std::copy(this->_digits.begin(), this->_digits.end(), res_digits.begin());

  int carry = 0;
  for (size_t i = 0; i < other._digits.size() || carry; ++i) {
	res_digits[i] -= carry + (i < other._digits.size() ? other._digits[i] : 0);
	carry = res_digits[i] < 0;
	if (carry) res_digits[i] += BASE;
  }

  BigInt result(res_digits, _negative);
  result.fixup();
  return result;
}
BigInt BigInt::operator-=(const BigInt &other) {
  return *this = *this - other;
}

BigInt BigInt::operator*(const BigInt &other) const {
  lnum res_digits(this->_digits.size() + other._digits.size());
  for (size_t i = 0; i < this->_digits.size(); ++i)
	for (int j = 0, carry = 0; j < (int)other._digits.size() || carry; ++j) {
	  long long cur =
		  res_digits[i + j] + this->_digits[i] * 1ll * (j < (int)other._digits.size() ? other._digits[j] : 0) + carry;
	  res_digits[i + j] = int(cur % BASE);
	  carry = int(cur / BASE);
	}

  while (res_digits.size() > 1 && res_digits.back() == 0)
	res_digits.pop_back();
  BigInt result(res_digits, !(res_digits.size() == 1 && res_digits[0] == 0) && (_negative ^ other._negative));
  return result;
}
BigInt BigInt::operator*=(const BigInt &other) {
  return *this = *this * other;
}

BigInt BigInt::operator/(const BigInt &other) const {
  return div_mod(other).first;
}
BigInt BigInt::operator/=(const BigInt &other) {
  return *this = *this / other;
}

BigInt BigInt::operator%(const BigInt &other) const {
  return div_mod(other).second;
}
BigInt BigInt::operator%=(const BigInt &other) {
  return *this = *this % other;
}

BigInt BigInt::operator-() const {
  if (*this == 0) return 0;
  BigInt result = BigInt(this->_digits, !this->_negative);
  return result;
}

std::pair<BigInt, BigInt> BigInt::div_mod(const BigInt &other) const {
  if (other == 0) {
	throw std::runtime_error("Zero is specified as the divisor.");
  }

  if (other._digits.size() == 1) {
	// Алгоритм деления большого на маленькое
	BigInt div_res;
	div_res._negative = this->_negative ^ other._negative;
	div_res._digits.resize(this->_digits.size());
	std::copy(this->_digits.begin(), this->_digits.end(), div_res._digits.begin());

	int number_second_integer = other._digits.front();
	long long in_mind = 0;
	long long composition;
	for (long long i = 0; i < div_res._digits.size(); i = i + 1) {
	  composition = (long long)div_res._digits[i] + in_mind * (long long)BASE;
	  in_mind = composition % number_second_integer;
	  div_res._digits[i] = (int)(composition / number_second_integer);
	}

	div_res.fixup();
	std::pair<BigInt, BigInt> result(div_res, in_mind);

	return result;
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
