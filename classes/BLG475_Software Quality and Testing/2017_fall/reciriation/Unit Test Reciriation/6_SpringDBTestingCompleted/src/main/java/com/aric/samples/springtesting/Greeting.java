package com.aric.samples.springtesting;

/**
 * @author dursun
 *
 */
public class Greeting {

    private final String content;
    private final long id;

    public Greeting(final long id, final String content) {
        this.id = id;
        this.content = content;
    }

    public String getContent() {
        return content;
    }

    public long getId() {
        return id;
    }
}
