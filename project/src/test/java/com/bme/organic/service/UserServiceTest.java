package com.bme.organic.service;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.anyString;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.List;

import javax.management.openmbean.KeyAlreadyExistsException;

import org.junit.jupiter.api.AfterEach;
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
import com.bme.organic.controller.dto.UserDTO;
import com.bme.organic.mapper.UserMapper;
import com.bme.organic.model.dao.UserRepository;
import com.bme.organic.model.entity.User;



@ExtendWith({MockitoExtension.class, SpringExtension.class})
@ContextConfiguration(classes = OrganicApplication.class)
@SpringBootTest
public class UserServiceTest {


    @Autowired
    UserMapper mapper;
    private static UserService service;
    private static UserDTO user;
    @Mock
    private UserRepository repository;

    @BeforeAll
    static void init() {
        user = new UserDTO();
        user.setUsername("Bob");
        user.setPassword("bob");
    }

    @BeforeEach
    void setUp() {
        service = new UserService(repository, mapper);
    }

    @AfterEach
    void tearDown() {
        Mockito.reset(repository);
    }


    @Test
    @DisplayName("Should return null when the username is not found")
    void authenticateWhenUsernameNotFound() {
        when(repository.findByUsername(anyString())).thenReturn(null);

        UserDTO result = service.authenticate(user);

        assertNull(result);
        verify(repository, times(1)).findByUsername(user.getUsername());
    }

    @Test
    @DisplayName("Should return the user when the username and password are correct")
    void authenticateWhenUsernameAndPasswordAreCorrect() {
        User userEntity = new User();
        userEntity.setUsername("Bob");
        userEntity.setPassword("bob");
        when(repository.findByUsername(anyString())).thenReturn(userEntity);

        UserDTO result = service.authenticate(user);

        assertNotNull(result);
        assertEquals(user.getUsername(), result.getUsername());
    }

    @Test
    @DisplayName("Should return null when the password is incorrect")
    void authenticateWhenPasswordIsIncorrect() {
        User userEntity = new User();
        userEntity.setUsername(user.getUsername());
        userEntity.setPassword("wrong_password");
        when(repository.findByUsername(anyString())).thenReturn(userEntity);

        UserDTO result = service.authenticate(user);

        assertNull(result);
        verify(repository, times(1)).findByUsername(user.getUsername());
    }

    @Test
    @DisplayName("Should return an empty list when there are no users")
    void getAllUsersWhenNoUsersExist() {
        List<User> userList = new ArrayList<>();
        when(repository.findAll()).thenReturn(userList);

        List<UserDTO> userDTOList = service.getAllUsers();

        assertTrue(userDTOList.isEmpty());
        verify(repository, times(1)).findAll();
    }

    @Test
    void testGetAllUsers() {
        List<User> userList = new ArrayList<>();
        User user1 = new User();
        User user2 = new User();
        userList.add(user1);
        userList.add(user2);
        when(repository.findAll()).thenReturn(userList);

        List<UserDTO> userDTOList = service.getAllUsers();
        assertEquals(userList.size(), userDTOList.size());
        assertEquals(user1.getUsername(), userDTOList.get(0).getUsername());
        assertEquals(user2.getUsername(), userDTOList.get(1).getUsername());
        verify(repository, times(1)).findAll();
    }

    @Test
    @DisplayName("Should throw an exception when the username is already taken")
    void saveUserWhenUsernameIsAlreadyTakenThenThrowException() {
        UserDTO userDTO = new UserDTO();
        userDTO.setUsername("Bob");
        userDTO.setPassword("bob");

        User user = new User();
        user.setUsername("Bob");
        user.setPassword("bob");

        Mockito.when(repository.findByUsername(anyString())).thenReturn(user);

        try {
            service.saveUser(userDTO);
        } catch (KeyAlreadyExistsException e) {
            assertEquals("User with username: Bob already exists", e.getMessage());
            verify(repository, times(1)).findByUsername(anyString());
        }
    }

    @Test
    @DisplayName("Should save the user when the username is not taken")
    void saveUserWhenUsernameIsNotTaken() {
        UserDTO userDTO = new UserDTO();
        userDTO.setUsername("Bob");
        userDTO.setPassword("bob");

        User user = new User();
        user.setUsername("Bob");
        user.setPassword("bob");

        when(repository.findByUsername(anyString())).thenReturn(null);
        when(repository.save(any(User.class))).thenReturn(user);

        UserDTO savedUserDTO = service.saveUser(userDTO);

        verify(repository, times(1)).findByUsername(userDTO.getUsername());
        verify(repository, times(1)).save(any(User.class));
        assertEquals(userDTO.getUsername(), savedUserDTO.getUsername());
        assertEquals(userDTO.getPassword(), savedUserDTO.getPassword());
    }

    @Test
    @DisplayName("Should return true when the username is not found in the repository")
    void validateWhenUsernameNotFound() {
        when(repository.findByUsername(anyString())).thenReturn(null);

        boolean result = service.validate(user);

        assertTrue(result);
        verify(repository, times(1)).findByUsername(user.getUsername());
    }

    @Test
    @DisplayName("Should return false when the username is found in the repository")
    void validateWhenUsernameFound() {
        User foundUser = new User();
        foundUser.setUsername(user.getUsername());
        when(repository.findByUsername(anyString())).thenReturn(foundUser);

        boolean result = service.validate(user);

        assertFalse(result);
        verify(repository, times(1)).findByUsername(user.getUsername());
    }

}
