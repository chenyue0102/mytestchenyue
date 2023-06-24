package com.xixi.observe.dao;

import com.xixi.observe.entity.UserEvent;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;


@Mapper
public interface UserEventDao {
    boolean insertUserEvent(UserEvent userEvent);

    List<UserEvent> findUserEvent(
            @Param("userId") int userId,
            @Param("eventId") int eventId,
            @Param("startTime") long startTime,
            @Param("endTime") long endTime);
}
