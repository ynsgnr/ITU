package com.aric.samples.springtesting;

import java.util.Optional;

import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.util.ReflectionTestUtils;

@RunWith(SpringRunner.class)
@SpringBootTest
public class GreetingServiceTest {
    private static Person CEMIL;
    private static final String FIRST_NAME = "Cemil";
    private static final String LAST_NAME = "Tekin";

    @BeforeClass
    public static void setUpBeforeClass() {
        CEMIL = new Person();
        CEMIL.setFirstName(FIRST_NAME);
        CEMIL.setLastName(LAST_NAME);
    }

    @Autowired
    private GreetingService greetingService;

    @Before
    public void setUp() {
        final PersonRepository mockPersonRepository = Mockito.mock(PersonRepository.class);
        ReflectionTestUtils.setField(greetingService, "personRepository", mockPersonRepository);
        Mockito.when(mockPersonRepository.findById(1l)).thenReturn(Optional.of(CEMIL));
    }

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
