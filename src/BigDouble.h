#include <utility>

#include "BigInt.h"

class BigDouble {
 public:

  BigDouble() : _num(0), _den(1) {};

  BigDouble(double n) : BigDouble(std::to_string(n)) {};
  BigDouble(BigInt integer) : _num(std::move(integer)), _den(1) {}
  BigDouble(BigInt numerator, BigInt denominator)
	  : _num(std::move(numerator)), _den(std::move(denominator)) { fixup(); };
  explicit BigDouble(const std::string &);

  std::string to_string() const;
  friend std::ostream &operator<<(std::ostream &ostream, const BigDouble &number);

  BigDouble operator+(const BigDouble &other) const;
  BigDouble operator+=(const BigDouble &other);

  BigDouble operator-(const BigDouble &other) const;
  BigDouble operator-=(BigDouble &other);

  BigDouble operator*(const BigDouble &other) const;
  BigDouble operator*=(const BigDouble &other);

  BigDouble operator/(const BigDouble &other) const;
  BigDouble operator/=(const BigDouble &other);

  BigDouble operator%(const BigDouble &other) const;
  BigDouble operator%=(const BigDouble &other);

  BigDouble operator-() const;

  BigInt whole_part() const;
  BigDouble fraction_part() const;
  static BigDouble abs(const BigDouble &n);

  friend bool operator<(const BigDouble &a, const BigDouble &b);
  friend bool operator>(const BigDouble &a, const BigDouble &b);
  friend bool operator==(const BigDouble &a, const BigDouble &b);
  friend bool operator<=(const BigDouble &a, const BigDouble &b);
  friend bool operator>=(const BigDouble &a, const BigDouble &b);
  friend bool operator!=(const BigDouble &a, const BigDouble &b);

  BigInt num() { return _num; }
  BigInt den() { return _den; }

 protected:
  void fixup();
 private:
  BigInt _num;
  BigInt _den;
};