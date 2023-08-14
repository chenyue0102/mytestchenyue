package com.xixi.observe.service;

import java.util.concurrent.TimeUnit;

public interface RedisService {
    Object get(final String key);
    boolean set(final String key, Object value);
    boolean set(final String key, Object value, long timeout, TimeUnit unit);
}
