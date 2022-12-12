#include "../BigDouble.h"
#include "../utils.cpp"

BigDouble::BigDouble(const std::string &s) {
  size_t index_point = s.find('.');
  size_t index_div = s.find('/');
  if (index_point < s.size()) {
	_num = BigInt(s.substr(0, index_point) +
		s.substr(index_point + 1, s.size() - index_point - 1));

	_den = pow<BigInt>(10, (int)(s.size() - index_point - 1));
  } else if (index_div < s.size()) {
	if (index_point == 0 || index_point == s.size() - 1)
	  throw std::runtime_error("Bad string BigDouble '" + s + "'");
	_num = BigInt(s.substr(0, index_div));
	_den = BigInt(s.substr(index_div + 1, s.size() - index_div - 1));
  } else {
	_num = BigInt(s);
	_den = 1;
  }
  fixup();
}
