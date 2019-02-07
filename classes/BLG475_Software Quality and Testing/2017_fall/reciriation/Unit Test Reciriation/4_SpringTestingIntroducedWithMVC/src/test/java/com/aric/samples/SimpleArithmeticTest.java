package com.aric.samples;

import org.junit.Assert;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import com.aric.samples.exceptions.AritmeticException;

/**
 * @author dursun
 *
 */
public class SimpleArithmeticTest {
    @Rule
    public ExpectedException exception = ExpectedException.none();

    @Test
    public void testAddWithNonZeroArguments() throws Exception {
        final SimpleArithmetic simpleArithmetic = new SimpleArithmetic();
        final int result = simpleArithmetic.add(1, 2);
        final int expected = 3;
        Assert.assertEquals(expected, result);
    }

    @Test
    public void testAddWithZero() throws Exception {
        final SimpleArithmetic simpleArithmetic = new SimpleArithmetic();
        exception.expect(AritmeticException.class);
        exception.expectMessage("I did not like 0+0!!!");
        simpleArithmetic.add(0, 0);
    }

    /*
     * FIXME Create simple test for Division denominator can be zero or non zero
     */
    /*
     * TODO Create simple tests for other operations
     */

}
