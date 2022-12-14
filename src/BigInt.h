#ifndef BIGNUM_SCR_BIG_INT_H_
#define BIGNUM_SCR_BIG_INT_H_

#include <string>
#include <vector>
#include <utility>
#include <iostream>

typedef std::vector<int> digits_t;

class BigInt {
 public:

  BigInt() : BigInt(0ull) {};

  BigInt(int n) : BigInt((long long)n) {}; // NOLINT(google-explicit-constructor)
  BigInt(unsigned int n) : BigInt((unsigned long long)n) {}; // NOLINT(google-explicit-constructor)
  BigInt(long long n); // NOLINT(google-explicit-constructor)
  BigInt(unsigned long long n); // NOLINT(google-explicit-constructor)

  explicit BigInt(const std::string &s);
  BigInt(digits_t n, bool negative) : _digits(std::move(n)), _negative(negative) {};

  [[nodiscard]] std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &ostream, const BigInt &number);
  BigInt &operator=(const BigInt &other);

  friend BigInt operator+(const BigInt &a, const BigInt &b);
  friend BigInt operator-(const BigInt &a, const BigInt &b);
  friend BigInt operator*(const BigInt &a, const BigInt &b);
  friend BigInt operator/(const BigInt &a, const BigInt &b);
  friend BigInt operator%(const BigInt &a, const BigInt &b);
  BigInt operator-() const;

  friend BigInt &operator+=(BigInt &a, const BigInt &b);
  friend BigInt &operator-=(BigInt &a, const BigInt &b);
  friend BigInt &operator*=(BigInt &a, const BigInt &b);
  friend BigInt &operator/=(BigInt &a, const BigInt &b);
  friend BigInt &operator%=(BigInt &a, const BigInt &b);

  [[nodiscard]] std::pair<BigInt, BigInt> div_mod(const BigInt &other) const;
  static BigInt abs(const BigInt &n);
  static BigInt gcd(const BigInt &a, const BigInt &b);

  friend bool operator<(const BigInt &a, const BigInt &b);
  friend bool operator>(const BigInt &a, const BigInt &b);
  friend bool operator==(const BigInt &a, const BigInt &b);
  friend bool operator<=(const BigInt &a, const BigInt &b);
  friend bool operator>=(const BigInt &a, const BigInt &b);
  friend bool operator!=(const BigInt &a, const BigInt &b);

 protected:
  void _shift_right();
  void fixup();

 private:
  static const int BASE = 1000 * 1000 * 1000;
  static const int BASE_LENGTH = 9;

  digits_t _digits;
  bool _negative = false;
};

#endif
