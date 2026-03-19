package com.bme.organic.controller.rest;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import javax.management.openmbean.KeyAlreadyExistsException;

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
import com.bme.organic.controller.dto.UserDTO;
import com.bme.organic.service.UserService;


@ExtendWith(MockitoExtension.class)
public class UserControllerTest {

    @Mock
    private UserService userService;

    @InjectMocks
    private UserController userController;

    @Test
    @DisplayName("Should return a list of all users with status OK")
    void getUserReturnsListOfUsersWithStatusOk() {
        List<UserDTO> userList = new ArrayList<>();
        UserDTO user1 = new UserDTO();
        user1.setId(UUID.randomUUID());
        user1.setUsername("user1");
        user1.setEmail("user1@example.com");
        userList.add(user1);

        UserDTO user2 = new UserDTO();
        user2.setId(UUID.randomUUID());
        user2.setUsername("user2");
        user2.setEmail("user2@example.com");
        userList.add(user2);

        when(userService.getAllUsers()).thenReturn(userList);

        ResponseEntity<List<UserDTO>> response = userController.getUser();

        assertEquals(HttpStatus.OK, response.getStatusCode());
        assertEquals(userList, response.getBody());
        verify(userService, times(1)).getAllUsers();
    }

    @Test
    @DisplayName("Should return unauthorized status when the credentials are invalid")
    void loginWhenCredentialsAreInvalidThenReturnUnauthorized() {
        UserDTO userDTO = new UserDTO();
        userDTO.setUsername("testuser");
        userDTO.setPassword("testpassword");

        when(userService.authenticate(userDTO)).thenReturn(null);

        ResponseEntity<UserDTO> response = userController.login(userDTO);

        assertEquals(HttpStatus.UNAUTHORIZED, response.getStatusCode());
        verify(userService, times(1)).authenticate(userDTO);
    }

    @Test
    @DisplayName("Should return the authenticated user when the credentials are valid")
    void loginWhenCredentialsAreValid() {
        UserDTO userDTO = new UserDTO();
        userDTO.setUsername("testuser");
        userDTO.setPassword("testpassword");

        UserDTO authenticatedUser = new UserDTO();
        authenticatedUser.setId(UUID.randomUUID());
        authenticatedUser.setUsername("testuser");
        authenticatedUser.setEmail("testuser@example.com");

        when(userService.authenticate(userDTO)).thenReturn(authenticatedUser);

        ResponseEntity<UserDTO> response = userController.login(userDTO);

        assertEquals(HttpStatus.OK, response.getStatusCode());
        assertEquals(authenticatedUser, response.getBody());
        verify(userService, times(1)).authenticate(userDTO);
    }

    @Test
    @DisplayName("Should save the user and return created status when the username is not taken")
    void saveUserWhenUsernameIsNotTaken() {
        UserDTO userDTO = new UserDTO();
        userDTO.setUsername("testuser");
        userDTO.setEmail("testuser@example.com");
        userDTO.setPassword("testpassword");
        List<OrganizationDTO> organizations = new ArrayList<>();
        userDTO.setOrganizations(organizations);

        when(userService.saveUser(userDTO)).thenReturn(userDTO);

        ResponseEntity<UserDTO> response = userController.save(userDTO);

        assertEquals(HttpStatus.CREATED, response.getStatusCode());
        assertEquals(userDTO, response.getBody());
        verify(userService, times(1)).saveUser(userDTO);
    }

    @Test
    @DisplayName("Should return conflict status when the username is already taken")
    void saveUserWhenUsernameIsAlreadyTakenThenReturnConflictStatus() {
        UserDTO userDTO = new UserDTO();
        userDTO.setUsername("john.doe");
        userDTO.setEmail("john.doe@example.com");
        userDTO.setPassword("password");
        List<OrganizationDTO> organizations = new ArrayList<>();
        userDTO.setOrganizations(organizations);

        List<TaskDTO> tasks = new ArrayList<>();
        userDTO.setTasks(tasks);

        when(userService.saveUser(userDTO)).thenThrow(new KeyAlreadyExistsException());

        ResponseEntity<UserDTO> response = userController.save(userDTO);

        assertEquals(HttpStatus.CONFLICT, response.getStatusCode());
        verify(userService, times(1)).saveUser(userDTO);
    }
}
