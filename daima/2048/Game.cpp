#include"Game.hpp"
#include <cstdlib>
#include <ctime>

Game::Game(int s):board(s,vector<int>(s,0)),score(0),gameOver(false),size(s),step(0)
{
    generateRandomTile();
    generateRandomTile();
}

void Game::generateRandomTile()
{
    srand(time(0));
    vector<pair<int,int>> emptyCells;
    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            if(board[i][j] == 0)
                emptyCells.emplace_back(i, j);
    if(!emptyCells.empty())
    {
        int randomIndex = rand() % emptyCells.size();
        int value = (rand() % 2 + 1) * 2; // 2 or 4
        board[emptyCells[randomIndex].first][emptyCells[randomIndex].second] = value;
        return;
    }
    gameOver = true;
}

bool Game::isGameOver()
{
    return gameOver;
}

void Game::rotateBoard(int t)
{
    vector<vector<int>> tempBoard(size, vector<int>(size, 0));
    for(;t>0; --t)
    {
        tempBoard = board;
        for(int i=0; i<size; ++i)
            for(int j=0; j<size; ++j)
                board[i][j] = tempBoard[size-1-j][i];
    }
}

void Game::move(char dir)
{
    int rotateTimes = 0;
    switch (dir)
    {
    case 'w':
    case 'W':
        rotateTimes = 3;
        break;
    case 's':
    case 'S':
        rotateTimes = 1;
        break;
    case 'a':
    case 'A':
        rotateTimes = 0;
        break;
    case 'd':
    case 'D':
        rotateTimes = 2;
        break;
    default:
        cout << "Invalid move!" << endl;
        return;
    }
    step++;
    previousBoard = board;
    previousScore = score;
    rotateBoard(rotateTimes);
    
    for(auto &r:board)
    {
        vector<int> temp;
        for(auto &c:r)
            if(c != 0)
                temp.push_back(c);
        for(int i=1; i<temp.size();++i)
        {
            if(temp[i] == temp[i-1])
            {
                temp[i] *= 2;
                score += temp[i];
                temp.erase(temp.begin() + i-1);
            }
        }
            
        for(int i=1; i<temp.size();++i)
        {
            if(temp[i] == temp[i-1])
            {
                temp[i] *= 2;
                score += temp[i];
                temp.erase(temp.begin() + i-1);
            }
        }
        r=temp;
        while(r.size() < size)
            r.push_back(0);
    }
    rotateBoard((4-rotateTimes)%4);
    generateRandomTile();
}
//
void Game::display()
{
    for(auto &r:board)
    {
        for(auto &c:r)
            cout << c << " ";
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void Game::undo()
{
    if(step == 0)
    {
        cout << "No previous step to undo!" << endl;
        return;
    }
    board = previousBoard;
    score = previousScore;
    step--;
    gameOver = false;
}

