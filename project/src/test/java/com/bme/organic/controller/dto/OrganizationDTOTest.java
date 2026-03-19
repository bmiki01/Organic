package com.bme.organic.controller.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class OrganizationDTOTest {

    private static OrganizationDTO org;

    @BeforeEach
    void setUp(){
       org = new OrganizationDTO();
       org.setAssignee(null);
       org.setId(null);
       org.setManager("Bob");
       org.setName("Bob's restaurant");
       org.setTasks(null);
    }

    @Test
    void testGetAssignee() {
        assertNull(org.getAssignee());
    }

    @Test
    void testGetId() {
        assertNull(org.getId());
    }

    @Test
    void testGetManager() {
        assertEquals("Bob", org.getManager());
    }

    @Test
    void testGetName() {
        assertEquals("Bob's restaurant", org.getName());
    }

    @Test
    void testGetTasks() {
        assertNull(org.getTasks());
    }

    @Test
    void testSetAssignee() {
        org.setAssignee(null);
        assertNull(org.getAssignee());
    }

    @Test
    void testSetId() {
        org.setId(null);
        assertNull(org.getId());
    }

    @Test
    void testSetManager() {
        org.setManager("Bob2");
        assertEquals("Bob2", org.getManager());
    }

    @Test
    void testSetName() {
        org.setName("Bob's restaurant2");
        assertEquals("Bob's restaurant2", org.getName());
    }

    @Test
    void testSetTasks() {
        org.setTasks(null);
        assertNull(org.getTasks());
    }
}
