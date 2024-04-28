set global local_infile=1;


-- task 01
create database week06;
use week06;

-- task 02

create table T01(
a int,
b int, 
c int unique not null,
d int unique not null,
e int,
primary key(a,b)
);

-- there are a lot of duplicate entries in the data,
-- for eg. duplicate entries for primary key (a,b)
-- and duplicate values for c, d

-- task 03
create table T02(
f int,
a int,
b int,
primary key(f),
foreign key (a,b) references T01(a,b)
);

-- there were  a few errors because of foreign key constraint violation because the foreign key may not be existing in T01
-- Error Code: 1062. Duplicate entry '9866' for key 'T02.PRIMARY'

-- task 04
create table T03(
h int,
i int,
f int,
primary key(h),
foreign key(f) references T02(f)
);
-- we had to fix the csv, becuase in line 49, there was an extra comma
-- gives error like
-- Error Code: 1452. Cannot add or update a child row: a foreign key constraint fails (`week06`.`T03`, CONSTRAINT `T03_ibfk_1` FOREIGN KEY (`f`) REFERENCES `T02` (`f`))


-- task 05
create table T04(
k int,
h int,
primary key(k),
foreign key(h) references T03(h)
);
-- we had to fix the csv, there were 2 commas in line 28, 160
-- one error in last row Error Code: 1452. Cannot add or update a child row: a foreign key constraint fails (`week06`.`T04`, CONSTRAINT `T04_ibfk_1` FOREIGN KEY (`h`) REFERENCES `T03` (`h`))

-- task 06
delete from T04;
delete from T03;
delete from T02;
delete from T01;

drop table T04;
drop table T03;
drop table T02;
drop table T01;
-- we need to reverse the order of deletion becuase T01 is being used in T02, T02 is being used in T03 and so on....

-- task 07
create table T01a(
a int,
b int, 
c int unique not null,
d int unique not null,
e int,
primary key(a,b)
);

-- gives the same error that were given during creation of table in task02

create table T02a(
f int,
a int,
b int,
primary key(f),
foreign key (a,b) references T01a(a,b)
on delete cascade
);

-- b)
delete from T01a
where (a,b) in (
(297, 77408),
(606, 48191),
(1071, 47061),
(1080, 48533),
(2268, 21577),
(3130, 79583),
(3613, 84692),
(3713, 19837),
(3720, 49661),
(4036, 38648));

-- c)
select * from T02a
where (a,b) in 
((297, 77408),
(606, 48191),
(1071, 47061),
(1080, 48533),
(2268, 21577),
(3130, 79583),
(3613, 84692),
(3713, 19837),
(3720, 49661),
(4036, 38648));


-- task 08
create table T01b(
a int,
b int, 
c int unique not null,
d int unique not null,
e int,
primary key(a,b)
);

create table T02b(
f int,
a int,
b int,
primary key(f),
foreign key (a,b) references T01b(a,b)
on update cascade
);

update T01b set a=298 where a=297;
update T01b set a=607 where a=607;
update T01b set a=21577 where a=2269;
update T01b set a=79583 where a=3131;
update T01b set a=49661 where a=3721;
update T01b set a=38648 where a=4037;

update T01b set b=47062 where b=1071;
update T01b set b=48534 where b=1080;
update T01b set b=84693 where b=3613;
update T01b set b=19838 where b=3713;

select * from T02b where a in 
(297,
298,
607,
607,
2269,
21577,
3131,
79583,
3721,
49661,
4037,
38648);


select * from T02b where b in 
(1071,
47062,
1080,
48534,
3613,
84693,
3713,
19838);

-- task09

create table T01c(
a int,
b int, 
c int unique not null,
d int unique not null,
e int,
primary key(a,b)
);
create table T02c(
f int,
a int,
b int,
primary key(f),
foreign key (a,b) references T01c(a,b)
on update cascade 
on delete cascade
);

delete from T01c where (a,b) in
((297, 77408),
(606, 48191),
(1071, 47061),
(1080, 48533),
(2268, 21577),
(3130, 79583),
(3613, 84692),
(3713, 19837),
(3720, 49661),
(4036, 38648));

select * from T02c where (a,b) in
((297, 77408),
(606, 48191),
(1071, 47061),
(1080, 48533),
(2268, 21577),
(3130, 79583),
(3613, 84692),
(3713, 19837),
(3720, 49661),
(4036, 38648));

update T01c set a=4129 where a=4128;
update T01c set a=4189 where a=4182;
update T01c set a=4676 where a=4675;
update T01c set a=4850 where a=4849;
update T01c set a=6196 where a=6195;

update T01c set b=32143 where b=32142;
update T01c set b=98681 where b=98680;
update T01c set b=27251 where b=27250;
update T01c set b=33912 where b=33911;
update T01c set b=33912 where b=53094;


select * from T02c where a in (
4128,
4129,
4182,
4189,
4675,
4676,
4849,
4850,
6195,
6196);

select * from T02c where b in (
32142,
32143,
98680,
98681,
27250,
27251,
33911,
33912,
53094,
53095);

-- task 10
delete from T02a;
delete from T02b;
delete from T02c;

delete from T01a;
delete from T01b;
delete from T01c;

drop table T02a;
drop table T02b;
drop table T02c;

drop table T01a;
drop table T01b;
drop table T01c;
-- drop T02s first because they use T01 as foreign key

-- task 11

create table T01d(
a int,
b int,
c int, 
primary key(a)
);

create table T02d(
d int,
e int,
primary key(e),
foreign key(d) references T01d(a));

alter table T01d
add foreign key(b) references T02d(e);
-- we add foreign key constraint later when T02d is created          
drop table T01d, T02d;