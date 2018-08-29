#include "OwnMathFuncs.h"
#include <iostream>

void OwnMathFuncs::OwnMathFuncs::normalize(Vector2 & vec)
{
	double magnitude = OwnMathFuncs::magnitude(vec);

	if (magnitude != 0) {
		vec.x /= magnitude;
		vec.y /= magnitude;
	}

}

float OwnMathFuncs::OwnMathFuncs::magnitude(Vector2 &vec)
{
	return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}
