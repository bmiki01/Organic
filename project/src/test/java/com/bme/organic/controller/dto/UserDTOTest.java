package com.bme.organic.controller.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;


import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class UserDTOTest {


    private static UserDTO user;

    @BeforeEach
    void setUp(){
        user = new UserDTO();
        user.setEmail("bob@test.com");
        user.setOrganizations(null);
        user.setPassword("bob");
        user.setTasks(null);
        user.setUsername("Bob");
        user.setId(null);
    }

    @Test
    void testGetEmail() {
        assertEquals("bob@test.com", user.getEmail());
    }

    @Test
    void testGetId() {
        assertNull(user.getId());
    }

    @Test
    void testGetOrganizations() {
        assertNull(user.getOrganizations());
    }

    @Test
    void testGetPassword() {
        assertEquals("bob", user.getPassword());
    }

    @Test
    void testGetTasks() {
        assertNull(user.getTasks());
    }

    @Test
    void testGetUsername() {
        assertEquals("Bob", user.getUsername());
    }

    @Test
    void testSetEmail() {
        user.setEmail("bob@test2.com");
        assertEquals("bob@test2.com", user.getEmail());
    }

    @Test
    void testSetId() {
        user.setId(null);
        assertNull(user.getId());
    }

    @Test
    void testSetOrganizations() {
        user.setOrganizations(null);
        assertNull(user.getOrganizations());
    }

    @Test
    void testSetPassword() {
        user.setPassword("bob2");
        assertEquals("bob2", user.getPassword());
    }

    @Test
    void testSetTasks() {
        user.setTasks(null);
        assertNull(user.getTasks());
    }

    @Test
    void testSetUsername() {
        user.setUsername("bob2");
        assertEquals("bob2", user.getUsername());
    }
}
