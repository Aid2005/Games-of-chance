#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class Player {//Player class
public:
    string name;
    int wins = 0, losses = 0;
    float money = 500, bet;

    Player() {//Constructor for casino login
        cout << "Login:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nEnter your name: ";
        cin >> name;
        cout << "Your starting money is: " << money << " KM\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    void Statistics() {//Function that prints statistics at the end
        cout << "Have a nice day!\nStatistics:\n Wins: " << wins
            << "\n Losses: " << losses
            << "\n Your remaining money is: " << money << " KM" << endl;
    }

    float Bankrupt() {//Returns player's money
        return money;
    }
};

class Game {//Game class
public:
    Player player;
    int guess, choice;

    void Statistics() {
        player.Statistics();
    }

    float Bankrupt() {
        return player.Bankrupt();
    }

    void DiceGame() {//Dice game
        cout << "How much money do you want to bet: ";
        cin >> player.bet;
        cout << "Choose a number from 1-6: ";
        cin >> guess;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        player.money = player.money - player.bet;
        int dice = rand() % 6 + 1;

        cout << "The dice rolled: " << dice << endl;

        if (dice != guess) {
            cout << "You lost! Remaining money: " << player.money << " KM" << endl;
            player.losses++;
        }
        else {
            player.money = player.money + (player.bet * 3);
            cout << "You won! Your money is now: " << player.money << " KM" << endl;
            player.wins++;
        }
    }

    void Roulette() {//Roulette simulation
        cout << "How much money do you want to bet: ";
        cin >> player.bet;
        player.money = player.money - player.bet;

        cout << "Choose an option:\n[1] Black\n[2] Red\n[3] Green\n[4] Pick a number\nChoice: ";
        cin >> choice;

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        int roll = rand() % 37;

        if (choice == 1 && roll % 2 == 0) {
            cout << "Roulette landed on black " << roll << endl;
            player.wins++;
            player.money += player.bet * 2;
        }
        else if (choice == 2 && roll % 2 != 0) {
            cout << "Roulette landed on red " << roll << endl;
            player.wins++;
            player.money += player.bet * 2;
        }
        else if (choice == 3 && roll == 0) {
            cout << "Roulette landed on green (0)" << endl;
            player.wins++;
            player.money += player.bet * 14;
        }
        else if (choice == 4) {
            int number;
            cout << "Enter the number you want to bet on: ";
            cin >> number;

            if (number == roll) {
                cout << "You guessed the correct number!" << endl;
                player.wins++;
                player.money += player.bet * 14;
            }
            else {
                cout << "Wrong number!" << endl;
                player.losses++;
            }

            cout << "Your money is: " << player.money << " KM" << endl;
        }
        else {
            cout << "You lost!" << endl;

            if (roll % 2 == 0)
                cout << "Roulette landed on black " << roll << endl;
            else
                cout << "Roulette landed on red " << roll << endl;

            player.losses++;
            cout << "Your money is: " << player.money << " KM" << endl;
        }
    }

    void SlotMachine() {//Slot machine simulation
        int one = 0, two = 0, three = 0;

        cout << "How much money do you want to bet: ";
        cin >> player.bet;

        cout << "\n#######\n#";
        player.money -= player.bet;

        for (int i = 0; i < 3; i++) {
            int x = rand() % 3 + 1;
            cout << x << "#";

            if (x == 1) one++;
            else if (x == 2) two++;
            else three++;
        }

        cout << "\n#######" << endl;

        if (one == 3 || two == 3 || three == 3) {
            player.money += player.bet * 5;
            cout << "You won! Your money is: " << player.money << " KM" << endl;
            player.wins++;
        }
        else {
            cout << "You lost! Your money is: " << player.money << " KM" << endl;
            player.losses++;
        }
    }

    void BlackJack() {//Blackjack simulation
        int card, playerSum = 0, dealerSum = 0, draw;

        cout << "How much money do you want to bet: ";
        cin >> player.bet;
        player.money -= player.bet;

        cout << "RULES: Enter 0 if you don't want to draw another card.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        do {
            card = rand() % 13 + 1;
            if (card > 10) card = 10;

            playerSum += card;

            cout << "Your current total is " << playerSum << ". Draw another card? ";
            cin >> draw;

            if (playerSum > 21) {
                cout << "You busted! Your money is: " << player.money << " KM" << endl;
                player.losses++;
                break;
            }

        } while (draw != 0);

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        do {
            card = rand() % 13 + 1;
            if (card > 10) card = 10;
            dealerSum += card;
        } while (dealerSum <= 16);

        if (dealerSum > 21 && playerSum <= 21) {
            cout << "You won! Dealer had " << dealerSum << endl;
            player.money += player.bet * 2;
            player.wins++;
        }
        else if (playerSum > dealerSum && playerSum <= 21) {
            cout << "You won! Dealer had " << dealerSum << endl;
            player.money += player.bet * 2;
            player.wins++;
        }
        else if (playerSum < dealerSum && playerSum <= 21) {
            cout << "You lost! Dealer had " << dealerSum << endl;
            player.losses++;
        }
        else if (playerSum == dealerSum) {
            cout << "Draw!" << endl;
            player.money += player.bet;
        }
        else if (playerSum > 21 && dealerSum > 21) {
            cout << "Draw! Dealer had " << dealerSum << endl;
            player.money += player.bet;
        }

        cout << "Your money is: " << player.money << " KM" << endl;
    }
};

int main() {
    int menu;
    srand(time(NULL));
    Game obj;

    cout << "Welcome to the casino \"AT EGON'S\"" << endl;

    do {

        if (obj.Bankrupt() == 0) {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nYour balance is 0 KM. Please leave the casino." << endl;
            break;
        }

        else if (obj.Bankrupt() < 0) {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nYou are going to jail!" << endl;
            break;
        }

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nMENU:\n"
            << "[1] Dice Game\n"
            << "[2] Roulette\n"
            << "[3] Slot Machine\n"
            << "[4] Blackjack\n"
            << "[5] End\nChoice: ";

        cin >> menu;

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        switch (menu) {
        case 1:
            obj.DiceGame();
            break;
        case 2:
            obj.Roulette();
            break;
        case 3:
            obj.SlotMachine();
            break;
        case 4:
            obj.BlackJack();
            break;
        case 5:
            obj.Statistics();
            break;
        default:
            cout << "Invalid input!" << endl;
        }

    } while (menu != 5);
}