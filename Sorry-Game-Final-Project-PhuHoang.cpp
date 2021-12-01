/* Program name: Sorry-Game-Final-Project-PhuHoang.cpp
*  Author: Phu Hoang
*  Date last updated: 5/12/2021
* Purpose: Sorry Game
*/


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

const int Spaces = 50;
const int maxPlayer = 4;

enum DICE { NONE = 0, ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, MAX = 6, MIN = 1 };

class FileIO {
    string winner;
public:
    void setWinner(string winner) {
        this->winner = winner;
    }
    string getWinner() {
        return winner;
    }
    virtual ostream& write(ostream& os, string winner) {
        os << winner << endl;
        return os;
    }
    virtual istream& read(istream& is) = 0;

    friend ostream& operator<< (ostream& os, FileIO& io) {
        return io.write(os, io.winner);
    }
};

class Game : public FileIO {
    // values
    const int Clear = -1;
    const int Begin = -1;
    const int Finish = 1;
    const int Continue = 0;
    vector<string> halloffamers;
public:

    void HallOfFame() {
        ifstream is;
        is.open("HallOfFame.txt");
        if (is.is_open()) {
            read(is);
            is.close();
        }
        if (halloffamers.size() == 0) {
            cout << "Become the first Hall Of Famer, What is your name: ";
        }
        else {
            cout << "HALL OF FAME" << endl;
            cout << "************" << endl;
            for (int i = halloffamers.size() - 1; i >= 0; i--) {
                cout << halloffamers[i] << endl;
            }
            cout << "\nBecome a member of the Hall Of Fame, What is your name: ";
        }
        string name;
        getline(cin, name);
        this->setWinner(name);

        ofstream os;
        os.open("HallOfFame.txt", ofstream::out | ofstream::app);
        os << *this;
        os.close();

    }

    istream& read(istream& is) {
        string line;
        while (getline(is, line)) {
            halloffamers.push_back(line);
        }
        return is;
    }
    void play() {

        int board[Spaces];
        int positions[maxPlayer];
        int playerNum = getUserNum();
        int round = 1;
        int result = Continue;

        // initial board
        for (int i = 0; i < Spaces; i++) {
            board[i] = Clear;
        }

        printBoard(board);

        // display player move
        for (int i = 0; i < maxPlayer; i++) {
            positions[i] = Begin;
        }

        while (result == Continue) {
            cout << "Round #" << round << "\n";
            for (int i = 0;
                i < playerNum && result == Continue
                ; i++) {
                result = playerMove(board, positions, i);
                printBoard(board);
                cout << "\n";
            }
            round++;
        }
        for (int i = 0; i < maxPlayer; i++) {
            if (positions[i] == Spaces - 1) {
                cout << "Player P" << i + 1 << " wins\n";
                HallOfFame();
                break;
            }
        }
    }
    // print the board with player move in 50 spaces
    void printBoard(int board[]) {

        system("cls");

        cout << "**********Sorry Game***********" << endl;

        for (int i = 0; i < Spaces; i++) {


            cout << "--";
        }
        cout << "-\n";


        for (int i = 0; i < Spaces; i++) {
            cout << "|";
            if (board[i] < 0) {

                cout << " ";
            }
            else {

                cout << board[i] + 1;
            }
        }
        cout << "|\n";

        for (int i = 0; i < Spaces; i++) {

            cout << "--";
        }
        cout << "-\n";

    }
    // make the roll to get dice
    DICE Roll(int order) {
        int num = abs(rand() % DICE::MAX) + DICE::MIN;
        char roll;
        cout << "\t\tPress any character and enter to roll dice #" << order;
        cin.clear();
        cin.ignore(100, '\n');
        cin >> roll;
        cout << "\t\tRoll dice [" << order << "]: " << num << "\n";
        DICE res;
        switch (num) {
        case 1:
            res = DICE::ONE;
            break;
        case 2:
            res = DICE::TWO;
            break;
        case 3:
            res = DICE::THREE;
            break;
        case 4:
            res = DICE::FOUR;
            break;
        case 5:
            res = DICE::FIVE;
            break;
        case 6:
            res = DICE::SIX;
            break;
        default:
            res = DICE::NONE;
            break;
        }


        return res;
    }
    int getUserNum() {

        int player;
        cout << "how many players?: ";
        cin >> player;


        while (player > 4 || player < 2)
        {
            if (player < 2)
            {
                cout << "we need more than 2 people to play. please re-enter players: ";
                cin >> player;
            }
            else if (player > 4)
            {
                cout << "too many people. please re-enter players: ";
                cin >> player;
            }

        }
        return player;
    }

    int playerMove(int board[], int positions[], int player) {

        // display where the player at
        cout << "Player P" << player + 1 << " at ";
        if (positions[player] == Begin) {
            cout << "the beginning\n";
        }
        else {
            cout << positions[player] + 1 << "\n";
        }

        // must roll a double to move
        if (positions[player] == Begin) {
            int dice1, dice2;

            dice1 = Roll(1);
            dice2 = Roll(2);

            cout << "\tAt Begining point\n";
            cout << "\t\tRoll 2 dice and get " << dice1 << " and " << dice2 << "\n";
            if (dice1 != dice2) {
                cout << "\t\tPlayer must roll a double to Begin\n";
            }
            else {
                int dice = dice1 + dice2;
                move(positions, player, dice, true);
            }

        }
        // roll two double, player get another roll
        else {
            int dice1, dice2;
            int dice;

            dice1 = Roll(1);
            dice2 = Roll(2);
            dice = dice1 + dice2;

            if (dice1 == dice2) {
                cout << "\t\tPlayer P" << player + 1 << " rolls a double. "
                    << "The player will get another roll\n";


                dice1 = Roll(1);
                dice2 = Roll(2);

                if (dice1 == dice2) {
                    cout << "\t\tPlayer P" << player + 1
                        << " rolls two double. The player will Begin over\n";
                    positions[player] = Begin;
                    return 0;
                }
                dice = dice1 + dice2;
            }

            move(positions, player, dice, false);
        }
        // update the board
        for (int i = 0; i < Spaces; i++) {
            board[i] = Clear;// clean all board
        }

        for (int i = 0; i < maxPlayer; i++) {
            if (positions[i] > Begin) {
                board[positions[i]] = i;// insert player into the board
            }
        }
        // check for quit the game
        if (positions[player] == Spaces - 1) {
            return Finish;
        }
        return Continue;
    }

    void move(int positions[], int player, int dice, bool atBegin) {
        int position;

        switch (dice) {
            // normal moves 
        case 2:
        case 3:
        case 5:
        case 6:
        case 8:
        case 9:
        case 10:
            cout << "\t\tMove " << dice << " spaces \n";
            position = positions[player] + dice;
            break;


        case 4: // move back one place
            if (atBegin) {
                cout << "\t\tMove " << 1 << " spaces \n";
                position = 0;
            }
            else {
                position = positions[player] - 1;
            }
            break;
        case 7: // switch to the first player
        {

            int leader = firstPlayer(positions);
            if (leader == player) {
                cout << "\t\tPlayer P" << player + 1 << " is in lead,"
                    << " no move will be taken\n";
                position = positions[player];
            }
            else {
                position = positions[leader];
                positions[leader] = positions[player];
                cout << "\t\tSwap position with P" << leader + 1 << "\n";
            }
            break;
        }
        case 11: // switch with the last player
        {

            int last = lastPlayer(positions);
            if (positions[last] == positions[player]) {
                position = positions[player];
                cout << "\t\tPlayer P" << player + 1 << " is last,"
                    << " no move will be taken\n";
            }
            else {
                position = positions[last];
                positions[last] = positions[player];
                cout << "\t\tSwap position with P" << last + 1 << "\n";
            }
            break;
        }
        case 12: // go back to the begin

            if (atBegin) {
                cout << "\t\tMove " << 1 << " spaces \n";
                position = 0;
            }
            else {
                position = Begin;
            }
        }
        // display 50 spaces to find the winner 
        if (position >= Spaces - 1) {
            if (position == Spaces - 1
                || positions[player] == Spaces - 2) {
                positions[player] = Spaces - 1;
                cout << "\t\tMove to winning space\n";
            }
            else {
                cout << "\t\tPlayer must roll an EXACT number "
                    << "to enter the winning space. "
                    << "Standing at " << positions[player] + 1 << "\n";
            }
        }
        else if (position == Begin) {
            cout << "\t\tMove back to  the beginning \n";
            positions[player] = position;
        }
        else if (position != positions[player]) {
            cout << "\t\tMove to " << position + 1 << "\n";
            positions[player] = position;

            // player land on another
            for (int i = 0; i < maxPlayer; i++)
            {
                if (i != player && positions[i] > Begin && positions[i] == position)
                {
                    cout << "\t\tP" << i + 1 << "'s land is captured, Return to the "
                        << " beginning\n";
                    positions[i] = Begin;
                    break;
                }
            }

        }
    }

    // find the last player
    int lastPlayer(int positions[]) {
        int last = firstPlayer(positions);
        for (int i = 0; i < maxPlayer; i++) {
            if (positions[i] < positions[last]) {
                last = i;
            }
        }
        return last;
    }
    // find the first player
    int firstPlayer(int positions[]) {
        int leading = Begin;

        int leader;
        for (int i = 0; i < maxPlayer; i++) {
            if (leading < positions[i]) {
                leading = positions[i];
                leader = i;
            }
        }
        return leader;
    }
};


int main() {


    srand(time(0));
    int option;
    Game game;
    do {
        game.play();
        cout << "press 1 to play again or other to quit the game!";
        cin >> option;
    } while (option == 1);


    return 0;
}



