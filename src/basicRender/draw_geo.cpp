#include "draw_geo.h"


void DrawGeo::drawLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
	// Draw a line using Bresenham's algorithm
	// if the line is steep, we transpose the image
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	// if the line is drawn from right to left, we swap the points
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void DrawGeo::drawTriangle(Vec2i* pts, TGAImage& image, TGAColor color)
{
	// pts[3] = {Vec2i(10,10), Vec2i(100, 30), Vec2i(190, 160)};
	Vec2i bbox_min(image.get_width() - 1, image.get_height() - 1);
	Vec2i bbox_max(0, 0);
	Vec2i clamp(image.get_width() - 1, image.get_height() - 1);

	for (int i = 0; i < 3; i++) {
		bbox_min.x = std::max(0, std::min(bbox_min.x, pts[i].x));
		bbox_min.y = std::max(0, std::min(bbox_min.y, pts[i].y));

		bbox_max.x = std::min(clamp.x, std::max(bbox_max.x, pts[i].x));
		bbox_max.y = std::min(clamp.y, std::max(bbox_max.y, pts[i].y));

	}
	Vec2i P;
	for (P.x = bbox_min.x; P.x <= bbox_max.x; P.x++) {
		for (P.y = bbox_min.y; P.y <= bbox_max.y; P.y++) {
			Vec3f bc_screen = barycentric(pts, P);
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
			image.set(P.x, P.y, color);
		}
	}
}

Vec3f DrawGeo::barycentric(Vec2i* pts, Vec2i P)
{
	Vec3f u = Vec3f(pts[2].x - pts[0].x, pts[1].x - pts[0].x, pts[0].x - P.x);
	Vec3f v = Vec3f(pts[2].y - pts[0].y, pts[1].y - pts[0].y, pts[0].y - P.y);
	Vec3f c = u ^ v;
	if (abs(c.z) < 1) return Vec3f(-1, 1, 1);
	return Vec3f(1.f - (c.x + c.y) / c.z, c.y / c.z, c.x / c.z);

}

