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


		Vector2 operator+(Vector2& vec) {

			Vector2 vector = { x + vec.x, y + vec.y };
			return vector;
		}

		Vector2 operator-(Vector2& vec) {

			Vector2 vector = { x - vec.x, y - vec.y };
			return vector;
		}
	};


class OwnMathFuncs
{
public:
	
	static void normalize(Vector2 &vec);
	static float magnitude(Vector2 &vec);

	static Vector2 getNormalize(Vector2& vec);
};

}
