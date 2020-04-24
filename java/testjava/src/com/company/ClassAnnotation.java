package com.company;

import java.lang.annotation.*;

@Documented
//只能修饰TYPE
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface ClassAnnotation {
    String value() default "ClassAnnotation";
}
