#include "cs50.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;


typedef struct
{
    int winner;
    int loser;
    int different;
}
difference;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)// clean locks
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)// numero de votos
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];//number of candidates

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)// cada candidato su ranking
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))// check the vote if it is valid
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        for (int i = 0; i < candidate_count; i++)
        {
            printf("order %d\n", ranks[i]);
        }

        record_preferences(ranks);// record the vote

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

bool vote(int rank, string name, int ranks[])
{
        for (int i = 0; candidates[i] != NULL; i++)
        {
            if (strcmp(candidates[i], name) == 0)
            {
                ranks[rank] = i;
                return true;
            }
        }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
//  0   1   2
//  1   0   2  rank

//          0   1   2
//    0     0   0   0
//    1     1   0   1
//    2     0   0   0

// 0 1 1 0
// 0 2 2 0
// 1 2 2 1

//        0   1   2   3
//    0   0   3   3   4
//    1   1   0   4   4
//    2   1   0   0   3
//    3   0   0   1   0


//        0   1   2   3  4
//    0   0   3   3   4  1
//    1   1   0   4   4  1
//    2   1   0   0   3  2
//    3   0   0   1   0  3
//    4   1   1   2   3  0


    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]+=1;
        }
    }

    preferences[0][0] =0;
    preferences[0][1] =76;
    preferences[0][2] =56;
    preferences[0][3] =1;

    preferences[1][0] = 34;
    preferences[1][1] =0;
    preferences[1][2] =23;
    preferences[1][3] =54;

    preferences[2][0] =1;
    preferences[2][1] =1;
    preferences[2][2] =0;
    preferences[2][3] =566;

    preferences[3][0] =13;
    preferences[3][1] =221;
    preferences[3][2] =5;
    preferences[3][3] =0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d ", preferences[i][j]);
        }
        printf("\n");
    }



}

// Update ranks given a new vote
typedef struct
{
    int index;
    int value;
}info;
//int orden[MAX];

info unsorted[MAX];


// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
    int size = candidate_count;
    int k = 1;
    int l = 0;
    int h = 0;

    for (int i = 0; i < size; i++) {
        for (int j = k; j < size; j++) {

            // i = 0, j = 1
            if (preferences[i][j] > preferences[j][i]) {   //0 1 > 1 0
                pairs[l].winner = i;
                pairs[l].loser = j;
                pair_count++;
                l++;

                unsorted[h].value = preferences[i][j] - preferences[j][i];
                unsorted[h].index = h;
                h++;
            } else if (preferences[i][j] < preferences[j][i]) {   //0 1 < 1 0
                pairs[l].winner = j;
                pairs[l].loser = i;
                pair_count++;
                l++;
                unsorted[h].value = preferences[j][i] - preferences[i][j];
                unsorted[h].index = h;
                h++;

            }

        }
        k++;

    }

    for (int m = 0; m < pair_count; ++m) {
        printf("Winnner: %d Loser: %d - by: %d\n", pairs[m].winner, pairs[m].loser, unsorted[m].value);

    }

    for (int n = 0; n < pair_count; ++n) {
        printf("value: %d index: %d ", unsorted[n].value, unsorted[n].index);


        printf("\n");
    }

}


void swap(info *a, info *b)
{
    info temp;
    temp = *a;
    *a = *b;
    *b = temp;

}

pair ordenado[MAX];

void sort_pairs(void)
{
    bool swapped;
    for (int k = 0; k < pair_count - 1; k++)
    {
        swapped = false;
        for (int l = 0; l < pair_count - k ; l++)
        {
            if (unsorted[l].value < unsorted[l + 1].value)
            {
                swap(&unsorted[l], &unsorted[l + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }

    for (int i = 0; i < pair_count ; ++i) {

    }

    printf("Ordenado--------> \n");
    for (int n = 0; n < pair_count; ++n)
    {
        printf("value: %d index: %d\n ", unsorted[n].value, unsorted[n].index);
    }

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

