package com.aric.samples.account.service;

import com.aric.samples.account.model.Account;
import com.aric.samples.account.repository.AccountRepository;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;

import java.util.Arrays;

import static org.junit.Assert.assertEquals;

public class AccountServiceTest {

    private AccountRepository ar;
    private int testCount=5;
    private int[] tckArray={12345,6789,101112,61566,654654};
    private final Account[] accounts = new Account[] { new Account(),new Account(),new Account(),new Account(),new Account()};
    private final AccountReposityMocker accountService = new AccountReposityMocker();

    @Before
    public void setUp(){
        int i;
        //Mock some data
        ar = Mockito.mock(AccountRepository.class);
        for (i=0;i<testCount-3;i++){
            accounts[i].setId(i);
            accounts[i].setOwnerTckn(tckArray[i]);
            accounts[i].setBalance(i*100);
            accounts[i].setOwnerFirstName(i+". Yunus");
            accounts[i].setOwnerLastName(i+". Güngör");
            Mockito.when(ar.findByOwnerTckn(tckArray[i])).thenReturn(Arrays.asList(accounts[i]));
            Mockito.when(ar.findOne(Long.valueOf(i))).thenReturn(accounts[i]);
            Mockito.when(ar.save(accounts[i])).thenReturn(accounts[i]);
        }
        i=testCount-2;
        //Add same id
        accounts[i].setId(i);
        accounts[i].setOwnerTckn(tckArray[i]);
        accounts[i].setBalance(452);
        accounts[i].setOwnerFirstName(i+". Yunus");
        accounts[i].setOwnerLastName(i+". Güngör");
        Mockito.when(ar.findByOwnerTckn(tckArray[i])).thenReturn(Arrays.asList(accounts[i]));
        Mockito.when(ar.findOne(Long.valueOf(i))).thenReturn(accounts[i]);
        Mockito.when(ar.save(accounts[i])).thenReturn(accounts[i]);

        i=testCount-1;
        //Add same tckno
        accounts[i].setId(i-1);
        accounts[i].setOwnerTckn(tckArray[i]);
        accounts[i].setBalance(1254);
        accounts[i].setOwnerFirstName(i+". Yunus");
        accounts[i].setOwnerLastName(i+". Güngör");
        Mockito.when(ar.findByOwnerTckn(tckArray[i])).thenReturn(Arrays.asList(accounts[i]));
        Mockito.when(ar.findOne(Long.valueOf(i))).thenReturn(accounts[i]);
        Mockito.when(ar.save(accounts[i])).thenReturn(accounts[i]);

        accountService.setAccountRep(ar);
    }

    @Test
    public void findPersonsByTcknTest() throws Exception {
        for (int i=0;i<testCount-3;i++){
            accountService.findPersonsByTckn(tckArray[i]);
            Mockito.verify(ar).findByOwnerTckn(tckArray[i]);
        }
    }

    @Test
    public void depositSimpleTest() {
        Account account;
        for (int i=0;i<testCount-3;i++){
            account = accountService.deposit(accounts[i].getId(),i*10.0+1);
            Mockito.verify(ar).findOne(accounts[i].getId());
            Mockito.verify(ar).save(account);
            assertEquals(i*110+1,(int)account.getBalance());
        }
    }

    @Test
    public void depositDuplicateIdTest() {
        Account account;
        account = accountService.deposit(accounts[testCount-2].getId(),13.0);
        Mockito.verify(ar).findOne(accounts[testCount-2].getId());
        Mockito.verify(ar).save(account);
        assertEquals(465,(int)account.getBalance());
    }

    @Test
    public void eftSimpleTest() {
        Account account;
        for (int i=1;i<testCount-3;i++){
            account = accountService.eft(accounts[i].getId(),accounts[i-1].getId(),10.0);
            Mockito.verify(ar).findOne(accounts[i].getId());
            Mockito.verify(ar).findOne(accounts[i-1].getId());
            Mockito.verify(ar).save(accounts[i-1]);
            Mockito.verify(ar).save(accounts[i]);
            assertEquals(i*100-10,(int)account.getBalance());
        }
    }

    @Test
    public void eftDuplicateIdTest() {
        Account account;
        int i = testCount-2;
        account = accountService.eft(accounts[i].getId(),accounts[i-1].getId(),10.0);
        Mockito.verify(ar).findOne(accounts[i].getId());
        Mockito.verify(ar).findOne(accounts[i-1].getId());
        Mockito.verify(ar).save(accounts[i]);
        assertEquals(442,(int)account.getBalance());
    }

}