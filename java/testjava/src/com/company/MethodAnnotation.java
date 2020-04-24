package com.company;

import java.lang.annotation.*;

@Documented
//只能修饰METHOD
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface MethodAnnotation {
    String value() default "";
}
