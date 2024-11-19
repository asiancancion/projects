-- The Binder Prime Company wants to recognize the employee who sold the most
-- of its products during a specified period. Write a query to display the
-- employee number, employee first name, employee last name, email address, and
-- total units sold for the employee who sold the most Binder Prime products
-- between November 1, 2015, and December 5, 2015. If there is a tie for most
-- units sold, sort the output by employee last name. (Problem 8.23)

--brandid = 33

--Need to count total units that they sold at brandid = 33 in between the dates

--Question: How to get that amount of units sold and then connect that back to LGEMPLOYEE entities?

WITH INTERMEDIATE AS(
SELECT EMP_NUM, EMP_FNAME, EMP_LNAME, EMP_EMAIL, SUM (LINE_QTY) AS TOTAL
FROM LGBRAND INNER JOIN LGPRODUCT ON LGBRAND.BRAND_ID = LGPRODUCT.BRAND_ID
INNER JOIN LGLINE ON LGPRODUCT.PROD_SKU = LGLINE.PROD_SKU
INNER JOIN LGINVOICE ON LGLINE.INV_NUM = LGINVOICE.INV_NUM
INNER JOIN LGEMPLOYEE ON LGINVOICE.EMPLOYEE_ID = LGEMPLOYEE.EMP_NUM
WHERE INV_DATE BETWEEN '2015-11-01' AND '2015-12-05' AND BRAND_NAME = 'BINDER PRIME'
GROUP BY EMP_NUM, EMP_FNAME, EMP_LNAME, EMP_EMAIL
)
SELECT EMP_NUM, EMP_FNAME, EMP_LNAME, EMP_EMAIL, TOTAL
FROM INTERMEDIATE
WHERE TOTAL = (
	SELECT MAX (TOTAL)
	FROM INTERMEDIATE
)
ORDER BY EMP_LNAME
