#pragma once
struct Color
{
	Color();
	Color(int r, int g, int b, int a);
	~Color();

	int r = 255, g = 255, b = 255, a = 255;
};

