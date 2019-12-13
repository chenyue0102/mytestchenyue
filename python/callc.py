# -*- coding:UTF-8 -*-
from ctypes import cdll


ll = cdll.LoadLibrary
lib = ll('./update.dll')
ctx = lib.createKSUpdate()
print(ctx)
lib.destroyKSUpdate(ctx)
ctx = lib.createKSUpdate()
print(ctx)
lib.destroyKSUpdate(ctx)