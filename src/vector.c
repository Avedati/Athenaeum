#include "../include/vector.h"
#include <stdlib.h>

/*
  struct vector* vector_init(void)
  
  This function returns a pointer to a new vector struct.
  It will allocate the necessary memory and set the vector's length to 0.
  
  @return A pointer to a new vector struct.
*/
struct vector* vector_init(void) {
	struct vector* v = malloc(sizeof(struct vector*));
	v->data = malloc(0);
	v->len = 0;
	return v;
}

/*
  void vector_add(struct vector* v, void* e)
  
  This function reallocates the vector's data,
  increments it's length field by 1 and adds the new
  element to the end of it's data field.
  
  @param v A pointer to a vector struct.
  @param e A pointer to an element of any type.
*/
void vector_add(struct vector* v, void* e) {
	v->data = realloc(v->data, sizeof(void*) * (v->len + 1));
	v->data[v->len++] = e;
}

/*
  void* vector_get(struct vector* v, int i)
  
  This function returns the element at index i,
  if i is greater than or equal to 0 and less than
  the vector's length field. Otherwise, it will return
  NULL.
  
  @param v A pointer to a vector struct.
  @param i The index of the element.
  @return The element if applicable, otherwise NULL.
*/
void* vector_get(struct vector* v, int i) {
	if(0 <= i && i < v->len) { return v->data[i]; }
	return NULL;
}

/*
  void vector_set(struct vector* v, int i, void* e)
  
  This function sets the element at index i to e,
  if i is greater than or equal to 0 and less than
  the vector's length field. Otherwise, it will simply
  add the element using the "vector_add" method.
  
  @param v A pointer to a vector struct.
  @param i The index of the element.
  @param e A pointer to an element of any type.
*/
void vector_set(struct vector* v, int i, void* e) {
	if(0 <= i && i < v->len) { v->data[i] = e; }
	vector_add(v, e);
}

/*
  void vector_free(struct vector* v)
  
  This function will free the data field of a vector
  and the vector itself.
  
  @param v A pointer to a vector struct.
*/
void vector_free(struct vector* v) {
	free(v->data);
	free(v);
}
