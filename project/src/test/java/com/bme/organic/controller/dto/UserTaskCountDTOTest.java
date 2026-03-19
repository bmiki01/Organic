package com.bme.organic.controller.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class UserTaskCountDTOTest {

    private static UserTaskCountDTO userTaskCount;

    @BeforeEach
    void setUp(){
        userTaskCount = new UserTaskCountDTO();
        userTaskCount.setCount(4L);
        userTaskCount.setUsername("Bob");
    }


    @Test
    void testGetCount() {
        assertEquals(4L, userTaskCount.getCount());
    }

    @Test
    void testGetUsername() {
        assertEquals("Bob", userTaskCount.getUsername());
    }

    @Test
    void testSetCount() {
        userTaskCount.setCount(5L);
        assertEquals(5L, userTaskCount.getCount());
    }

    @Test
    void testSetUsername() {
        userTaskCount.setUsername("John");
        assertEquals("John", userTaskCount.getUsername());
    }
}
