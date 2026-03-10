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

class Game : public Player {//Game class that inherits Player
public:
    int guess, choice;

    void DiceGame() {//Dice game
        cout << "How much money do you want to bet: ";
        cin >> bet;
        cout << "Choose a number from 1-6: ";
        cin >> guess;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        money = money - bet;
        int dice = rand() % 6 + 1;

        cout << "The dice rolled: " << dice << endl;

        if (dice != guess) {
            cout << "You lost! Remaining money: " << money << " KM" << endl;
            losses++;
        }
        else {
            money = money + (bet * 3);
            cout << "You won! Your money is now: " << money << " KM" << endl;
            wins++;
        }
    }

    void Roulette() {//Roulette simulation
        cout << "How much money do you want to bet: ";
        cin >> bet;
        money = money - bet;

        cout << "Choose an option:\n[1] Black\n[2] Red\n[3] Green\n[4] Pick a number\nChoice: ";
        cin >> choice;

        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        int roll = rand() % 37;

        if (choice == 1 && roll % 2 == 0) {
            cout << "Roulette landed on black " << roll << endl;
            wins++;
            money += bet * 2;
        }
        else if (choice == 2 && roll % 2 != 0) {
            cout << "Roulette landed on red " << roll << endl;
            wins++;
            money += bet * 2;
        }
        else if (choice == 3 && roll == 0) {
            cout << "Roulette landed on green (0)" << endl;
            wins++;
            money += bet * 14;
        }
        else if (choice == 4) {
            int number;
            cout << "Enter the number you want to bet on: ";
            cin >> number;

            if (number == roll) {
                cout << "You guessed the correct number!" << endl;
                wins++;
                money += bet * 14;
            }
            else {
                cout << "Wrong number!" << endl;
                losses++;
            }

            cout << "Your money is: " << money << " KM" << endl;
        }
        else {
            cout << "You lost!" << endl;

            if (roll % 2 == 0)
                cout << "Roulette landed on black " << roll << endl;
            else
                cout << "Roulette landed on red " << roll << endl;

            losses++;
            cout << "Your money is: " << money << " KM" << endl;
        }
    }

    void SlotMachine() {//Slot machine simulation
        int one = 0, two = 0, three = 0;

        cout << "How much money do you want to bet: ";
        cin >> bet;

        cout << "\n#######\n#";
        money -= bet;

        for (int i = 0; i < 3; i++) {
            int x = rand() % 3 + 1;
            cout << x << "#";

            if (x == 1) one++;
            else if (x == 2) two++;
            else three++;
        }

        cout << "\n#######" << endl;

        if (one == 3 || two == 3 || three == 3) {
            money += bet * 5;
            cout << "You won! Your money is: " << money << " KM" << endl;
            wins++;
        }
        else {
            cout << "You lost! Your money is: " << money << " KM" << endl;
            losses++;
        }
    }

    void BlackJack() {//Blackjack simulation
        int card, playerSum = 0, dealerSum = 0, draw;

        cout << "How much money do you want to bet: ";
        cin >> bet;
        money -= bet;

        cout << "RULES: Enter 0 if you don't want to draw another card.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

        do {
            card = rand() % 13 + 1;
            if (card > 10) card = 10;

            playerSum += card;

            cout << "Your current total is " << playerSum << ". Draw another card? ";
            cin >> draw;

            if (playerSum > 21) {
                cout << "You busted! Your money is: " << money << " KM" << endl;
                losses++;
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
            money += bet * 2;
            wins++;
        }
        else if (playerSum > dealerSum && playerSum <= 21) {
            cout << "You won! Dealer had " << dealerSum << endl;
            money += bet * 2;
            wins++;
        }
        else if (playerSum < dealerSum && playerSum <= 21) {
            cout << "You lost! Dealer had " << dealerSum << endl;
            losses++;
        }
        else if (playerSum == dealerSum) {
            cout << "Draw!" << endl;
            money += bet;
        }
        else if (playerSum > 21 && dealerSum > 21) {
            cout << "Draw! Dealer had " << dealerSum << endl;
            money += bet;
        }

        cout << "Your money is: " << money << " KM" << endl;
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