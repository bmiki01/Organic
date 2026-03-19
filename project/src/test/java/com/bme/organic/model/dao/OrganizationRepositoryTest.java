package com.bme.organic.model.dao;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.Mockito;

import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.test.context.ContextConfiguration;

import com.bme.organic.OrganicApplication;
import com.bme.organic.model.entity.Organization;



@DataJpaTest
@ContextConfiguration(classes = OrganicApplication.class)
public class OrganizationRepositoryTest {

    
    @Mock
    private OrganizationRepository repository;

    private static Organization organization;

    @BeforeAll
    public static void init(){
        organization = new Organization();
        organization.setAssignee(null);
        organization.setId(null);
        organization.setManager(null);
        organization.setName("BME");
        organization.setTasks(null);
    }

    @AfterEach
    public void clear(){
        repository.deleteAll();
    }

    @Test
    void testFindByName() {
        Mockito.when(repository.findByName(organization.getName())).thenReturn(organization);
        Organization result  = repository.findByName(organization.getName());
        assertEquals(result, organization);
        assertEquals(result.getName(),organization.getName());
        assertNull(result.getAssignee());
        assertNotEquals("BME2", result.getName());
    }
}
