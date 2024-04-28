-- task 01
create database week07;
use week07;

-- task 02
create table T01(
a int,
b int unique not null,
c int unique not null,
d int unique not null,
e char(20) unique not null,
primary key(a)
);

-- ERRORS
-- Error Code: 1062. Duplicate entry 'pede' for key 'T01.e'
-- Error Code: 1062. Duplicate entry '48546' for key 'T01.c'
-- Error Code: 1062. Duplicate entry '82941' for key 'T01.PRIMARY'


-- TASK 03

create table T02(
c1 int,
c2 char(20) not null,
c3 int not null,
primary key(c1)
);

-- ERRORS
-- Error Code: 1062. Duplicate entry '82941' for key 'T02.PRIMARY'

-- TASK 04

-- 1
select a,b,c,d,e from T01;

-- 2
select a,b,c,d from T01;

-- 3
select c,d,e from T01;

-- 4 
select a,c,e from T01;

-- 5
select e,d,c,b,a from T01;

-- 6
select a,a+10, b, b-20, c, c*30, d, d/40 from T01;

-- 7
select * from T01;

-- 8
select * from T01 order by e;

-- 9
select * from T01 order by e DESC;

-- TASK 05

-- 1
select * from T01 where a=82941;

-- 2
select a,b,c,d from T01 where a<>82941;

-- 3
select c,d,e from T01 where a>84921;

-- 4
select a,c,e from T01 where a>=84921;

-- 5
select e,d,c,b,a from T01 where a<84921;

-- 6
select e,d,c,b,a from T01 where a<=84921;

-- 7
select e,d,c,b,a from T01 where a between 80000 and 84921;

-- 8
select a, a+10, b, b-20, c, c*30, d, d/40
from T01
where (a between 80000 and 84921) and
b<>84921 and
c>40000 and
d<65000;

-- 9
select * from T01
where (a between 0 and 50000) and
b>50000;


-- 10
select * from T01
where (a between 0 and 50000) and
b>50000
order by e;

-- 11
select * from T01
where (a between 0 and 50000) and
b>50000
order by e ASC, b DESC;


-- TASK 6

-- 1
select e from T01
where e like 'lo%';

-- 2
select e from T01
where e like '%ing';

-- 3
select e from T01 
where e like '____';

-- 4
select e from T01 
where e like '__i_';

-- 5
select e from T01
where e like '_i_h' or e like '_i_l';

-- 6
select e from T01
where e not like '__i_' and e like '____';

-- 7
select e from T01
where e like '_______%';


-- TASK 07

-- 1
(select a ,b from T01 where a>50000)
union
(select c1,c3 from T02 where c2 like 'e%');

-- 2
SELECT c1,c2,c3 from T02 
where (c1,c2,c3) in
(select a,e,c from T01);

-- 3
SELECT c1,c2,c3 from T02 
where (c1,c2,c3) not in
(select a,e,c from T01);
