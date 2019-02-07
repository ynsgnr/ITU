/**
 *
 */
package com.aric.samples.springtesting;

import java.util.concurrent.atomic.AtomicLong;

import org.springframework.stereotype.Service;

/**
 * @author dursun
 *
 */
@Service
public class GreetingService {
    private static final String T = "Hello %s";
    private final AtomicLong counter = new AtomicLong();

    public Greeting greet(final String name) {
        return new Greeting(counter.incrementAndGet(), String.format(T, name));
    }
}
