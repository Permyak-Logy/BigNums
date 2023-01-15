#include "BigDouble.h"
#include "utils.cpp"

BigDouble::BigDouble(const std::string& s) {
  size_t index_point = s.find('.');
  size_t index_div = s.find('/');
  if (index_point < s.size()) {
	_num = BigInt(s.substr(0, index_point) +
		s.substr(index_point + 1, s.size() - index_point - 1));

	_den = pow<BigInt>(10, (int)(s.size() - index_point - 1));
  } else if (index_div < s.size()) {
	if (index_point == 0 || index_point == s.size() - 1)
	  throw std::runtime_error("Bad string BigDouble '" + s + "'");
	_num = BigInt(s.substr(0, index_div));
	_den = BigInt(s.substr(index_div + 1, s.size() - index_div - 1));
  } else {
	_num = BigInt(s);
	_den = 1;
  }
  fixup();
}

BigDouble operator+(const BigDouble& a, const BigDouble& b) {
  BigDouble result;
  result._num = a._num * b._den + b._num * a._den;
  result._den = a._den * b._den;
  result.fixup();
  return result;
}
BigDouble operator-(const BigDouble& a, const BigDouble& b) {
  BigDouble result;
  result._num = a._num * b._den - b._num * a._den;
  result._den = a._den * b._den;
  result.fixup();
  return result;
}
BigDouble operator*(const BigDouble& a, const BigDouble& b) {
  BigDouble result;
  result._num = a._num * b._num;
  result._den = a._den * b._den;
  result.fixup();
  return result;
}
BigDouble operator/(const BigDouble& a, const BigDouble& b) {
  BigDouble result;
  result._num = a._num * b._den;
  result._den = a._den * b._num;
  result.fixup();
  return result;
}
BigDouble operator%(const BigDouble& a, const BigDouble& b) {
  BigDouble div_result = a / b;
  return div_result.fraction_part();
}
BigDouble BigDouble::operator-() const {
  BigDouble result(-_num, _den);
  return result;
}

BigDouble& BigDouble::operator++() {
  return (*this += 1);
}
BigDouble BigDouble::operator++(int) {
  *this += 1;
  return *this - 1;
}
BigDouble& BigDouble::operator--() {
  return (*this -= 1);
}
BigDouble BigDouble::operator--(int) {
  *this -= 1;
  return *this + 1;
}

BigDouble& BigDouble::operator+=(const BigDouble& other) {
  return *this = *this + other;
}
BigDouble& BigDouble::operator-=(const BigDouble& other) {
  return *this = *this - other;
}
BigDouble& BigDouble::operator*=(const BigDouble& other) {
  return *this = *this * other;
}
BigDouble& BigDouble::operator/=(const BigDouble& other) {
  return *this = *this / other;
}
BigDouble& BigDouble::operator%=(const BigDouble& other) {
  return *this = *this % other;
}

BigDouble BigDouble::abs(const BigDouble& n) {
  BigDouble result(BigInt::abs(n._num), n._den);
  return result;
}

bool operator<(const BigDouble& a, const BigDouble& b) {
  return a._num * b._den < b._num * a._den;
}
bool operator>(const BigDouble& a, const BigDouble& b) {
  return !(a < b || a == b);
}
bool operator==(const BigDouble& a, const BigDouble& b) {
  return a._num == b._num && a._den == b._den;
}
bool operator<=(const BigDouble& a, const BigDouble& b) {
  return a < b || a == b;
}
bool operator>=(const BigDouble& a, const BigDouble& b) {
  return !(a < b) || a == b;
}
bool operator!=(const BigDouble& a, const BigDouble& b) {
  return !(a == b);
}

std::string BigDouble::to_string() const {
  BigDouble fraction = abs(fraction_part());

  if (fraction == 0) return whole_part().to_string();

  // Составляем историю деления, а также пытаемся найти период.
  typedef std::pair<BigInt, BigInt> res_rem;
  BigInt reminder = fraction.num() * 10, div = fraction.den();
  std::vector<res_rem> history;
  size_t period_index = -1;
  while (true) {
	res_rem act(reminder / div, reminder);
	for (size_t i = 0; i < history.size(); ++i)
	  if (history[i].first == act.first && history[i].second == act.second) {
		period_index = i;
		break;
	  }
	if (period_index != -1) break;
	history.push_back(act);
	reminder = (reminder % div) * 10;
  }

  // Целая часть
  std::string str_whole = whole_part().to_string();

  // Дробная непериодическая часть
  std::string str_fraction;
  for (size_t i = 0; i < std::min(period_index, history.size()); ++i)
	str_fraction += history[i].first.to_string();

  // Период
  std::string str_period;
  for (size_t i = period_index; i < history.size(); ++i) {
	str_period += history[i].first.to_string();
  }

  // Сборка
  std::string result = str_whole + "." + str_fraction;
  if (str_period != "0") result += "(" + str_period + ")";
  return result;
}

std::ostream& operator<<(std::ostream& ostream, const BigDouble& number) {
  std::string string = number.to_string();
  for (long long i = 0; i < string.size(); i = i + 1) {
	ostream.put(string[i]);
  }
  return ostream;
}

void BigDouble::fixup() {
  if (_num == 0) {
	_den = 1;
  } else if (_den < 0) {
	_num = -_num;
	_den = -_den;
  }

  BigInt gcd = BigInt::gcd(_num, _den);
  _num /= gcd;
  _den /= gcd;
}

BigInt BigDouble::whole_part() const {
  return _num / _den;
}
BigDouble BigDouble::fraction_part() const {
  return *this - whole_part();
}
