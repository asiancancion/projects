-- Write a query to display the employee number, last name, first name, salary
-- "from" date, salary end date, and salary amount for employees 83731, 83745,
-- and 84039. Sort the output by employee number and salary "from" date.
-- (Problem 7.48)


SELECT LGEMPLOYEE.EMP_NUM, EMP_LNAME, EMP_FNAME, SAL_FROM, SAL_END, SAL_AMOUNT
FROM LGEMPLOYEE INNER JOIN LGSALARY_HISTORY ON  LGEMPLOYEE.EMP_NUM = LGSALARY_HISTORY.EMP_NUM
WHERE LGEMPLOYEE.EMP_NUM = 83731 OR LGEMPLOYEE.EMP_NUM = 83745 OR LGEMPLOYEE.EMP_NUM = 84039
ORDER BY EMP_NUM ASC, SAL_FROM ASC;