/**
 *
 */
package com.aric.samples.account.repository;

import java.util.List;

import org.springframework.data.repository.PagingAndSortingRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

import com.aric.samples.account.model.Account;

@RepositoryRestResource(collectionResourceRel = "account", path = "account")
public interface AccountRepository extends PagingAndSortingRepository<Account, Long> {
    public List<Account> findByOwnerTckn(long tckn);
}
