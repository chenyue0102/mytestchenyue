package com.xixi.observe.service.impl;

import com.xixi.observe.dao.PrivateKeyDao;
import com.xixi.observe.entity.PrivateKey;
import com.xixi.observe.service.ErrorException;
import com.xixi.observe.service.PrivateKeyService;
import com.xixi.observe.util.Result;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.sql.Timestamp;

@Service
public class PrivateKeyServiceImp implements PrivateKeyService {
    @Autowired
    private PrivateKeyDao privateKeyDao;

    @Override
    public PrivateKey getPrivateKey(Timestamp enableTime, Timestamp expiration) throws ErrorException {
        PrivateKey privateKey = privateKeyDao.getPrivateKey(enableTime, expiration);
        if (null == privateKey){
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }
        return privateKey;
    }
}
