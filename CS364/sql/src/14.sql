-- Write a query to display the number of products within each base and type
-- combination. Sort the results by product base and type. (Problem 7.53)

SELECT PROD_BASE, PROD_TYPE, COUNT (PROD_TYPE) as NUMPRODUCTS
FROM LGPRODUCT
GROUP BY PROD_BASE, PROD_TYPE
ORDER BY PROD_BASE, PROD_TYPE;