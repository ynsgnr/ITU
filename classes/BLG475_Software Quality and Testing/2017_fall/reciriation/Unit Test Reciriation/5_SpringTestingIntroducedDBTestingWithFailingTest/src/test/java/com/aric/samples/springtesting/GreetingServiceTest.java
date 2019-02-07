package com.aric.samples.springtesting;

import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@RunWith(SpringRunner.class)
@SpringBootTest
public class GreetingServiceTest {
    private static final String FIRST_NAME = "Cemil";
    private static final String LAST_NAME = "Tekin";

    @Autowired
    private GreetingService greetingService;

    @Test
    public void testGreetShouldReturnAValidGreetingObjectWhenANameIsProvided() throws Exception {
        final Greeting greeting = greetingService.greet(FIRST_NAME);
        Assert.assertEquals(String.format("Hello %s", FIRST_NAME), greeting.getContent());
    }

    @Test
    public void testGreetShouldReturnAValidGreetingObjectWhenAnExistingIdProvided() throws Exception {
        final Greeting greeting = greetingService.greet(1);
        Assert.assertEquals(String.format("Hello %s %s", FIRST_NAME, LAST_NAME), greeting.getContent());
    }

}
