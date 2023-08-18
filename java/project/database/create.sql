CREATE DATABASE observe;
USE observe;

CREATE TABLE `user_info`(
    `user_id` INTEGER AUTO_INCREMENT,
    `name` VARCHAR(32) NOT NULL,
    `login_name` VARCHAR(32) NOT NULL UNIQUE,
    `password` VARCHAR(32) NOT NULL,
    `state` TINYINT NOT NULL DEFAULT 0,
    `manager` TINYINT NOT NULL DEFAULT 0,
	`create_time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `modify_time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY(`user_id`)
)CHARSET=utf8mb4;

CREATE TABLE `user_observe`(
	`user_id` INTEGER NOT NULL,
	`observe_user_id` INTEGER NOT NULL,
	`create_time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
	CONSTRAINT `fk_user_id` FOREIGN KEY(`user_id`) REFERENCES `user_info`(`user_id`),
	CONSTRAINT `fk_observe_user_id` FOREIGN KEY(`observe_user_id`) REFERENCES `user_info`(`user_id`),
	INDEX(`user_id`),
	INDEX(`observe_user_id`),
	PRIMARY KEY(`user_id`, `observe_user_id`)
)CHARSET=utf8mb4;

CREATE TABLE `private_key`(
	`private_key` VARCHAR(4096) NOT NULL,
	`state` INTEGER NOT NULL,
	`enable_time` TIMESTAMP NOT NULL,
	`expiration` TIMESTAMP NOT NULL,
	INDEX(`enable_time`,`expiration`),
	INDEX(`state`),
	PRIMARY KEY(`enable_time`, `state`)
)CHARSET=utf8mb4;

CREATE TABLE `user_event`(
    `user_id` INTEGER NOT NULL,
    `event_id` INTEGER NOT NULL,
    `timestamp` BIGINT NOT NULL,			/* 毫秒时间戳 */
    `data` INTEGER,
    PRIMARY KEY(`user_id`, `event_id`, `timestamp`),
    INDEX(`user_id`),
    INDEX(`event_id`),
    INDEX(`timestamp`)
)CHARSET=utf8mb4;

CREATE TABLE `user_state`(
    `user_id` INTEGER NOT NULL,
    `state_id` INTEGER NOT NULL,
    `start_timestamp` BIGINT NOT NULL,			/* 毫秒时间戳 */
    `end_timestamp` BIGINT NOT NULL,			/* 毫秒时间戳 */
    `data` INTEGER,
    PRIMARY KEY(`user_id`, `state_id`, `start_timestamp`),
    INDEX(`user_id`),
    INDEX(`state_id`),
    INDEX(`start_timestamp`, `end_timestamp`)
)CHARSET=utf8mb4;