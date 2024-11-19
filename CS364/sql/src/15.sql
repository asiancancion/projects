-- Write a query to display the total inventory -- that is, the sum of all
-- products on hand for each brand ID. Sort the output by brand ID in
-- descending order. (Problem 7.54)

SELECT BRAND_ID, SUM (PROD_QOH) AS TOTALINVENTORY
FROM LGPRODUCT
GROUP BY BRAND_ID
ORDER BY BRAND_ID DESC;