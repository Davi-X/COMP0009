CLI (Command Line Interface)  
Bash (the Bourne-Again SHell)   

[cat and echo]   
SQL (Structured Query Language)

We use **database management systems** ,DBMS in short  to work with database

A database is a set of data stored in the computer, and structured into tables

Unlike Excel and Google Sheets, you may not manipluate the data directly, instead, you can write quires to access the subset of data.

Common data type
* INTEGER
* TEXT
* DATE
* REAL  

Some constraints (or *constraints violation*)
* PRIMARY KEY
  * uniquely identify the rows in the table
  * one in each table
* UNIQUE
   (e.g. for political scientists, they want to find which Boris Joson, so they may label Boris JosonA,Boris JosonB to unquely identify, also id and email may not be human-readible, so they may use this way to identify)
  * Different value for every row
  * Could have many UNIQUE columns in a table
* NOT NULL
* DEFAULT 'XXX'

```sql
CREATE TABLE table_name (
      column_name1 Type,
      column_name2 Type,
      column_name3 Type
);
```

```sql
INSERT INTO table_name (column_name1, column_name2, column_name3)
VALUES
(row1_val1, row1_val2, row1_val3),
(row2_val1, row2_val2, row2_val3),
(row3_val1, row3_val2, row3_val3);

```
**_We use semicolon as the end of the query**  

```sql
ALTER TABLE table_name /* Make special changes */
ADD COLUMN column_name Type
```
```sql
UPDATE table_name
SET column_name2 = xxxx
WHERE column_name1 = xxx;
```
ALTER for columns (add, remove, modify)
UPDATE for rows (only modify)

```sql
DELETE FROM table_name
WHERE xxxx; /* condition */
/* LIMIT n */
```

```sql
SELECT a AS 'b', c AS 'd'
FROM xxx;
/* rename only in the result, not change the original name in the table */
```
```sql
SELECT DISTINCT genre, year /* This only works for the distinct combination of genre & year */
FROM xxx;
```

```sql
/*
This will return all rows where the value in the
x column is greater than the y column value.
*/
SELECT x, y
FROM coordinates
WHERE x > y;
/*
   or WHERE condition1 AND condition2
   or WHERE condition1 OR condition2
*/
```

equal sign in SQL is '='

```sql
WHERE name LIKE 'S_v_en';
/* Each underscore represents a character or symbol (like .) */
WHERE name LIKE '%man%';
/* % sign represents zero or more characters */
```

```SQL
SELECT *
FROM movies
WHERE name BETWEEN 'A' AND 'J'; /*inclusive*/
/* Starts from movies' name begin with A to G && the movie's name is J */
```

```SQL
WHERE condition /* always following after order */
ORDER BY XXX DESC /* descending order */
ASC /* ascending order */
```
**Question**  

Is there a limit to the number of columns a table can have?

**Answer**  

Yes, there is a limit to the number of columns a table can have.

In SQLite in particular, the upper bound for this number of columns is stored in a parameter called SQLITE_MAX_COLUMN, and by default, it is set to 2000 columns.

This value can be changed during compile time and can be set up to a maximum value of 32767. However, realistically, your tables will probably never need these many columns, but, it is available as an option if ever needed.

---

Question

In the context of this lesson 8, can we see a database’s schema without being given a diagram?
Answer

Yes, you can!

In SQLite specifically, there is a special table named SQLITE_MASTER, which defines the schema for databases. This special table contains information about certain qualities like the table name and the schema, which provides details about all the column names and their data types.

To view this table, you can run the following statement,

SELECT *
FROM sqlite_master;

Feel free to try this out in some of the exercises to view the table information!

---
Calculations performed on multiple rows of a table are called aggregates.

```sql
select round(avg(price), n)
--'n'represents n decimal places
```

```sql
select category, sum(downloads)
from table_name
where condition
group by category
order by xxx;
```

```sql
select category, price, avg(downloads)
from fake_apps
group by 1, 2;
/*
   Column Reference (column_number after the 'SELECT' command)
   1 represents 1st column
   2 represents 2nd column
   ...
*/
```
When we want to join two tables together
we use *join on* command
This is the *inner join*  
[Inner Join] (https://s3.amazonaws.com/codecademy-content/courses/learn-sql/multiple-tables/inner-join.gif)
```sql
select *
from orders
join subscriptions
  on orders.subscription_id = subscriptions.subscription_id;
```
*[Left Join]* (https://s3.amazonaws.com/codecademy-content/courses/learn-sql/multiple-tables/left-join.gif)
*[Full Outer Join]* merges the left join & right join

When the primary key for one table appears in a different table, it is called a foreign key.

The most common types of joins will be joining a foreign key from one table with the primary key from another table.

A column that can uniquely identify a record of data is known as a "Candidate Key". Tables can have multiple "Candidate Key"s, each of which could potentially be the "Primary Key", but there must only be one "Primary Key" per table.

```sql
select month, count(*)
from newspaper
cross join months
where start_month <= month and end_month >= month
group by month;

--*cross join* gives all the combinations for tables
```

When we want to stack one dataset on top of the other, we can use Union
```sql
SELECT *
FROM table1
UNION
SELECT *
FROM table2;
--When you combine tables with UNION, duplicate rows will be excluded. Recall in the Venn Diagram
```

```sql
WITH previous_query AS (
   SELECT customer_id,
      COUNT(subscription_id) AS 'subscriptions'
   FROM orders
   GROUP BY customer_id
)
SELECT customers.customer_name,
   previous_query.subscriptions
FROM previous_query
JOIN customers
  ON previous_query.customer_id = customers.customer_id;

  /*
  Essentially, we are putting a whole first query inside the parentheses () and giving it a name. After that, we can use this name as if it’s a table and write a new query using the first query.
  */
```

Calculate the churn_rate for multiple months
```sql
WITH months AS (
  SELECT
    '2017-01-01' AS first_day,
    '2017-01-31' AS last_day
  UNION
  SELECT
    '2017-02-01' AS first_day,
    '2017-02-28' AS last_day
  UNION
  SELECT
    '2017-03-01' AS first_day,
    '2017-03-31' AS last_day
),
cross_join AS (
  SELECT *
  FROM subscriptions
  CROSS JOIN months
),
status AS (
  SELECT
    id,
    first_day AS month,
    CASE
      WHEN (subscription_start < first_day)
        AND (
          subscription_end > first_day
          OR subscription_end IS NULL
        ) THEN 1
      ELSE 0
    END AS is_active,
    CASE
      WHEN subscription_end BETWEEN first_day AND last_day THEN 1
      ELSE 0
    END AS is_canceled
  FROM cross_join
),
status_aggregate AS (
  SELECT
    month,
    SUM(is_active) AS active,
    SUM(is_canceled) AS canceled
  FROM status
  GROUP BY month
)
SELECT
  month,
  1.0 * canceled / active AS churn_rate
FROM status_aggregate;
```
Many Data Analyt using Python to visualsize the data rather R since
* Versatility (Numerous third-party libraries)
* Python has become a go-to language for data analysis

Web scraping is a term used to describe the extraction of data from websites, typically through the HTML code.

**Pandas** python library provides **Dataframe**, which resembles 2D array  
i.e. collective Series(induvidual column)  

**Matplotlib** python library to visualize data (Charts ,control color and labels)

Machine Learning can be branched out into 2 categories
* Supervised Learning   
  Take the labeled input to predict the future output
* Unsupervised Learning  
  Take all unlabeled input and group them based on patterns




  Aliasing Table name
  ```sql
  from person p;
  -- no need for the as command
  ```

  ```sql
  select *
  from person p
  where p.first_name
  in ('Jon', 'Fritiz');

  -- Multiple boolean expressions
  -- select all people whose first_name is Jon or Firtiz
  -- equivalent to where p.first_name = 'Jon' or p.first_name = 'Fritiz'
  ```

  ```sql
  -- Add a constraint
  CREATE TABLE (
    id, INTEGER NOT NULL,
    person_id INTEGER NOT NULL,
    number VARCHAR(55) NOT NULL,
    CONSTRAINT
    PK_person
    PRIMARY KEY
    (id, person_id)
    /* There is a constraint called PK_person (pk shorts for primary key) is a primary key constraint, the columns in the parethese are PK */
  )
  ```
  ADD CONSTARINT
  FK_xxx_xxx
  FOREIGN KEY
  (XXX)
  REFERENCES
  table_name
  (XXXX)

  DROP TABLE --delete the whole table

   /* You cannot drop the table if it is a foreign table references others */
