#ifndef BIGNUM_SRC_ALIASES_
#define BIGNUM_SRC_ALIASES_

#include "BigDouble.h"

#define COMP(R, P) bool operator R P {return BigDouble(a) R BigDouble(b);}
#define COMPS(R) COMP(R, (const BigInt& a, double b)) COMP(R, (double b, const BigInt& a))
#define FUNC(R, P) BigDouble operator R P {return BigDouble(a) R BigDouble(b);}
#define FUNCS(R) FUNC(R, (const BigInt& a, double b)) FUNC(R, (double b, const BigInt& a))

COMPS(<)
COMPS(>)
COMPS(<=)
COMPS(>=)
COMPS(==)
COMPS(!=)

FUNCS(+)
FUNCS(-)
FUNCS(*)
FUNCS(/)
FUNCS(%)

#endif