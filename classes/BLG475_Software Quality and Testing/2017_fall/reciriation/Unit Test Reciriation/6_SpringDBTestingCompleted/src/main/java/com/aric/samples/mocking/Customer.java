package com.aric.samples.mocking;

/**
 * @author dursun
 *
 */
public class Customer {
    private String first;
    private long id;
    private String last;

    public Customer() {
    }

    public Customer(final long id, final String firstName, final String lastName) {
        this.id = id;
        this.first = firstName;
        this.last = lastName;
    }

    public String getFirst() {
        return first;
    }

    public long getId() {
        return id;
    }

    public String getLast() {
        return last;
    }

    public void setFirst(final String first) {
        this.first = first;
    }

    public void setId(final long id) {
        this.id = id;
    }

    public void setLast(final String last) {
        this.last = last;
    }

    @Override
    public String toString() {
        return String.format("Customer{id=%d, firs='%s', last='%s'}", id, first, last);
    }
}
