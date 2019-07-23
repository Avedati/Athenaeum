#ifndef __VECTOR_H
#define __VECTOR_H

struct vector {
	void** data;
	int len;
};

struct vector* vector_init(void);
void vector_add(struct vector*,void*);
void* vector_get(struct vector*,int);
void vector_set(struct vector*,int,void*);
void vector_free(struct vector*);

#endif // __VECTOR_H
