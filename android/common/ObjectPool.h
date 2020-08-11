//
// Created by chenyue on 2020/8/8.
//

#ifndef TESTFFMPEG_OBJECTPOOL_H
#define TESTFFMPEG_OBJECTPOOL_H
#include <list>

template<typename T>
class ObjectPool {
public:
    ObjectPool(){

    }
    ~ObjectPool(){

    }

public:
    T* alloc();
    void free(T *t);


};


#endif //TESTFFMPEG_OBJECTPOOL_H
