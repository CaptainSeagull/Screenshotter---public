
internal Rectangle
create_rectangle(Int x, Int y, Int width, Int height, U8 r, U8 g, U8 b, U8 a) {
	Rectangle res = {};
	res.x = x;
	res.y = y;
	res.width = width;
	res.height = height;
	res.output_colour = (a << 24 | r << 16 | g << 8 | b << 0);

	return(res);
}

internal Rectangle *
push_solid_rectangle(Renderer *renderer, Int start_x, Int start_y, Int width, Int height, U8 r, U8 g, U8 b, U8 a) {
	renderer->rectangles[renderer->rectangle_count] = create_rectangle(start_x, start_y, width, height, r, g, b, a);
	Rectangle *res = &renderer->rectangles[renderer->rectangle_count];
	++renderer->rectangle_count;

	return(res);
}

internal Void
render(Renderer *renderer, Bitmap *bitmap) {
	for(Int rect_i = 0; (rect_i < renderer->rectangle_count); ++rect_i) {
		Rectangle *rectangle = &renderer->rectangles[rect_i];

		for(Int y = rectangle->y; (y < rectangle->y + rectangle->height); ++y) {
			U32 *out = (U32 *)bitmap->memory + (y * bitmap->width) + rectangle->x;
			for(Int x = rectangle->x; (x < rectangle->x + rectangle->width); ++x) {
				*out++ = rectangle->output_colour;
			}
		}
	}
}

