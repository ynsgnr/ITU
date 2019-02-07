package com.aric.samples.account.model;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

public class AccountTest {

    private Account account = new Account();

    @Before
    public void setUp() {
        account.setId(124);
        account.setBalance(100);
        account.setOwnerFirstName("Clark");
        account.setOwnerLastName("Kent");
        account.setOwnerTckn(424242);
    }

    @Test
    public void setIdTest() {
        account.setId(124);
    }

    @Test
    public void setBalanceTest() {
        account.setBalance(100);
    }

    @Test
    public void setOwnerFirstNameTest() {
        account.setOwnerFirstName("Clark");
    }

    @Test
    public void setOwnerLastNameTest() {
        account.setOwnerLastName("Kent");
    }

    @Test
    public void setOwnerTcknTest() {
        account.setOwnerTckn(424242);
    }

    @Test
    public void getIdTest() {
       assertEquals(124,account.getId());
    }

    @Test
    public void getBalanceTest() {
        assertEquals(100,(int)account.getBalance());
    }

    @Test
    public void getOwnerTcknTest() {
        assertEquals(424242,(int)account.getOwnerTckn());
    }

    @Test
    public void getOwnerFirstNameTest() {
        assertEquals("Clark",account.getOwnerFirstName());
    }

    @Test
    public void getOwnerLastNameTest() {
        assertEquals("Kent",account.getOwnerLastName());
    }

    @Test
    public void testDeposit() {
        assertEquals(125,(int)account.deposit(25.0));
    }

    @Test
    public void testDepositNegative() {
        try{
            account.deposit(-10);
        }catch (IllegalArgumentException e) {
            if (e.getMessage() != "Amount should be a positive value")
                fail("Wrong exception trowed while depositing negative value");
        }finally {
            assertEquals(100,(int)account.getBalance());
        }
    }

    @Test
    public void testWithdraw() {
        assertEquals(85,(int)account.withdraw(15.0));
    }

    @Test
    public void testNegativeWithdraw() {
        try{
            account.withdraw(-15);
        }catch (IllegalArgumentException e) {
            if (e.getMessage() != "Amount cannot be greater than balance")
                fail("Wrong exception trowed while withdrawing negative value");
        }finally {
            assertEquals(100,(int)account.getBalance());
        }
    }

    @Test
    public void testMoreThanBalanceWithdraw() {
        try{
            account.withdraw(account.getBalance()+100);
        }catch (IllegalArgumentException e) {
            if (e.getMessage() != "Amount cannot be greater than balance")
                fail("Wrong exception trowed while withdrawing negative value");
        }finally {
            assertEquals(100,(int)account.getBalance());
        }
    }

    @Test
    public void testSettingBalanceNegative(){
        //According to requirements balance might become negative
        //But for this project it is assumed that balance can not be negative
        try{
            account.setBalance(-100);
        }catch (Exception e) {
            if (e==null)
                fail();
        }finally {
            assertEquals(100,(int)account.getBalance());
        }
    }

    @Test
    public void testSettingNameEmpty(){
        account.setOwnerFirstName("");
        assertEquals("",account.getOwnerFirstName());
    }

    @Test
    public void testSettingSurnameEmpty(){
        account.setOwnerLastName("");
        assertEquals("",account.getOwnerLastName());
    }

    @Test
    public void  testSettingTcknoNegative () {
        //TCKNO can not be negative, another test for tckno integrity test can be added
        try{
            account.setOwnerTckn(-4242);
        }catch (Exception e) {
            if (e==null)
                fail();
        }finally {
            assertEquals(0,(int)account.getOwnerTckn());
        }
    }

}