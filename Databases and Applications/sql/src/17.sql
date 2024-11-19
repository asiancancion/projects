-- Write a query to display the customer code, first name, last name, and sum
-- of all invoice totals for customers with cumulative invoice totals greater
-- than $1,500. Sort the output by the sum of invoice totals in descending
-- order. (Problem 7.58)

--
SELECT LGCUSTOMER.CUST_CODE, CUST_FNAME, CUST_LNAME, SUM (INV_TOTAL) AS TOTALINVOICE
FROM LGCUSTOMER INNER JOIN LGINVOICE ON LGCUSTOMER.CUST_CODE = LGINVOICE.CUST_CODE
GROUP BY LGCUSTOMER.CUST_CODE
HAVING SUM (INV_TOTAL)> 1500
ORDER BY TOTALINVOICE DESC;