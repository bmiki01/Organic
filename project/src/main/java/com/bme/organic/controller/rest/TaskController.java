package com.bme.organic.controller.rest;

import com.bme.organic.controller.dto.TaskDTO;
import com.bme.organic.exception.InconsistentDataException;
import com.bme.organic.service.TaskService;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.UUID;

@RestController
@RequestMapping("/api/task")
public class TaskController {

    TaskService service;
    private static final Logger logger = LogManager.getLogger("method");

    public TaskController(TaskService service) {
        this.service = service;
    }

    @GetMapping
    public ResponseEntity<List<TaskDTO>> getTasks(){
        return new ResponseEntity<>(service.getAll(), HttpStatus.OK);
    }

    @PostMapping("/{userId}")
    public ResponseEntity<TaskDTO> save(@PathVariable UUID userId , @RequestBody TaskDTO task){
        try {
            TaskDTO saved = service.save(userId, task);
            return new ResponseEntity<>(saved, HttpStatus.CREATED);
        } catch(InconsistentDataException ide) {
            logger.warn(ide.getMessage());
            return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
        }
    }
}
