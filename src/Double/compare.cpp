#include "../BigDouble.h"

bool operator<(const BigDouble& a, const BigDouble& b) {
  return a._num * b._den < b._num * a._den;
}

bool operator>(const BigDouble& a, const BigDouble& b) {
  return !(a < b);
}

bool operator==(const BigDouble& a, const BigDouble& b) {
  return a._num == b._num && a._den == b._den;
}

bool operator<=(const BigDouble& a, const BigDouble& b) {
  return (a < b) || a == b;
}

bool operator>=(const BigDouble& a, const BigDouble& b) {
  return !(a < b) || a == b;
}

bool operator!=(const BigDouble& a, const BigDouble& b) {
  return !(a == b);
}
