struct Image {
    Int width;
    Int height;
    U32 *pixels;
};

// TODO: Not sure this really belongs in here... but works!
struct Image_Letter {
    Image img;
    Int off_x, off_y;
};
