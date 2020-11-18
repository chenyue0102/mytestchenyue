#pragma once
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct _my_vector_t {
		size_t size;
		size_t capacity;
		size_t item_size;
		uint8_t *data;
	}my_vector_t;
//item_size需要考虑内存对齐
struct _my_vector_t *my_vector_alloc(size_t item_size, size_t alloc_item_count);

void my_vector_free(struct _my_vector_t* p);

//拷贝data内容
void my_vector_push_back(struct _my_vector_t *p, void *data);
void my_vector_assign(struct _my_vector_t *p, void *data, size_t index);
//void my_vector_pop_back(struct _my_vector_t *p);

void my_vector_clear(struct _my_vector_t *p);
void my_vector_resize(struct _my_vector_t *p, size_t size);
void my_vector_erase(struct _my_vector_t *p, size_t index);

size_t my_vector_size(struct _my_vector_t *p);
void* my_vector_data(struct _my_vector_t *p);
void* my_vector_at(struct _my_vector_t *p, size_t index);
void* my_vector_begin(struct _my_vector_t *p);
void* my_vector_end(struct _my_vector_t *p);

#ifdef __cplusplus
}
#endif