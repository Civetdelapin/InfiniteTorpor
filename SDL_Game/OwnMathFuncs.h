#define _USE_MATH_DEFINES

#pragma once
#include <math.h>
#include <random>


namespace OwnMathFuncs
{
	struct Vector2
	{
		float x;
		float y;

		Vector2(float x, float y) : x(x), y(y) {

		}


		Vector2 operator+(Vector2 vec) {

			Vector2 vector = { x + vec.x, y + vec.y };
			return vector;
		}

		Vector2 operator-(Vector2 vec) {

			Vector2 vector = { x - vec.x, y - vec.y };
			return vector;
		}

		Vector2 operator*(Vector2 vec) {

			Vector2 vector = { x * vec.x, y * vec.y };
			return vector;
		}

		Vector2 operator*(float value) {

			Vector2 vector = { x * value, y * value };
			return vector;
		}

	};


class OwnMathFuncs
{
public:
	
	static void normalize(Vector2 &vec);
	static float magnitude(Vector2 &vec);

	static Vector2 getNormalize(Vector2& vec);

	static float distanceBetweenVect(Vector2 vec, Vector2 vec2);

	static Vector2 Lerp(Vector2 start, Vector2 end, float perc);
	static float Lerp(float start, float end, float perc);

	static Vector2 getRandomPointInCircle(float radius);
};

}
