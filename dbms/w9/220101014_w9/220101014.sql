-- 1
create database week09;
use week09;

-- 2
create table sailors(
sid int primary key,
sname char(50),
rating int,
age decimal(3,1)
);


create table boats(
bid int primary key, 
bname char(50),
bcolor char(50)
);

create table reserves(
sid int references sailors(sid),
bid int references boats(bid),
day char(50),
primary key (sid,bid,day)
);


-- 3
-- populating


-- ------------------------------------------------------------------------------------------------------------
-- ------------------------------------------------------------------------------------------------------------
-- 4
-- creating updatable views
-- a
create view view1 as 
select sid, rating 
from sailors;

insert into view1 values(91,7);
insert into view1 values(92,8);
insert into view1 values(93,9);
insert into view1 values(94,10);
insert into view1 values(22,8); -- Error Code: 1062. Duplicate entry '22' for key 'sailors.PRIMARY'

update view1 set sid=8 where sid=91;

delete from view1 where sid=91;
-- ------------------------------------------------------------------------------------------------------------
-- b
create view view2 as
select * from boats 
where bcolor='green';

insert into view2 values(205, 'River Mania', 'green');
insert into view2 values(206, 'green-bird', 'green');
insert into view2 values(207, 'blue-warriors', 'blue');

create view view3 as
select * from boats where bcolor='green'
with check option;

insert into view3 values(207, 'blue-warriors', 'blue');
-- Error Code: 1369. CHECK OPTION failed 'week09.view3'

-- -------------------------------------------------------------------------------------------------------------------------------
-- c

-- 1
create view view4 as
select sid, rating, bid, bname
from sailors natural join boats natural join reserves;

-- 2
insert into view4(sid, rating) values (80,8);

-- 3
insert into view4(bid, bname) values (105,'Lucky Lake');

-- 4
update view4 set bname='Jumper' 
where bid=101;

update view4 set bname='Interlake' 
where bid=101;
-- ------------------------------------------------------------------------------------------------------------
-- ------------------------------------------------------------------------------------------------------------
-- creating views that are not updatable

-- a
create view view5 as
select sid, sname, rating, bid, bname
from sailors natural join boats natural join reserves
where rating in (select max(rating) from sailors natural join boats natural join reserves);

insert into view5(sid, sname, rating) values(80,'best sailor',10);
-- Error Code: 1471. The target table view5 of the INSERT is not insertable-into

update view5 set rating=-9 where sid=74;
-- Error Code: 1288. The target table view5 of the UPDATE is not updatable

delete from view5 where sid=74;
-- Error Code: 1395. Can not delete from join view 'week09.view5'

update view5 set bname='Can I get updated?' where bid=102;
-- Error Code: 1288. The target table view5 of the UPDATE is not updatable


-- ------------------------------------------------------------------------------------------------------------
-- b
create view view6 as
select distinct rating from sailors;

insert into view6 values(2);
-- Error Code: 1471. The target table view6 of the INSERT is not insertable-into
-- no primary key for rating 2 as null cannot be a primary key

update view6 set rating=-7 where ratng=7;
-- Error Code: 1288. The target table view6 of the UPDATE is not updatable

delete from view6 where rating=7;
-- Error Code: 1288. The target table view6 of the DELETE is not updatable

-- ------------------------------------------------------------------------------------------------------------
-- c
create view view7 as 
select *
from sailors natural join reserves
group by rating;

insert into view7(sid, sname,rating,age) values(80,'budding sailor',10,25);

update view7 set rating=6 where rating=8;

delete from view7 where rating=7;

drop view view7;

select * from view7;

-- ------------------------------------------------------------------------------------------------------------
-- d
create view view77 as 
select *
from sailors natural join reserves
group by rating
having age>36;

insert into view77(sid, sname,rating,age) values(80,'budding sailor',10,25);

update view77 set rating=6 where rating=8;

delete from view77 where rating=7;

drop view view77;

select * from view77;



-- ------------------------------------------------------------------------------------------------------------
-- e
create view view8 as
(select sid,sname,bid,bcolor
from sailors natural join boats natural join reserves
where bcolor='green')
union
(select sid,sname,bid,bcolor
from sailors natural join boats natural join reserves
where bcolor='blue');

insert into view8(sid, rating) values(81,9);
-- Error Code: 1471. The target table view8 of the INSERT is not insertable-into

update view8 set rating=9 where sid=22;
-- Error Code: 1288. The target table view8 of the UPDATE is not updatable

delete from view8 where sid=22;
-- Error Code: 1288. The target table view8 of the DELETE is not updatable

-- ------------------------------------------------------------------------------------------------------------
-- ------------------------------------------------------------------------------------------------------------
-- creating views using views using VIEW1
-- a
create view view9 as
select rating from view1;

-- b
insert into view9 values(7);
insert into view9 values(8);
insert into view9 values(9);
insert into view9 values(10);
insert into view9 values(8);
-- errors in all insert 
-- Error Code: 1423. Field of view 'week09.view9' underlying table doesn't have a default value

-- c
update view9 set rating=9 where rating=8;

-- d
delete from view9 where rating=10;

-- e
create view view10 as
select sid,bname,day 
from view2 natural join reserves;
-- ------------------------------------------------------------------------------------------------------------
-- ------------------------------------------------------------------------------------------------------------

-- creating views using views USING VIEW5
-- a
create view view11 as
select rating from view5;

-- b
insert into view11 values(7);
insert into view11 values(8);
insert into view11 values(9);
insert into view11 values(10);
insert into view11 values(8);
-- errors in all insert 
-- Error Code: 1423. Field of view 'week09.view9' underlying table doesn't have a default value

-- c
update view11 set rating=9 where rating=8;

-- d
delete from view11 where rating=10;

-- e
create view view12 as
select sid,bname,day 
from view6 natural join reserves;
-- ------------------------------------------------------------------------------------------------------------
-- ------------------------------------------------------------------------------------------------------------

-- effect of altering original tables on views
-- a

alter table sailors 
rename column rating to rting;

-- b
select * from view1;
select * from view4;
select * from view5;
select * from view6;
select * from view7;
select * from view77;
select * from view9;
select * from view11;
-- Error Code: 1356. View 'week09.view1' references invalid table(s) or column(s) or function(s) or definer/invoker of view lack rights to use them
-- all of the views are showing the same error because of change of column name rating to rting

-- c
alter table sailors 
rename column rting to rating;

-- d
select * from view1;
select * from view4;
select * from view5;
select * from view6;
select * from view7;
select * from view77;
select * from view9;
select * from view11;
-- all of these run fine

-- e
alter table sailors
drop column rating;

-- f
select * from view1;
select * from view4;
select * from view5;
select * from view6;
select * from view7;
select * from view77;
select * from view9;
select * from view11;
-- Error Code: 1356. View 'week09.view1' references invalid table(s) or column(s) or function(s) or definer/invoker of view lack rights to use them
-- all of these statements showing the same error as above becuase we deleted column rating


-- -------------------------------------------------------------------------------------------
-- -------------------------------------------------------------------------------------------

-- type conversion
-- a
create table sailors_1(
sid int primary key,
sname char(50),
rating int,
age decimal(3,1)
);


create table boats_1(
bid int primary key, 
bname char(50),
bcolor char(50)
);

create table reserves_1(
sid int references sailors(sid),
bid int references boats(bid),
day char(50),
primary key (sid,bid,day)
);

-- c

alter table reserves_1
modify column sid smallint;

alter table sailors_1
modify column sid smallint;

alter table reserves_1
modify column bid char(3);

alter table boats_1
modify column bid char(3);

alter table reserves_1 
modify column bcolor char(5);

alter table boats_1 
modify column bcolor char(5);



