#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Player {
    std::string name;
    int points;
    int rank;
    int consecutiveOnes;

    Player(const std::string& playerName)
        : name(playerName), points(0), rank(0), consecutiveOnes(0) {}
};

void movePlayer(Player& player,int roll) {
    std::cout << "Player " << player.name << " rolled a " << roll << std::endl;
    
    if (roll == 1) {
        if (player.consecutiveOnes == 1) {
            std::cout << "Player " << player.name << " rolled two consecutive 1s and is penalized." << std::endl;
            player.consecutiveOnes = 0;
        } else {
            player.points += roll;
            player.consecutiveOnes++;
        }
    } 
    else if(roll==6){
        while(roll==6){
            std::cout<<"Player "<<player.name<<" roll again because of 6 in dice"<<std::endl;
            player.points += roll;
            std::cout << "Player " << player.name << ", it's your turn. Press any character to roll the dice: ";
            char input;
            std::cin >> input;
            if(input){
                roll = rand()%6+1;
            }
        }
        player.points += roll;

    }
    else {
        player.points += roll;
        player.consecutiveOnes = 0;
    }

    std::cout << "Player " << player.name << " accumulated " << player.points << " points." << std::endl;
}

void rollDice(Player& player){
    int roll = rand() % 6 + 1;
    movePlayer(player,roll);
}

void printRankings(const std::vector<Player>& players) {
    std::cout << "Rankings:\n";
    for (int i=0;i<players.size();i++) {
        Player player = players[i];
        std::cout << "Player " << player.name << " - Points: " << player.points;
        if (player.rank > 0) {
            std::cout << " - Rank: " << players.size() - player.rank+1;
        }
        std::cout << std::endl;
    }
}

void playGame(int numPlayers, int targetPoints) {
    std::vector<Player> players;

    // Initialize players
    for (int i = 1; i <= numPlayers; i++) {
        players.push_back(Player("Player-" + std::to_string(i)));
    }

    srand(time(nullptr));
    int currentPlayer = rand() % numPlayers;
    int remainingPlayers = numPlayers;

    // Game loop
    while (remainingPlayers > 0) {
        Player& player = players[currentPlayer];
        if(player.points>=targetPoints){
            currentPlayer = (currentPlayer + 1) % numPlayers;
            continue;
        }
        std::cout << "Player " << player.name << ", it's your turn. Press any character to roll the dice: ";
        char input;
        std::cin >> input;

        if (input) {
            rollDice(player);

            if (player.points >= targetPoints) {
                player.rank = remainingPlayers;
                remainingPlayers--;
                std::cout << "Player " << player.name << " completed the game and is assigned rank " << player.rank << "!" << std::endl;
            }

            printRankings(players);
            std::cout << std::endl;
        }
        

        currentPlayer = (currentPlayer + 1) % numPlayers;
    }
}

int main() {
    int numPlayers, targetPoints;

    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;

    std::cout << "Enter the target points: ";
    std::cin >> targetPoints;

    playGame(numPlayers, targetPoints);


    return 0;
}



