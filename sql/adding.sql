--insert into Suppliers(name,contacts) values('alibibi','alibibi.@example.mail'),('BestOfTheBestComp','bestContactEver'),('TMCS','goToGoogle');
insert into Products(name,supplierId,availableAmount) values('someFish',2,25),('Crucian',3,100),('Perch',1,60);
--insert into Clients(name,phoneNumber) values('john','+123123123'),('Sasha Crucian','-321321321'),('CatMurzik','лапи та хвіст');
--insert into Orders(clientId,ProductId,amount,orderDate,completeDate) values(1,1,200,'01/05/2025'),(2,2,3000),(2,1,1500);
insert into Deliveries(supplierId,deliveryDate,expDate,amount,productId,pricePerPiece) values(1,'24/04/2025','24/05/2025',500,1,50);

