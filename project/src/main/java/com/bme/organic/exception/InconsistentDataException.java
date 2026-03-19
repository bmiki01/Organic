package com.bme.organic.exception;

/**
 * This exception is thrown if the received value is
 * inconsistent with the state of the database
 */
public class InconsistentDataException extends RuntimeException {

    public InconsistentDataException(String errorMessage) {
        super(errorMessage);
    }

}