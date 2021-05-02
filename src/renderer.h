
struct Rectangle {
	Int x, y;
	Int width, height;
	U32 output_colour;
};

struct Renderer {
	Rectangle rectangles[256];
	Int rectangle_count;
};