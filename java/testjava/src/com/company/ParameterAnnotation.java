package com.company;

import java.lang.annotation.*;

@Documented
//只能修饰PARAMETER
@Target(ElementType.PARAMETER)
@Retention(RetentionPolicy.RUNTIME)
@Inherited
public @interface ParameterAnnotation {
    String value();
}
