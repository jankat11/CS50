-- Keep a log of any SQL queries you execute as you solve the mystery.

-- crime reports and witnesses at humphrey street with given date
SELECT *
  FROM crime_scene_reports
 WHERE street LIKE "%humphrey street%"
   AND day = 28;
SELECT *
  FROM interviews
 WHERE year = 2021 AND month = 7
   AND day = 28;

--people who leaves bakery with car about ten minutes after theft
SELECT name
  FROM people
 WHERE license_plate IN
     (SELECT license_plate FROM bakery_security_logs
       WHERE year = 2021
         AND month = 7 AND day = 28 AND hour >= 10 AND hour < 11 AND minute >= 14 AND activity = "exit")
INTERSECT

-- people who withdraw money from atm at legget street morning time.
SELECT name
  FROM people
 WHERE id IN
     (SELECT person_id
        FROM bank_accounts WHERE account_number IN
            (SELECT account_number
               FROM atm_transactions
              WHERE atm_location
               LIKE "%legget%" AND month = 7 AND day = 28 AND transaction_type = "withdraw"))
INTERSECT

--people who talked with phone less than one minute after theft
SELECT name
  FROM people
 WHERE phone_number IN
     (SELECT caller
        FROM phone_calls
       WHERE month = 7 AND day = 28 AND duration <= 60)

INTERSECT
-- people who flighed from fiftyville earliest next day
SELECT name
  FROM people
 WHERE passport_number IN
     (SELECT passport_number
        FROM passengers
       WHERE flight_id IN
           (SELECT id
              FROM flights
             WHERE year = 2021
               AND month = 7 AND day = 29 AND origin_airport_id = 8
          ORDER BY hour LIMIT 1));

-- earliest flght from fiftville next day of theft and its destination
SELECT city
  FROM airports
 WHERE id IN
     (SELECT destination_airport_id
        FROM flights
       WHERE year = 2021
         AND month = 7 AND day = 29
         AND origin_airport_id
          IN (SELECT id FROM airports WHERE full_name LIKE "%fiftyville%")
    ORDER BY hour LIMIT 1);

-- the person who talked too much with phone on crime day and its accomplice according clues from Raymond and Emma
SELECT name
  FROM people
 WHERE phone_number IN
     (SELECT receiver
        FROM phone_calls
       WHERE month = 7
         AND day = 28 AND caller = "(367) 555-5533"
         AND duration = 45);
