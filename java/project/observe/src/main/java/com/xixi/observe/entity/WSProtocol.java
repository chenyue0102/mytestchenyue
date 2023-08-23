package com.xixi.observe.entity;

import lombok.Data;
import lombok.EqualsAndHashCode;

import java.io.Serializable;

public class WSProtocol {
    @Data
    public static class MsgBase implements Serializable {
        private int msgId;
        private int sourceId;
        private int destUserId;
    }

    @EqualsAndHashCode(callSuper = true)
    @Data
    public static class MsgReqBase<T> extends MsgBase{
        private T data;
    }
    @EqualsAndHashCode(callSuper = true)
    @Data
    public static class MsgAckBase<T> extends MsgBase{
        private boolean success;
        private T data;
    }

    public static final int MSG_SHOW_TIP_REQ = 1;
    @Data
    public static class MsgShowTipReq{
        private String text;
    }
    public static final int MSG_SHOW_TIP_ACK = 1;
    @EqualsAndHashCode(callSuper = true)
    @Data
    public static class MsgShowTipAck extends MsgBase{
        private boolean success;
        private String text;
    }
}
