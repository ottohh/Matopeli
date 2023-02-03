/*
 * Score Saving systems
 * Opens file called scores.txt and and reads scores to players map
 * Only saves the best scores of each player
 * destructor saves all the scores back to scores.txt
 * Format   playerName:score   otto:10
 *
 *
 */



#ifndef SCORESAVING_H
#define SCORESAVING_H
#include "fstream"
#include "string.h"
#include "vector"
#include "map"
#include "QListWidget"
#include "QString"

using namespace std;
class scoreSaving
{
public:

    scoreSaving();
    ~scoreSaving();


    /* Saves score of player, the highest score of certain player is saved*/
    void saveScore(int score,std::string player);

    void clearScores(QListWidget *scoreBoard);

    //prints scores to scoreboard ListWidget
    void printScores(QListWidget *scoreBoard);
private:

    std::fstream scoreFile;

    //Contains all players and scores
    map<string,int> players;
    std::string scoresTxt = "scores.txt";

    vector<string> split(string &line);

};

#endif // SCORESAVING_H
