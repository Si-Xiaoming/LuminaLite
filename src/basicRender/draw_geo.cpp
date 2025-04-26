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
Vec3f DrawGeo::barycentric3d(Vec3f A, Vec3f B, Vec3f C, Vec3f P) {
	Vec3f s[2];
	for (int i = 2; i--; ) {
		s[i][0] = C[i] - A[i];
		s[i][1] = B[i] - A[i];
		s[i][2] = A[i] - P[i];
	}
	Vec3f u = cross(s[0], s[1]);
	if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
		return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	return Vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
}
void DrawGeo::drawTriangleZBuffer(Vec3f* pts, float* zbuffer, TGAImage& image, TGAColor color, int width, int height)
{
	Vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());

	Vec2f clamp(image.get_width() - 1, image.get_height() - 1);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			bboxmin[j] = std::max(0.f, std::min(bboxmin[j], pts[i][j]));
			bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
		}
	}
	Vec3f P;
	for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
		for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++) {
			Vec3f bc_screen = this->barycentric3d(pts[0], pts[1], pts[2], P);
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
			P.z = 0;
			for (int i = 0; i < 3; i++) {
				P.z += pts[i][2] * bc_screen[i];   
			}
			if (zbuffer[int(P.x + P.y * width)] < P.z) {
				zbuffer[int(P.x + P.y * width)] = P.z;
				image.set(P.x, P.y, color);
			}
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

