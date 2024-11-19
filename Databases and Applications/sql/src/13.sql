-- Write a query to display the number of products in each category that have a
-- water base. Sort the results by product category. (Problem 7.52)
SELECT PROD_CATEGORY, COUNT (PROD_CATEGORY) AS NUMPRODUCTS
FROM LGPRODUCT
WHERE PROD_BASE = 'Water'
GROUP BY PROD_CATEGORY
ORDER BY PROD_CATEGORY;