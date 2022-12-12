#include "../BigDouble.h"

BigDouble operator+(const BigDouble &a, const BigDouble &b) {
  BigDouble result;
  result._num = a._num * b._den + b._num * a._den;
  result._den = a._den * b._den;
  result.fixup();
  return result;
}
BigDouble operator-(const BigDouble &a, const BigDouble &b) {
  BigDouble result;
  result._num = a._num * b._den - b._num * a._den;
  result._den = a._den * b._den;
  result.fixup();
  return result;
}
BigDouble operator*(const BigDouble &a, const BigDouble &b) {
  BigDouble result;
  result._num = a._num * b._num;
  result._den = a._den * b._den;
  result.fixup();
  return result;
}
BigDouble operator/(const BigDouble &a, const BigDouble &b) {
  BigDouble result;
  result._num = a._num * b._den;
  result._den = a._den * b._num;
  result.fixup();
  return result;
}
BigDouble operator%(const BigDouble &a, const BigDouble &b) {
  BigDouble div_result = a / b;
  return div_result.fraction_part();
}
BigDouble BigDouble::operator-() const {
  BigDouble result(-_num, _den);
  return result;
}

BigDouble BigDouble::operator+=(const BigDouble &other) {
  return *this = *this + other;
}
BigDouble BigDouble::operator-=(const BigDouble &other) {
  return *this = *this - other;
}
BigDouble BigDouble::operator*=(const BigDouble &other) {
  return *this = *this * other;
}
BigDouble BigDouble::operator/=(const BigDouble &other) {
  return *this = *this / other;
}
BigDouble BigDouble::operator%=(const BigDouble &other) {
  return *this = *this % other;
}

BigDouble BigDouble::abs(const BigDouble &n) {
  BigDouble result(BigInt::abs(n._num), n._den);
  return result;
}