#pragma once

struct _my_mutex_t*  create_my_mutex();

void lock_my_mutex(struct _my_mutex_t* mtx);

void unlock_my_mutex(struct _my_mutex_t* mtx);

void destroy_my_mutex(struct _my_mutex_t* mtx);