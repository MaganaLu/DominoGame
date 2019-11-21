#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct player_data{
    vector<string> inHand;
    string name;
};

class CRandom{

public:
    CRandom(){}

// constructor
    ~CRandom(){}

// destructor
    int getRandomPublic(int rangeLow, int rangeHigh){
        int myRand_scaled;
        myRand_scaled=getRandomPrivate(rangeLow, rangeHigh);
        return myRand_scaled;
    }

private:// uniform distribution between rangeLow and rangeHigh
    int getRandomPrivate(int rangeLow, int rangeHigh) {
        double myRand = rand()/(1.0 + RAND_MAX);
        int range = rangeHigh - rangeLow + 1;
        int myRand_scaled = (myRand * range) + rangeLow;
        return myRand_scaled;
    }
protected:// uniform distribution between rangeLow and rangeHigh
    int getRandomProtected(int rangeLow, int rangeHigh) {
        double myRand = rand()/(1.0 + RAND_MAX);
        int range = rangeHigh - rangeLow + 1;
        int myRand_scaled = (myRand * range) + rangeLow;
        return myRand_scaled;
    }
};

class CDominoes{
public:
    vector<string> allDominoes{ "0,0", "0,1","0,2", "0,3", "0,4", "0,5", "0,6",
                                "1,1", "1,2", "1,3", "1,4","1,5", "1,6",
                                "2,2", "2,3", "2,4", "2,5", "2,6",
                                "3,3", "3,4", "3,5", "3,6",
                                "4,4", "4,5", "4,6",
                                "5,5", "5,6",
                                "6,6"};

    void divideDominoes(player_data *player){

        vector<string> listPlayer1;
        vector<string> listPlayer2;
        CRandom random;


        for(int i = 0; i < 20; i++){
            int index = random.getRandomPublic(0,allDominoes.size());
            string domino = allDominoes.at(index);

            allDominoes.erase(allDominoes.begin() + index);

            if(i % 2 == 0){
                listPlayer1.push_back(domino);
            }else{
                listPlayer2.push_back(domino);
            }
        }
        player[0].inHand = listPlayer1;
        player[1].inHand = listPlayer2;
    }
    string getStarter(){
        CRandom random;
        int index = random.getRandomPublic(0,6);
        string domino = allDominoes.at(index);

        allDominoes.erase(allDominoes.begin() + index);

        return domino;
    }

};

class CPlayer{
public:
    player_data *player = new player_data[2];
    void playerStuff() {
        CDominoes cdominoes;
        CRandom random;

        string playerName;
        string dominoChain;
        string starterTile;
        string answer;
        bool finished = false;

        //player_data *player = new player_data[2];

        for (int i = 0; i < 2; i++) {
            cout << "Enter name for player: ";
            cin >> playerName;
            player[i].name = playerName;
        }

    }


};


class CTable{

public:
    void playingtable(){
        CPlayer cp;
        cp.playerStuff();
        CDominoes cdominoes;
        CRandom random;

        string dominoChain;
        string starterTile;
        string answer;
        bool finished = false;

        cdominoes.divideDominoes(cp.player);

        dominoChain = cdominoes.getStarter();
        while (!finished) {
            for (int i = 0; i < 2; i++) {
                int counter = 0;
                char firstCharInChain = dominoChain.at(0);
                char lastCharInChain = dominoChain.back();

                cout << "Domino chain: " << dominoChain << endl;

                cout << "player: " << cp.player[i].name<< endl;

                for (const auto& printthing : cp.player[i].inHand) {
                    // process i
                    cout << "[" << printthing << "]"; // this will print all the contents of *features*
                }
                cout << endl;

                vector<string> inHandCopy;

                for(string answer : cp.player[i].inHand){

                    inHandCopy = cp.player[i].inHand;


                    if (answer.at(0) == firstCharInChain || answer.at(0) == lastCharInChain) {
                        if (answer.at(0) == lastCharInChain) {
                            //add it to the domino chain
                            dominoChain.append(answer);
                            //delete it from the players in hand vector
                            inHandCopy.erase(remove(inHandCopy.begin(), inHandCopy.end(), answer),
                                             inHandCopy.end());

                        }
                        else if (answer.at(0) == firstCharInChain) {
                            reverse(begin(answer), end(answer));
                            //add it to the domino chain at the beginning
                            dominoChain.insert(0, answer);
                            //delete it from the players inHand
                            reverse(begin(answer), end(answer));
                            inHandCopy.erase(remove(inHandCopy.begin(), inHandCopy.end(), answer),
                                             inHandCopy.end());

                        }


                    }

                    else if (answer.back() == firstCharInChain || answer.back() == lastCharInChain) {
                        if (answer.back() == firstCharInChain) {

                            //append tot he front of the chain
                            dominoChain.insert(0, answer);

                            // delete from the player InHand
                            inHandCopy.erase(remove(inHandCopy.begin(),inHandCopy.end(), answer),
                                             inHandCopy.end());

                        }
                        if (answer.back() == lastCharInChain) {
                            //reverse();
                            reverse(begin(answer), end(answer));
                            dominoChain.append(answer);

                            reverse(begin(answer), end(answer));
                            //delete it from player inHand
                            inHandCopy.erase(remove(inHandCopy.begin(), inHandCopy.end(), answer),
                                             inHandCopy.end());

                        }

                    }else{

                        counter++;
                        if(counter == inHandCopy.size()){

                            if(cdominoes.allDominoes.size() == 0){
                                cout << "Player: " << cp.player[i].name << " lost!!!";
                                finished = true;
                            }

                            CRandom random;
                            int index = random.getRandomPublic(0,cdominoes.allDominoes.size());
                            string domino = cdominoes.allDominoes.at(index);

                            inHandCopy.insert(inHandCopy.begin(), domino);
                            cdominoes.allDominoes.erase(cdominoes.allDominoes.begin() + index);
                        }

                    }

                    if (cp.player[1].inHand.size() == 0 || cp.player[0].inHand.size() == 0){
                            finished = true;
                            cout <<" ---GAME OVER--- " << endl;

                            if(cp.player[0].inHand.size() == 0){
                                cout<<cp.player[0].name << " Won!!!" << endl;
                                cout << "The domino chain is: "<<dominoChain ;
                                break;
                            }
                        if(cp.player[1].inHand.size() == 0){
                            cout<<cp.player[1].name << " Won!!!"<< endl;
                            cout << "The domino chain is: "<<dominoChain ;
                            break;
                        }
                    }
                    cp.player[i].inHand = inHandCopy;

                    if(answer.at(0) == firstCharInChain || answer.at(0) == lastCharInChain || answer.back() == firstCharInChain || answer.back() == lastCharInChain){
                        break;
                    }
                }
            }
        }
    }
};

int main() {

    CTable game;
    game.playingtable();
    return 0;
}