-- Write a query to display the customer code, first name, and last name of all
-- customers who have had at least one invoice completed by employee 83649 and
-- at least one invoice completed by employee 83677. Sort the output by
-- customer last name and then first name. (Problem 8.24)


--WHERE EMP_1 = 83649 AND EMP_2 = 83677

SELECT DISTINCT LGCUSTOMER.CUST_CODE, CUST_FNAME, CUST_LNAME
FROM LGCUSTOMER 
INNER JOIN LGINVOICE AS I1 ON LGCUSTOMER.CUST_CODE = I1.CUST_CODE
INNER JOIN LGINVOICE AS I2 ON LGCUSTOMER.CUST_CODE = I2.CUST_CODE
WHERE I1.EMPLOYEE_ID = 83649 AND I2.EMPLOYEE_ID = 83677
ORDER BY CUST_LNAME, CUST_FNAME
