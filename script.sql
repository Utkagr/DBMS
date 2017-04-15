CREATE USER '13MA20044'@'localhost' IDENTIFIED BY 'dbms';
GRANT ALL PRIVILEGES ON * . * TO '13MA20044'@'localhost';
CREATE DATABASE Institute;
CREATE TABLE departments(
	dept_id varchar(255) PRIMARY KEY,
	dept_name varchar(255) NOT NULL,
	dept_type varchar(255) NOT NULL,
	CHECK(dept_type ='Department' OR dept_type ='Center' OR dept_type ='School')
);

CREATE TABLE courses(
	course_id varchar(255) PRIMARY KEY,
	course_name varchar(255) NOT NULL,
	credit int NOT NULL,
	course_type varchar(255) NOT NULL,
	offered_by_dept varchar(255) NOT NULL,
	CHECK((credit BETWEEN 0 and 15) AND (course_type ='Theory' OR course_type ='Lab' OR course_type ='Project')),
	FOREIGN KEY(offered_by_dept) REFERENCES departments(dept_id)
);

CREATE TABLE students(
	rollno varchar(255) PRIMARY KEY,
	student_name varchar(255) NOT NULL,
	dept_id varchar(255) NOT NULL,
	degree varchar(255) NOT NULL,
	CHECK(degree = 'BTech' OR degree = 'MSc' OR degree = 'MTech'),
	FOREIGN KEY(dept_id) REFERENCES departments(dept_id)
);
CREATE TABLE performance(
	rollno varchar(255),
	course_id varchar(255),
	marks int,
	CHECK(marks BETWEEN 0 and 100),
	PRIMARY KEY (rollno,course_id),
	FOREIGN KEY(rollno) REFERENCES students(rollno),
	FOREIGN KEY(course_id) REFERENCES courses(course_id)
);

INSERT INTO departments
VALUES('MA','mathematics','Department');
INSERT INTO departments
VALUES('NA','oena','Department');
INSERT INTO departments
VALUES('CS','computer science','Department');
INSERT INTO departments
VALUES('VGSOM','vinod gupta school','School');
INSERT INTO departments
VALUES('CIC','computer informatics center','Center');

INSERT INTO courses
VALUES('MA10004','dbms',3,'Theory','MA');
INSERT INTO courses
VALUES('MA10002','os',4,'Lab','MA');
INSERT INTO courses
VALUES('ML10003','machine learning',6,'Project','CS');
INSERT INTO courses
VALUES('MA10006','pk_lab',2,'Lab','MA');
INSERT INTO courses
VALUES('OE10005','fluid mechanics',4,'Theory','NA');

INSERT INTO students
VALUES('13MA20044','utkarsh agrawal','MA','MSc');
INSERT INTO students
VALUES('13MA20045','abcd1','MA','MSc');
INSERT INTO students
VALUES('13CS10023','ankush chatterjee','CS','BTech');
INSERT INTO students
VALUES('13NA21034','arnav jain','NA','MTech');
INSERT INTO students
VALUES('13VG10021','aradhya kasat','VGSOM','BTech');
INSERT INTO students
VALUES('13MA20041','Sidhharth Tekriwal','MA','MTech');
INSERT INTO students
VALUES('13MA20037','Shivam Adarsh','MA','MTech');
INSERT INTO students
VALUES('13MA20023','Mudit bachhawat','MA','MTech');

INSERT INTO performance
VALUES('13MA20044','MA10004',99);
INSERT INTO performance
VALUES('13MA20045','MA10004',87);
INSERT INTO performance
VALUES('13CS10023','ML10003',20);
INSERT INTO performance
VALUES('13NA21034','OE10005',65);
INSERT INTO performance
VALUES('13VG10021','MA10006',78);
INSERT INTO performance
VALUES('13MA20044','ML10003',97);
INSERT INTO performance
VALUES('13MA20041','MA10004',93);
INSERT INTO performance
VALUES('13MA20037','MA10004',73);
INSERT INTO performance
VALUES('13MA20037','MA10006',83);
INSERT INTO performance
VALUES('13MA20023','MA10004',84);
INSERT INTO performance
VALUES('13MA20044','MA10002',84);
INSERT INTO performance
VALUES('13MA20023','OE10005',24);

select * from departments;
select * from courses;
select * from students;
select * from performance;

/* The list of all students who belonged to "MA" department and registered for course offered by "CS" department.*/
select s.rollno,s.student_name 
from students as s,performance as p,courses as c
where (s.rollno = p.rollno and p.course_id = c.course_id 
and s.dept_id = 'MA' and c.offered_by_dept = 'CS');

/*All courses which has atleast one "MTech" student with marks greater than 80.*/
select distinct c.course_name 
from courses as c,students as s,performance as p
where (c.course_id = p.course_id and s.rollno=p.rollno and s.degree= 'MTech' and p.marks>80);

/*maximum marks of department/ center/ school wise maximum marks in each course.*/
select d.dept_id,c.course_id,MAX(p.marks)
from departments as d,courses as c,students as s,performance as p
where (d.dept_id = s.dept_id and c.course_id = p.course_id and s.rollno=p.rollno)
group by c.course_id;

/* The list of "MSc" students with average score greater than 90*/
select s.student_name
from students as s,performance as p
where s.rollno = p.rollno and s.degree = 'MSc'
group by s.student_name
having avg(p.marks) > 90;
