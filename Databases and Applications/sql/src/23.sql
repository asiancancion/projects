-- LargeCo is planning a new promotion in Alabama (AL) and wants to know about
-- the largest purchases made by customers in that state. Write a query to
-- display the customer code, customer first name, last name, full address,
-- invoice date, and invoice total of the largest purchase made by each
-- customer in Alabama. Be certain to include any customers in Alabama who have
-- never made a purchase; their invoice dates should be NULL and the invoice
-- totals should display as 0.00. Order the results by the customers' last and
-- first names. (Problem 8.25)

--NEED HELP MAKING DISTINCT AHHH

WITH INTERMEDIATE AS (
SELECT LGCUSTOMER.CUST_CODE AS CUST_CODE, CUST_FNAME, CUST_LNAME, CUST_STREET, CUST_CITY, CUST_STATE, CUST_ZIP, INV_DATE, MAX (INV_TOTAL) AS LARGESTINVOICE
FROM LGCUSTOMER LEFT JOIN LGINVOICE ON LGCUSTOMER.CUST_CODE = LGINVOICE.CUST_CODE
WHERE CUST_STATE = 'AL'
GROUP BY LGCUSTOMER.CUST_CODE, INV_DATE
ORDER BY CUST_LNAME, CUST_FNAME
)
SELECT CUST_CODE , CUST_FNAME, CUST_LNAME, CUST_STREET, CUST_CITY, CUST_STATE, CUST_ZIP, INV_DATE, COALESCE (LARGESTINVOICE, 0.00) AS "largest invoice"
FROM INTERMEDIATE
WHERE LARGESTINVOICE IN(
	SELECT MAX (LARGESTINVOICE)
	FROM INTERMEDIATE
	GROUP BY CUST_CODE
)
OR LARGESTINVOICE IS NULL

ORDER BY CUST_LNAME, CUST_FNAME
