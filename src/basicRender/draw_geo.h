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
	void drawTriangleZBuffer(Vec3f* pts, float* zbuffer, TGAImage& image, TGAColor color, int width = 800, int height = 800);
	Vec3f barycentric3d(Vec3f A, Vec3f B, Vec3f C, Vec3f P);

private:
	Vec3f barycentric(Vec2i* pts, Vec2i P);
};
