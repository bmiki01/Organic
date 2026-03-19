package com.bme.organic.model.dao;

import com.bme.organic.model.entity.User;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;
import java.util.UUID;

public interface UserRepository extends JpaRepository<User, UUID> {
    User findByUsername(String username);
    List<User> findAllByUsernameIn(List<String> usernameList);
}
