package com.company;

@FunctionalInterface
@ClassAnnotation("TestAnnotation")
public interface TestAnnotation {
    @MethodAnnotation("/test/url")
    String getAnnotationResult(@ParameterAnnotation("userId") String userId);
}
