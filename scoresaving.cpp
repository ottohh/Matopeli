#include "scoresaving.h"


scoreSaving::scoreSaving()
{

    scoreFile.open(scoresTxt,ios_base::in);
    std::string line;
    if(!scoreFile.is_open())return;


    while(getline(scoreFile,line)){

        vector<string> parts = split(line);

        if(parts.size()!=2)continue;
        players[parts.at(0)]=stoi(parts.at(1));
    }

    scoreFile.close();
}

scoreSaving::~scoreSaving()
{

    scoreFile.open(scoresTxt,ios_base::out);
    scoreFile.clear();
    for(auto player:players){

        scoreFile<<player.first<<":"<<player.second<<endl;

    }

    scoreFile.close();
}

void scoreSaving::saveScore(int score, std::string player)
{
    if(score==0)return;

    if(players.find(player)==players.end()){
        players[player]=score;
    }else{
        if(players[player]<score)players[player]=score;

    }


}

void scoreSaving::clearScores(QListWidget *scoreBoard)
{
    scoreBoard->clear();
    players.clear();
}

void scoreSaving::printScores(QListWidget *scoreBoard)
{
    scoreBoard->clear();
    for(auto player : players){

        QString Item = QString(QString::fromStdString(player.first));
        Item.append(" best score:");
        Item.append(QString::number(player.second));
        scoreBoard->addItem(Item);

    }
}

vector<string> scoreSaving::split(string &line)
{
    unsigned long substr_start = 0;
    vector<string> parts;
    char separator = ':';
    string str;
    for(unsigned long i =0;i<line.size();i++){


        if(line.at(i)==separator){

            str = line.substr(substr_start,i-substr_start);
            substr_start=i+1;

            parts.push_back(str);
            continue;

        }

        if(i+1==line.size()){

            str = line.substr(substr_start,line.size()-substr_start);
         ;
            parts.push_back(str);
        }



    }
    return parts;
}

