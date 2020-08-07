//
// Created by EDZ on 2020/7/20.
//

#ifndef TESTMEDIA_MACRODEFINE_H
#define TESTMEDIA_MACRODEFINE_H

//单例
#define SC(T) \
	Single<T>::instance()

//成员引用
#define REFM(memberVariable) \
    auto &memberVariable = mData->memberVariable

#endif //TESTMEDIA_MACRODEFINE_H
