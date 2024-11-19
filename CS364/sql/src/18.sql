-- Write a query to display the employee number, last name, first name, and sum
-- of invoice totals for all employees who completed an invoice. Sort the
-- output by employee last name and then by first name. (Problem 7.61)

--more than answer key output

SELECT LGEMPLOYEE.EMP_NUM, EMP_LNAME, EMP_FNAME, SUM (INV_TOTAL) AS TOTALINVOICES
FROM LGEMPLOYEE INNER JOIN LGINVOICE ON LGEMPLOYEE.EMP_NUM = LGINVOICE.EMPLOYEE_ID
GROUP BY LGEMPLOYEE.EMP_NUM
ORDER BY EMP_LNAME, EMP_FNAME;