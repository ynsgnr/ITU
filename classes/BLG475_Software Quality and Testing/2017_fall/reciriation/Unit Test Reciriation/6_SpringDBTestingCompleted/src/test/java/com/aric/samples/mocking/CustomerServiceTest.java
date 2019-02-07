package com.aric.samples.mocking;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;

public class CustomerServiceTest {
    private final Customer[] customers = new Customer[] { new Customer(1, "Dursun", "KOC"),
            new Customer(2, "Dursun", "Ozbek") };
    private Database database;

    @Before
    public void setUp() {
        database = Mockito.mock(Database.class);
        Mockito.when(database.getCustomers()).thenReturn(Stream.of(customers));
        Mockito.when(database.getCustomersByFirst("Dursun")).thenReturn(Arrays.asList(customers));
    }

    /**
     * @throws Exception
     */
    @Test
    public void testFindCustomerByFirst() throws Exception {
        final CustomerService customerService = new CustomerService(database);
        customerService.findCustomerByFirst("Dursun");
        Mockito.verify(database).getCustomersByFirst("Dursun");
    }

    /**
     * @throws Exception
     */
    @Test
    public void testFindCustomerByFirstShouldReturnTheCustomers() throws Exception {
        final CustomerService customerService = new CustomerService(database);
        final List<Customer> customers = customerService.findCustomerByFirst("Dursun");
        Assert.assertEquals(2, customers.size());

    }

}
