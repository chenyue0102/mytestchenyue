#include "my_vector.h"
#include <assert.h>
#include <malloc.h>
#include <stdint.h>
#include <memory.h>

#define DEFAULT_VECTOR_SIZE 8

struct _my_vector_t *my_vector_alloc(size_t item_size, size_t alloc_item_count) {
	if (alloc_item_count == 0) {
		alloc_item_count = DEFAULT_VECTOR_SIZE;
	}
	my_vector_t *p = malloc(sizeof(my_vector_t));
	memset(p, 0, sizeof(my_vector_t));
	p->item_size = item_size;
	p->capacity = alloc_item_count;
	p->size = 0;
	p->data = malloc(p->capacity * item_size);
	return p;
}

void my_vector_free(struct _my_vector_t* p) {
	if (NULL != p) {
		free(p->data);
		free(p);
	}
}

void my_vector_reserve(struct _my_vector_t *p, size_t capacity) {
	if (p->capacity < capacity) {
		void *new_data = realloc(p->data, capacity * p->item_size);
		if (NULL == new_data) {
			new_data = malloc(capacity * p->item_size);
			if (NULL != new_data) {
				memcpy(new_data, p->data, p->size * p->item_size);
				free(p->data);
				p->data = new_data;
			}
			else {
				assert(0);
				return;
			}
		}
		else {
			p->capacity = capacity;
			p->data = new_data;
		}
	}
}

void my_vector_push_back(struct _my_vector_t *p, void *data) {
	if (p->size == p->capacity) {
		my_vector_reserve(p, p->capacity * 2);
		if (p->capacity == p->size) {
			return;
		}
	}

	memcpy(p->data + (p->size * p->item_size), data, p->item_size);
	p->size++;
}

void my_vector_assign(struct _my_vector_t *p, void *data, size_t index) {
	void* tmp = my_vector_at(p, index);
	if (NULL != tmp) {
		memcpy(tmp, data, p->item_size);
	}
}

void my_vector_clear(struct _my_vector_t *p) {
	p->size = 0;
}

void my_vector_resize(struct _my_vector_t *p, size_t size) {
	if (p->capacity >= size) {
		p->size = size;
	}
	else {
		my_vector_reserve(p, size);
		p->size = size;
	}
}

void my_vector_erase(struct _my_vector_t *p, size_t index) {
	if (index < p->size) {
		memcpy(p->data + (index * p->item_size), p->data + ((index + 1) * p->item_size), (p->size - index - 1) * p->item_size);
	}
}

size_t my_vector_size(struct _my_vector_t *p) {
	return p->size;
}

void* my_vector_data(struct _my_vector_t *p) {
	return (void*)p->data;
}

void* my_vector_at(struct _my_vector_t *p, size_t index) {
	if (index >= p->size) {
		assert(0);
		return NULL;
	}
	else {
		return p->data + (index * p->item_size);
	}
}

void* my_vector_begin(struct _my_vector_t *p) {
	return p->data;
}

void* my_vector_end(struct _my_vector_t *p) {
	return p->data + (p->size * p->item_size);
}