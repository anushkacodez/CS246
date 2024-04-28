
create database week05;
use week05;


-- task 2
create table T1(
id char(20),
roll_no int,
cpi float);
insert into T1(id, roll_no, cpi) values ('student 01', 270101001, 9.8);
insert into T1(id, roll_no, cpi) values ('student 02', 270101002, 8.9);
insert into T1(id, roll_no, cpi) values ('student 03', 270101003, 7.6);
UPDATE T1 SET cpi=8.1 where id='student 03';
DELETE FROM T1 WHERE id='student 02';


-- task 3
create table T2(
id char(20),
roll_no int,
cpi float,
primary key(roll_no));

insert into T2(id, roll_no, cpi) values ('student 01', 270101001, 9.8);
insert into T2(id, roll_no, cpi) values ('student 01', 270101002, 8.9);
insert into T2(id, roll_no, cpi) values ('student 03', 270101001, 7.6);
-- gives error becuase roll_no is duplicate
UPDATE T2 SET roll_no=270101002 where id='student 01';
-- this will give an error because 270101002 is primary key for another tuple and primary keys should be unqiue for  every tuple
DELETE FROM T2 WHERE id='student 02';



-- task 4
create table T3(
id char(20) not null,
roll_no int unique,
cpi float);

insert into T3(id, roll_no, cpi) values (NULL, 270101001, 9.8);
-- gives error because id should be not null as it has not null constraint

insert into T3(id, roll_no, cpi) values ('student 02', 270101002, 8.9);

insert into T3(id, roll_no, cpi) values ('student 03', 270101002, 7.6);
-- gives error becuase roll_no is unique, there exists another column with roll_no 270101002

update T3 set id=NULL where id='student 02';
-- gives error because name cannot be null (it has not null constraint)

DELETE FROM T3 WHERE id='student 02';



-- task 5
create table T4(
id char(20),
roll_no int,
cpi float default 0.0,
primary key(roll_no));

insert into T4(id, roll_no) values (NULL, 270101001);
insert into T4(id, roll_no, cpi) values (NULL, 270101002, 8.9);
insert into T4(id, roll_no, cpi) values ('student 03', 270101002, -7.6);
-- gives error because 270101002 is a primary key and it cant have duplicate entries
insert into T4(id, roll_no, cpi) values ('student 03', 270101003, 8.2);
insert into T4(id, roll_no) values ('student 03', 270101004);




-- task 6
create table T5(
id char(20) not null,
roll_no int primary key,
cpi float default 0.0);

insert into T5(id, roll_no) values (NULL, 270101001);
-- gives error because id (name) has not null constraint

insert into T5(id, roll_no, cpi) values ('student 01', 270101001, 9.6);
insert into T5(id, roll_no, cpi) values ('student 02', 270101002, 8.2);
insert into T5(id, roll_no, cpi) values ('student 02', 270101003, 7.6);
insert into T5(id, roll_no, cpi) values ('student 03', 270101003, 7.2);
-- gives error becuase 270101003 is a duplicate and it is a primary key and hence should have unique values
insert into T5(id, roll_no) values ('student 04', 270101004);



-- task 7
create table T6(
id char(20),
roll_no int,
cpi float);

insert into T6(id, roll_no, cpi) values('student 01', 270101001, 9.6);
insert into T6(id, roll_no, cpi) values('student 02', 270101001, 9.4);
insert into T6(id, roll_no, cpi) values('student 03', 270101001, 9.2);
select * from T6;
alter table T6 add primary key(roll_no);
-- gives error because roll_no column has duplicate entries

alter table T6
add column semester_number int default 1;

insert into T6 values('student 03', 270101002, 9.2, 3);
insert into T6(id, roll_no, cpi) values('student 03', 270101001, 9.2);

alter table T6 
drop column roll_no;





