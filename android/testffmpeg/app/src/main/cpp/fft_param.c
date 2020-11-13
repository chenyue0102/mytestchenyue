#include "fft_param.h"
#include <assert.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include "my_mutex.h"
#include "my_dlist.h"

static struct _my_mutex_t* g_mutex = NULL;

typedef struct _fft_param_node {
	int used;
	size_t fftlen;
	FFTParam fftparam;
}fft_param_node;
struct _my_dlist_list* g_list = NULL;

void init_fft(size_t fftlen, FFTParam *h) {
	int temp;
	h->Points = fftlen / 2;
	h->SinTable = malloc(2 * h->Points * sizeof(fft_type));
	h->BitReversed = malloc(h->Points * sizeof(int));

	for (size_t i = 0; i < h->Points; i++) {
		temp = 0;
		for (size_t mask = h->Points / 2; mask > 0; mask >>= 1) {
			temp = (temp >> 1) + (i & mask ? h->Points : 0);
		}
		h->BitReversed[i] = temp;
	}

	for (size_t i = 0; i < h->Points; i++) {
		h->SinTable[h->BitReversed[i]] = (fft_type)-sin(2 * M_PI * i / (2 * h->Points));
		h->SinTable[h->BitReversed[i + 1]] = (fft_type)-cos(2 * M_PI * i / (2 * h->Points));
	}
}


void init_fft_param() {
	assert(NULL == g_mutex);
	g_mutex = create_my_mutex();
	g_list = my_dlist_alloc();
}

void free_fft_param(void *data) {
	fft_param_node *node = (fft_param_node*)(data);
	free(node->fftparam.BitReversed);
	free(node->fftparam.SinTable);
	free(node);
}

void destroy_fft_param() {
	if (NULL != g_mutex) {
		lock_my_mutex(g_mutex);
		
		my_dlist_clear(g_list, &free_fft_param);
		my_dlist_free(g_list);
		g_list = NULL;

		destroy_my_mutex(g_mutex);
		g_mutex = NULL;
	}
}

static int find_fft_node_by_fftlen(void *param, void *data) {
	size_t fftlen = (size_t)(param);
	fft_param_node *node = (fft_param_node*)(data);
	if (node->used) {
		return -1;
	}
	else {
		return fftlen - node->fftlen;
	}
}

FFTParam* get_fft_param(size_t fftlen) {
	assert(NULL != g_mutex);
	FFTParam *result = NULL;
	fft_param_node *node = NULL;

	lock_my_mutex(g_mutex);
	
	node = my_dlist_find(g_list, &find_fft_node_by_fftlen, fftlen);

	if (NULL == node) {
		fft_param_node *newNode = malloc(sizeof(fft_param_node));
		memset(newNode, 0, sizeof(fft_param_node));
		newNode->fftlen = fftlen;
		init_fft(fftlen, &newNode->fftparam);
		result = &newNode->fftparam;
		my_dlist_add(g_list, newNode);
	}

	unlock_my_mutex(g_mutex);

	return result;
}

int find_fft_node_by_fftparam(void *param, void *data) {
	FFTParam *fft_param = (FFTParam*)param;
	fft_param_node *node = (fft_param_node*)(data);
	if (&node->fftparam == fft_param) {
		return 0;
	}
	else {
		return -1;
	}
}

void release_fft_param(FFTParam* param) {
	assert(NULL != g_mutex);

	lock_my_mutex(g_mutex);

	fft_param_node *node = my_dlist_find(g_list, &find_fft_node_by_fftparam, param);
	if (NULL != node) {
		node->used = 0;
	}
	else {
		assert(0);
	}

	unlock_my_mutex(g_mutex);
}