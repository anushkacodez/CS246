create database week11;
use week11;

-- 1
SET @stmt_1 = "create table sailors (sid int primary key,sname char(50),rating int,age decimal(3,1));";
PREPARE stmt FROM @stmt_1;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- 2
SET @stmt_1 = "create table reserves(
sid int references sailors(sid),
bid int references boats(bid),
day char(50),
primary key (sid,bid,day)
);
";
PREPARE stmt FROM @stmt_1;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;


-- 3
SET @stmt_1 = "create table boats(
bid int primary key, 
bname char(50),
bcolor char(50)
);";
PREPARE stmt FROM @stmt_1;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;


-- 4
create table sailor_name(
serial_number int,
name char(20));

create table boat_name(
serial_number int,
name char(20));

create table boat_color(
serial_number int,
name char(20));

-- 5 done through c files

-- 6
DELIMITER //
CREATE procedure p1()
BEGIN
	DECLARE a int default 1;
	while a<=500 DO
	insert into sailors(sid, sname, age, rating) values(a,(select name from sailor_name order by rand() limit 1),floor(18+rand()*(65-18+1)),floor(1+rand()*(10-1+1)));
    set a=a+1;
    END WHILE;	
END //
DELIMITER ;


call p1();
select * from sailors;


7
DELIMITER //
CREATE procedure p2()
BEGIN
	DECLARE a int default 1;
	while a<=50 DO
	insert into boats values(a,(select name from boat_name order by rand() limit 1),(select name from boat_color order by rand() limit 1));
    set a=a+1;
    END WHILE;	
END //
DELIMITER ;


call p2();
select * from boats;

-- 8
DELIMITER //
CREATE procedure p3()
BEGIN
	DECLARE a int default 1;
	while a<=5000 DO
	insert into reserves values((select sid from sailors order by rand() limit 1),(select bid from boats order by rand() limit 1),random_date());
    set a=a+1;
    END WHILE;	
END //
DELIMITER ;



call p3();
select * from reserves;


-- 9
DELIMITER //
create function random_date() returns date deterministic
BEGIN
	DECLARE DAY INT;
    DECLARE MONTH INT;
    SET MONTH=FLOOR(1+RAND()*12);
    
    IF MONTH IN (1,3,5,7,8,10,12) THEN
		SET DAY=FLOOR(1+RAND()*31);
    ELSEIF MONTH=2 THEN
		SET DAY=FLOOR(1+RAND()*29);
    ELSE 
		SET DAY=FLOOR(1+RAND()*30);
    END IF;
    RETURN concat('2024-',LPAD(month,2,'0'),'-',LPAD(day,2,'0'));
END //
DELIMITER //;

select random_date();


-- 10
DELIMITER //
CREATE procedure p4(in sdin int, out bcol char(20))
BEGIN
	select bcolor into bcol from reserves natural join boats where sid=sdin limit 1;
END //
DELIMITER ;

call p4(120,@bcol);
select @bcol;

-- 11
DELIMITER //
CREATE procedure p5(out cumulative_rating int)
BEGIN
	declare temp int default 0;
	select sum(rating) into temp from sailors natural join reserves where dayname(day)='Sunday';
    set cumulative_rating=temp;
END //
DELIMITER ;

call p5(@cumulative_rating);
select @cumulative_rating;
 
-- 12
DELIMITER //
CREATE function rating_to_grade	(rating int) returns char(2) deterministic
BEGIN
	DECLARE grade char(2);
    if rating=1 then
		set grade='F';
    elseif rating=2 then
		set grade='F';
	elseif rating=3 then
		set grade='F';
    elseif rating=4 then
		set grade='DD';
    elseif rating=5 then
		set grade='CD';
    elseif rating=6 then
		set grade='CC';
    elseif rating=7 then
		set grade='BC';
    elseif rating=8 then
		set grade='BB';
    elseif rating=9 then
		set grade='AB';
    elseif rating=10 then
		set grade='AA';
	END IF;
    RETURN grade;
END //
DELIMITER ;

select rating_to_grade(5);

-- 13
select sid, rating, rating_to_grade(rating) as grade from sailors;