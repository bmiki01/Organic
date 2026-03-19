package com.bme.organic.service;

import com.bme.organic.controller.dto.OrganizationDTO;
import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.controller.dto.UserTaskCountDTO;
import com.bme.organic.exception.InconsistentDataException;
import com.bme.organic.mapper.OrganizationMapper;
import com.bme.organic.mapper.TaskMapper;
import com.bme.organic.model.dao.OrganizationRepository;
import com.bme.organic.model.dao.UserRepository;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.model.entity.Task;
import com.bme.organic.model.entity.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.data.crossstore.ChangeSetPersister;
import org.springframework.stereotype.Service;

import javax.management.BadAttributeValueExpException;
import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.UUID;

@Service
public class OrganizationService {

    OrganizationMapper mapper;
    TaskMapper taskMapper;
    OrganizationRepository repository;
    UserRepository userRepository;

    public OrganizationService(OrganizationMapper mapper, OrganizationRepository repository,
                               UserRepository userRepository, TaskMapper taskMapper) {
        this.mapper = mapper;
        this.taskMapper = taskMapper;
        this.repository = repository;
        this.userRepository = userRepository;
    }

    public OrganizationDTO save(OrganizationDTO organization) throws InconsistentDataException {
        Organization org = mapUsers(organization);
        return mapper.EntityToDTO(repository.save(org));
    }

    public Organization mapUsers(OrganizationDTO organization) throws InconsistentDataException {
        User manager = userRepository.findByUsername(organization.getManager());
        if(manager == null) {
            throw new InconsistentDataException(organization.getManager() +
                    " is not found in the database, the organization cannot be persisted");
        }
        List<User> users = null;
        if(organization.getAssignee() != null) {
            users = userRepository.findAllByUsernameIn(organization.getAssignee());
        }

        Organization org = mapper.DTOToEntity(organization);
        if(users != null) {
            org.setAssignee(users);
        }
        org.setManager(manager);
        return org;
    }

    public List<OrganizationDTO> getAll(){
        return mapper.EntityListToDTOList(repository.findAll());
    }

    public OrganizationDTO join(UUID userID, OrganizationDTO dto) throws NoSuchElementException {
        User foundUser = findUser(userID);
        Organization foundOrg = findOrganization(dto.getId());
        foundOrg.addAssignee(foundUser);
        repository.save(foundOrg);
        return mapper.EntityToDTO(foundOrg);
    }

    public ArrayList<TaskDTO> getTasks(String username, UUID orgID) {
        User foundUser = findUserByUsername(username);
        Organization foundOrg = findOrganization(orgID);
        ArrayList<TaskDTO> tasksInOrg = new ArrayList<>();
        for(Task task : foundUser.getTasks()) {
            if(task.getOrganization().getId().equals(foundOrg.getId()))
                tasksInOrg.add(taskMapper.EntityToDTO(task));
        }
        return tasksInOrg;
    }

    public User findUser(UUID userID) {
        User found = userRepository.findById(userID).orElseThrow(() ->
                new NoSuchElementException("User with id: " + userID + "is not found."));
        return found;
    }

    public Organization findOrganization(UUID orgID) {
        Organization found = repository.findById(orgID).orElseThrow(() ->
                new NoSuchElementException("Organization with id: " + orgID + " not found."));
        return found;
    }


    public User findUserByUsername(String username) {
        User found = userRepository.findByUsername(username);
        if(found == null) {
            throw new NoSuchElementException("User with username: " + username + "is not found.");
        }
        return found;
    }

    public ArrayList<UserTaskCountDTO> getTaskCount(UUID orgID) {
        Organization found = findOrganization(orgID);
        ArrayList<UserTaskCountDTO> countDTOList = new ArrayList<>();
        for(User assignee : found.getAssignee()) {
            UserTaskCountDTO userTaskCountDTO = new UserTaskCountDTO();
            userTaskCountDTO.setUsername(assignee.getUsername());
            userTaskCountDTO.setCount(getNoTasks(assignee, orgID));
            countDTOList.add(userTaskCountDTO);
        }
        return countDTOList;
    }

    public Long getNoTasks(User assignee, UUID orgID) {
        Long noTasks = 0L;
        for(Task task : assignee.getTasks()) {
            if(task.getOrganization().getId().equals(orgID))
                noTasks++;
        }
        return noTasks;
    }
}
