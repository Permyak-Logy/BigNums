#include "../BigDouble.h"

BigDouble BigDouble::operator+(const BigDouble &other) const {
  BigDouble result;
  result._num = this->_num * other._den + other._num*this->_den;
  result._den = this->_den * other._den;
  result.fixup();
  return result;
}
BigDouble BigDouble::operator+=(const BigDouble &other) {
  return *this = *this + other;
}

BigDouble BigDouble::operator-(const BigDouble &other) const {
  BigDouble result;
  result._num = this->_num * other._den - other._num*this->_den;
  result._den = this->_den * other._den;
  result.fixup();
  return result;
}
BigDouble BigDouble::operator-=(BigDouble& other) {
  return *this = *this - other;
}

BigDouble BigDouble::operator*(const BigDouble &other) const {
  BigDouble result;
  result._num = this->_num * other._num;
  result._den = this->_den * other._den;
  result.fixup();
  return result;
}
BigDouble BigDouble::operator*=(const BigDouble &other) {
  return *this = *this * other;
}

BigDouble BigDouble::operator/(const BigDouble &other) const {
  BigDouble result;
  result._num = this->_num * other._den;
  result._den = this->_den * other._num;
  result.fixup();
  return result;
}
BigDouble BigDouble::operator/=(const BigDouble &other) {
  return *this = *this / other;
}

BigDouble BigDouble::operator%(const BigDouble &other) const {
  BigDouble div_result = *this / other;
  return div_result.fraction_part();
}
BigDouble BigDouble::operator%=(const BigDouble &other) {
  return *this = *this % other;
}

BigDouble BigDouble::operator-() const {
  BigDouble result(-_num, _den);
  return result;
}
