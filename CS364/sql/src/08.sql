-- Write a query to display the first name, last name, phone number, title, and
-- department number of employees who work in department 300 or have the title
-- "CLERK I." Sort the output by last name and then by first name. (Problem
-- 7.47)

--More rows than answer key

SELECT EMP_FNAME, EMP_LNAME, EMP_PHONE, EMP_TITLE, DEPT_NUM
FROM LGEMPLOYEE
WHERE DEPT_NUM = 300 OR EMP_TITLE = 'CLERK I'
ORDER BY EMP_LNAME ASC, EMP_FNAME ASC;