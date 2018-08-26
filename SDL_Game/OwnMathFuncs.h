#pragma once
#include <math.h>

namespace OwnMathFuncs
{
	struct Vector2
	{
		float x;
		float y;

		Vector2(float x, float y) : x(x), y(y) {

		}

	};


class OwnMathFuncs
{
public:
	
	static void normalize(Vector2 &vec);

};

}
