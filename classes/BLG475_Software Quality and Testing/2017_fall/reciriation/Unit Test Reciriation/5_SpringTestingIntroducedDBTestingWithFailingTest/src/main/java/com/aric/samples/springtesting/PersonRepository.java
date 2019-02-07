/**
 *
 */
package com.aric.samples.springtesting;

import java.util.Optional;

import org.springframework.data.repository.PagingAndSortingRepository;
import org.springframework.data.repository.query.Param;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource(collectionResourceRel = "people", path = "people")
public interface PersonRepository extends PagingAndSortingRepository<Person, Long> {
    /**
     * @param id
     * @return
     */
    public Optional<Person> findById(@Param("id") Long id);
}