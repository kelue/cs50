--this query below work too but it is slow. Better to use when results are small.
-- SELECT T1.movie_id
-- FROM stars T1
-- JOIN stars T2 ON T1.movie_id = T2.movie_id AND T2.person_id=(SELECT id FROM people WHERE name="Johnny Depp")
-- WHERE T1.person_id=(SELECT id FROM people WHERE name="Helena Bonham Carter");

SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN ((SELECT id FROM people WHERE name="Helena Bonham Carter"), (SELECT id FROM people WHERE name="Johnny Depp")) GROUP BY movie_id HAVING COUNT(*) = 2);