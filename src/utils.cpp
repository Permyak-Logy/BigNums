
template<typename T = int>
T pow(const T& x, int n) {
  T result = 1;
  T multi = x;
  while (n) {
	if (n & 1)
	  result *= multi;
	multi *= multi;
	n >>= 1;
  }
  return result;
}