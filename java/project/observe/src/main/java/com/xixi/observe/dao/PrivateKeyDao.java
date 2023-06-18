package com.xixi.observe.dao;

import com.xixi.observe.entity.PrivateKey;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.sql.Timestamp;

@Mapper
public interface PrivateKeyDao {
    //enableTime <= time < expiration
    PrivateKey getPrivateKey(@Param("enableTime") Timestamp enableTime,
                             @Param("expiration") Timestamp expiration);
}
