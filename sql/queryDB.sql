PRAGMA foreign_keys = ON;
create table Suppliers(
  id integer not null primary key,
  name varchar(255) not null,
  contacts varchar(255),
  address varchar(255)
);
create table Products(
  id integer not null primary key,
  name varchar(255) not null,
  availableAmount int
);
create table Clients(
  id integer not null primary key,
  name varchar(255) not null,
  phoneNumber varchar(20)
);
create table Orders(
  clientId int not null,
  productId int not null,
  amount int not null default 1,
  orderDate date not null,
  completeDate date,
  foreign key(clientId) references Clients(id),
  foreign key(productId) references Products(id)
);
create table Deliveries(
  supplierId int,
  deliveryDate date not null,
  expDate date not null,
  amount int not null default 1,
  productId int not null,
  pricePerPiece int not null,
  foreign key(supplierId) references Suppliers(id),
  foreign key(productId) references Products(id)
);




-- Тригер після вставки у Purchases
drop trigger purchaseAddAmount;
CREATE TRIGGER purchaseAddAmount
AFTER INSERT ON Orders
FOR EACH ROW
BEGIN
  UPDATE Products
  SET availableAmount = availableAmount - NEW.amount
  WHERE id = NEW.productId;
END;

-- trigger for deliveries
CREATE TRIGGER addAmount
AFTER INSERT ON Deliveries
FOR EACH ROW
BEGIN
  UPDATE Products
  SET availableAmount = availableAmount + NEW.amount
  WHERE id = NEW.productId;
END;

-- Якщо нова кількість більша — збільшуємо залишок
CREATE TRIGGER addAmountUpdate_increase
AFTER UPDATE ON Deliveries
FOR EACH ROW
WHEN NEW.amount > OLD.amount
BEGIN
  UPDATE Products
  SET availableAmount = availableAmount + (NEW.amount - OLD.amount)
  WHERE id = NEW.productId;
END;

-- Якщо нова кількість менша — зменшуємо залишок
CREATE TRIGGER addAmountUpdate_decrease
AFTER UPDATE ON Deliveries
FOR EACH ROW
WHEN NEW.amount < OLD.amount
BEGIN
  UPDATE Products
  SET availableAmount = availableAmount - (OLD.amount - NEW.amount)
  WHERE id = NEW.productId;
END;

-- Тригер перед видаленням із Deliveries
CREATE TRIGGER delDeliveries
BEFORE DELETE ON Deliveries
FOR EACH ROW
BEGIN
  UPDATE Products
  SET availableAmount = availableAmount - OLD.amount
  WHERE id = OLD.productId;
END;

-- Тригер перед видаленням із Purchases
CREATE TRIGGER delPurchases
BEFORE DELETE ON Orders
FOR EACH ROW
BEGIN
  UPDATE Products
  SET availableAmount = availableAmount + OLD.amount
  WHERE id = OLD.productId;
END;



