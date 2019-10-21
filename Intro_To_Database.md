Contrasting Database system with system which stored data but not
File-based system
   * Definition: 
     * It is the system of collections of application programs (stores data) that perform services for end users
      e.g. reports 
     * Each application program defines & manages its own data 
   * cons
     * Speration and isolation of data  
     * Dulplication of data  (Wasted space)
     * Data Dependence (Each program defins its own data & sturcture in their own code)
     * Incompatible file formats (cannot easily access another file data) 
     * Fixed quiries / proliferation of appplication programs (Any new requirments need a new program)

DBMS (Database Management System)
   * Definition: 
     * A shared collection of logically related data (and a description of data), designed to meet the information needs of an origansation
     * A self describing collection of integrated records 
   
   * Users -> DBMS -> Database (stores data in a structure way) 
   * Multiple users are allowed to access at the same time, solving the problem of concurrent access of the same data 
   * Basic functions
      * Communicate with database (SQL)
      * Security system (keep security & authorised access only for the authorised data)
      * Data integrity system (Data meet the standard & reach the minimum of duplicated data)
      * Concurrency control system
      * Recovery control system (Data won't be damaged by the failure if transation)
      * user - acces catalog 
        * what structure
        * data it holds
        * statics about data
  
  DDL: Data Definition Language (creating and modifying data structures)
  DML: Data Manipulation Languagae (Manipulation of data content)

SQL Notes
* Different storage engines (2 most popular ones)
  [MySql Storage engines](http://www.expertphp.in/article/what-are-the-main-differences-between-innodb-and-myisam)
   * MYISAM 
   * INNODB
  
* Insert data from a local file
  * LOAD DATA LOCAL INFILE "name.txt" INTO TABLE xxx;
  * in phpMyadmin use tools under import tab
* Extract info functions and caluses
  * SELECT * FROM XXX;
  * WHERE 
  * ORDER BY XXX DESC / ASCE (default asceding)
  * GROUP BY
    (If there is a 'group by', all columns appeared in select must appear in group by unless aggregrate functions)
  * HAVING  
  * BETWEEN AND (inclusive)
  * IN (A, B, ...) (in particular multiple columns)
  * LIKE '%XXX%'  (pattern matching)
    ('%' zero or more characters)
    ('_' single character)
     e.g. LIKE '%awr'
  * IS NULL (IS NOT NULL)
  * logic symbols
    * AND 
    * OR 
    * NOT
* Aggregrate functions (can only be used in SELECT & HAVING clauses)
  * numeric & non-numeric fields
    * COUNT
    * MIN
    * MAX
  * only numeric field
    * SUM
    * AVG
    * ROUND(XXX, n) (n decimal placesß)
* Subquery   
   is a SELECT statement embedded in a query 
   (results still from the same table)
   (does not connect multiple tables)
   * nested subquery needs 'IN'
   e.g. main IN (sub_A (sub_B))
   * use 'ALL', 'ANY' / 'SOME' to limit the data in the subquery
   e.g. main expression (consisits of subquery)
   xxx... salary > some (xxx...)
   * (NOT) EXISTS to simply produce true / false 
     * true  --> at least one row in result
     * false --> empty result table
     * since it just only check for existence, the subquery can contain more than one column 
* JOIN Structure  
  [SQL Join Prensentation](https://www.w3resource.com/slides/sql-joins-slide-presentation.php) 

Note: We can use multiple ‘GROUP BY' to get data

* Combine multiple tables 
  * support in MySql
    * UNION  
    (XXX...) UNION (XXX...)
  * does not support in MySql
    * INSERSECT
    * EXCEPT (equivalent to difference in set theory) 

  