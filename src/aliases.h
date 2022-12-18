#ifndef BIGNUM_SRC_ALIASES_
#define BIGNUM_SRC_ALIASES_

#include "BigDouble.h"

bool operator<(const BigInt& a, double b) {
  return BigDouble(a) < BigDouble(b);
}
bool operator<(double a, const BigInt& b) {
  return BigDouble(a) < BigDouble(b);
}

bool operator>(const BigInt& a, double b) {
  return BigDouble(a) > BigDouble(b);
}
bool operator>(double a, const BigInt& b) {
  return BigDouble(a) > BigDouble(b);
}

bool operator<=(const BigInt& a, double b) {
  return BigDouble(a) <= BigDouble(b);
}
bool operator<=(double a, const BigInt& b) {
  return BigDouble(a) <= BigDouble(b);
}

bool operator>=(const BigInt& a, double b) {
  return BigDouble(a) >= BigDouble(b);
}
bool operator>=(double a, const BigInt& b) {
  return BigDouble(a) >= BigDouble(b);
}

bool operator==(const BigInt& a, double b) {
  return BigDouble(a) == BigDouble(b);
}
bool operator==(double a, const BigInt& b) {
  return BigDouble(a) == BigDouble(b);
}

bool operator!=(const BigInt& a, double b) {
  return BigDouble(a) != BigDouble(b);
}
bool operator!=(double a, const BigInt& b) {
  return BigDouble(a) != BigDouble(b);
}

BigDouble operator+(const BigInt& a, double b) {
  return BigDouble(a) + BigDouble(b);
}
BigDouble operator+(double a, const BigInt& b) {
  return BigDouble(a) + BigDouble(b);
}

BigDouble operator-(const BigInt& a, double b) {
  return BigDouble(a) - BigDouble(b);
}
BigDouble operator-(double a, const BigInt& b) {
  return BigDouble(a) - BigDouble(b);
}

BigDouble operator*(const BigInt& a, double b) {
  return BigDouble(a) * BigDouble(b);
}
BigDouble operator*(double a, const BigInt& b) {
  return BigDouble(a) * BigDouble(b);
}

BigDouble operator/(const BigInt& a, double b) {
  return BigDouble(a) / BigDouble(b);
}
BigDouble operator/(double a, const BigInt& b) {
  return BigDouble(a) / BigDouble(b);
}

BigDouble operator%(const BigInt& a, double b) {
  return BigDouble(a) % BigDouble(b);
}
BigDouble operator%(double a, const BigInt& b) {
  return BigDouble(a) % BigDouble(b);
}

#endif