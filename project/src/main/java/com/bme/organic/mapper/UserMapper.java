package com.bme.organic.mapper;

import com.bme.organic.controller.dto.UserDTO;
import com.bme.organic.model.entity.User;
import org.mapstruct.Mapper;

import java.util.List;

@Mapper(componentModel = "spring",uses = {OrganizationMapper.class, TaskMapper.class})
public interface UserMapper {
    UserDTO EntityToDTO(User entity);
    User DTOToEntity(UserDTO dto);
    List<UserDTO> EntityListToDTOList(List<User> userList);
    List<User> DTOListToEntityList(List<UserDTO> dtoList);
}
