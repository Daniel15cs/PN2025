select Products.*, julianday(Deliveries.expDate)-julianday('now') as diff
from Products 
inner join Deliveries on Products.id=Deliveries.productId
where availableAmount > 0 and diff >0



--timediff(strftime('%Y-%m-%d',Deliveries.expDate),strftime('%Y-%m-%d','now'))
