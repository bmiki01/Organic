package com.bme.organic.service;

import com.bme.organic.model.dao.OrganizationRepository;
import com.bme.organic.model.entity.Organization;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.annotation.EnableScheduling;
import org.springframework.scheduling.annotation.Scheduled;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Configuration
@EnableScheduling
public class ScheduleService {

    private static final Logger logger = LogManager.getLogger("method");
    OrganizationRepository orgRepo;

    public ScheduleService(OrganizationRepository orgRepo) {
        this.orgRepo = orgRepo;
    }

    @Scheduled(cron = "0 0 22 * * ?")
    public void logStatus() {
        Map<String, Integer> taskPerOrg = new HashMap<>();
        List<Organization> orgs = orgRepo.findAll();
        for(Organization org: orgs) {
            taskPerOrg.put(org.getName(), org.getTasks().size());
        }
        logger.info(taskPerOrg);
    }


}
