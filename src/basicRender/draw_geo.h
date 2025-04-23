#include <iostream>
#include<tgaimage/tgaimage.h>
class DrawGeo {
	// DrawGeo class to handle drawing of geometric shapes
public:
	void drawLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
};
