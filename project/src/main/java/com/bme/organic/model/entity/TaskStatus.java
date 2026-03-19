package com.bme.organic.model.entity;

public enum TaskStatus {
    READY_TO_START("Ready to start"),
    IN_PROGRESS("In progress"),
    BLOCKED("Blocked"),
    DONE("Done");

    public final String label;
    private TaskStatus(String label){
        this.label = label;
    }
}
