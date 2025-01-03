-- Write the SQL code that will create the table structure for a table named
-- EMP_1. This table is a subset of the EMPLOYEE table. Note that JOB_CODE is a
-- foreign key to JOB. (Problem 7.1)

--DROP TABLE IF EXISTS "EMP_1"; 
CREATE TABLE EMP_1(
	EMP_NUM INTEGER,
	EMP_LNAME CHARACTER VARYING (15),
	EMP_FNAME CHARACTER VARYING (15),
	EMP_INITIAL CHARACTER (1),
	EMP_HIREDATE DATE,
	JOB_CODE INTEGER,
	PRIMARY KEY (EMP_NUM),
	FOREIGN KEY (JOB_CODE) REFERENCES JOB (JOB_CODE) ON UPDATE CASCADE ON DELETE RESTRICT
);

