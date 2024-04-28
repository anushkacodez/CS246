-- 1
create database week12;
use week12;

-- 2
create table sailors(
sid int primary key,
sname char(50),
rating int,
age decimal(3,1));

create table boats(
bid int primary key,
bname char(50),
bcolor char(50));

create table reserves(
sid int,
bid int,
day char(50),
foreign key (sid) references sailors(sid) on update cascade on delete cascade,
foreign key (bid) references boats(bid) on update cascade on delete cascade,
primary key (sid,bid,day));

-- 3

-- 3.1
create table sailor_log(
sid int primary key,
event_ba char(50),
ops char(50),
date_time datetime default current_timestamp,
check (event_ba in('before','after')),
check (ops in ('insert','update','delete'))
);


-- 3.2
create table boats_log(
bid int,
event_ba char(50),
ops char(50),
date_time datetime default current_timestamp,
check (event_ba in('before','after')),
check (ops in ('insert','update','delete'))
);

-- 3.3
create table reserves_log(
sid int,
bid int,
day char(10),
event_ba char(50),
ops char(50),
date_time datetime default current_timestamp,
check (event_ba in('before','after')),
check (ops in ('insert','update','delete'))
);

-- 3.4
create table sailors_log_log(
sid int,
event_ba char(50),
ops char(50),
date_time datetime default current_timestamp,
check (event_ba in('before','after')),
check (ops in ('insert','update','delete'))
);

create table sailors_log_log_log(
sid int,
event_ba char(50),
ops char(50),
date_time datetime default current_timestamp,
check (event_ba in('before','after')),
check (ops in ('insert','update','delete'))
);

-- 4
-- done through c files

-- 5.1
DELIMITER //
CREATE TRIGGER sailor_t1
BEFORE INSERT
ON sailors
FOR EACH ROW
BEGIN
INSERT INTO sailor_log(sid,event_ba,ops) VALUES (New.sid,'before','insert');
END //
DELIMITER ;

-- 5.2
DELIMITER //
CREATE TRIGGER boat_t1
BEFORE INSERT
ON boats
FOR EACH ROW
BEGIN
INSERT INTO boats_log(bid,event_ba,ops) VALUES (New.bid,'before','insert');
END //
DELIMITER ;

-- 5.3
DELIMITER //
CREATE TRIGGER reserves_t1
BEFORE INSERT
ON reserves
FOR EACH ROW
BEGIN
INSERT INTO reserves_log(sid, bid, day,event_ba,ops) VALUES (New.sid,New.bid,New.day,'before','insert');
END //
DELIMITER ;

-- 5.4
DELIMITER //
CREATE TRIGGER sailor_t2
AFTER UPDATE
ON sailors
FOR EACH ROW
BEGIN
INSERT INTO sailor_log(sid,event_ba,ops) VALUES (New.sid,'after','update');
END //
DELIMITER ;

-- 5.5
DELIMITER //
CREATE TRIGGER boat_t2
AFTER UPDATE
ON boats
FOR EACH ROW
BEGIN
INSERT INTO boats_log(bid,event_ba,ops) VALUES (New.bid,'after','update');
END //
DELIMITER ;

-- 5.6
DELIMITER //
CREATE TRIGGER reserves_t2
AFTER UPDATE
ON reserves
FOR EACH ROW
BEGIN
INSERT INTO reserves_log(sid, bid, day,event_ba,ops) VALUES (New.sid,New.bid,New.day,'after','update');
END //
DELIMITER ;

-- 5.7
DELIMITER //
CREATE TRIGGER sailor_t3
AFTER DELETE
ON sailors
FOR EACH ROW
BEGIN
INSERT INTO sailor_log(sid,event_ba,ops) VALUES (old.sid,'after','deleted');
END //
DELIMITER ;

-- 5.8
DELIMITER //
CREATE TRIGGER boat_t3
AFTER DELETE
ON boats
FOR EACH ROW
BEGIN
INSERT INTO boats_log(bid,event_ba,ops) VALUES (old.bid,'after','deleted');
END //
DELIMITER ;

-- 5.9
DELIMITER //
CREATE TRIGGER reserves_t3
AFTER DELETE
ON reserves
FOR EACH ROW
BEGIN
INSERT INTO reserves_log(sid, bid, day,event_ba,ops) VALUES (old.sid,old.bid,old.day,'after','deleted');
END //
DELIMITER ;


-- 5.1 task5_1.c
-- 5.2 task5_2.c
-- 5.3
DELIMITER //
CREATE PROCEDURE populate_reserves()
BEGIN
DECLARE i int default 0;
DECLARE day_rand date;
DECLARE sid_new int;
DECLARE bid_new int;

WHILE i<(select count(*) from sailor_log)*(select count(*) from boats_log)*2 DO
set sid_new = (select sid from sailor_log order by rand() limit 1);
set bid_new = (select bid from boats_log order by rand() limit 2);
set rand_day=date_add(2024-01-01,interval floor(rand()*365) day);
if not exists (select * from reserves where (sid=sid_new and bid=bid_new and day=day_rand))
then
if ((select count(*) from reserves where sid=sid_new and bid=bid_new)<2)
then
begin
insert into reserves values (sid_new,bid_new,day_rand);
set i=i+1;
end;
end if;
end if;
end while;
end //
DELIMITER ;


-- done through c files

-- 5.4
select * from sailor_log;
-- output of 5.4
-- '1', 'before', 'insert', '2024-04-05 14:52:23'
-- '2', 'before', 'insert', '2024-04-05 14:52:24'
-- '3', 'before', 'insert', '2024-04-05 14:52:24'
-- '4', 'before', 'insert', '2024-04-05 14:52:24'
-- '5', 'before', 'insert', '2024-04-05 14:52:24'
-- '6', 'before', 'insert', '2024-04-05 14:52:24'
-- '7', 'before', 'insert', '2024-04-05 14:52:25'
-- '8', 'before', 'insert', '2024-04-05 14:52:25'
-- '9', 'before', 'insert', '2024-04-05 14:52:25'
-- '10', 'before', 'insert', '2024-04-05 14:52:25'
-- '11', 'before', 'insert', '2024-04-05 14:52:25'
-- '12', 'before', 'insert', '2024-04-05 14:52:25'
-- '13', 'before', 'insert', '2024-04-05 14:52:25'
-- '14', 'before', 'insert', '2024-04-05 14:52:25'
-- '15', 'before', 'insert', '2024-04-05 14:52:25'
-- '16', 'before', 'insert', '2024-04-05 14:52:26'
-- '17', 'before', 'insert', '2024-04-05 14:52:26'
-- '18', 'before', 'insert', '2024-04-05 14:52:26'
-- '19', 'before', 'insert', '2024-04-05 14:52:26'
-- '20', 'before', 'insert', '2024-04-05 14:52:26'
-- '21', 'before', 'insert', '2024-04-05 14:52:26'
-- '23', 'before', 'insert', '2024-04-05 14:52:26'
-- '24', 'before', 'insert', '2024-04-05 14:52:26'
-- '25', 'before', 'insert', '2024-04-05 14:52:27'
-- '26', 'before', 'insert', '2024-04-05 14:52:27'
-- '27', 'before', 'insert', '2024-04-05 14:52:27'
-- '28', 'before', 'insert', '2024-04-05 14:52:27'
-- '30', 'before', 'insert', '2024-04-05 14:52:27'
-- '33', 'before', 'insert', '2024-04-05 14:52:27'
-- '34', 'before', 'insert', '2024-04-05 14:52:27'
-- '35', 'before', 'insert', '2024-04-05 14:52:28'
-- '36', 'before', 'insert', '2024-04-05 14:52:28'
-- '37', 'before', 'insert', '2024-04-05 14:52:28'
-- '38', 'before', 'insert', '2024-04-05 14:52:28'
-- '39', 'before', 'insert', '2024-04-05 14:52:28'
-- '40', 'before', 'insert', '2024-04-05 14:52:28'
-- '41', 'before', 'insert', '2024-04-05 14:52:28'
-- '42', 'before', 'insert', '2024-04-05 14:52:29'
-- '43', 'before', 'insert', '2024-04-05 14:52:29'
-- '44', 'before', 'insert', '2024-04-05 14:52:29'
-- '45', 'before', 'insert', '2024-04-05 14:52:29'
-- '46', 'before', 'insert', '2024-04-05 14:52:29'
-- '47', 'before', 'insert', '2024-04-05 14:52:29'
-- '48', 'before', 'insert', '2024-04-05 14:52:29'
-- '49', 'before', 'insert', '2024-04-05 14:52:29'
-- '50', 'before', 'insert', '2024-04-05 14:52:30'
-- '51', 'before', 'insert', '2024-04-05 14:52:30'
-- '52', 'before', 'insert', '2024-04-05 14:52:30'
-- '53', 'before', 'insert', '2024-04-05 14:52:30'
-- '54', 'before', 'insert', '2024-04-05 14:52:30'
-- '55', 'before', 'insert', '2024-04-05 14:52:30'
-- '56', 'before', 'insert', '2024-04-05 14:52:30'
-- '57', 'before', 'insert', '2024-04-05 14:52:30'
-- '59', 'before', 'insert', '2024-04-05 14:52:31'
-- '60', 'before', 'insert', '2024-04-05 14:52:31'
-- '61', 'before', 'insert', '2024-04-05 14:52:31'
-- '62', 'before', 'insert', '2024-04-05 14:52:31'
-- '63', 'before', 'insert', '2024-04-05 14:52:31'
-- '65', 'before', 'insert', '2024-04-05 14:52:31'
-- '66', 'before', 'insert', '2024-04-05 14:52:31'
-- '67', 'before', 'insert', '2024-04-05 14:52:31'
-- '68', 'before', 'insert', '2024-04-05 14:52:31'
-- '69', 'before', 'insert', '2024-04-05 14:52:32'
-- '70', 'before', 'insert', '2024-04-05 14:52:32'
-- '72', 'before', 'insert', '2024-04-05 14:52:32'
-- '73', 'before', 'insert', '2024-04-05 14:52:32'
-- '75', 'before', 'insert', '2024-04-05 14:52:32'
-- '76', 'before', 'insert', '2024-04-05 14:52:32'
-- '77', 'before', 'insert', '2024-04-05 14:52:32'
-- '78', 'before', 'insert', '2024-04-05 14:52:32'
-- '79', 'before', 'insert', '2024-04-05 14:52:33'
-- '80', 'before', 'insert', '2024-04-05 14:52:33'
-- '81', 'before', 'insert', '2024-04-05 14:52:33'
-- '82', 'before', 'insert', '2024-04-05 14:52:33'
-- '83', 'before', 'insert', '2024-04-05 14:52:33'
-- '84', 'before', 'insert', '2024-04-05 14:52:33'
-- '86', 'before', 'insert', '2024-04-05 14:52:33'
-- '87', 'before', 'insert', '2024-04-05 14:52:33'
-- '88', 'before', 'insert', '2024-04-05 14:52:34'
-- '89', 'before', 'insert', '2024-04-05 14:52:34'
-- '90', 'before', 'insert', '2024-04-05 14:52:34'
-- '91', 'before', 'insert', '2024-04-05 14:52:34'
-- '92', 'before', 'insert', '2024-04-05 14:52:34'
-- '93', 'before', 'insert', '2024-04-05 14:52:34'
-- '94', 'before', 'insert', '2024-04-05 14:52:34'
-- '96', 'before', 'insert', '2024-04-05 14:52:35'
-- '97', 'before', 'insert', '2024-04-05 14:52:35'
-- '98', 'before', 'insert', '2024-04-05 14:52:35'
-- '99', 'before', 'insert', '2024-04-05 14:52:35'
-- '100', 'before', 'insert', '2024-04-05 14:52:35'
-- '101', 'before', 'insert', '2024-04-05 14:52:35'
-- '102', 'before', 'insert', '2024-04-05 14:52:35'
-- '103', 'before', 'insert', '2024-04-05 14:52:35'
-- '104', 'before', 'insert', '2024-04-05 14:52:35'
-- '105', 'before', 'insert', '2024-04-05 14:52:36'
-- '106', 'before', 'insert', '2024-04-05 14:52:36'
-- '107', 'before', 'insert', '2024-04-05 14:52:36'
-- '108', 'before', 'insert', '2024-04-05 14:52:36'
-- '109', 'before', 'insert', '2024-04-05 14:52:36'
-- '110', 'before', 'insert', '2024-04-05 14:52:36'
-- '111', 'before', 'insert', '2024-04-05 14:52:36'
-- '112', 'before', 'insert', '2024-04-05 14:52:36'
-- '113', 'before', 'insert', '2024-04-05 14:52:37'
-- '114', 'before', 'insert', '2024-04-05 14:52:37'
-- '115', 'before', 'insert', '2024-04-05 14:52:37'
-- '116', 'before', 'insert', '2024-04-05 14:52:37'
-- '117', 'before', 'insert', '2024-04-05 14:52:37'
-- '118', 'before', 'insert', '2024-04-05 14:52:37'
-- '119', 'before', 'insert', '2024-04-05 14:52:37'
-- '120', 'before', 'insert', '2024-04-05 14:52:37'
-- '121', 'before', 'insert', '2024-04-05 14:52:38'
-- '122', 'before', 'insert', '2024-04-05 14:52:38'
-- '123', 'before', 'insert', '2024-04-05 14:52:38'
-- '124', 'before', 'insert', '2024-04-05 14:52:38'
-- '125', 'before', 'insert', '2024-04-05 14:52:38'
-- '126', 'before', 'insert', '2024-04-05 14:52:38'
-- '127', 'before', 'insert', '2024-04-05 14:52:38'
-- '128', 'before', 'insert', '2024-04-05 14:52:38'
-- '129', 'before', 'insert', '2024-04-05 14:52:39'
-- '130', 'before', 'insert', '2024-04-05 14:52:39'
-- '131', 'before', 'insert', '2024-04-05 14:52:39'
-- '132', 'before', 'insert', '2024-04-05 14:52:39'
-- '133', 'before', 'insert', '2024-04-05 14:52:39'
-- '134', 'before', 'insert', '2024-04-05 14:52:39'
-- '135', 'before', 'insert', '2024-04-05 14:52:39'
-- '136', 'before', 'insert', '2024-04-05 14:52:39'
-- '137', 'before', 'insert', '2024-04-05 14:52:39'
-- '138', 'before', 'insert', '2024-04-05 14:52:40'
-- '139', 'before', 'insert', '2024-04-05 14:52:40'
-- '140', 'before', 'insert', '2024-04-05 14:52:40'
-- '141', 'before', 'insert', '2024-04-05 14:52:40'
-- '142', 'before', 'insert', '2024-04-05 14:52:40'
-- '143', 'before', 'insert', '2024-04-05 14:52:40'
-- '144', 'before', 'insert', '2024-04-05 14:52:40'
-- '145', 'before', 'insert', '2024-04-05 14:52:40'
-- '146', 'before', 'insert', '2024-04-05 14:52:40'
-- '147', 'before', 'insert', '2024-04-05 14:52:40'
-- '148', 'before', 'insert', '2024-04-05 14:52:41'
-- '149', 'before', 'insert', '2024-04-05 14:52:41'
-- '150', 'before', 'insert', '2024-04-05 14:52:41'
-- '151', 'before', 'insert', '2024-04-05 14:52:41'
-- '152', 'before', 'insert', '2024-04-05 14:52:41'
-- '153', 'before', 'insert', '2024-04-05 14:52:41'
-- '154', 'before', 'insert', '2024-04-05 14:52:41'
-- '155', 'before', 'insert', '2024-04-05 14:52:41'
-- '156', 'before', 'insert', '2024-04-05 14:52:42'
-- '157', 'before', 'insert', '2024-04-05 14:52:42'
-- '158', 'before', 'insert', '2024-04-05 14:52:42'
-- '159', 'before', 'insert', '2024-04-05 14:52:42'
-- '160', 'before', 'insert', '2024-04-05 14:52:42'
-- '161', 'before', 'insert', '2024-04-05 14:52:42'
-- '162', 'before', 'insert', '2024-04-05 14:52:42'
-- '163', 'before', 'insert', '2024-04-05 14:52:42'
-- '164', 'before', 'insert', '2024-04-05 14:52:42'
-- '165', 'before', 'insert', '2024-04-05 14:52:43'
-- '166', 'before', 'insert', '2024-04-05 14:52:43'
-- '167', 'before', 'insert', '2024-04-05 14:52:43'
-- '168', 'before', 'insert', '2024-04-05 14:52:43'
-- '169', 'before', 'insert', '2024-04-05 14:52:43'
-- '170', 'before', 'insert', '2024-04-05 14:52:43'
-- '171', 'before', 'insert', '2024-04-05 14:52:43'
-- '172', 'before', 'insert', '2024-04-05 14:52:43'
-- '173', 'before', 'insert', '2024-04-05 14:52:43'
-- '174', 'before', 'insert', '2024-04-05 14:52:43'
-- '175', 'before', 'insert', '2024-04-05 14:52:44'
-- '176', 'before', 'insert', '2024-04-05 14:52:44'
-- '177', 'before', 'insert', '2024-04-05 14:52:44'
-- '178', 'before', 'insert', '2024-04-05 14:52:44'
-- '179', 'before', 'insert', '2024-04-05 14:52:44'
-- '180', 'before', 'insert', '2024-04-05 14:52:44'
-- '181', 'before', 'insert', '2024-04-05 14:52:44'
-- '182', 'before', 'insert', '2024-04-05 14:52:45'
-- '183', 'before', 'insert', '2024-04-05 14:52:45'
-- '184', 'before', 'insert', '2024-04-05 14:52:45'
-- '185', 'before', 'insert', '2024-04-05 14:52:45'
-- '186', 'before', 'insert', '2024-04-05 14:52:45'
-- '187', 'before', 'insert', '2024-04-05 14:52:45'
-- '188', 'before', 'insert', '2024-04-05 14:52:45'
-- '189', 'before', 'insert', '2024-04-05 14:52:46'
-- '190', 'before', 'insert', '2024-04-05 14:52:46'
-- '191', 'before', 'insert', '2024-04-05 14:52:46'
-- '192', 'before', 'insert', '2024-04-05 14:52:46'
-- '193', 'before', 'insert', '2024-04-05 14:52:46'
-- '194', 'before', 'insert', '2024-04-05 14:52:46'
-- '195', 'before', 'insert', '2024-04-05 14:52:46'
-- '196', 'before', 'insert', '2024-04-05 14:52:46'
-- '197', 'before', 'insert', '2024-04-05 14:52:46'
-- '198', 'before', 'insert', '2024-04-05 14:52:47'
-- '199', 'before', 'insert', '2024-04-05 14:52:47'
-- '200', 'before', 'insert', '2024-04-05 14:52:47'
-- '201', 'before', 'insert', '2024-04-05 14:52:47'
-- '202', 'before', 'insert', '2024-04-05 14:52:47'
-- '203', 'before', 'insert', '2024-04-05 14:52:47'
-- '204', 'before', 'insert', '2024-04-05 14:52:47'
-- '205', 'before', 'insert', '2024-04-05 14:52:47'
-- '206', 'before', 'insert', '2024-04-05 14:52:47'
-- '207', 'before', 'insert', '2024-04-05 14:52:47'
-- '208', 'before', 'insert', '2024-04-05 14:52:48'
-- '209', 'before', 'insert', '2024-04-05 14:52:48'
-- '210', 'before', 'insert', '2024-04-05 14:52:48'
-- '211', 'before', 'insert', '2024-04-05 14:52:48'
-- '212', 'before', 'insert', '2024-04-05 14:52:48'
-- '213', 'before', 'insert', '2024-04-05 14:52:48'
-- '214', 'before', 'insert', '2024-04-05 14:52:48'
-- '215', 'before', 'insert', '2024-04-05 14:52:49'
-- '216', 'before', 'insert', '2024-04-05 14:52:49'
-- '217', 'before', 'insert', '2024-04-05 14:52:49'
-- '218', 'before', 'insert', '2024-04-05 14:52:49'
-- '219', 'before', 'insert', '2024-04-05 14:52:49'
-- '220', 'before', 'insert', '2024-04-05 14:52:49'
-- '221', 'before', 'insert', '2024-04-05 14:52:49'
-- '222', 'before', 'insert', '2024-04-05 14:52:49'
-- '223', 'before', 'insert', '2024-04-05 14:52:49'
-- '224', 'before', 'insert', '2024-04-05 14:52:50'
-- '225', 'before', 'insert', '2024-04-05 14:52:50'
-- '226', 'before', 'insert', '2024-04-05 14:52:50'
-- '227', 'before', 'insert', '2024-04-05 14:52:50'
-- '228', 'before', 'insert', '2024-04-05 14:52:50'
-- '229', 'before', 'insert', '2024-04-05 14:52:50'
-- '230', 'before', 'insert', '2024-04-05 14:52:50'
-- '231', 'before', 'insert', '2024-04-05 14:52:50'
-- '232', 'before', 'insert', '2024-04-05 14:52:50'
-- '233', 'before', 'insert', '2024-04-05 14:52:51'
-- '234', 'before', 'insert', '2024-04-05 14:52:51'
-- '235', 'before', 'insert', '2024-04-05 14:52:51'
-- '236', 'before', 'insert', '2024-04-05 14:52:51'
-- '237', 'before', 'insert', '2024-04-05 14:52:51'
-- '238', 'before', 'insert', '2024-04-05 14:52:51'
-- '239', 'before', 'insert', '2024-04-05 14:52:51'
-- '240', 'before', 'insert', '2024-04-05 14:52:51'
-- '241', 'before', 'insert', '2024-04-05 14:52:52'
-- '242', 'before', 'insert', '2024-04-05 14:52:52'
-- '243', 'before', 'insert', '2024-04-05 14:52:52'
-- '244', 'before', 'insert', '2024-04-05 14:52:52'
-- '245', 'before', 'insert', '2024-04-05 14:52:52'
-- '246', 'before', 'insert', '2024-04-05 14:52:52'
-- '247', 'before', 'insert', '2024-04-05 14:52:52'
-- '248', 'before', 'insert', '2024-04-05 14:52:52'
-- '249', 'before', 'insert', '2024-04-05 14:52:53'
-- '250', 'before', 'insert', '2024-04-05 14:52:53'
-- '251', 'before', 'insert', '2024-04-05 14:52:53'
-- '252', 'before', 'insert', '2024-04-05 14:52:53'
-- '253', 'before', 'insert', '2024-04-05 14:52:53'
-- '254', 'before', 'insert', '2024-04-05 14:52:53'
-- '255', 'before', 'insert', '2024-04-05 14:52:53'
-- '256', 'before', 'insert', '2024-04-05 14:52:53'
-- '257', 'before', 'insert', '2024-04-05 14:52:53'
-- '258', 'before', 'insert', '2024-04-05 14:52:54'
-- '259', 'before', 'insert', '2024-04-05 14:52:54'
-- '260', 'before', 'insert', '2024-04-05 14:52:54'
-- '261', 'before', 'insert', '2024-04-05 14:52:54'
-- '262', 'before', 'insert', '2024-04-05 14:52:54'
-- '263', 'before', 'insert', '2024-04-05 14:52:54'
-- '264', 'before', 'insert', '2024-04-05 14:52:54'
-- '265', 'before', 'insert', '2024-04-05 14:52:54'
-- '266', 'before', 'insert', '2024-04-05 14:52:54'
-- '267', 'before', 'insert', '2024-04-05 14:52:55'
-- '268', 'before', 'insert', '2024-04-05 14:52:55'
-- '269', 'before', 'insert', '2024-04-05 14:52:55'
-- '270', 'before', 'insert', '2024-04-05 14:52:55'
-- '271', 'before', 'insert', '2024-04-05 14:52:55'
-- '272', 'before', 'insert', '2024-04-05 14:52:55'
-- '273', 'before', 'insert', '2024-04-05 14:52:55'
-- '274', 'before', 'insert', '2024-04-05 14:52:56'
-- '275', 'before', 'insert', '2024-04-05 14:52:56'
-- '276', 'before', 'insert', '2024-04-05 14:52:56'
-- '277', 'before', 'insert', '2024-04-05 14:52:56'
-- '278', 'before', 'insert', '2024-04-05 14:52:56'
-- '279', 'before', 'insert', '2024-04-05 14:52:56'
-- '280', 'before', 'insert', '2024-04-05 14:52:57'
-- '281', 'before', 'insert', '2024-04-05 14:52:57'
-- '282', 'before', 'insert', '2024-04-05 14:52:57'
-- '283', 'before', 'insert', '2024-04-05 14:52:57'
-- '284', 'before', 'insert', '2024-04-05 14:52:57'
-- '285', 'before', 'insert', '2024-04-05 14:52:57'
-- '286', 'before', 'insert', '2024-04-05 14:52:57'
-- '287', 'before', 'insert', '2024-04-05 14:52:57'
-- '288', 'before', 'insert', '2024-04-05 14:52:58'
-- '289', 'before', 'insert', '2024-04-05 14:52:58'
-- '290', 'before', 'insert', '2024-04-05 14:52:58'
-- '291', 'before', 'insert', '2024-04-05 14:52:58'
-- '292', 'before', 'insert', '2024-04-05 14:52:58'
-- '293', 'before', 'insert', '2024-04-05 14:52:59'
-- '294', 'before', 'insert', '2024-04-05 14:52:59'
-- '295', 'before', 'insert', '2024-04-05 14:52:59'
-- '296', 'before', 'insert', '2024-04-05 14:52:59'
-- '297', 'before', 'insert', '2024-04-05 14:52:59'
-- '298', 'before', 'insert', '2024-04-05 14:52:59'
-- '299', 'before', 'insert', '2024-04-05 14:52:59'
-- '300', 'before', 'insert', '2024-04-05 14:53:00'
-- '301', 'before', 'insert', '2024-04-05 14:53:00'
-- '302', 'before', 'insert', '2024-04-05 14:53:00'
-- '303', 'before', 'insert', '2024-04-05 14:53:00'
-- '304', 'before', 'insert', '2024-04-05 14:53:00'
-- '305', 'before', 'insert', '2024-04-05 14:53:00'
-- '306', 'before', 'insert', '2024-04-05 14:53:00'
-- '307', 'before', 'insert', '2024-04-05 14:53:00'
-- '308', 'before', 'insert', '2024-04-05 14:53:00'
-- '309', 'before', 'insert', '2024-04-05 14:53:01'
-- '310', 'before', 'insert', '2024-04-05 14:53:01'
-- '311', 'before', 'insert', '2024-04-05 14:53:01'
-- '312', 'before', 'insert', '2024-04-05 14:53:01'
-- '313', 'before', 'insert', '2024-04-05 14:53:01'
-- '314', 'before', 'insert', '2024-04-05 14:53:01'
-- '315', 'before', 'insert', '2024-04-05 14:53:02'
-- '316', 'before', 'insert', '2024-04-05 14:53:02'
-- '317', 'before', 'insert', '2024-04-05 14:53:02'
-- '318', 'before', 'insert', '2024-04-05 14:53:02'
-- '319', 'before', 'insert', '2024-04-05 14:53:02'
-- '320', 'before', 'insert', '2024-04-05 14:53:02'
-- '321', 'before', 'insert', '2024-04-05 14:53:02'
-- '322', 'before', 'insert', '2024-04-05 14:53:02'
-- '323', 'before', 'insert', '2024-04-05 14:53:02'
-- '324', 'before', 'insert', '2024-04-05 14:53:03'
-- '325', 'before', 'insert', '2024-04-05 14:53:03'
-- '326', 'before', 'insert', '2024-04-05 14:53:03'
-- '327', 'before', 'insert', '2024-04-05 14:53:03'
-- '328', 'before', 'insert', '2024-04-05 14:53:03'
-- '329', 'before', 'insert', '2024-04-05 14:53:03'
-- '330', 'before', 'insert', '2024-04-05 14:53:03'
-- '331', 'before', 'insert', '2024-04-05 14:53:03'
-- '332', 'before', 'insert', '2024-04-05 14:53:03'
-- '333', 'before', 'insert', '2024-04-05 14:53:04'
-- '334', 'before', 'insert', '2024-04-05 14:53:04'
-- '335', 'before', 'insert', '2024-04-05 14:53:04'
-- '336', 'before', 'insert', '2024-04-05 14:53:04'
-- '337', 'before', 'insert', '2024-04-05 14:53:04'
-- '338', 'before', 'insert', '2024-04-05 14:53:04'
-- '339', 'before', 'insert', '2024-04-05 14:53:04'
-- '340', 'before', 'insert', '2024-04-05 14:53:05'
-- '341', 'before', 'insert', '2024-04-05 14:53:05'
-- '342', 'before', 'insert', '2024-04-05 14:53:05'
-- '343', 'before', 'insert', '2024-04-05 14:53:05'
-- '344', 'before', 'insert', '2024-04-05 14:53:05'
-- '345', 'before', 'insert', '2024-04-05 14:53:05'
-- '346', 'before', 'insert', '2024-04-05 14:53:05'
-- '347', 'before', 'insert', '2024-04-05 14:53:05'
-- '348', 'before', 'insert', '2024-04-05 14:53:05'
-- '349', 'before', 'insert', '2024-04-05 14:53:06'
-- '350', 'before', 'insert', '2024-04-05 14:53:06'
-- '351', 'before', 'insert', '2024-04-05 14:53:06'
-- '352', 'before', 'insert', '2024-04-05 14:53:06'
-- '353', 'before', 'insert', '2024-04-05 14:53:06'
-- '354', 'before', 'insert', '2024-04-05 14:53:06'
-- '355', 'before', 'insert', '2024-04-05 14:53:06'
-- '356', 'before', 'insert', '2024-04-05 14:53:07'
-- '357', 'before', 'insert', '2024-04-05 14:53:07'
-- '358', 'before', 'insert', '2024-04-05 14:53:07'
-- '359', 'before', 'insert', '2024-04-05 14:53:07'
-- '360', 'before', 'insert', '2024-04-05 14:53:07'
-- '361', 'before', 'insert', '2024-04-05 14:53:07'
-- '362', 'before', 'insert', '2024-04-05 14:53:07'
-- '363', 'before', 'insert', '2024-04-05 14:53:07'
-- '364', 'before', 'insert', '2024-04-05 14:53:07'
-- '365', 'before', 'insert', '2024-04-05 14:53:08'
-- '366', 'before', 'insert', '2024-04-05 14:53:08'
-- '367', 'before', 'insert', '2024-04-05 14:53:08'
-- '368', 'before', 'insert', '2024-04-05 14:53:08'
-- '369', 'before', 'insert', '2024-04-05 14:53:08'
-- '370', 'before', 'insert', '2024-04-05 14:53:08'
-- '371', 'before', 'insert', '2024-04-05 14:53:08'
-- '372', 'before', 'insert', '2024-04-05 14:53:09'
-- '373', 'before', 'insert', '2024-04-05 14:53:09'
-- '374', 'before', 'insert', '2024-04-05 14:53:09'
-- '375', 'before', 'insert', '2024-04-05 14:53:09'
-- '376', 'before', 'insert', '2024-04-05 14:53:09'
-- '377', 'before', 'insert', '2024-04-05 14:53:09'
-- '378', 'before', 'insert', '2024-04-05 14:53:09'
-- '379', 'before', 'insert', '2024-04-05 14:53:10'
-- '380', 'before', 'insert', '2024-04-05 14:53:10'
-- '381', 'before', 'insert', '2024-04-05 14:53:10'
-- '382', 'before', 'insert', '2024-04-05 14:53:10'
-- '383', 'before', 'insert', '2024-04-05 14:53:10'
-- '384', 'before', 'insert', '2024-04-05 14:53:10'
-- '385', 'before', 'insert', '2024-04-05 14:53:10'
-- '386', 'before', 'insert', '2024-04-05 14:53:10'
-- '387', 'before', 'insert', '2024-04-05 14:53:10'
-- '388', 'before', 'insert', '2024-04-05 14:53:10'
-- '389', 'before', 'insert', '2024-04-05 14:53:11'
-- '390', 'before', 'insert', '2024-04-05 14:53:11'
-- '391', 'before', 'insert', '2024-04-05 14:53:11'
-- '392', 'before', 'insert', '2024-04-05 14:53:11'
-- '393', 'before', 'insert', '2024-04-05 14:53:11'
-- '394', 'before', 'insert', '2024-04-05 14:53:11'
-- '395', 'before', 'insert', '2024-04-05 14:53:11'
-- '396', 'before', 'insert', '2024-04-05 14:53:12'
-- '397', 'before', 'insert', '2024-04-05 14:53:12'
-- '398', 'before', 'insert', '2024-04-05 14:53:12'
-- '399', 'before', 'insert', '2024-04-05 14:53:12'
-- '400', 'before', 'insert', '2024-04-05 14:53:12'
-- '401', 'before', 'insert', '2024-04-05 14:53:12'
-- '402', 'before', 'insert', '2024-04-05 14:53:12'
-- '403', 'before', 'insert', '2024-04-05 14:53:12'
-- '404', 'before', 'insert', '2024-04-05 14:53:12'
-- '405', 'before', 'insert', '2024-04-05 14:53:13'
-- '406', 'before', 'insert', '2024-04-05 14:53:13'
-- '407', 'before', 'insert', '2024-04-05 14:53:13'
-- '408', 'before', 'insert', '2024-04-05 14:53:13'
-- '409', 'before', 'insert', '2024-04-05 14:53:13'
-- '410', 'before', 'insert', '2024st 100 records from the reserves ta-04-05 14:53:13'
-- '411', 'before', 'insert', '2024-04-05 14:53:13'
-- '412', 'before', 'insert', '2024-04-05 14:53:13'
-- '413', 'before', 'insert', '2024-04-05 14:53:14'
-- '414', 'before', 'insert', '2024-04-05 14:53:14'
-- '415', 'before', 'insert', '2024-04-05 14:53:14'
-- '416', 'before', 'insert', '2024-04-05 14:53:14'
-- '417', 'before', 'insert', '2024-04-05 14:53:14'
-- '418', 'before', 'insert', '2024-04-05 14:53:14'
-- '419', 'before', 'insert', '2024-04-05 14:53:14'
-- '420', 'before', 'insert', '2024-04-05 14:53:14'
-- '421', 'before', 'insert', '2024-04-05 14:53:15'
-- '422', 'before', 'insert', '2024-04-05 14:53:15'
-- '423', 'before', 'insert', '2024-04-05 14:53:15'
-- '424', 'before', 'insert', '2024-04-05 14:53:15'
-- '425', 'before', 'insert', '2024-04-05 14:53:15'
-- '426', 'before', 'insert', '2024-04-05 14:53:15'
-- '427', 'before', 'insert', '2024-04-05 14:53:15'
-- '428', 'before', 'insert', '2024-04-05 14:53:15'
-- '429', 'before', 'insert', '2024-04-05 14:53:15'
-- '430', 'before', 'insert', '2024-04-05 14:53:16'
-- '431', 'before', 'insert', '2024-04-05 14:53:16'
-- '432', 'before', 'insert', '2024-04-05 14:53:16'
-- '433', 'before', 'insert', '2024-04-05 14:53:16'
-- '434', 'before', 'insert', '2024-04-05 14:53:16'
-- '435', 'before', 'insert', '2024-04-05 14:53:16'
-- '436', 'before', 'insert', '2024-04-05 14:53:16'
-- '437', 'before', 'insert', '2024-04-05 14:53:16'
-- '438', 'before', 'insert', '2024-04-05 14:53:17'
-- '439', 'before', 'insert', '2024-04-05 14:53:17'
-- '440', 'before', 'insert', '2024-04-05 14:53:17'
-- '441', 'before', 'insert', '2024-04-05 14:53:17'
-- '442', 'before', 'insert', '2024-04-05 14:53:17'
-- '443', 'before', 'insert', '2024-04-05 14:53:17'
-- '444', 'before', 'insert', '2024-04-05 14:53:17'
-- '445', 'before', 'insert', '2024-04-05 14:53:17'
-- '446', 'before', 'insert', '2024-04-05 14:53:18'
-- '447', 'before', 'insert', '2024-04-05 14:53:18'
-- '448', 'before', 'insert', '2024-04-05 14:53:18'
-- '449', 'before', 'insert', '2024-04-05 14:53:18'
-- '450', 'before', 'insert', '2024-04-05 14:53:18'
-- '451', 'before', 'insert', '2024-04-05 14:53:18'
-- '452', 'before', 'insert', '2024-04-05 14:53:19'
-- '453', 'before', 'insert', '2024-04-05 14:53:19'
-- '454', 'before', 'insert', '2024-04-05 14:53:19'
-- '455', 'before', 'insert', '2024-04-05 14:53:19'
-- '456', 'before', 'insert', '2024-04-05 14:53:19'
-- '457', 'before', 'insert', '2024-04-05 14:53:19'
-- '458', 'before', 'insert', '2024-04-05 14:53:19'
-- '459', 'before', 'insert', '2024-04-05 14:53:19'
-- '460', 'before', 'insert', '2024-04-05 14:53:20'
-- '461', 'before', 'insert', '2024-04-05 14:53:20'
-- '462', 'before', 'insert', '2024-04-05 14:53:20'
-- '463', 'before', 'insert', '2024-04-05 14:53:20'
-- '464', 'before', 'insert', '2024-04-05 14:53:20'
-- '465', 'before', 'insert', '2024-04-05 14:53:20'
-- '466', 'before', 'insert', '2024-04-05 14:53:20'
-- '467', 'before', 'insert', '2024-04-05 14:53:20'
-- '468', 'before', 'insert', '2024-04-05 14:53:21'
-- '469', 'before', 'insert', '2024-04-05 14:53:21'
-- '470', 'before', 'insert', '2024-04-05 14:53:21'
-- '471', 'before', 'insert', '2024-04-05 14:53:21'
-- '472', 'before', 'insert', '2024-04-05 14:53:21'
-- '473', 'before', 'insert', '2024-04-05 14:53:21'
-- '474', 'before', 'insert', '2024-04-05 14:53:21'
-- '475', 'before', 'insert', '2024-04-05 14:53:21'
-- '476', 'before', 'insert', '2024-04-05 14:53:22'
-- '477', 'before', 'insert', '2024-04-05 14:53:22'
-- '478', 'before', 'insert', '2024-04-05 14:53:22'
-- '479', 'before', 'insert', '2024-04-05 14:53:22'
-- '480', 'before', 'insert', '2024-04-05 14:53:22'
-- '481', 'before', 'insert', '2024-04-05 14:53:22'
-- '482', 'before', 'insert', '2024-04-05 14:53:23'
-- '483', 'before', 'insert', '2024-04-05 14:53:23'
-- '484', 'before', 'insert', '2024-04-05 14:53:23'
-- '485', 'before', 'insert', '2024-04-05 14:53:23'
-- '486', 'before', 'insert', '2024-04-05 14:53:23'
-- '487', 'before', 'insert', '2024-04-05 14:53:23'
-- '488', 'before', 'insert', '2024-04-05 14:53:23'
-- '489', 'before', 'insert', '2024-04-05 14:53:23'
-- '490', 'before', 'insert', '2024-04-05 14:53:23'
-- '491', 'before', 'insert', '2024-04-05 14:53:24'
-- '492', 'before', 'insert', '2024-04-05 14:53:24'
-- '493', 'before', 'insert', '2024-04-05 14:53:24'
-- '494', 'before', 'insert', '2024-04-05 14:53:24'
-- '495', 'before', 'insert', '2024-04-05 14:53:24'
-- '496', 'before', 'insert', '2024-04-05 14:53:24'
-- '497', 'before', 'insert', '2024-04-05 14:53:24'
-- '498', 'before', 'insert', '2024-04-05 14:53:25'
-- '499', 'before', 'insert', '2024-04-05 14:53:25'
-- '500', 'before', 'insert', '2024-04-05 14:53:25'
-- '502', 'before', 'insert', '2024-04-05 14:52:26'
-- '503', 'before', 'insert', '2024-04-05 14:52:27'
-- '504', 'before', 'insert', '2024-04-05 14:52:27'
-- '505', 'before', 'insert', '2024-04-05 14:52:27'
-- '506', 'before', 'insert', '2024-04-05 14:52:31'
-- '507', 'before', 'insert', '2024-04-05 14:52:32'
-- '508', 'before', 'insert', '2024-04-05 14:52:32'
-- '509', 'before', 'insert', '2024-04-05 14:52:33'
-- '510', 'before', 'insert', '2024-04-05 14:52:34'



-- 5.5
select * from boats_log;

-- '5', 'before', 'insert', '2024-04-05 14:54:42'
-- '6', 'before', 'insert', '2024-04-05 14:54:42'
-- '7', 'before', 'insert', '2024-04-05 14:54:42'
-- '8', 'before', 'insert', '2024-04-05 14:54:42'
-- '9', 'before', 'insert', '2024-st 100 records from the reserves ta04-05 14:54:43'
-- '10', 'before', 'insert', '2024-04-05 14:54:43'
-- '11', 'before', 'insert', '2024-04-05 14:54:43'
-- '12', 'before', 'insert', '2024-04-05 14:54:43'
-- '13', 'before', 'insert', '2024-04-05 14:54:43'
-- '14', 'before', 'insert', '2024-04-05 14:54:43'
-- '15', 'before', 'insert', '2024-04-05 14:54:43'
-- '16', 'before', 'insert', '2024-04-05 14:54:44'
-- '17', 'before', 'insert', '2024-04-05 14:54:44'
-- '18', 'before', 'insert', '2024-04-05 14:54:44'
-- '19', 'before', 'insert', '2024-04-05 14:54:44'
-- '20', 'before', 'insert', '2024-04-05 14:54:44'
-- '21', 'before', 'insert', '2024-04-05 14:54:44'
-- '22', 'before', 'insert', '2024-04-05 14:54:44'
-- '23', 'before', 'insert', '2024-04-05 14:54:44'
-- '24', 'before', 'insert', '2024-04-05 14:54:45'
-- '25', 'before', 'insert', '2024-04-05 14:54:45'
-- '26', 'before', 'insert', '2024-04-05 14:54:45'
-- '27', 'before', 'insert', '2024-04-05 14:54:45'
-- '28', 'before', 'insert', '2024-04-05 14:54:45'
-- '29', 'before', 'insert', '2024-04-05 14:54:45'
-- '30', 'before', 'insert', '2024-04-05 14:54:45'
-- '31', 'before', 'insert', '2024-04-05 14:54:45'
-- '32', 'before', 'insert', '2024-04-05 14:54:46'
-- '33', 'before', 'insert', '2024-04-05 14:54:46'
-- '34', 'before', 'insert', '2024-04-05 14:54:46'
-- '35', 'before', 'insert', '2024-04-05 14:54:46'
-- '36', 'before', 'insert', '2024-04-05 14:54:46'
-- '37', 'before', 'insert', '2024-04-05 14:54:46'
-- '38', 'before', 'insert', '2024-04-05 14:54:46'
-- '39', 'before', 'insert', '2024-04-05 14:54:47'
-- '40', 'before', 'insert', '2024-04-05 14:54:47'
-- '41', 'before', 'insert', '2024-04-05 14:54:47'
-- '42', 'before', 'insert', '2024-04-05 14:54:47'
-- '43', 'before', 'insert', '2024-04-05 14:54:47'
-- '44', 'before', 'insert', '2024-04-05 14:54:47'
-- '45', 'before', 'insert', '2024-04-05 14:54:47'
-- '46', 'before', 'insert', '2024-04-05 14:54:48'
-- '47', 'before', 'insert', '2024-04-05 14:54:48'
-- '48', 'before', 'insert', '2024-04-05 14:54:48'
-- '49', 'before', 'insert', '2024-04-05 14:54:48'
-- '50', 'before', 'insert', '2024-04-05 14:54:48'
-- '51', 'before', 'insert', '2024-04-05 14:54:48'
-- '52', 'before', 'insert', '2024-04-05 14:54:48'
-- '53', 'before', 'insert', '2024-04-05 14:54:49'
-- '54', 'before', 'insert', '2024-04-05 14:54:49'

-- 5.6
select * from reserves_log;

-- 5.7 task5_7.c-->update_sailors.sql
-- 5.8 task5_8.c-->update_boats.sql

-- 5.10
select * from sailor_log;

-- 5.11
select * from boats_log;

-- 5.12
select * from reserves_log;

-- 5.13 task5_13.c
-- 5.14 task5_14.c

-- 5.15
delete from reserves limit 100;

-- 5.16 
select * from sailors_log;

-- 5.17
select * from boats_log;

-- 5.18
select * from reserves_log;

-- 6.2
DELIMITER //
CREATE TRIGGER sailor6_t3 -- name used earlier
BEFORE INSERT
ON sailors
FOR EACH ROW
precedes sailor_t1
BEGIN
INSERT INTO sailor_log(sid,event_ba,ops) VALUES (New.sid,'before','t3 insert');
END //
DELIMITER ;
-- violates check constraint

-- 6.1
DELIMITER //
CREATE TRIGGER sailor6_t2 -- name used earlier
BEFORE INSERT
ON sailors
FOR EACH ROW
precedes sailor_t3
BEGIN
INSERT INTO sailor_log(sid,event_ba,ops) VALUES (New.sid,'before','t2 insert');
END //
DELIMITER ;
-- violates check constraint

-- 7.1 task7_1.c

-- 7.2
select * from sailor_log;

-- 8.1
DELIMITER //
CREATE TRIGGER sailors_log_t1 -- name used earlier
after INSERT
ON sailor_log
FOR EACH ROW
BEGIN
INSERT INTO sailors_log_log(sid,event_ba,ops) VALUES (New.sid,'after','insert');
END //
DELIMITER ;


-- 8.2
DELIMITER //
CREATE TRIGGER sailors_log_log_t1 -- name used earlier
after INSERT
ON sailors_log_log
FOR EACH ROW
BEGIN
INSERT INTO sailors_log_log_log(sid,event_ba,ops) VALUES (New.sid,'after','insert');
END //
DELIMITER ;

-- 10.1 task10.c

-- 10.2
select * from sailor_log;

-- 10.3
select * from sailors_log_log;

-- 10.4
select * from sailors_log_log_log;

-- 11.1
DELIMITER //
CREATE TRIGGER sailors_log_log_log_t1 -- name used earlier
after INSERT
ON sailors_log_log_log
FOR EACH ROW
BEGIN
INSERT INTO sailors(sid,event_ba,ops) VALUES ('anushka','after','insert');
END //
DELIMITER ;

-- 12.1 task12.c
-- 12.2 
select * from sailor_log;
-- 12.3
select * from sailors_log_log;
-- 12.4
select * from sailors_log_log_log;

-- 13.1 task13_1.c
-- 13.2 task13_2.c
-- 13.3 task13_3.c

-- 13.4 
select * from sailor_log;
-- 13.5
select * from sailors_log_log;
-- 13.6
select * from sailors_log_log_log;