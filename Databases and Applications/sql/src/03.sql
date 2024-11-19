-- Assuming that the data shown in the EMP_1 table have been entered (see prior
-- table), write the SQL code that will list all attributes for a job code of
-- 502. Sort the results by employee number in ascending order. (Problem 7.3)

SELECT *
FROM EMP_1
WHERE JOB_CODE = 502
ORDER BY EMP_NUM;