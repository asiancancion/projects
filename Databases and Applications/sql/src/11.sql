-- Write a query to display the employee number, last name, email address,
-- title, and department name of each employee whose job title ends in the word
-- "ASSOCIATE." Sort the output by department name, employee title, and
-- employee number. (Problem 7.50)


SELECT LGEMPLOYEE.EMP_NUM, EMP_LNAME, EMP_EMAIL,EMP_TITLE, LGDEPARTMENT.DEPT_NAME
FROM LGEMPLOYEE LEFT JOIN LGDEPARTMENT ON LGEMPLOYEE.DEPT_NUM = LGDEPARTMENT.DEPT_NUM
WHERE EMP_TITLE LIKE '%ASSOCIATE'
ORDER BY LGDEPARTMENT.DEPT_NAME ASC, EMP_TITLE ASC, EMP_NUM ASC;