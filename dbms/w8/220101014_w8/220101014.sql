-- TASK 1
create database week08;
use week08;

-- TASK 2

-- 1
create table student(
roll_number int primary key,
student_name varchar(20) not null,
program varchar(20),
check (program in ('Certificate','Diploma', 'Degree', 'Honors'))
);

SELECT * FROM student;

-- 2
create table course(
cid char(5),
cname varchar(100),
primary key(cid)
);

-- 3
create table concept(
cid char(5),
qn char(5),
description varchar(100),
primary key (cid,qn),
foreign key (cid) references course(cid)
);

-- 4
create table marks(
roll_number int,
cid char(5),
set1 char(5),
set1_marks int,
set2 char(5),
set2_marks int,
primary key (roll_number, cid, set1),
foreign key (roll_number) references student(roll_number),
foreign key (cid) references course(cid)
);

-- TASK 03

-- 1
select student_name, cid, set1, set1_marks, set2, set2_marks
from student, marks
where student.roll_number=marks.roll_number;

-- 2
select roll_number, cname, set1, set1_marks, set2, set2_marks
from marks,course 
where marks.cid=course.cid;

-- 3
select student_name, cname, set1, set1_marks, set2, set2_marks
from student, course, marks
where student.roll_number=marks.roll_number
and course.cid=marks.cid;

-- 4
select student_name, c1.cid, set1, c1.description, set1_marks, set2, c2.description, set2_marks
from student, marks, concept as c1, concept as c2
where student.roll_number=marks.roll_number
and marks.cid=c1.cid
and c1.cid=c2.cid
and c1.description=set1
and c2.description=set2;

-- 12
select avg(set1_marks) from marks
where set1='q01s1' and cid='DA105';
-- answer=5.1003

-- 13
select avg(set2_marks) from marks
where set2='q01s2' and cid='DA106';
-- answer=5.0871

-- 14
select avg(set1_marks) from marks
where set1='q01s1' and cid='DA107';
-- answer=4.8566

-- 15
select avg(set2_marks) from marks
where set2='q01s2' and cid='DA108';
-- answer= 5.1347

-- 16
select count(*) from marks 
where set1_marks between 0 and 5 
and set1='q01s1'
and cid='DA107';
-- gives answer 323

-- 17
with maxi(value) as
	(select max(set1_marks) 
	from marks
	where set1='q07s1'
	and cid='DA107')

select student_name
from student, marks,maxi
where student.roll_number=marks.roll_number
and marks.set1='q07s1'
and marks.cid='DA107'
and marks.set1_marks=maxi.value;
-- 62 rows returned

-- 18
with maxi(value) as
	(select max(set2_marks) 
	from marks
	where set2='q02s2'
	and cid='DA107')

select student.roll_number
from student, marks,maxi
where student.roll_number=marks.roll_number
and marks.set2='q02s2'
and marks.cid='DA107'
and marks.set2_marks=maxi.value
and student.program='Diploma';
-- 12 row(s) returned

-- 19
with m1(value) as
	(select max(set1_marks)
	from marks 
	where cid='DA107'),

m2(value) as
	(select max(set2_marks)
	from marks
	where cid='DA107'),

select student.roll_number
from student, marks,m1,m2
where student.roll_number=marks.roll_number
and marks.cid='DA107'
and marks.set1_marks>=m1.value
and marks.set2_marks>=m2.value
and student.program='Honors';


-- 20
with m1(value) as
	(select max(set1_marks)
	from marks, concept 
	where cid='DA107'),

m2(value) as
	(select max(set2_marks)
	from marks
	where cid='DA107'),

select student.roll_number
from student,marks m1,m2, concept
where marks.cid='DA107'
and 

select * from marks;

-- 21
with t1(roll_number, m1) as
(select roll_number, sum(set1_marks), cid, cname)
group by (roll_number, cid)

-- 22
select roll_number, student.name,cid, cname, sum(set1_marks), sum(set2_marks)


-- 23
select program,count(*) from student
group by program;


-- 24
select avg(set1_marks)
from marks, student
where marks.roll_number=student.roll_number
and marks.cid='DA105'
and marks.set1='q01s1'
and student.program='Certificate';
-- answer=5.4366

-- 25
select avg(set1_marks)
from marks, student
where marks.roll_number=student.roll_number
and marks.cid='DA108'
and marks.set1='q12s1'
and student.program='Diploma';
-- answer =4.800

-- 26
with t1(value) as
(select sum(set1_marks)
from marks 
where marks.roll_number=270101636
and marks.cid='DA105'),

 t2(value) as
(select sum(set2_marks)
from marks 
where marks.roll_number=270101636
and marks.cid='DA105')
-- answer= 126

select t1.value+t2.value
from t1, t2;

-- 27
with t1(value) as
(select sum(set1_marks)
from marks 
where marks.roll_number=270101636
and marks.cid='DA106'),

 t2(value) as
(select sum(set2_marks)
from marks 
where marks.roll_number=270101636
and marks.cid='DA106')

select t1.value+t2.value
from t1, t2;



-- 28
with t1(value) as
(select sum(set1_marks)
from marks 
where marks.roll_number=270101636
and marks.cid='DA107'),

 t2(value) as
(select sum(set2_marks)
from marks 
where marks.roll_number=270101636
and marks.cid='DA107')


select t1.value+t2.value
from t1, t2;


-- 29
with t1(value) as
(select sum(set1_marks)
from marks 
where marks.roll_number=270101636
and marks.cid='DA108'),

 t2(value) as
(select sum(set2_marks)
from marks 
where marks.roll_number=270101636
and marks.cid='DA108')
-- answer= 122

select t1.value+t2.value
from t1, t2;

