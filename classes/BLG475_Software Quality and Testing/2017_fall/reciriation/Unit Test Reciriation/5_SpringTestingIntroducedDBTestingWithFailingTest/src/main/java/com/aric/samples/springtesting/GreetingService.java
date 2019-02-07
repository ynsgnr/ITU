/**
 *
 */
package com.aric.samples.springtesting;

import java.util.concurrent.atomic.AtomicLong;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * @author dursun
 *
 */
@Service
public class GreetingService {
    private static final String T = "Hello %s";
    private final AtomicLong counter = new AtomicLong();

    @Autowired
    private PersonRepository personRepository;

    public Greeting greet(final Integer id) {
        final Person personFound = personRepository.findById(id.longValue()).orElseGet(() -> {
            final Person person = new Person();
            person.setFirstName("World");
            person.setLastName("Planet");
            return person;
        });
        final String name = personFound.getName();
        return new Greeting(counter.incrementAndGet(), String.format(T, name));
    }

    public Greeting greet(final String name) {
        return new Greeting(counter.incrementAndGet(), String.format(T, name));
    }
}
