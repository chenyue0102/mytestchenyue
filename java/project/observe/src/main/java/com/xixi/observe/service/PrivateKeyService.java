package com.xixi.observe.service;

import com.xixi.observe.entity.PrivateKey;

import java.sql.Timestamp;

public interface PrivateKeyService {
    PrivateKey getPrivateKey(Timestamp enableTime, Timestamp expiration) throws ErrorException;
}
