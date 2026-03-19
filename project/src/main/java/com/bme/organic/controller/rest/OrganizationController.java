package com.bme.organic.controller.rest;

import com.bme.organic.controller.dto.OrganizationDTO;
import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.controller.dto.UserTaskCountDTO;
import com.bme.organic.exception.InconsistentDataException;
import com.bme.organic.model.entity.Organization;
import com.bme.organic.service.OrganizationService;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import javax.management.BadAttributeValueExpException;
import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.UUID;

@RestController
@RequestMapping("api/organization")
public class OrganizationController {

    OrganizationService service;
    private static final Logger logger = LogManager.getLogger("method");

    public OrganizationController(OrganizationService service) {
        this.service = service;
    }

    @GetMapping
    public ResponseEntity<List<OrganizationDTO>> getTasks(){
        return new ResponseEntity<>(service.getAll(),HttpStatus.OK);
    }

    @PostMapping
    public ResponseEntity<OrganizationDTO> save(@RequestBody OrganizationDTO organization) {
        try {
            OrganizationDTO saved = service.save(organization);
            return new ResponseEntity<>(saved, HttpStatus.CREATED);
        } catch(InconsistentDataException ide) {
            logger.warn(ide.getMessage());
            return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
        }
    }

    @PostMapping("/join/{userID}")
    public ResponseEntity<OrganizationDTO> join(@PathVariable UUID userID, @RequestBody OrganizationDTO dto) {
        try {
            OrganizationDTO found = service.join(userID,dto);
            return ResponseEntity.ok(found);
        } catch(NoSuchElementException ex) {
            logger.debug(ex.getMessage());
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @GetMapping("/tasks/{username}/{orgID}")
    public ResponseEntity<ArrayList<TaskDTO>> getTasks(@PathVariable String username, @PathVariable UUID orgID) {
        try{
            ArrayList<TaskDTO> tasks = service.getTasks(username, orgID);
            return ResponseEntity.ok(tasks);
        } catch(NoSuchElementException ex) {
            logger.debug(ex.getMessage());
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

    @GetMapping("/taskcount/{orgID}")
    public ResponseEntity<ArrayList<UserTaskCountDTO>> getTaskCount(@PathVariable UUID orgID) {
        try{
            ArrayList<UserTaskCountDTO> countDTO = service.getTaskCount(orgID);
            return ResponseEntity.ok(countDTO);
        } catch(NoSuchElementException ex) {
            logger.debug(ex.getMessage());
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
    }

}
