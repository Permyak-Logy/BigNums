#include "src/BigDouble.h"
#include "src/utils.cpp"

int main() {
  std::string inp1, inp2;
  std::cin >> inp1 >> inp2;
  BigDouble a(inp1), b(inp2);

  std::cout << a << " + " << b << " = " << a + b << std::endl;
  std::cout << a << " - " << b << " = " << a - b << std::endl;
  std::cout << a << " * " << b << " = " << a * b << std::endl;
  if (b != 0)
	std::cout << a << " / " << b << " = " << a / b << std::endl;

  return 0;
}
