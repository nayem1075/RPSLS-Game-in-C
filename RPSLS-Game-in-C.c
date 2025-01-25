#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Structure to store player information
struct Player
{
    char name[50];// Player's name
    int wins;    // Number of wins
    int losses; // Number of losses
    int ties;  // Number of ties
};

// Function to display the choices to the player
void Choice()
{
    printf("\nChoose your move : \n");
    printf("0. Rock\n");
    printf("1. Paper\n");
    printf("2. Scissors\n");
    printf("3. Lizard\n");
    printf("4. Spock\n");
}

// Function to get the computer's random choice
int getComputerChoice()
{
    return rand() % 5;// Randomly selects between 0 and 4 (Rock, Paper, Scissors, Lizard, Spock)
}

// Function to calculate the winner between the player and the computer
int calculateWinner(int PlayerChoice,int ComputerChoice)
{
    if(PlayerChoice == ComputerChoice)
        return 0; // It's a tie
    // Rules for winning
    if(PlayerChoice == 0 && (ComputerChoice == 2 || ComputerChoice==3))
        return 1; // Rock beats Scissors and Lizard
    else if(PlayerChoice == 1 && (ComputerChoice == 0 || ComputerChoice == 4))
        return 1;// Paper beats Rock and Spock
    else if(PlayerChoice == 2 && (ComputerChoice == 1 || ComputerChoice == 3))
        return 1;// Scissors beats Paper and Lizard
    else if(PlayerChoice == 3 && (ComputerChoice == 1 || ComputerChoice == 4))
        return 1;// Lizard beats Paper and Spock
    else if(PlayerChoice == 4 && (ComputerChoice == 0 || ComputerChoice == 2))
        return 1;// Spock beats Rock and Scissors
    else
    return -1;// Player loses
}

// Function to display the leaderboard
void displayLeaderboard(int TotalPlayers,struct Player players[])
{
    printf("\nLeaderboard : \n");
    for(int i=0; i<TotalPlayers; i++)
    {
        // Display player statistics
        printf("\n%d.%s\nWins : %d\nLosses : %d\nTies : %d\n",
               i+1,players[i].name,players[i].wins,players[i].losses,players[i].ties);
    }
}

// Function to play the game for a specific player
void PlayGame(struct Player*player,int TotalRounds)
{
    int PlayerChoice,ComputerChoice,result;
    int RoundsPlayed = 0;

    while(RoundsPlayed < TotalRounds)
    {
        printf("\nRound %d of %d : \n",RoundsPlayed + 1,TotalRounds);
        Choice();
        printf("Enter your choice (0-4) : ");
        scanf("%d",&PlayerChoice);

        if(PlayerChoice <0 || PlayerChoice >4)
        {
            // Validate the player's choice
            printf("Invalid choice. Please select a valid Option (0-4).\n");
            continue;
        }

        ComputerChoice = getComputerChoice();

         // Display the choices made by the player and the computer
        printf("%s choose : %s\n",player->name,
               PlayerChoice == 0? "Rock":
               PlayerChoice == 1? "Paper":
               PlayerChoice == 2? "Scissors":
               PlayerChoice == 3? "Lizard": "Spock");

        printf("Computer Choose : %s\n",
               ComputerChoice == 0? "Rock":
               ComputerChoice == 1? "Paper":
               ComputerChoice == 2? "Scissors":
               ComputerChoice == 3? "Lizard": "Spock");

        result = calculateWinner(PlayerChoice,ComputerChoice);
        // Update player statistics based on the result
        if(result==1)
        {
            printf("Congratulations %s. You won this round!\n",player->name);
            player->wins++;
        }
        else if (result == -1)
        {
            printf("Oops %s. You lost this round.\n",player->name);
            player->losses++;
        }
        else
        {
            printf("Match tied.\n");
            player->ties++;
        }
        RoundsPlayed++;
        // Display the overall result after all rounds
        if(RoundsPlayed == TotalRounds)
        {
            printf("\nBest of %d Rounds Result : \n",TotalRounds);
            printf("Player %d | Computer : %d | Ties : %d\n",
                   player->wins,player->losses,player->ties);
            break;
        }
        // Ask if the player wants to play another round
        char choice;
        while(1)
        {
            printf("Do you want to play another round?(y/n) : ");
            scanf(" %c",&choice);
            if(choice == 'y' || choice == 'Y')
            {
                break;
            }
            else if(choice == 'n' || choice == 'N')
            {
                printf("Thanks for playing! See you next time.\n");
                return;
            }
            else
            {
                printf("Invalid choice.Please enter 'y' or 'n'.\n");
            }
        }
    }
}

int main()
{
    srand(time(0)); // Seed the random number generator

    printf("************************************* \n*****************\n");

    printf("                 Welcome to Rock Paper \n        Scissors Lizard Spock\n");

    printf("*************************************\n*****************\n\n");

    int MaximumPlayers;
    printf("Enter how many Players will play : ");
    scanf(" %d",&MaximumPlayers);

    // Clear any remaining input from the buffer
    while (getchar()!= '\n');

    struct Player players[MaximumPlayers];
    int TotalRounds;

    // Get player names
    for(int i=0; i<MaximumPlayers; i++)
    {
        printf("Enter Player %d's name : ",i+1);

        gets(players[i].name);// Reads the player's name as a string.

        players[i].wins = 0;
        players[i].losses = 0;
        players[i].ties = 0;
    }
    printf("Enter the number of rounds for Best of N : ");
    scanf("%d",&TotalRounds);
    char PlayAgain;
    do
    {
        // Start game for each player
        for(int i=0; i<MaximumPlayers; i++)
        {
            printf("\n\nStarting game for player : %s\n",players[i].name);
            PlayGame(&players[i],TotalRounds);
        }
        // Display leaderboard
        displayLeaderboard(MaximumPlayers,players);
        // Ask if players want to play another game
        printf("\nDo you want to Play another Game? (y/n) : ");
        scanf(" %c",&PlayAgain);
    }
    while(PlayAgain == 'y' || PlayAgain == 'Y');

    printf("Thanks for playing! See you next time.\n");

    return 0;
}






