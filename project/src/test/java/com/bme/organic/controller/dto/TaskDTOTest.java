package com.bme.organic.controller.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class TaskDTOTest {

    private static TaskDTO task;


    @BeforeEach
    void setUp(){
        task = new TaskDTO();
        task.setDescription("Test");
        task.setId(5L);
        task.setName("Testcase");
        task.setOrganization("BME");
        task.setStatus(null);
    }

    @Test
    void testGetDescription() {
        assertEquals("Test", task.getDescription());
    }

    @Test
    void testGetId() {
        assertEquals(5L, task.getId());
    }

    @Test
    void testGetName() {
        assertEquals("Testcase", task.getName());
    }

    @Test
    void testGetOrganization() {
        assertEquals("BME", task.getOrganization());
    }

    @Test
    void testGetStatus() {
        assertEquals(null, task.getStatus());
    }

    @Test
    void testSetDescription() {
        task.setDescription("Test2");
        assertEquals("Test2", task.getDescription());
    }

    @Test
    void testSetId() {
        task.setId(6L);
        assertEquals(6L, task.getId());
    }

    @Test
    void testSetName() {
        task.setName("Testcase2");
        assertEquals("Testcase2", task.getName());
    }

    @Test
    void testSetOrganization() {
        task.setOrganization("BME2");
        assertEquals("BME2", task.getOrganization());
    }

    @Test
    void testSetStatus() {
        task.setStatus(null);
        assertEquals(null, task.getStatus());
    }
}
