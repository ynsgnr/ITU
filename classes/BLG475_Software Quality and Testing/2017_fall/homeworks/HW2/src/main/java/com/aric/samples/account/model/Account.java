/**
 *
 */
package com.aric.samples.account.model;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

/**
 * @author dursun
 *
 */
@Entity
public class Account {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long id;

    private double balance;

    private long ownerTckn;
    private String ownerFirstName;
    private String ownerLastName;

    public long getId() {
        return id;
    }

    public double getBalance() {
        return balance;
    }

    public long getOwnerTckn() {
		return ownerTckn;
	}

	public void setOwnerTckn(long ownerTckn) {
		this.ownerTckn = ownerTckn;
	}

	public String getOwnerFirstName() {
        return ownerFirstName;
    }

    public String getOwnerLastName() {
        return ownerLastName;
    }

    public void setId(final long id) {
        this.id = id;
    }

    public void setBalance(final double balance) {
        this.balance = balance;
    }

    public void setOwnerFirstName(final String ownerFirstName) {
        this.ownerFirstName = ownerFirstName;
    }

    public void setOwnerLastName(final String ownerLastName) {
        this.ownerLastName = ownerLastName;
    }

    public double deposit(final double amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("Amount should be a positive value");
        }
        this.balance += amount;
        return balance;
    }

    public double withdraw(final double amount) {
        if (amount > this.balance) {
            throw new IllegalArgumentException("Amount cannot be greater than balance");
        }
        this.balance -= amount;
        return balance;
    }

}
