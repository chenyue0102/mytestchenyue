//
// Created by EDZ on 2020/8/5.
//

#include "MyLock.h"

MyLock::MyLock(): mLock(ATOMIC_FLAG_INIT) {

}

void MyLock::lock() {
    while(mLock.test_and_set());
}

void MyLock::unlock() {
    mLock.clear();
}
