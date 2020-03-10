package com.example.testcplusplus;

public class MyClassLoader {
    public Class<?> loadClass(String name) throws ClassNotFoundException {
        Class<?> clazz = null;
        if (name.equals("com/example/testcplusplus/MainActivity")){
            clazz = MainActivity.class;
        }else{
            throw new ClassNotFoundException();
        }
        return clazz;
    }
}
