package com.bme.organic.model.entity;

import jakarta.persistence.*;

import java.util.List;
import java.util.UUID;

@Entity
public class Organization {
    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private UUID id;
    @Column(unique = true)
    private String name;
    @OneToMany(mappedBy = "organization", cascade = {CascadeType.REMOVE})
    private List<Task> tasks;
    @ManyToMany
    private List<User> assignee;
    @OneToOne
    private User manager;

    public void addAssignee(User user) {
        assignee.add(user);
    }

    public UUID getId() {
        return id;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<Task> getTasks() {
        return tasks;
    }

    public void setTasks(List<Task> tasks) {
        this.tasks = tasks;
    }

    public List<User> getAssignee() {
        return assignee;
    }

    public void setAssignee(List<User> assignee) {
        this.assignee = assignee;
    }

    public User getManager() {
        return manager;
    }

    public void setManager(User manager) {
        this.manager = manager;
    }
}
