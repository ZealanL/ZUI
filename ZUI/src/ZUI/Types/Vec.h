// A 2D vector class

#pragma once
#include "../Framework.h"

namespace ZUI {
	// A type representing a 2D floating-point vector
	struct Vec {
		float x, y;

		Vec() {
			x = y = 0;
		}

		Vec(float x, float y) { this->x = x; this->y = y; }

		Vec(float both) {
			this->x = both;
			this->y = both;
		}

		bool IsZero() const {
			return x == y == 0;
		}

		float Length() const {
			return std::sqrtf(x * x + y * y);
		}

		float LengthSqr() const {
			return x * x + y * y;
		}

		float Distance(Vec other) const {
			float dx = x - other.x;
			float dy = y - other.y;
			return std::sqrtf(dx * dx + dy * dy);
		}

		float DistanceSqr(Vec other) const {
			float dx = x - other.x;
			float dy = y - other.y;
			return dx * dx + dy * dy;
		}

		Vec Rotate(float radians) const {
			float c = cosf(radians), s = sinf(radians);
			return Vec(c * x - s * y, s * x + c * y);
		}

		Vec Rounded() const {
			return Vec(roundf(x), roundf(y));
		}

		Vec Floored() const {
			return Vec(floorf(x), floorf(y));
		}

		string ToString(bool asInts = false) {
			return ZUI_FMT(asInts ? "[%i, %i]" : "[%f, %f]", x, y);
		}

#pragma region Operator Overloads

		// This macro is needed for indirection, otherwise intellisense very gets confused
#define MAKE_VEC_OP_SIG(ret, op) ret operator op

#define MAKE_VEC_OP_VEC(op) \
	MAKE_VEC_OP_SIG(Vec, op)(Vec other) const	{ return Vec(this->x op other.x, this->y op other.y); }  \
	MAKE_VEC_OP_SIG(Vec, op=)(Vec other)		{ *this = *this op other; return *this; }

#define MAKE_VEC_OP_FLOAT(op) \
	MAKE_VEC_OP_SIG(Vec, op)(float val) const	{ return Vec(this->x op val, this->y op val); }  \
	MAKE_VEC_OP_SIG(friend Vec, op=)(float val, const Vec& vec)	{ return Vec(val op vec.x, val op vec.y); } \
	MAKE_VEC_OP_SIG(Vec, op=)(float val)		{ *this = *this op val; return *this; } \

		MAKE_VEC_OP_VEC(+); MAKE_VEC_OP_VEC(-); MAKE_VEC_OP_VEC(*); MAKE_VEC_OP_VEC(/ );
		MAKE_VEC_OP_FLOAT(+); MAKE_VEC_OP_FLOAT(-); MAKE_VEC_OP_FLOAT(*); MAKE_VEC_OP_FLOAT(/ );

#undef MAKE_VEC_OP_VEC
#undef MAKE_VEC_OP_FLOAT
#undef MAKE_VEC_OP_SIG

		bool operator ==(Vec other)		const { return x == other.x && y == other.y; }
		bool operator >(Vec other)		const { return x > other.x && y > other.y; }
		bool operator <(Vec other)		const { return other > *this; }
		bool operator >=(Vec other)		const { return *this > other || *this == other; }
		bool operator <=(Vec other)		const { return *this < other || *this == other; }

		Vec operator-() {
			return Vec(-x, -y);
		}
#pragma endregion
	};
}