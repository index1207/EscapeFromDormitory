#pragma once
#include <math.h>

typedef struct _Vec {
	double x;
	double y;
} vec2;

static const vec2 vUp = { 0, 1 };
static const vec2 vDown = { 0, -1 };
static const vec2 vLeft = { -1, 0 };
static const vec2 vRight = { 1,0 };

double vec2_size(vec2 u) {
	return sqrt(u.x * u.x + u.y * u.y);
}

vec2 vec2_normalize(vec2* u, double size) {
	vec2 n = { u->x / size, u->y / size };
	return n;
}

double vec2_dot(vec2 u, vec2 v) {
	return u.x*v.x + u.y*v.y;
}

void set_vec2(vec2* v, double x, double y) {
	v->x = x;
	v->y = y;
}

