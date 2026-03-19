package com.bme.organic.service;

import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.exception.InconsistentDataException;
import com.bme.organic.mapper.TaskMapper;
import com.bme.organic.model.dao.OrganizationRepository;
import com.bme.organic.model.dao.TaskRepository;
import com.bme.organic.model.dao.UserRepository;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.model.entity.Task;
import com.bme.organic.model.entity.User;
import jakarta.transaction.Transactional;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.NoSuchElementException;
import java.util.UUID;

@Service
public class TaskService {

    TaskRepository repository;
    TaskMapper mapper;
    OrganizationRepository orgRepository;
    UserRepository userRepository;

    public TaskService(TaskRepository repository, TaskMapper mapper, OrganizationRepository orgRepository, UserRepository userRepository) {
        this.repository = repository;
        this.mapper = mapper;
        this.orgRepository = orgRepository;
        this.userRepository = userRepository;
    }

    @Transactional
    public TaskDTO save(UUID userId, TaskDTO taskDTO) throws InconsistentDataException {
        Task task = mapper.DTOToEntity(taskDTO);
        Organization org = mapOrganization(taskDTO);
        task.setOrganization(org);
        org.addTask(task);
        User user = mapUser(userId, task);
        Task saved = repository.save(task);
        userRepository.save(user);
        return mapper.EntityToDTO(saved);
    }

    public User mapUser(UUID userId, Task task) {
        User user = userRepository.findById(userId).orElseThrow(NoSuchElementException::new);
        user.addTask(task);
        return user;
    }

    /**
     * Find the organization from the database
     */
    public Organization mapOrganization(TaskDTO taskDTO) throws InconsistentDataException {
        Task task = mapper.DTOToEntity(taskDTO);
        if(taskDTO.getOrganization() == null) {
            return null;
        }
        Organization org = orgRepository.findByName(taskDTO.getOrganization());
        if(org == null) {
            throw new InconsistentDataException(taskDTO.getOrganization() + " is not found in the database");
        }
        return org;
    }

    public List<TaskDTO> getAll(){
        return mapper.EntityListToDTOList(repository.findAll());
    }

}
