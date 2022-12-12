#include <string>
#include <vector>
#include <utility>
#include <iostream>

typedef std::vector<int> lnum;

class BigInt {
 public:

  BigInt() : BigInt(0) {};
  BigInt(int n) : BigInt((long long) n) {};
  BigInt(long long n);
  explicit BigInt(const std::string &s);

  explicit BigInt(lnum n) : _digits(std::move(n)), _negative(false) {};
  BigInt(lnum n, bool negative) : _digits(std::move(n)), _negative(negative) {};

  std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &ostream, const BigInt &number);

  BigInt operator+(const BigInt &other) const;
  BigInt operator+=(const BigInt &other);

  BigInt operator-(const BigInt &other) const;
  BigInt operator-=(const BigInt &other);

  BigInt operator*(const BigInt &other) const;
  BigInt operator*=(const BigInt &other);

  BigInt operator/(const BigInt &other) const;
  BigInt operator/=(const BigInt &other);

  BigInt operator%(const BigInt &other) const;
  BigInt operator%=(const BigInt &other);

  BigInt operator-() const;

  static BigInt abs(const BigInt &n);
  static BigInt gcd(BigInt a, BigInt b);

  std::pair<BigInt, BigInt> div_mod(const BigInt &other) const;

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
  lnum _digits;
  bool _negative = false;

};
