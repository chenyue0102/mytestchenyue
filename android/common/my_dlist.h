#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

struct _my_dlist_list* my_dlist_alloc();
void my_dlist_free(struct _my_dlist_list* list);

void my_dlist_add(struct _my_dlist_list *list, void *data);
void my_dlist_del(struct _my_dlist_list *list, void *data);

typedef int(*MY_DLIST_COMPARE)(void *param, void *data);
void* my_dlist_find(struct _my_dlist_list *list, MY_DLIST_COMPARE compFun, void *param);

typedef void(*MY_DLIST_CLEAR)(void *data);
void my_dlist_clear(struct _my_dlist_list *list, MY_DLIST_CLEAR fun);

size_t my_dlist_size(struct _my_dlist_list *list);

#ifdef __cplusplus
}
#endif