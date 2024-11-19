-- Having created the table structure in the prior problem, write the SQL code
-- to enter the first two rows for the following table. (Problem 7.2)

INSERT INTO EMP_1 (EMP_NUM, EMP_LNAME, EMP_FNAME, EMP_INITIAL, EMP_HIREDATE, JOB_CODE)
VALUES (101, 'News', 'John', 'G', '2000-11-08', 502), (102, 'Senior', 'David', 'H', '1989-07-12', 501);
--INSERT INTO "EMP_1" (EMP_NUM, EMP_LNAME, EMP_FNAME, EMP_INITIAL, EMP_HIREDATE, JOB_CODE)