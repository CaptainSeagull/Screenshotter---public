
// Methods
LANE_PUBLIC_DEC float extract(Lane_F32 a, uint32_t lane) {
    float r = ((float *)&a)[lane];
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 clamp(Lane_F32 a, Lane_F32 l, Lane_F32 u) {
    Lane_F32 r = minf32(maxf32(a, l), u);
    return(r);
}


LANE_PUBLIC_DEC Lane_F32 clamp(Lane_F32 a, float l, float u) {
    Lane_F32 r = clamp(a, lane_f32(l), lane_f32(u));
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 lane_clamp01(Lane_F32 a) {
    Lane_F32 r = clamp(a, lane_f32(0.0f), lane_f32(1.0f));
    return(r);
}

Lane_F32 Lane_F32::operator=(float a) {
    *this = lane_f32(a);
    return(*this);
}

// Mul
LANE_PUBLIC_DEC Lane_F32 operator*(Lane_F32 a, float b) {
    Lane_F32 r = a * lane_f32(b);
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator*(float a, Lane_F32 b) {
    Lane_F32 r = lane_f32(a) * b;
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator*=(Lane_F32 &a, Lane_F32 b) {
    a = a * b;
    return(a);
}

// Div
LANE_PUBLIC_DEC Lane_F32 operator/(Lane_F32 a, float b) {
    Lane_F32 r = a / lane_f32(b);
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator/(float a, Lane_F32 b) {
    Lane_F32 r = lane_f32(a) / b;
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator/=(Lane_F32 &a, Lane_F32 b) {
    a = a / b;
    return(a);
}

// Add
LANE_PUBLIC_DEC Lane_F32 operator+(Lane_F32 a, float b) {
    Lane_F32 r = a + lane_f32(b);
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator+(float a, Lane_F32 b) {
    Lane_F32 r = lane_f32(a) + b;
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator+=(Lane_F32 &a, Lane_F32 b) {
    a = a + b;
    return(a);
}

// Subtract
LANE_PUBLIC_DEC Lane_F32 operator-(Lane_F32 a) {
    Lane_F32 r = lane_f32_zero() - a;
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator-(Lane_F32 a, float b) {
    Lane_F32 r = a - lane_f32(b);
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator-(float a, Lane_F32 b) {
    Lane_F32 r = lane_f32(a) - b;
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 operator-=(Lane_F32 &a, Lane_F32 b) {
    a = a - b;
    return(a);
}

LANE_PUBLIC_DEC float horizontal_add(Lane_F32 a) {
    float r = 0;
    float *v = (float *)&a.v;
    for(uint32_t i = 0; (i < LANE_WIDTH); ++i) {
        r += v[i];
    }

    return(r);
}

LANE_PUBLIC_DEC Lane_U32 operator>(Lane_F32 a, float b) {
    Lane_U32 r = (a > lane_f32(b));
    return(r);
}

LANE_PUBLIC_DEC Lane_U32 operator>=(Lane_F32 a, float b) {
    Lane_U32 r = (a >= lane_f32(b));
    return(r);
}

LANE_PUBLIC_DEC Lane_U32 operator<(Lane_F32 a, float b) {
    Lane_U32 r = (a < lane_f32(b));
    return(r);
}

LANE_PUBLIC_DEC Lane_U32 operator<=(Lane_F32 a, float b) {
    Lane_U32 r = (a <= lane_f32(b));
    return(r);
}

LANE_PUBLIC_DEC Lane_U32 operator==(Lane_F32 a, float b) {
    Lane_U32 r = (a == lane_f32(b));
    return(r);
}

LANE_PUBLIC_DEC Lane_U32 operator!=(Lane_F32 a, float b) {
    Lane_U32 r = (a != lane_f32(b));
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 maxf32(Lane_F32 a, float b) {
    Lane_F32 r = maxf32(a, lane_f32(b));
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 maxf32(float a, Lane_F32 b) {
    Lane_F32 r = maxf32(lane_f32(a), b);
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 minf32(Lane_F32 a, float b) {
    Lane_F32 r = minf32(a, lane_f32(b));
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 minf32(float a, Lane_F32 b) {
    Lane_F32 r = minf32(lane_f32(a), b);
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 lerp(Lane_F32 t, Lane_F32 a, Lane_F32 b) {
    Lane_F32 r = (lane_f32(1.0f) - t) * a + t * b;
    return(r);
}

LANE_PUBLIC_DEC Lane_F32 lerp(float t, Lane_F32 a, Lane_F32 b) {
    Lane_F32 r = (lane_f32(1.0f) - lane_f32(t)) * a + t * b;
    return(r);
}
