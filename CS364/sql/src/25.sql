-- The purchasing manager is still concerned about the impact of price on
-- sales. Write a query to display the brand name, brand type, product SKU,
-- product description, and price of any products that are not a premium brand,
-- but that cost more than the most expensive premium brand products. (Problem
-- 8.27)

SELECT BRAND_NAME, BRAND_TYPE, PROD_SKU, PROD_DESCRIPT, PROD_PRICE
FROM LGBRAND INNER JOIN LGPRODUCT ON LGBRAND.BRAND_ID = LGPRODUCT.BRAND_ID
WHERE BRAND_TYPE != 'PREMIUM' AND PROD_PRICE > (
	SELECT MAX (PROD_PRICE)
	FROM LGPRODUCT
	WHERE BRAND_ID IN(
		SELECT BRAND_ID
		FROM LGBRAND
		WHERE BRAND_TYPE = 'PREMIUM'
	)
);
