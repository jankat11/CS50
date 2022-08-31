-- write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.
SELECT DISTINCT(name) FROM people JOIN stars ON stars.person_id = people.id WHERE movie_id IN
(SELECT id FROM movies WHERE year = 2004) ORDER BY birth;