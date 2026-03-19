package com.bme.organic.controller.dto;

public class UserTaskCountDTO {

    String username;
    Long count;

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public Long getCount() {
        return count;
    }

    public void setCount(Long count) {
        this.count = count;
    }
}
