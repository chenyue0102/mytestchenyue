package com.xixi.observe.service;

public interface RedisService {
    Object get(final String key);
    boolean set(final String key, Object value);
}
