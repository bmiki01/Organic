package com.bme.organic.service;

import com.bme.organic.controller.dto.UserDTO;
import com.bme.organic.mapper.UserMapper;
import com.bme.organic.model.entity.User;
import com.bme.organic.model.dao.UserRepository;
import org.hibernate.exception.ConstraintViolationException;
import org.springframework.stereotype.Service;

import javax.management.openmbean.KeyAlreadyExistsException;
import java.util.List;

@Service
public class UserService {

    private UserRepository repository;
    private UserMapper mapper;

    public UserService(UserRepository repository, UserMapper mapper) {
        this.repository = repository;
        this.mapper = mapper;
    }

    public UserDTO saveUser(UserDTO dto) {
        if(!validate(dto)) {
            throw new KeyAlreadyExistsException("User with username: " + dto.getUsername() + " already exists");
        }
        User entity = mapper.DTOToEntity(dto);
        return mapper.EntityToDTO(repository.save(entity));
    }

    public boolean validate(UserDTO dto) {
        User found = repository.findByUsername(dto.getUsername());
        if(found != null)
            return false;
        return true;
    }

    public UserDTO authenticate(UserDTO dto) {
        User found = repository.findByUsername(dto.getUsername());
        if(found != null) {
            if (dto.getPassword().equals(found.getPassword()))
                    return mapper.EntityToDTO(found);
        }
        return null;
    }

    public List<UserDTO> getAllUsers(){
        return mapper.EntityListToDTOList(repository.findAll());
    }
}
