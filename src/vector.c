#include "../include/vector.h"
#include <stdlib.h>

struct vector* vector_init(void) {
	struct vector* v = malloc(sizeof(struct vector*));
	v->data = malloc(0);
	v->len = 0;
	return v;
}

void vector_add(struct vector* v, void* e) {
	v->data = realloc(v->data, sizeof(void*) * (v->len + 1));
	v->data[v->len++] = e;
}

void* vector_get(struct vector* v, int i) {
	if(0 <= i && i < v->len) { return v->data[i]; }
	return NULL;
}

void vector_set(struct vector* v, int i, void* e) {
	if(0 <= i && i < v->len) { v->data[i] = e; }
	vector_add(v, e);
}

void vector_free(struct vector* v) {
	free(v->data);
	free(v);
}
