#include "src/BigNums.h"

void init_big_int() {
  std::cout << "====== Init BigInt ======" << std::endl;

  // По умолчанию 0
  BigInt def_zero;
  std::cout << "Default: " << def_zero << std::endl;

  // Через число
  BigInt integer1(123), integer2(-12);
  std::cout << "Int: " << integer1 << " " << integer2 << std::endl;

  // Через строку
  BigInt str1("134567890987654345678901238781927873821");
  BigInt str2("-1123902839218398219839283928193892183");
  std::cout << "Str: " << str1 << " " << str2 << std::endl;
}

void init_big_double() {
  std::cout << "====== Init BigDouble ======" << std::endl;

  // По умолчанию 0
  BigDouble def_zero;
  std::cout << "Default: " << def_zero << std::endl;

  // Через число
  BigDouble d1(10), d2(13.3), d3(-1), d4(-3.9);
  std::cout << "Double: " << d1 << " " << d2 << " " << d3 << " " << d4 << std::endl;

  // Через BigInt
  BigDouble d5(BigInt("1000000000000000000000"));
  std::cout << "BigInt: " << d5 << std::endl;

  // Через обыкновенную дробь (необязательно несократимую)
  BigDouble d6(1, 2), d7(-7, 3);
  std::cout << "Fraction: " << d6 << " " << d7 << std::endl;

  // Через строку
  BigDouble s1("1.3"), s2("1/2"), s3("10000000000000000.000100010001000100010001");
  std::cout << "Str: " << s1 << " " << s2 << " " << s3 << std::endl;
}

void arithmetic_big_int() {
  std::cout << "====== Arithmetic BigInt ======" << std::endl;

  BigInt a("100000000000000000"), b("-1234567890987654");

  std::cout << a << " + " << b << " = " << a + b << std::endl;
  std::cout << a << " - " << b << " = " << a - b << std::endl;
  std::cout << a << " * " << b << " = " << a * b << std::endl;
  std::cout << a << " / " << b << " = " << a / b << std::endl;
  std::cout << a << " % " << b << " = " << a % b << std::endl;
  std::cout << "- " << a << " = " << -a << std::endl;
  std::cout << "|" << a << "| = " << BigInt::abs(b) << std::endl;
  std::cout << "|" << b << "| = " << BigInt::abs(b) << std::endl;

  std::cout << "\na = " << a << "\nb = " << b << std::endl;
  a += b;
  std::cout << "(a+=b): a = " << a << std::endl;
  a *= b;
  std::cout << "(a*=b): a = " << a << std::endl;
  a -= b;
  std::cout << "(a-=b): a = " << a << std::endl;
  a /= b;
  std::cout << "(a/=b): a = " << a << std::endl;

  // Можно умножать на число
  std::cout << "a * 10 = " << a * 10 << std::endl;

  // Или на дробь, но тогда на выходе будет BigDouble
  std::cout << "a * 10.1 = " << a * 10.1 << std::endl;
}

void arithmetic_big_double() {
  std::cout << "====== Arithmetic BigDouble ======" << std::endl;
  BigDouble a("123.13"), b("1.5");

  std::cout << a << " + " << b << " = " << a + b << std::endl;
  std::cout << a << " - " << b << " = " << a - b << std::endl;
  std::cout << a << " * " << b << " = " << a * b << std::endl;
  std::cout << a << " / " << b << " = " << a / b << std::endl;
  std::cout << a << " % " << b << " = " << a % b << std::endl;
  std::cout << "- " << a << " = " << -a << std::endl;
  std::cout << "|" << a << "| = " << BigDouble::abs(b) << std::endl;
  std::cout << "|" << b << "| = " << BigDouble::abs(b) << std::endl;

  std::cout << "\na = " << a << "\nb = " << b << std::endl;
  a += b;
  std::cout << "(a+=b): a = " << a << std::endl;
  a *= b;
  std::cout << "(a*=b): a = " << a << std::endl;
  a -= b;
  std::cout << "(a-=b): a = " << a << std::endl;
  a /= b;
  std::cout << "(a/=b): a = " << a << std::endl;

  // Можно выполнять аналогично с числами, дробями и BigInt
  std::cout << "a + 10.1 = " << a + 10.1 << std::endl;
  std::cout << "10 - a = " << 10 - a << std::endl;
  std::cout << "a + 100" << a + BigInt(100) << std::endl;
}

void compares() {
  std::cout << "====== Compare ======" << std::endl;
  BigInt a(123);
  BigDouble b(150.5);

  // Можно сравнивать BigInt, BigDouble, int, double
  std::cout << a << " < " << b << " = " << (a < b ? "True" : "False") << std::endl;
  std::cout << a << " > " << b << " = " << (a > b ? "True" : "False") << std::endl;
  std::cout << a << " <= " << b << " = " << (a <= b ? "True" : "False") << std::endl;
  std::cout << a << " >= " << b << " = " << (a >= b ? "True" : "False") << std::endl;
  std::cout << a << " == " << b << " = " << (a == b ? "True" : "False") << std::endl;
  std::cout << a << " != " << b << " = " << (a != b ? "True" : "False") << std::endl;
  std::cout << a << " < 10" << " = " << (a < 10 ? "True" : "False") << std::endl;
  std::cout << b << " > 10." << " = " << (b > 10. ? "True" : "False") << std::endl;
  std::cout << a << " < 10." << " = " << (a < 10. ? "True" : "False") << std::endl;
}

void other() {
  std::cout << "====== Other ======" << std::endl;

  // Наибольший общий делитель
  BigInt a(123), b(15);
  std::cout << "gcd(" << a << ", " << b << ") = " << BigInt::gcd(a, b) << std::endl;

  // Преобразование к строке
  std::cout << '"' << BigInt("2132131").to_string() << '"' << std::endl;
  std::cout << '"' << BigDouble("2/3").to_string() << '"' << std::endl;

  // Дробь в виде простой дроби
  BigDouble f("1/2");
  std::cout << f << " = " << f.num() << "/" << f.den() << std::endl;
}

int main() {
  init_big_int();
  init_big_double();
  arithmetic_big_int();
  arithmetic_big_double();
  compares();
  other();
  return 0;
}
