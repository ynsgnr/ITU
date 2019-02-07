/**
 *
 */
package com.aric.samples;

import com.aric.samples.exceptions.AritmeticException;

/**
 * @author dursun
 *
 */
public class SimpleArithmetic {

    /**
     * @param a
     * @param b
     * @return
     * @throws AritmeticException
     */
    public int add(final int a, final int b) throws AritmeticException {
        if (a == b && a == 0) {
            throw new AritmeticException("I did not like 0+0!!!");
        }
        return a + b;
    }

    /**
     * @param a
     * @param b
     * @return
     */
    public int divide(final int a, final int b) {
        return a / b;
    }

    /**
     * @param a
     * @param b
     * @return
     */
    public int multiply(final int a, final int b) {
        return a * b;
    }

    /**
     * @param a
     * @param b
     * @return
     */
    public int subtract(final int a, final int b) {
        return a - b;
    }

}
