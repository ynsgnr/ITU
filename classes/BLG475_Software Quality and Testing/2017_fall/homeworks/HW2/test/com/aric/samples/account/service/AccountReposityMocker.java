package com.aric.samples.account.service;

import com.aric.samples.account.repository.AccountRepository;

public class AccountReposityMocker extends AccountService {

    public void setAccountRep (AccountRepository ar){
        super.accountRepository=ar;
    }

}
