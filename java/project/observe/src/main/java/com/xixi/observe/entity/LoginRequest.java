package com.xixi.observe.entity;

import lombok.Data;
import org.hibernate.validator.constraints.NotEmpty;

@Data
public class LoginRequest {
    @NotEmpty
    private String loginName;

    @NotEmpty
    private String passwordHash;

    private String serverRandom;

    private String clientRandom;
}
