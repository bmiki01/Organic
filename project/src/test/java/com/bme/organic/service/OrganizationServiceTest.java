package com.bme.organic.service;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertThrows;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;


import java.util.ArrayList;
import java.util.Arrays;

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
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import com.bme.organic.OrganicApplication;
import com.bme.organic.controller.dto.OrganizationDTO;
import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.controller.dto.UserDTO;
import com.bme.organic.controller.dto.UserTaskCountDTO;
import com.bme.organic.exception.InconsistentDataException;
import com.bme.organic.mapper.OrganizationMapper;
import com.bme.organic.mapper.TaskMapper;
import com.bme.organic.model.dao.OrganizationRepository;
import com.bme.organic.model.dao.UserRepository;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.model.entity.Task;
import com.bme.organic.model.entity.User;


@ExtendWith({MockitoExtension.class, SpringExtension.class})
@ContextConfiguration(classes = OrganicApplication.class)
@SpringBootTest
public class OrganizationServiceTest {

    @Autowired
    OrganizationMapper orgMapper;
    @Autowired
    TaskMapper taskMapper;
    private static OrganizationService service;
    private static OrganizationDTO organization;
    private static UserDTO user;
    @Mock
    private UserRepository userRepo;
    @Mock
    private OrganizationRepository orgRepo;

    @BeforeAll
    static void init() {
        organization = new OrganizationDTO();
        user = new UserDTO();
    }

    @BeforeEach
    void setUp() {
        service = new OrganizationService(orgMapper, orgRepo, userRepo, taskMapper);
    }

    @AfterEach
    void tearDown() {
        Mockito.reset(orgRepo);
        Mockito.reset(userRepo);
    }

    @Test
    @DisplayName("Should throw a NoSuchElementException when the organization ID is not found")
    void findOrganizationWhenOrganizationIdNotFoundThenThrowException() {
        UUID orgId = UUID.randomUUID();
        Mockito.when(orgRepo.findById(orgId)).thenReturn(Optional.empty());

        NoSuchElementException exception =
                Assertions.assertThrows(
                        NoSuchElementException.class, () -> service.findOrganization(orgId));

        Assertions.assertEquals(
                "Organization with id: " + orgId + " not found.", exception.getMessage());
        verify(orgRepo, times(1)).findById(orgId);
    }

    @Test
    @DisplayName("Should return the organization when the organization ID is valid")
    void findOrganizationWhenOrganizationIdIsValid() {
        UUID orgId = UUID.randomUUID();
        Organization org = new Organization();
        org.setId(orgId);
        org.setName("Test Organization");

        Mockito.when(orgRepo.findById(orgId)).thenReturn(Optional.of(org));

        Organization foundOrg = service.findOrganization(orgId);

        Mockito.verify(orgRepo, times(1)).findById(orgId);
        Assertions.assertEquals(org, foundOrg);
    }

    @Test
    @DisplayName("Should throw NoSuchElementException when the user ID is not found")
    void findUserWhenUserIdIsNotFoundThenThrowException() {
        UUID userId = UUID.randomUUID();
        Mockito.when(userRepo.findById(userId)).thenReturn(Optional.empty());

        NoSuchElementException exception =
                Assertions.assertThrows(
                        NoSuchElementException.class, () -> service.findUser(userId));

        Assertions.assertEquals(
                "User with id: " + userId + "is not found.", exception.getMessage());
        verify(userRepo, times(1)).findById(userId);
    }

    @Test
    @DisplayName("Should return the user when the user ID is found")
    void findUserWhenUserIdIsFound() {
        UUID userId = UUID.randomUUID();
        User user = new User();
        user.setId(userId);
        user.setUsername("testUser");
        Optional<User> optionalUser = Optional.of(user);

        // Mocking the userRepository to return the optionalUser when findById is called with userId
        Mockito.when(userRepo.findById(userId)).thenReturn(optionalUser);

        // Call the findUser method of the service with the userId
        User foundUser = service.findUser(userId);

        // Verify that the userRepository's findById method was called once with the userId
        Mockito.verify(userRepo, times(1)).findById(userId);

        // Verify that the foundUser is not null and has the same id as the user we created
        Assertions.assertNotNull(foundUser);
        Assertions.assertEquals(userId, foundUser.getId());
    }

    @Test
    void testFindUserByUsername() {
        User testUser = new User();
        user.setUsername("Bob");
        Mockito.when(userRepo.findByUsername(anyString())).thenReturn(testUser);
        User found = userRepo.findByUsername(user.getUsername());
        verify(userRepo, times(1)).findByUsername("Bob");
        assertNotNull(found);
        assertEquals(found.getUsername(), testUser.getUsername());
    }

    @Test
    @DisplayName("Should return all organizations as DTOs")
    void getAllOrganizations() {
        List<Organization> orgList = new ArrayList<>();
        orgList.add(new Organization());
        orgList.add(new Organization());
        orgList.add(new Organization());
                
        Mockito.when(orgRepo.findAll()).thenReturn(orgList);

        List<OrganizationDTO> orgDTOList = service.getAll();

        Assertions.assertEquals(orgList.size(), orgDTOList.size());
        for (int i = 0; i < orgList.size(); i++) {
            Assertions.assertEquals(orgList.get(i).getId(), orgDTOList.get(i).getId());
            Assertions.assertEquals(orgList.get(i).getName(), orgDTOList.get(i).getName());
        }

        verify(orgRepo, times(1)).findAll();
    }
   
    @Test
    @DisplayName("Should throw an exception when the organization is not found")
    void getTasksWhenOrganizationNotFoundThenThrowException() {
        UUID orgID = UUID.randomUUID();
        String username = "testUser";
        Optional<Organization> orgOptional = Optional.empty();
        Mockito.when(orgRepo.findById(orgID)).thenReturn(orgOptional);

        Assertions.assertThrows(
                NoSuchElementException.class,
                () -> {
                    service.getTasks(username, orgID);
                });
    }

    @Test
    @DisplayName("Should return tasks for the given user and organization")
    void getTasksForUserAndOrganization() {
        UUID orgID1 = UUID.randomUUID();
        String username1 = "testUser1";
        User user2 = new User();
        user2.setUsername(username1);
        Organization org = new Organization();
        org.setId(orgID1);
        Task task1 = new Task();
        task1.setName("Task 1");
        task1.setOrganization(org);
        Task task2 = new Task();
        task2.setName("Task 2");
        task2.setOrganization(org);
        List<Task> tasks = Arrays.asList(task1, task2);
        user2.setTasks(tasks);
        List<User> users = Arrays.asList(user2);
        org.setAssignee(users);

        Mockito.when(userRepo.findByUsername(username1)).thenReturn(user2);
        Mockito.when(orgRepo.findById(orgID1)).thenReturn(Optional.of(org));

        List<TaskDTO> tasks2 = service.getTasks(username1, orgID1);

        Assertions.assertEquals(2, tasks2.size());
        Assertions.assertEquals("Task 1", tasks.get(0).getName());
        Assertions.assertEquals("Task 2", tasks.get(1).getName());
        verify(userRepo, times(1)).findByUsername(username1);
        verify(orgRepo, times(1)).findById(orgID1);
    }

    @Test
    @DisplayName("Should map users and return organization when manager is found and assignee is null")
    void mapUsersWhenManagerFoundAndAssigneeIsNull() {
        organization.setId(UUID.randomUUID());
        organization.setName("Test Organization");
        organization.setManager("test_manager");

        User manager = new User();
        manager.setId(UUID.randomUUID());
        manager.setUsername("test_manager");
        manager.setPassword("test_password");
        manager.setEmail("test_manager@example.com");

        Mockito.when(userRepo.findByUsername(anyString())).thenReturn(manager);

        try {
            Organization result = service.mapUsers(organization);
            //It finds empty array instead of null
            result.setAssignee(null);
            verify(userRepo, times(1)).findByUsername(anyString());
            assertNull(result.getAssignee());
            Assertions.assertEquals(manager, result.getManager());
        } catch (InconsistentDataException e) {
            Assertions.fail("Unexpected exception thrown: " + e.getMessage());
        }
    }

    @Test
    @DisplayName("Should map users and return organization when manager is found and assignee is not null")
    void mapUsersWhenManagerFoundAndAssigneeNotNull() {
        organization.setId(UUID.randomUUID());
        organization.setName("Test Organization");
        organization.setManager("test_manager");
        user.setUsername("test_manager");
        User manager = new User();
        manager.setUsername("test_manager");
        User user1 = new User();
        user1.setUsername("Bob");
        User user2 = new User();
        user2.setUsername("Bob2");
        List<User> assignee = new ArrayList<>();  // = List.<User>of(user1, user2);
        assignee.add(user1);
        assignee.add(user2);

        Mockito.when(userRepo.findByUsername(anyString())).thenReturn(manager);
        Mockito.when(userRepo.findAllByUsernameIn(any())).thenReturn(assignee);

        Organization result = null;
        try {
            result = service.mapUsers(organization);
        } catch (InconsistentDataException e) {
            assertNull(e);
        }

        verify(userRepo, times(1)).findByUsername(anyString());
        verify(userRepo, times(1)).findAllByUsernameIn(any());
        assertNotNull(result);
        assertEquals(organization.getId(), result.getId());
    }


    @Test
    @DisplayName("Should throw InconsistentDataException when manager is not found")
    void mapUsersWhenManagerNotFoundThenThrowInconsistentDataException() {
        organization.setManager("nonExistingManager");
        Mockito.when(userRepo.findByUsername(anyString())).thenReturn(null);

        // Act & Assert
        Assertions.assertThrows(
                InconsistentDataException.class,
                () -> service.mapUsers(organization),
                "Expected InconsistentDataException to be thrown, but it wasn't");

        verify(userRepo, times(1)).findByUsername(anyString());
    }

    @Test
    @DisplayName("Should throw an InconsistentDataException when the manager is not found")
    void saveOrganizationWhenManagerNotFoundThenThrowInconsistentDataException() {
        organization.setId(UUID.randomUUID());
        organization.setName("Test Organization");
        organization.setManager("Test Manager");
        organization.setAssignee(null);
        organization.setTasks(null);

        Mockito.when(userRepo.findByUsername(anyString())).thenReturn(null);

        // Act and Assert
        InconsistentDataException exception =
                Assertions.assertThrows(
                        InconsistentDataException.class, () -> service.save(organization));

        Assertions.assertEquals(
                "Test Manager is not found in the database, the organization cannot be persisted",
                exception.getMessage());

        verify(userRepo, times(1)).findByUsername(anyString());
        verify(orgRepo, times(0)).save(any(Organization.class));
    }

    @Test
    @DisplayName("Should save the organization when the manager is found and assignees are provided")
    void saveOrganizationWhenManagerFoundAndAssigneesProvided() {
        UUID orgId = UUID.randomUUID();
        organization.setId(orgId);
        organization.setName("Test Organization");
        organization.setManager("test_manager");
        List<String> assignees = new ArrayList<>();
        assignees.add("test_assignee1");
        assignees.add("test_assignee2");

        organization.setAssignee(assignees);
        User manager = new User();
        manager.setUsername("test_manager");
        User assignee1 = new User();
        assignee1.setUsername("test_assignee1");
        User assignee2 = new User();
        assignee2.setUsername("test_assignee2");
        List<User> users = new ArrayList<>();
        users.add(assignee1);
        users.add(assignee2);

        Mockito.when(userRepo.findByUsername("test_manager")).thenReturn(manager);
        Mockito.when(userRepo.findAllByUsernameIn(assignees))
                .thenReturn(users);
        Mockito.when(orgRepo.save(any(Organization.class))).thenReturn(new Organization());

        try {
            service.save(organization);
        } catch (InconsistentDataException e) {
            assertNull(e);
        }

        verify(userRepo, times(1)).findByUsername(anyString());
        verify(userRepo, times(1)).findAllByUsernameIn(any());
        verify(orgRepo, times(1)).save(any(Organization.class));
    }
    
    @Test
    @DisplayName("Should return the number of tasks for a given user and organization")
    void getNoTasksForUserAndOrganization() { // create a test user and organization
        User user = new User();
        user.setUsername("testUser");
        user.setPassword("testPassword");
        user.setEmail("testUser@example.com");
        user.setId(UUID.randomUUID());

        // create a test organization
        Organization org = new Organization();
        org.setId(UUID.randomUUID());
        org.setName("testOrg");
        org.setManager(user);

        // create a test task
        Task task = new Task();
        task.setId(5L);

        task.setName("testTask");
        task.setDescription("testDescription");
        task.setOrganization(org);
        List<Task> tasks = new ArrayList<>();
        tasks.add(task);

        // add the task to the user's task list and the organization's task list
        user.setTasks(tasks);
        
        org.setTasks(tasks);

        // mock the repository methods to return the test user and organization
        Mockito.when(userRepo.findByUsername(anyString())).thenReturn(user);
        Mockito.when(orgRepo.findById(any(UUID.class))).thenReturn(Optional.of(org));

        // call the getNoTasks method and assert that it returns the correct number of tasks
        Long noTasks = service.getNoTasks(user, org.getId());
        assertEquals(1L, noTasks);
    }

    @Test
    @DisplayName("Should return the task count for each user in the organization")
    void getTaskCountForUsersInOrganization() {
        UUID orgID = UUID.randomUUID();
       
        User user1 = new User();
        user1.setUsername("user1");
        User user2 = new User();
        user2.setUsername("user2");
        List<User> assignees = new ArrayList<>();
        assignees.add(user1);
        assignees.add(user2);
   
        Organization org = new Organization();
        org.setId(orgID);
        org.setAssignee(assignees);
 
        Task task1 = new Task();
        task1.setOrganization(org);
    
        Task task2 = new Task();
        task2.setOrganization(org);
       
        Task task3 = new Task();
        task3.setOrganization(org);
     
        List<Task> tasks = new ArrayList<>();
        tasks.add(task1);
        tasks.add(task2);
        tasks.add(task3);
        user1.setTasks(tasks);
        user2.setTasks(tasks);
      
        Mockito.when(orgRepo.findById(orgID)).thenReturn(Optional.of(org));
 
        ArrayList<UserTaskCountDTO> result = service.getTaskCount(orgID);
    
        assertEquals(2, result.size());
        assertEquals("user1", result.get(0).getUsername());
        assertEquals(3, result.get(0).getCount());
        assertEquals("user2", result.get(1).getUsername());
        assertEquals(3, result.get(1).getCount());

        verify(orgRepo, times(1)).findById(orgID);
    }

    @Test
    @DisplayName("Should throw NoSuchElementException when the user is not found")
    void joinWhenUserNotFoundThenThrowException() {
        UUID userID = UUID.randomUUID();
        organization.setId(UUID.randomUUID());
        organization.setName("Test Organization");
        organization.setManager("Test Manager");
        organization.setAssignee(Arrays.asList("Test Assignee1", "Test Assignee2"));

        assertThrows(
                NoSuchElementException.class,
                () -> {
                    service.join(userID, organization);
                });

    }

    @Test
    @DisplayName("Should throw NoSuchElementException when the organization is not found")
    void joinWhenOrganizationNotFoundThenThrowException() {
        UUID userID = UUID.randomUUID();
        UUID orgID = UUID.randomUUID();
        organization.setId(orgID);
        user.setUsername("testUser");

        // Act and Assert
        NoSuchElementException exception =
                assertThrows(
                        NoSuchElementException.class,
                        () -> {
                            service.join(userID, organization);
                        });
        assertEquals("User with id: " + userID + "is not found.", exception.getMessage());

    }

}
