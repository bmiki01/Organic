package com.bme.organic.mapper;

import com.bme.organic.controller.dto.OrganizationDTO;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.model.entity.User;
import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.Named;

import java.util.ArrayList;
import java.util.List;

@Mapper(componentModel = "spring", uses = TaskMapper.class)
public interface OrganizationMapper {

    @Mapping(target = "assignee",source = "assignee",qualifiedByName = "nameListToUsers")
    @Mapping(target = "manager",source = "manager", qualifiedByName = "stringToUser")
    Organization DTOToEntity(OrganizationDTO dto);
    @Mapping(target = "assignee",source = "assignee",qualifiedByName = "userListToString")
    @Mapping(target = "manager",source = "manager",qualifiedByName = "userToString")
    OrganizationDTO EntityToDTO(Organization organization);
    List<Organization> DTOListToEntityList(List<OrganizationDTO> dtoList);
    List<OrganizationDTO> EntityListToDTOList(List<Organization> organizations);

    @Named("userListToString")
    static List<String> userAttribute(List<User> userList){
        if(userList == null) return new ArrayList<>();
        List<String> result = new ArrayList<>();
        for(User u : userList)
            result.add(u.getUsername());
        return result;
    }
    //This method exists only for the implementation to be generated correctly
    @Named("nameListToUsers")
    static List<User> nameListToUsers(List<String> stringList){
        if(stringList == null) return new ArrayList<>();
        List<User> users = new ArrayList<>();
        for(String s : stringList){
            User u = new User();
            u.setUsername(u.getUsername());
            users.add(u);
        }
        return users;
    }

    @Named("userToString")
    static String userToString(User user){
        if(user == null) return "";
        return user.getUsername();
    }
    @Named("stringToUser")
    static User stringToUser(String name){
        if(name == null) return null;
        User result = new User();
        result.setUsername(name);
        return result;
    }
}
