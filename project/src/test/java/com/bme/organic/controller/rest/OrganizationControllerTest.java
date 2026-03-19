package com.bme.organic.controller.rest;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.UUID;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

import com.bme.organic.controller.dto.OrganizationDTO;
import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.controller.dto.UserTaskCountDTO;
import com.bme.organic.model.entity.TaskStatus;
import com.bme.organic.service.OrganizationService;


@ExtendWith(MockitoExtension.class)
public class OrganizationControllerTest {

    @Mock
    OrganizationService service;

    @InjectMocks
    OrganizationController controller;

    @Test
    @DisplayName("Should return a not found status when the organization does not exist")
    void getTaskCountWhenOrganizationNotFound() {
        UUID orgID = UUID.randomUUID();
        when(service.getTaskCount(orgID)).thenThrow(new NoSuchElementException());

        ResponseEntity<ArrayList<UserTaskCountDTO>> response = controller.getTaskCount(orgID);

        assertEquals(HttpStatus.NOT_FOUND, response.getStatusCode());
        verify(service, times(1)).getTaskCount(orgID);
    }

    @Test
    @DisplayName("Should return an empty list when there are no users in the organization")
    void getTaskCountWhenNoUsersInOrganization() {
        UUID orgID = UUID.randomUUID();
        ArrayList<UserTaskCountDTO> expected = new ArrayList<>();

        when(service.getTaskCount(orgID)).thenReturn(expected);

        ResponseEntity<ArrayList<UserTaskCountDTO>> response = controller.getTaskCount(orgID);

        assertEquals(HttpStatus.OK, response.getStatusCode());
        assertEquals(expected, response.getBody());

        verify(service, times(1)).getTaskCount(orgID);
    }

    @Test
    @DisplayName("Should return the task count for each user in the organization")
    void getTaskCountForUsersInOrganization() { // create test data
        UUID orgID = UUID.randomUUID();
        UserTaskCountDTO user1 = new UserTaskCountDTO();
        user1.setUsername("user1");
        user1.setCount(5L);
        UserTaskCountDTO user2 = new UserTaskCountDTO();
        user2.setUsername("user2");
        user2.setCount(3L);
        ArrayList<UserTaskCountDTO> expected = new ArrayList<>();
        expected.add(user1);
        expected.add(user2);

        // mock service method
        when(service.getTaskCount(orgID)).thenReturn(expected);

        // call controller method
        ResponseEntity<ArrayList<UserTaskCountDTO>> response = controller.getTaskCount(orgID);

        // verify response
        assertEquals(HttpStatus.OK, response.getStatusCode());
        assertEquals(expected, response.getBody());

        // verify service method was called
        verify(service, times(1)).getTaskCount(orgID);
    }

    @Test
    @DisplayName("Should return not found status when the username or orgID is invalid")
    void getTasksWhenUsernameOrOrgIdIsInvalidThenReturnNotFound() {
        String username = "invalid_username";
        UUID orgID = UUID.randomUUID();
        when(service.getTasks(username, orgID)).thenThrow(new NoSuchElementException());

        ResponseEntity<ArrayList<TaskDTO>> response = controller.getTasks(username, orgID);

        assertEquals(HttpStatus.NOT_FOUND, response.getStatusCode());
        verify(service, times(1)).getTasks(username, orgID);
    }

    @Test
    @DisplayName("Should return tasks when the username and orgID are valid")
    void getTasksWhenUsernameAndOrgIdAreValid() {
        String username = "testuser";
        UUID orgID = UUID.randomUUID();
        ArrayList<TaskDTO> tasks = new ArrayList<>();
        TaskDTO task1 = new TaskDTO();
        task1.setId(1L);
        task1.setName("Task 1");
        task1.setStatus(TaskStatus.READY_TO_START);
        task1.setOrganization("Org 1");
        task1.setDescription("Description 1");
        tasks.add(task1);

        TaskDTO task2 = new TaskDTO();
        task2.setId(2L);
        task2.setName("Task 2");
        task2.setStatus(TaskStatus.IN_PROGRESS);
        task2.setOrganization("Org 2");
        task2.setDescription("Description 2");
        tasks.add(task2);

        when(service.getTasks(username, orgID)).thenReturn(tasks);

        ResponseEntity<ArrayList<TaskDTO>> response = controller.getTasks(username, orgID);

        assertEquals(HttpStatus.OK, response.getStatusCode());
        assertEquals(tasks, response.getBody());
        verify(service, times(1)).getTasks(username, orgID);
    }

    @Test
    @DisplayName("Should return a not found status when the user or organization is not found")
    void joinWhenUserOrOrganizationNotFoundThenReturnNotFoundStatus() {
        UUID userID = UUID.randomUUID();
        OrganizationDTO organizationDTO = new OrganizationDTO();
        organizationDTO.setId(UUID.randomUUID());
        when(service.join(userID, organizationDTO)).thenThrow(new NoSuchElementException());

        ResponseEntity<OrganizationDTO> response = controller.join(userID, organizationDTO);

        assertEquals(HttpStatus.NOT_FOUND, response.getStatusCode());
        verify(service, times(1)).join(userID, organizationDTO);
    }

    @Test
    @DisplayName("Should return the updated organization when the user successfully joins")
    void joinWhenUserSuccessfullyJoins() {
        UUID userID = UUID.randomUUID();
        UUID orgID = UUID.randomUUID();
        OrganizationDTO organizationDTO = new OrganizationDTO();
        organizationDTO.setId(orgID);
        organizationDTO.setName("Test Organization");
        organizationDTO.setManager("Test Manager");
        List<String> assignee = new ArrayList<>();
        assignee.add("Test User");
        organizationDTO.setAssignee(assignee);
        List<TaskDTO> tasks = new ArrayList<>();
        TaskDTO taskDTO = new TaskDTO();
        taskDTO.setId(1L);
        taskDTO.setName("Test Task");
        taskDTO.setStatus(TaskStatus.READY_TO_START);
        taskDTO.setOrganization("Test Organization");
        taskDTO.setDescription("Test Description");
        tasks.add(taskDTO);
        organizationDTO.setTasks(tasks);

        when(service.join(userID, organizationDTO)).thenReturn(organizationDTO);

        ResponseEntity<OrganizationDTO> response = controller.join(userID, organizationDTO);

        assertEquals(HttpStatus.OK, response.getStatusCode());
        assertEquals(organizationDTO, response.getBody());

        verify(service, times(1)).join(userID, organizationDTO);
    }

    @Test
    @DisplayName("Should save the organization when the data is consistent")
    void saveOrganizationWhenDataIsConsistent() {
        OrganizationDTO organization = new OrganizationDTO();
        organization.setId(UUID.randomUUID());
        organization.setName("Test Organization");
        organization.setManager("Test Manager");
        List<String> assignee = new ArrayList<>();
        assignee.add("Test Assignee");
        organization.setAssignee(assignee);
        List<TaskDTO> tasks = new ArrayList<>();
        TaskDTO task = new TaskDTO();
        task.setId(1L);
        task.setName("Test Task");
        task.setStatus(TaskStatus.READY_TO_START);
        task.setOrganization("Test Organization");
        task.setDescription("Test Description");
        tasks.add(task);
        organization.setTasks(tasks);

        when(service.save(organization)).thenReturn(organization);

        ResponseEntity<OrganizationDTO> response = controller.save(organization);

        assertEquals(HttpStatus.CREATED, response.getStatusCode());
        assertEquals(organization, response.getBody());
        verify(service, times(1)).save(organization);
    }

    @Test
    @DisplayName("Should return a list of all organizations with HTTP status OK")
    void getTasksReturnsListOfOrganizationsWithStatusOk() {
        List<OrganizationDTO> organizations = new ArrayList<>();
        organizations.add(new OrganizationDTO());
        organizations.add(new OrganizationDTO());
        when(service.getAll()).thenReturn(organizations);

        ResponseEntity<List<OrganizationDTO>> response = controller.getTasks();

        assertEquals(HttpStatus.OK, response.getStatusCode());
        assertEquals(2, response.getBody().size());
        verify(service, times(1)).getAll();
    }
}
