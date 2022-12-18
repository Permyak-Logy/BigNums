#ifndef BIGNUM_SRC_BIG_DOUBLE_H_
#define BIGNUM_SRC_BIG_DOUBLE_H_

#include <utility>
#include "BigInt.h"

class BigDouble {
 public:

  BigDouble() : _num(0ull), _den(1ull) {};

  BigDouble(double n) : BigDouble(std::to_string(n)) {}; // NOLINT(google-explicit-constructor)
  BigDouble(const BigInt& integer) : _num(integer), _den(1ull) {} // NOLINT(google-explicit-constructor)
  BigDouble(const BigInt& numerator, const BigInt& denominator)
	  : _num(numerator), _den(denominator) { fixup(); };
  explicit BigDouble(const std::string&);

  [[nodiscard]] std::string to_string() const;
  friend std::ostream& operator<<(std::ostream& ostream, const BigDouble& number);

  friend BigDouble operator+(const BigDouble& a, const BigDouble& b);
  friend BigDouble operator-(const BigDouble& a, const BigDouble& b);
  friend BigDouble operator*(const BigDouble& a, const BigDouble& b);
  friend BigDouble operator/(const BigDouble& a, const BigDouble& b);
  friend BigDouble operator%(const BigDouble& a, const BigDouble& b);
  BigDouble operator-() const;

  BigDouble& operator++();
  BigDouble operator++(int);
  BigDouble& operator--();
  BigDouble operator--(int);

  BigDouble& operator+=(const BigDouble& other);
  BigDouble& operator-=(const BigDouble& other);
  BigDouble& operator*=(const BigDouble& other);
  BigDouble& operator/=(const BigDouble& other);
  BigDouble& operator%=(const BigDouble& other);

  [[nodiscard]] BigInt whole_part() const;
  [[nodiscard]] BigDouble fraction_part() const;
  static BigDouble abs(const BigDouble& n);

  friend bool operator<(const BigDouble& a, const BigDouble& b);
  friend bool operator>(const BigDouble& a, const BigDouble& b);
  friend bool operator==(const BigDouble& a, const BigDouble& b);
  friend bool operator<=(const BigDouble& a, const BigDouble& b);
  friend bool operator>=(const BigDouble& a, const BigDouble& b);
  friend bool operator!=(const BigDouble& a, const BigDouble& b);

  BigInt num() { return _num; }
  BigInt den() { return _den; }

 protected:
  void fixup();
 private:
  BigInt _num;
  BigInt _den;
};
#endif