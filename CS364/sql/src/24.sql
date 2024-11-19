-- One of the purchasing managers is interested in the impact of product prices
-- on the sale of products of each brand. Write a query to display the brand
-- name, brand type, average price of products of each brand, and total units
-- sold of products of each brand. Even if a product has been sold more than
-- once, its price should only be included once in the calculation of the
-- average price. However, you must be careful because multiple products of the
-- same brand can have the same price, and each of those products must be
-- included in the calculation of the brand's average price. Be sure to round
-- the average price to two decimal places. Sort the results in ascending order
-- by the brand name. (Problem 8.26)

--find avg price find units and then put together as two tables

--SELECT LGBRAND.BRAND_NAME, BRAND_TYPE, AVG (PROD_PRICE) AS AVERAGE_PRICE, SUM (INV_TOTAL) AS UNITS_SOLD
--FROM LGPRODUCT INNER JOIN LGBRAND ON LGPRODUCT.BRAND_ID = LGBRAND.BRAND_ID
--INNER JOIN LGLINE ON LGPRODUCT.PROD_SKU = LGLINE.PROD_SKU
--INNER JOIN LGINVOICE ON LGINVOICE.INV_NUM = LGLINE.INV_NUM
--GROUP BY BRAND_NAME, BRAND_TYPE, PROD_QOH
--ORDER BY BRAND_NAME;


WITH TABLE_AVG AS (
	SELECT BRAND_NAME, BRAND_TYPE, ROUND (AVG (PROD_PRICE), 2) as AVERAGE_PRICE
	FROM LGBRAND
	INNER JOIN LGPRODUCT ON LGBRAND.BRAND_ID = LGPRODUCT.BRAND_ID
	GROUP BY BRAND_NAME, BRAND_TYPE
),
TABLE_SOLD AS (
	SELECT BRAND_NAME, BRAND_TYPE, SUM (LINE_QTY) AS "units sold"
	FROM LGBRAND
	INNER JOIN LGPRODUCT ON LGBRAND.BRAND_ID = LGPRODUCT.BRAND_ID
	INNER JOIN LGLINE ON LGPRODUCT.PROD_SKU = LGLINE.PROD_SKU
	GROUP BY BRAND_NAME, BRAND_TYPE
)
SELECT TABLE_SOLD.BRAND_NAME, TABLE_SOLD.BRAND_TYPE, AVERAGE_PRICE as "average price", "units sold"
FROM TABLE_AVG INNER JOIN TABLE_SOLD ON TABLE_AVG.BRAND_NAME = TABLE_SOLD.BRAND_NAME
GROUP BY TABLE_SOLD.BRAND_NAME, TABLE_SOLD.BRAND_TYPE, AVERAGE_PRICE, "units sold"
ORDER BY BRAND_NAME;