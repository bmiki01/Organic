package com.bme.organic.service;

import static org.junit.jupiter.api.Assertions.assertEquals;

import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertThrows;

import static org.mockito.ArgumentMatchers.any;

import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.verifyNoInteractions;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;
import java.util.UUID;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import com.bme.organic.OrganicApplication;
import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.exception.InconsistentDataException;
import com.bme.organic.mapper.TaskMapper;
import com.bme.organic.model.dao.OrganizationRepository;
import com.bme.organic.model.dao.TaskRepository;
import com.bme.organic.model.dao.UserRepository;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.model.entity.Task;
import com.bme.organic.model.entity.TaskStatus;
import com.bme.organic.model.entity.User;


@ExtendWith({MockitoExtension.class, SpringExtension.class})
@ContextConfiguration(classes = OrganicApplication.class)
@SpringBootTest
public class TaskServiceTest {

    @Autowired
    private TaskMapper mapper;
    @InjectMocks
    private TaskService service;
    private static TaskDTO task;
    @Mock
    private TaskRepository taskRepo;
    @Mock
    private OrganizationRepository orgRepo;
    @Mock
    private UserRepository userRepo;

    @BeforeAll
    static void init() {
        task = new TaskDTO();
    }

    @BeforeEach
    void setUp() {
        service = new TaskService(taskRepo, mapper, orgRepo, userRepo);
    }

    @AfterEach
    void tearDown() {
        Mockito.reset(taskRepo);
    }

    @Test
    @DisplayName("Should return all tasks in the repository")
    void getAllTasks() {
        Task task1 = new Task();
        task1.setId(UUID.randomUUID().getMostSignificantBits() & Long.MAX_VALUE);
        task1.setName("Task 1");
        task1.setStatus(TaskStatus.READY_TO_START);
        task1.setDescription("Description 1");
        task1.setOrganization(new Organization());

        Task task2 = new Task();
        task2.setId(UUID.randomUUID().getMostSignificantBits() & Long.MAX_VALUE);
        task2.setName("Task 2");
        task2.setStatus(TaskStatus.IN_PROGRESS);
        task2.setDescription("Description 2");
        task2.setOrganization(new Organization());

        List<Task> tasks0 = new ArrayList<>();
        tasks0.add(task1);
        tasks0.add(task2);

        Mockito.when(taskRepo.findAll()).thenReturn(tasks0);

        List<TaskDTO> tasks = service.getAll();

        Assertions.assertEquals(2, tasks.size());
        Assertions.assertEquals(task1.getId(), tasks.get(0).getId());
        Assertions.assertEquals(task1.getName(), tasks.get(0).getName());
        Assertions.assertEquals(task1.getStatus(), tasks.get(0).getStatus());
        Assertions.assertEquals(task1.getDescription(), tasks.get(0).getDescription());
        Assertions.assertEquals(task1.getOrganization().getName(), tasks.get(0).getOrganization());
        Assertions.assertEquals(task2.getId(), tasks.get(1).getId());
        Assertions.assertEquals(task2.getName(), tasks.get(1).getName());
        Assertions.assertEquals(task2.getStatus(), tasks.get(1).getStatus());
        Assertions.assertEquals(task2.getDescription(), tasks.get(1).getDescription());
        Assertions.assertEquals(task2.getOrganization().getName(), tasks.get(1).getOrganization());

        verify(taskRepo, times(1)).findAll();
    }

    @Test
    void testMapOrganization() {
        Task test = mapper.DTOToEntity(task);
        Mockito.when(orgRepo.findByName(task.getOrganization())).thenReturn(null);
        Organization org = orgRepo.findByName(task.getOrganization());
        test.setOrganization(org);
        verify(orgRepo, times(1)).findByName(task.getOrganization());
        assertNull(test.getOrganization());
    }

    @Test
    @DisplayName("Should throw an exception when the organization is not found in the database")
    void mapOrganizationWhenOrganizationIsNotFoundThenThrowException() {
        task.setOrganization("Nonexistent Organization");
        Task taskEntity = new Task();
        taskEntity.setOrganization(null);
        Mockito.when(orgRepo.findByName(task.getOrganization())).thenReturn(null);

        // Act and Assert
        Assertions.assertThrows(
                InconsistentDataException.class,
                () -> {
                    service.mapOrganization(task);
                });

        verify(orgRepo, times(1)).findByName(task.getOrganization());
    }

    @Test
    @DisplayName("Should map the organization when the organization is found in the database")
    void mapOrganizationWhenOrganizationIsFound() {
        TaskDTO taskDTO = new TaskDTO();
        taskDTO.setOrganization("Test Organization");
        Task task = new Task();
        task.setOrganization(new Organization());
        Mockito.when(orgRepo.findByName(taskDTO.getOrganization()))
                .thenReturn(task.getOrganization());

        Organization mappedOrg = service.mapOrganization(taskDTO);

        verify(orgRepo, times(1)).findByName(taskDTO.getOrganization());
        Assertions.assertEquals(task.getOrganization(), mappedOrg);
    }

    @Test
    @DisplayName("Should not map the organization when the organization is not provided")
    void mapOrganizationWhenOrganizationIsNotProvided() {
        TaskDTO taskDTO = new TaskDTO();
        taskDTO.setId(5L);
        taskDTO.setName("Task 1");
        taskDTO.setStatus(TaskStatus.READY_TO_START);
        taskDTO.setDescription("Task 1 description");

        Organization org = service.mapOrganization(taskDTO);

        assertNull(org);
        verify(orgRepo, times(0)).findByName(any(String.class));
    }

    @Test
    @DisplayName("Should throw NoSuchElementException when the user is not found")
    void saveTaskWhenUserNotFoundThenThrowNoSuchElementException() {
        UUID userId = UUID.randomUUID();
        TaskDTO taskDTO = new TaskDTO();
        taskDTO.setName("Test task");
        taskDTO.setStatus(TaskStatus.READY_TO_START);
        taskDTO.setDescription("Test description");
        taskDTO.setOrganization("Test organization");

        assertThrows(InconsistentDataException.class, () -> service.save(userId, taskDTO));

        verify(orgRepo, times(1)).findByName("Test organization");
        verifyNoInteractions(taskRepo);
        verifyNoInteractions(userRepo);
    }

    @Test
    @DisplayName("Should throw an InconsistentDataException when the organization is not found")
    void saveTaskWithInvalidOrganizationThenThrowInconsistentDataException() {
        task.setName("Task 1");
        task.setDescription("Task 1 description");
        task.setOrganization("Invalid Organization");
        task.setStatus(TaskStatus.READY_TO_START);

        Mockito.when(orgRepo.findByName(task.getOrganization())).thenReturn(null);

        // Act and Assert
        InconsistentDataException exception =
                assertThrows(
                        InconsistentDataException.class,
                        () -> service.save(null, task),
                        "Expected save() to throw InconsistentDataException, but it didn't");

       assertEquals(
                "Invalid Organization is not found in the database", exception.getMessage());

        verify(orgRepo, times(1)).findByName(task.getOrganization());
        verify(taskRepo, times(0)).save(any(Task.class));
    }

    @Test
    @DisplayName("Should throw NoSuchElementException when the user is not found")
    void mapUserWhenUserNotFoundThenThrowException() {
        UUID userId = UUID.randomUUID();
        Task task = new Task();
        task.setId(1L);
        task.setName("Test Task");
        task.setStatus(TaskStatus.READY_TO_START);

        when(userRepo.findById(userId)).thenReturn(Optional.empty());

        assertThrows(
                NoSuchElementException.class,
                () -> {
                    service.mapUser(userId, task);
                });

        verify(userRepo, times(1)).findById(userId);
        verifyNoInteractions(taskRepo, orgRepo);
    }

    @Test
    @DisplayName("Should map the user and add the task to the user's task list")
    void mapUserAndAddTaskToUserTaskList() { // Create a new task
        Task task = new Task();
        task.setId(1L);
        task.setName("Test Task");
        task.setStatus(TaskStatus.READY_TO_START);
        task.setDescription("Test Description");
        task.setOrganization(new Organization());
        List<Task> tasks = new ArrayList<>();
        tasks.add(task);
        // Create a new user
        User user = new User();
        user.setId(UUID.randomUUID());
        user.setUsername("testuser");
        user.setEmail("testuser@example.com");
        user.setPassword("testpassword");
        user.setTasks(tasks);

        // Mock the userRepository to return the user when findById is called
        when(userRepo.findById(user.getId())).thenReturn(Optional.of(user));

        // Call the mapUser method
        User mappedUser = service.mapUser(user.getId(), task);

        // Verify that the userRepository's findById method was called once with the correct
        // argument
        verify(userRepo, times(1)).findById(user.getId());

        // Verify that the task was added to the user's task list
        assertEquals(2, mappedUser.getTasks().size());
        assertEquals(task, mappedUser.getTasks().get(0));

        // Verify that the mapped user is the same as the original user
        assertEquals(user, mappedUser);
    }
    
}
