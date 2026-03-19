package com.bme.organic.model.entity;

import jakarta.persistence.*;
import org.hibernate.annotations.Cascade;

import java.util.List;
import java.util.UUID;

@Entity
@Table(name = "Users")
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private UUID id;
    @Column(unique = true)
    private String username;
    @Column(unique = true)
    private String email;
    private String password;
    @ManyToMany(mappedBy = "assignee")
    private List<Organization> organizations;
    @OneToMany
    @Cascade(org.hibernate.annotations.CascadeType.SAVE_UPDATE)
    private List<Task> tasks;

    public void addOrganization(Organization organization) {
        organizations.add(organization);
    }

    public void addTask(Task task) {
        tasks.add(task);
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public List<Task> getTasks() {
        return tasks;
    }

    public void setTasks(List<Task> tasks) {
        this.tasks = tasks;
    }

    public UUID getId() {
        return id;
    }

    public void setId(UUID id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public List<Organization> getOrganizations() {
        return organizations;
    }

    public void setOrganizations(List<Organization> organizations) {
        this.organizations = organizations;
    }
}

