CREATE DATABASE observe;
USE observe;

CREATE TABLE `user_info`(
    `id` INTEGER AUTO_INCREMENT,
    `name` VARCHAR(32) NOT NULL,
    `login_name` VARCHAR(32) NOT NULL UNIQUE,
    `password` VARCHAR(32) NOT NULL,
    `state` TINYINT NOT NULL DEFAULT 0,
    `manager` TINYINT NOT NULL DEFAULT 0,
	`create_time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `modify_time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY(`id`)
)CHARSET=utf8mb4;

CREATE TABLE `private_key`(
	`private_key` VARCHAR(4096) NOT NULL,
	`enable_time` TIMESTAMP NOT NULL,
	`expiration` TIMESTAMP NOT NULL,
	INDEX(`enable_time`,`expiration`),
	PRIMARY KEY(`enable_time`)
)CHARSET=utf8mb4;