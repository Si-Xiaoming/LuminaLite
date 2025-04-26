#include "draw_triangle.h"
int hidden_faces() {
    const TGAColor white = TGAColor(255, 255, 255, 255);
    const TGAColor red = TGAColor(255, 0, 0, 255);

    const int width = 800;
    const int height = 800;
    Model* model = NULL;
    DrawGeo drawGeo;
    TGAImage image(width, height, TGAImage::RGB);
    model = new Model("data/models/african_head.obj");
    float* zbuffer = new float[width * height];
    for (int i = width * height; i--; zbuffer[i] = -std::numeric_limits<float>::max());
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f pts[3];
        for (int i = 0; i < 3; i++) pts[i] = world2screen(model->vert(face[i]));
        drawGeo.drawTriangleZBuffer(pts, zbuffer, image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255),800,800);
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("hidden_faces.tga");
    delete model;
    return 0;
}

void main(int argc, char** argv) {
    hidden_faces();

}