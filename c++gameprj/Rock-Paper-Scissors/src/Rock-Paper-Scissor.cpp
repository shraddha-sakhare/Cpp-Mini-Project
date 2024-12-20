#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

class Game {
public:
    virtual void playRound() = 0;
    virtual ~Game() = default;
};

class Player {
private:
    string name;
    int score;
public:
    Player(string playerName) : name(playerName), score(0) {}

    void incrementScore() { score++; }
    string getName() const { return name; }
    int getScore() const { return score; }
};

class RockPaperScissorsGame : public Game {
private:
    Player& player;
    string computerChoice;
    string playerChoice;

    string getChoiceName(int choice) {
        switch (choice) {
            case 1: return "Rock";
            case 2: return "Paper";
            case 3: return "Scissor";
            default: return "";
        }
    }

    int determineWinner(const string& playerChoice, const string& computerChoice) {
        if (playerChoice == computerChoice) return -1;  // Draw
        if ((playerChoice == "Rock" && computerChoice == "Scissor") ||
            (playerChoice == "Paper" && computerChoice == "Rock") ||
            (playerChoice == "Scissor" && computerChoice == "Paper")) return 1;  // Player wins
        return 0;  // Computer wins
    }

public:
    RockPaperScissorsGame(Player& p) : player(p) { srand(time(0)); }

    void playRound() override {
        int computerInput = rand() % 3 + 1;
        computerChoice = getChoiceName(computerInput);

        int input;
        cout << "1) Rock\n2) Paper\n3) Scissor\nEnter your choice: ";
        while (true) {
            cin >> input;
            if (cin.fail() || input < 1 || input > 3) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 3: ";
            } else {
                break;
            }
        }
        playerChoice = getChoiceName(input);

        cout << "You chose: " << playerChoice << endl;
        cout << "Computer chose: " << computerChoice << endl;

        int result = determineWinner(playerChoice, computerChoice);
        if (result == 1) {
            cout << "You win this round!\n";
            player.incrementScore();
        } else if (result == 0) {
            cout << "Computer wins this round!\n";
        } else {
            cout << "It's a draw!\n";
        }
    }
};

void displayRules() {
    cout << "************\n";
    cout << "Welcome to the Rock-Paper-Scissors Game!\n";
    cout << "Rules:\n";
    cout << "- Rock crushes Scissors\n";
    cout << "- Scissors cuts Paper\n";
    cout << "- Paper covers Rock\n";
    cout << "************\n\n";
}

int main() {
    string playerName;
    cout << "Enter your name: ";
    getline(cin, playerName);
    Player player(playerName);

    char playAgain;
    do {
        system("cls");  // Windows-specific, use a portable approach if needed
        displayRules();
        RockPaperScissorsGame game(player);
        game.playRound();

        cout << "Would you like to play again? (y/n): ";
        cin >> playAgain;
        cout << endl;
    } while (playAgain != 'n');

    cout << "\nThanks for playing, " << player.getName() << "!\n";
    cout << "Your final score is: " << player.getScore() << "\n";

    return 0;
}



