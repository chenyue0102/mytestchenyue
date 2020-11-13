#include "my_dlist.h"
#include <malloc.h>

typedef struct _my_dlist_list {
	void *data;
	struct _my_dlist_list *pre_ptr;
	struct _my_dlist_list *next_ptr;
}my_dlist_list;

static void my_dlist_add_size(my_dlist_list *list) {
	size_t count = (size_t)(list->data);
	list->data = (void*)(++count);
}

static void my_dlist_release_size(my_dlist_list *list) {
	size_t count = (size_t)(list->data);
	list->data = (void*)(--count);
}

struct _my_dlist_list* my_dlist_alloc() {
	//list节点不存储数据，用作结束判断
	my_dlist_list *list = malloc(sizeof(my_dlist_list));
	list->next_ptr = list->pre_ptr = list;
	list->data = NULL;
	return list;
}

void my_dlist_free(struct _my_dlist_list* list) {
	if (NULL != list) {
		list->pre_ptr->next_ptr = NULL;
		for (my_dlist_list *cur = list; cur != NULL; cur = cur->next_ptr) {
			my_dlist_list *next = cur->next_ptr;
			free(cur);
			cur = next;
		}
	}
}

void my_dlist_add(struct _my_dlist_list *list, void *data) {
	my_dlist_list *node = malloc(sizeof(my_dlist_list));
	node->data = data;
	node->next_ptr = list;
	node->pre_ptr = list->pre_ptr;
	list->pre_ptr->next_ptr = node;
	list->pre_ptr = node;
	my_dlist_add_size(list);
}

void my_dlist_del(struct _my_dlist_list *list, void *data) {
	for (my_dlist_list *cur = list->next_ptr; cur != list; cur = cur->next_ptr) {
		if (cur->data == data) {
			cur->pre_ptr->next_ptr = cur->next_ptr;
			cur->next_ptr->pre_ptr = cur->pre_ptr;
			free(cur);
			my_dlist_release_size(list);
			break;
		}
	}
}

void* my_dlist_find(struct _my_dlist_list *list, MY_DLIST_COMPARE compFun, void *param) {
	void *result = NULL;
	for (my_dlist_list *cur = list->next_ptr; cur != list; cur = cur->next_ptr) {
		if (0 == compFun(param, cur->data)) {
			result = cur->data;
			break;
		}
	}
	return result;
}

void my_dlist_clear(struct _my_dlist_list *list, MY_DLIST_CLEAR fun) {
	if (NULL == fun) {
		for (my_dlist_list *cur = list->next_ptr; cur != list; ) {
			my_dlist_list *next = cur->next_ptr;
			free(cur);
			cur = next;
		}
	}
	else {
		for (my_dlist_list *cur = list->next_ptr; cur != list; ) {
			my_dlist_list *next = cur->next_ptr;
			fun(cur->data);
			free(cur);
			cur = next;
		}
	}
	list->next_ptr = list->pre_ptr = list;
	list->data = NULL;
}