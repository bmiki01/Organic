package com.bme.organic.model.dao;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import java.util.ArrayList;
import java.util.List;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.mockito.Mock;
import org.mockito.Mockito;

import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.test.context.ContextConfiguration;

import com.bme.organic.OrganicApplication;
import com.bme.organic.model.entity.User;


@DataJpaTest
@ContextConfiguration(classes = OrganicApplication.class)
public class UserRepositoryTest {

    @Mock
    private UserRepository userRepository;

    private static User user;
    private static User user2;
    private static List<String> list;
    private static List<User> list2;

    @BeforeAll
    public static void init(){
       user = new User();
       user.setEmail("bob@test.com");
       user.setPassword("bob");
       user.setUsername("Bob");
       user2 = new User();
       user2.setEmail("bob2@test.com");
       user2.setPassword("bob2");
       user2.setUsername("Bob2");
       list = new ArrayList<String>();
       list2 = new ArrayList<User>();
    }

    @AfterEach
    public void clear(){
        userRepository.deleteAll();
    }


    @Test
    void testFindAllByUsernameIn() {
        Mockito.when(userRepository.findAllByUsernameIn(list)).thenReturn(list2);
        list2.add(user);
        list2.add(user2);
        list.add(user.getUsername());
        list.add(user2.getUsername());
        List<User> users = userRepository.findAllByUsernameIn(list);
        assertEquals(2, users.size());
        assertEquals("Bob", users.get(0).getUsername());
        assertEquals("Bob2", users.get(1).getUsername());
        assertNotEquals(users.get(0).getEmail(), users.get(1).getEmail());
    }

    @Test
    void testFindByUsername() {
        Mockito.when(userRepository.findByUsername("Bob")).thenReturn(user);
        User result = userRepository.findByUsername("Bob");
        assertEquals(result.getUsername(), user.getUsername());
    }
}
