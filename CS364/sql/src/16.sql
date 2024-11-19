-- Write a query to display the employee number, first name, last name, and
-- largest salary amount for each employee in department 200. Sort the output
-- by largest salary in descending order and employee number in ascending
-- order. (Problem 7.57)


--MAX SAL_AMOUNT AS LARGESTSALARY
SELECT DISTINCT LGEMPLOYEE.EMP_NUM, EMP_FNAME, EMP_LNAME, MAX (SAL_AMOUNT) as LARGESTSALARY
FROM LGEMPLOYEE INNER JOIN LGSALARY_HISTORY ON LGEMPLOYEE.EMP_NUM = LGSALARY_HISTORY.EMP_NUM
WHERE DEPT_NUM = 200
GROUP BY LGEMPLOYEE.EMP_NUM
ORDER BY LARGESTSALARY DESC;