package com.bme.organic.service;

import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.exception.InconsistentDataException;
import com.bme.organic.mapper.TaskMapper;
import com.bme.organic.model.dao.OrganizationRepository;
import com.bme.organic.model.dao.TaskRepository;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.model.entity.Task;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class TaskService {

    TaskRepository repository;
    TaskMapper mapper;
    OrganizationRepository orgRepository;

    public TaskService(TaskRepository repository, TaskMapper mapper, OrganizationRepository orgRepository) {
        this.repository = repository;
        this.mapper = mapper;
        this.orgRepository = orgRepository;
    }

    public TaskDTO save(TaskDTO taskDTO) throws InconsistentDataException {
        Task task = mapOrganization(taskDTO);
        return mapper.EntityToDTO(repository.save(task));
    }

    /**
     * Find the organization from the database
     */
    public Task mapOrganization(TaskDTO taskDTO) throws InconsistentDataException {
        Task task = mapper.DTOToEntity(taskDTO);
        if(taskDTO.getOrganization() == null) {
            return task;
        }
        Organization org = orgRepository.findByName(taskDTO.getOrganization());
        if(org == null) {
            throw new InconsistentDataException(taskDTO.getOrganization() + " is not found in the database");
        }
        task.setOrganization(org);
        return task;
    }

    public List<TaskDTO> getAll(){
        return mapper.EntityListToDTOList(repository.findAll());
    }

}
