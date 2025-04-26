#include <iostream>
#include "model.h"
#include "geometry.h"
#include "draw_geo.h"
int draw_line() {
    const TGAColor white = TGAColor(255, 255, 255, 255);
    const TGAColor red = TGAColor(255, 0, 0, 255);

    const int width = 800;
    const int height = 800;
    Model* model = NULL;
    DrawGeo* drawGeo = NULL;
    model = new Model("data/models/african_head.obj");
    drawGeo = new DrawGeo();

    TGAImage image(width, height, TGAImage::RGB);
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.) * width / 2.;
            int y0 = (v0.y + 1.) * height / 2.;
            int x1 = (v1.x + 1.) * width / 2.;
            int y1 = (v1.y + 1.) * height / 2.;
            drawGeo->drawLine(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}
Vec3f world2screen(Vec3f v, int width = 800, int height = 800) {
    return Vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), v.z);
}
int flat_shading_render() {
    const TGAColor white = TGAColor(255, 255, 255, 255);
    const TGAColor red = TGAColor(255, 0, 0, 255);

    const int width = 800;
    const int height = 800;
    Model* model = NULL;
    DrawGeo drawGeo;
    TGAImage image(width, height, TGAImage::RGB);
    model = new Model("data/models/african_head.obj");
    
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f world_coords = model->vert(face[j]);
            screen_coords[j] = Vec2i((world_coords.x + 1.) * width / 2., (world_coords.y + 1.) * height / 2.);
        }

        drawGeo.drawTriangle(screen_coords, image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("flat_shading_render.tga");
    delete model;
    return 0;
}


int draw_triangle() {
	TGAImage frame(200, 200, TGAImage::RGB);
	Vec2i pts[3] = { Vec2i(10, 10), Vec2i(100, 10), Vec2i(50, 100) };
	DrawGeo drawGeo;
	drawGeo.drawTriangle(pts, frame, TGAColor(255, 0, 0, 0));

    frame.flip_vertically(); // to place the origin in the bottom left corner of the image 
    frame.write_tga_file("framebuffer.tga");
    return 0;
}
int draw_triangle_add_light() {
    const TGAColor white = TGAColor(255, 255, 255, 255);
    const TGAColor red = TGAColor(255, 0, 0, 255);

    const int width = 800;
    const int height = 800;
    Model* model = NULL;
    DrawGeo drawGeo;
    TGAImage image(width, height, TGAImage::RGB);
    model = new Model("data/models/african_head.obj");
    Vec3f light_dir(0, 0, -1); // define light_dir

    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
            world_coords[j] = v;
        }
        Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        n.normalize();
        float intensity = n * light_dir;
        if (intensity > 0) {
            drawGeo.drawTriangle(screen_coords, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
        }
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("triangle_add_light.tga");
    delete model;
    return 0;
}