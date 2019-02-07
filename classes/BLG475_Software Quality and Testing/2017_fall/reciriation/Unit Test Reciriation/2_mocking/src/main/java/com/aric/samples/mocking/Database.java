/**
 *
 */
package com.aric.samples.mocking;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * @author dursun
 *
 */
public class Database {
    private List<Customer> customers;

    public Database() {
        customers = new ArrayList<>();
    }

    public boolean addCustomer(final Customer c) {
        return this.customers.add(c);
    }

    public boolean deleteCustomer(final Customer c) {
        return this.customers.remove(c);
    }

    public void destroy() {
        this.customers = new ArrayList<>();
    }

    public Stream<Customer> getCustomers() {
        return this.customers.stream();
    }

    public List<Customer> getCustomersByFirst(final String first) {
        return getCustomers().filter(c -> c.getFirst().equalsIgnoreCase(first)).collect(Collectors.toList());
    }

}
