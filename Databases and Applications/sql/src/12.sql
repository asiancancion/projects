-- Write a query to display a brand name and the number of products of that
-- brand that are in the database. Sort the output by the brand name. (Problem
-- 7.51)


SELECT BRAND_NAME, COUNT (LGPRODUCT.BRAND_ID) as NUMPRODUCTS
FROM LGPRODUCT LEFT JOIN LGBRAND ON LGPRODUCT.BRAND_ID = LGBRAND.BRAND_ID
GROUP BY BRAND_NAME
ORDER BY BRAND_NAME;