#include "../BigInt.h"

bool operator<(const BigInt &a, const BigInt &b) {
  if (a._negative != b._negative)
	return a._negative;

  if (a._digits.size() != b._digits.size())
	return (a._digits.size() < b._digits.size()) ^ a._negative;

  for (size_t i = a._digits.size(); i > 0; --i)
	if (a._digits[i - 1] != b._digits[i - 1])
	  return (a._digits[i - 1] < b._digits[i - 1]) ^ a._negative;

  return false;
}

bool operator>(const BigInt &a, const BigInt &b) {
  return !(a < b);
}

bool operator==(const BigInt &a, const BigInt &b) {
  if (a._negative != b._negative) return false;
  if (a._digits.size() != b._digits.size()) return false;
  for (size_t i = 0; i < a._digits.size(); ++i) {
	if (a._digits[i] != b._digits[i]) return false;
  }
  return true;
}

bool operator<=(const BigInt &a, const BigInt &b) {
  return (a < b) || a == b;
}

bool operator>=(const BigInt &a, const BigInt &b) {
  return !(a < b) || a == b;
}

bool operator!=(const BigInt &a, const BigInt &b) {
  return !(a == b);
}
