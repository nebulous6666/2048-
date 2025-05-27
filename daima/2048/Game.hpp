#ifndef GAME_HPP
#define GAME_HPP

#include<vector>
#include<string>
#include<iostream>
using namespace std;
class Game
{
public:
    Game(int s);                  // 构造函数
    void generateRandomTile();
    void move(char dir);  // 移动棋子
    void rotateBoard(int t);         // 旋转棋盘简化移动操作
    void display();              // 打印棋盘
    bool isGameOver();         // 判断游戏是否结束
    void saveGame(const string &filename); // 保存游戏
    void loadGame(const string &filename); // 读取游戏
    void undo();              // 撤销上一步操作
private:
    int size;
    vector<vector<int>> board;        // 棋盘对象
    vector<vector<int>> previousBoard; // 上一步棋盘
    unsigned int score,previousScore,step;               // 分数
    bool gameOver;           // 游戏是否结束
};

#endif