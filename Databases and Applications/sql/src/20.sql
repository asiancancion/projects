-- Write a query to display the invoice number, line numbers, product SKUs,
-- product descriptions, and brand ID for sales of sealer and top coat products
-- of the same brand on the same invoice with the sealer information appearing
-- before top coat. Sort the results by invoice number, sealer line number, and
-- top coat line number in ascending order. (Problem 8.22)

--NOT WORKING AHHH


--SELECT LGINVOICE.INV_NUM, LINE_NUM AS L1, LGLINE.PROD_SKU AS P1, LINE_NUM AS L2,  LGLINE.PROD_SKU AS P2, BRAND_ID
--FROM LGINVOICE INNER JOIN LGLINE ON LGINVOICE.INV_NUM = LGLINE.INV_NUM INNER JOIN LGPRODUCT ON LGLINE.PROD_SKU = LGPRODUCT.PROD_SKU
--WHERE PROD_CATEGORY = 'Top Coat' OR PROD_CATEGORY = 'Sealer'


SELECT I1.INV_NUM, L1.LINE_NUM, L1.PROD_SKU, P1.PROD_DESCRIPT, L2.LINE_NUM, L2.PROD_SKU, P2.PROD_DESCRIPT, P1.BRAND_ID
FROM LGINVOICE AS I1 
INNER JOIN LGLINE AS L1 ON I1.INV_NUM = L1.INV_NUM
INNER JOIN LGPRODUCT AS P1 ON L1.PROD_SKU = P1.PROD_SKU
INNER JOIN LGLINE AS L2 ON I1.INV_NUM = L2.INV_NUM
INNER JOIN LGPRODUCT AS P2 ON L2.PROD_SKU = P2.PROD_SKU

WHERE P1.BRAND_ID = P2.BRAND_ID
AND P1.PROD_CATEGORY = 'Sealer'
AND P2.PROD_CATEGORY = 'Top Coat'
ORDER BY I1.INV_NUM, L1.LINE_NUM, L2.LINE_NUM