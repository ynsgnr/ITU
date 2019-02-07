/**
 *
 */
package com.aric.samples.account.service;

import com.aric.samples.account.model.Account;
import com.aric.samples.account.repository.AccountRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * @author dursun
 *
 */
@Service
public class AccountService {
    @Autowired
    protected AccountRepository accountRepository;
    //private AccountRepository accountRepository;

    public List<Account> findPersonsByTckn(final long tckn) {
        return accountRepository.findByOwnerTckn(tckn);
    }

    public Account deposit(final Long accountId, final Double amount) {
        final Account acc = accountRepository.findOne(accountId);
        acc.deposit(amount);
        return accountRepository.save(acc);
    }
    
    public Account eft(final Long senderAccountId, final Long receiverAccountId, final Double amount) {
        final Account senderAcc = accountRepository.findOne(senderAccountId);
        senderAcc.withdraw(amount);
        final Account receiverAcc = accountRepository.findOne(receiverAccountId);
        receiverAcc.deposit(amount);
        accountRepository.save(receiverAcc);
        return accountRepository.save(senderAcc);
    }
    
}
