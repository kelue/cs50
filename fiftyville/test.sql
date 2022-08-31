SELECT people.name, people.phone_number, people.license_plate FROM people JOIN phone_calls ON people.phone_number=phone_calls.receiver WHERE phone_calls.caller IN (SELECT people.phone_number FROM people
     JOIN bank_accounts ON people.id=bank_accounts.person_id
     WHERE bank_accounts.account_number IN
         (SELECT account_number FROM atm_transactions
          WHERE day = 28 AND month = 7 AND atm_location LIKE "%Leggett%" AND transaction_type LIKE "withdraw")
          AND people.phone_number IN
            (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND duration < 60)
            AND people.license_plate IN
            (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND hour = 10 AND minute < 26 AND activity = "exit")) AND phone_calls.day=28 AND month = 7 AND duration < 60;