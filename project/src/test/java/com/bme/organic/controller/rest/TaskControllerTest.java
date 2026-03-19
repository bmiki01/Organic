package com.bme.organic.controller.rest;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.doThrow;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.exception.InconsistentDataException;
import com.bme.organic.model.dao.OrganizationRepository;
import com.bme.organic.model.dao.UserRepository;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.model.entity.TaskStatus;
import com.bme.organic.model.entity.User;
import com.bme.organic.service.TaskService;

@ExtendWith(MockitoExtension.class)
public class TaskControllerTest {

    @Mock
    private TaskService service;

    @Mock
    private OrganizationRepository orgRepository;

    @Mock
    private UserRepository userRepository;

    @InjectMocks
    private TaskController controller;

    @Test
    @DisplayName("Should return a list of tasks with status OK")
    void getTasksReturnsListOfTasksWithStatusOk() {
        List<TaskDTO> taskList = new ArrayList<>();
        TaskDTO task1 = new TaskDTO();
        task1.setId(1L);
        task1.setName("Task 1");
        task1.setStatus(TaskStatus.READY_TO_START);
        task1.setOrganization("Org 1");
        task1.setDescription("Description 1");
        taskList.add(task1);

        TaskDTO task2 = new TaskDTO();
        task2.setId(2L);
        task2.setName("Task 2");
        task2.setStatus(TaskStatus.IN_PROGRESS);
        task2.setOrganization("Org 2");
        task2.setDescription("Description 2");
        taskList.add(task2);

        when(service.getAll()).thenReturn(taskList);

        ResponseEntity<List<TaskDTO>> response = controller.getTasks();

        assertEquals(HttpStatus.OK, response.getStatusCode());
        assertEquals(taskList, response.getBody());
    }

    @Test
    @DisplayName("Should save the task and return the saved task with status CREATED")
    void saveTaskWhenDataIsConsistent() {
        UUID userId = UUID.randomUUID();
        TaskDTO taskDTO = new TaskDTO();
        taskDTO.setName("Test Task");
        taskDTO.setStatus(TaskStatus.READY_TO_START);
        taskDTO.setOrganization("Test Organization");
        taskDTO.setDescription("Test Description");

        User user = new User();
        user.setId(userId);
        user.setUsername("testuser");
        user.setEmail("testuser@example.com");

        Organization organization = new Organization();
        organization.setId(UUID.randomUUID());
        organization.setName("Test Organization");

        when(service.save(any(UUID.class), any(TaskDTO.class))).thenReturn(taskDTO);

        ResponseEntity<TaskDTO> response = controller.save(userId, taskDTO);

        assertEquals(HttpStatus.CREATED, response.getStatusCode());
        assertEquals(taskDTO, response.getBody());
        verify(service, times(1)).save(userId, taskDTO);
    }

    @Test
    @DisplayName("Should return BAD_REQUEST status when InconsistentDataException is thrown")
    void saveTaskWhenInconsistentDataExceptionIsThrown() {
        UUID userId = UUID.randomUUID();
        TaskDTO taskDTO = new TaskDTO();
        taskDTO.setName("Test Task");
        taskDTO.setStatus(TaskStatus.READY_TO_START);
        taskDTO.setOrganization("Test Organization");
        taskDTO.setDescription("Test Description");

        User user = new User();
        user.setId(userId);
        user.setUsername("Test User");
        user.setEmail("testuser@example.com");

        Organization organization = new Organization();
        organization.setId(UUID.randomUUID());
        organization.setName("Test Organization");

        doThrow(new InconsistentDataException("Inconsistent data"))
                .when(service)
                .save(any(), any());

        ResponseEntity<TaskDTO> response = controller.save(userId, taskDTO);

        assertEquals(HttpStatus.BAD_REQUEST, response.getStatusCode());
        verify(service, times(1)).save(userId, taskDTO);
    }
   
}
