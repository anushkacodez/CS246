-- 1
create database week13;
use week13;

-- 2.1
create table employees(
eid int primary key,
ename char(50),
dept char(50),
salary decimal(10,0),
gender char(1),
check (gender in ('M','F'))
);

-- 2.2 task2_2.c

-- 2.3
create table languages(
ename char(50),
speaks char(50),
primary key(ename,speaks)
);

-- 2.4 task2_4.c

-- 3.1
select dept,count(*) as cnt 
from employees 
group by dept 
order by cnt 
limit 1;

-- 3.2
select * from(
select dept,rank() over (order by temp.cnt)
as temp_rank from(
select dept,count(*) as cnt from employees group by dept) as temp)
as temp2 where temp2.temp_rank=1;

-- 4.1
select ename, count(*) as cnt 
from languages 
group by ename
order by cnt desc limit 1;

-- 4.2
select * from(
select ename,cnt,rank() over (order by temp.cnt desc)
as temp_rank from(
select ename,count(*) as cnt from languages group by ename) as temp)
as temp2 where temp2.temp_rank=1;

-- 5.1
select gender, avg(salary) as AVG
from employees 
group by gender
order by AVG desc limit 1;

-- 5.2
select rank_, gender from(
select gender,avg,rank() over 
(order by temp.avg desc) as rank_
from (select gender,avg(salary) as avg from employees group by gender)
as temp) as temp2;

-- 6.1
select * from(
select ename, sal, rank() over (order by temp.sal desc) as 'RANK'
from
(select ename, salary as sal from employees where dept='Marketing' order by sal desc) as temp)
as temp2 limit 2;


-- 6.2
select ename, salary
from (
select ename, salary, rank() over (
partition by gender order by salary desc)
as gender_salary_rank from employees)
as ranked_sal where gender_salary_rank=1;

-- 7.1
create table students(
sid int primary key,
sname char(50),
marks int,
gender char(6),
department char(11),
check (gender in ('Male','Female')),
check (department in ('CSE','Mathematics'))
);

-- 7.2 task7_2.sql

-- 8.1
SELECT sid, marks, rank() OVER (ORDER BY marks DESC) AS ranks
FROM students;

-- 8.2
SELECT sid, department, marks, RANK() OVER (PARTITION BY department ORDER BY marks DESC) AS dept_rank
FROM students;

-- 8.3
SELECT sid, gender, marks, RANK() OVER (PARTITION BY gender ORDER BY marks DESC) AS gender_rank
FROM students;

-- 8.4
SELECT sid, department, gender, RANK() OVER (PARTITION BY department, gender ORDER BY marks DESC) AS dept_gender_rank
FROM students;

-- 8.5
SELECT sid, department, gender, RANK() OVER (ORDER BY marks DESC) AS ranke,
       DENSE_RANK() OVER (ORDER BY marks DESC) AS dense_ranke
FROM students;

-- 8.6 (a)
select sname, marks from students where marks=
(select first_value(marks) over w from students window w as 
(order by marks desc range between unbounded preceding and unbounded following) limit 1);

-- 8.6 (b)
select sname, marks from students where marks=
(select nth_value(marks,100) over w from students window w as 
(order by marks desc range between unbounded preceding and unbounded following) limit 1);


-- 8.6 (c)
select sname, marks from students where marks=
(select nth_value(marks,200) over w from students window w as 
(order by marks desc range between unbounded preceding and unbounded following) limit 1);

-- 8.6(d)
select sname, marks from students where marks=
(select last_value(marks) over w from students window w as 
(order by marks desc range between unbounded preceding and unbounded following) limit 1);

-- 8.7
SELECT sname AS name, marks,
       LAG(marks) OVER (PARTITION BY department ORDER BY marks) AS previous_marks,
       LEAD(marks) OVER (PARTITION BY department ORDER BY marks) AS next_marks
FROM students;