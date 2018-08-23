#include "OwnMathFuncs.h"
#include <iostream>

void OwnMathFuncs::OwnMathFuncs::normalize(Vector2 & vec)
{
	double magnitude = sqrt(pow(vec.x,2) + pow(vec.y,2));

	if (magnitude != 0) {
		vec.x /= magnitude;
		vec.y /= magnitude;
	}

}
