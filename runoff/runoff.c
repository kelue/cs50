#include <cs50.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            //record the voters preference for that candidate.
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int preferred_candidate = 0;
    // for each voter
    for (int i = 0; i < voter_count; i++)
    {
        // check each ranked preference
        for (int j = 0; j < candidate_count; j++)
        {
            //assign the index of the candidate to a variable and use that variable to recover the candidate.
            preferred_candidate = preferences[i][j];
            if (!candidates[preferred_candidate].eliminated)
            {
                candidates[preferred_candidate].votes++;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    //calculate 50% of votes needed to win
    int wincount = ceil(voter_count / 2);

    //loop to check each candidate's number of vote, declare them winner if they meet the required number
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > wincount)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //calculate 50% of votes needed to win and initialize it to minimum value
    int min = ceil(voter_count / 2);

    //loop through the candidates votes, if the vote is less than the value of min, assign the vote count to min. At the end of the loop we should have the smallest vote count.
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min && !candidates[i].eliminated)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //loop through each remaining candidate, if any candidate has higher than the minimum and is not eliminated, that means the result is not tied.
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > min && !candidates[i].eliminated)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //loop through all the candidates and eliminate those whose votes are equal to the minimum votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}