package com.bme.organic.mapper;

import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.model.entity.Task;
import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.Named;

import java.util.List;

@Mapper(componentModel = "spring")
public interface TaskMapper {
    @Mapping(target = "organization",source = "organization",qualifiedByName = "orgToStr")
    TaskDTO EntityToDTO(Task entity);
    @Mapping(target = "organization",source = "organization",qualifiedByName = "strToOrg")
    Task DTOToEntity(TaskDTO dto);
    List<TaskDTO> EntityListToDTOList(List<Task> taskList);
    List<Task> DTOListToEntityList(List<TaskDTO> dtoList);

    @Named("orgToStr")
    static String orgToStr(Organization org){
        return org.getName();
    }
    @Named("strToOrg")
    static Organization strToOrg(String name) {
        Organization org = new Organization();
        org.setName(name);
        return org;
    }
}
