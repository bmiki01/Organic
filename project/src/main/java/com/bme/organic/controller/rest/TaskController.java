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

    @PostMapping
    public ResponseEntity<TaskDTO> save(@RequestBody TaskDTO task){
        try {
            TaskDTO saved = service.save(task);
            return new ResponseEntity<>(saved, HttpStatus.CREATED);
        } catch(InconsistentDataException ide) {
            logger.warn(ide.getMessage());
            return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
        }
    }
}
