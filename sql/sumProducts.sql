create procedure monthSum()
begin
  select count(*) from Orders
  where completeDate is not null and 
  completeDate > strftime('%m','now');
end;



select * from Products 
where availableAmount >0;
