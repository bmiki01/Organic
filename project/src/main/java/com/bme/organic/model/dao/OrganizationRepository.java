package com.bme.organic.model.dao;

import com.bme.organic.model.entity.Organization;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;
import java.util.UUID;

public interface OrganizationRepository extends JpaRepository<Organization, UUID> {

    Organization findByName(String name);

}
