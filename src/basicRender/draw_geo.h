#include <iostream>
#include<tgaimage/tgaimage.h>
#include "geometry.h"
class DrawGeo {
	// DrawGeo class to handle drawing of geometric shapes
public:
	void drawLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
	//https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
	//https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm

	void drawTriangle(Vec2i* pts, TGAImage& image, TGAColor color);

private:
	Vec3f barycentric(Vec2i* pts, Vec2i P);
};
