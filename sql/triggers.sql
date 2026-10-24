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



