package com.aric.samples.mocking;

import java.util.List;

/**
 * @author dursun
 *
 */
public class CustomerService {
    private final Database database;

    public CustomerService(final Database database) {
        this.database = database;
    }

    public List<Customer> findCustomerByFirst(final String first) {
        return this.database.getCustomersByFirst(first);
    }
}
