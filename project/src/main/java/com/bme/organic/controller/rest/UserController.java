package com.bme.organic.controller.rest;
import com.bme.organic.controller.dto.UserDTO;
import com.bme.organic.service.UserService;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import javax.management.openmbean.KeyAlreadyExistsException;
import java.util.List;

@RestController
@RequestMapping("/api/user")
public class UserController {

    private UserService service;
    private static final Logger logger = LogManager.getLogger("method");

    public UserController(UserService service) {
        this.service = service;
    }

    @GetMapping()
    public ResponseEntity<List<UserDTO>> getUser() {
        logger.debug("GET - Users");
        List<UserDTO> users = service.getAllUsers();
        return new ResponseEntity<>(users, HttpStatus.OK);
    }
    @PostMapping
    public ResponseEntity<UserDTO> save(@RequestBody UserDTO userDTO) {
        logger.debug("SAVE - User: " + userDTO.getUsername());
        try {
            UserDTO saved = service.saveUser(userDTO);
            return new ResponseEntity<>(saved, HttpStatus.CREATED);
        } catch(KeyAlreadyExistsException ex) {
            return new ResponseEntity<>(HttpStatus.CONFLICT);
        }
    }

    @PostMapping("/login")
    public ResponseEntity<UserDTO> login(@RequestBody UserDTO userDTO) {
        logger.debug("LOGIN");
        UserDTO found = service.authenticate(userDTO);
        if(found != null) {
            return ResponseEntity.ok(found);
        }
        return new ResponseEntity<>(HttpStatus.UNAUTHORIZED);
    }

}
