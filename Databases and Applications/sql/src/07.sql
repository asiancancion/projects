-- Write a query to display the first name, last name, and email address of
-- employees hired from January 1, 2003, to December 31, 2012. Sort the output
-- by last name and then by first name. (Problem 7.46)

SELECT EMP_FNAME, EMP_LNAME, EMP_EMAIL
FROM LGEMPLOYEE
WHERE EMP_HIREDATE BETWEEN '2003-01-01' AND '2012-12-31'
ORDER BY EMP_LNAME ASC, EMP_FNAME ASC;