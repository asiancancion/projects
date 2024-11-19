-- Write a query to display the SKU (stock keeping unit), description, type,
-- base, category, and price for all products that have a PROD_BASE of water
-- and a PROD_CATEGORY of sealer. (Problem 7.45)

SELECT PROD_SKU, PROD_DESCRIPT, PROD_TYPE, PROD_BASE, PROD_CATEGORY, PROD_PRICE
FROM LGPRODUCT
WHERE PROD_BASE = 'Water' AND PROD_CATEGORY = 'Sealer';