#include <SFML/Graphics.hpp>
#include <iostream>
#include "Monster1.hpp"
#include <cmath>
using namespace std;
using namespace sf;


class Player{
    public:
        float pos[2][2];
        int debX;
        int debY;
        int playerSpeed;
        float accelerationY;
        int actualSprite;
        int lastDirec;
        int animationRate;
        int animActualRate;
        int hp;

        Sprite sprites[16];
        Texture textures[16];
        bool canjump;
        bool isAlive;
        
        //ATTACK
        bool canAttack;

        Player(int debX,int debY);
        void loadSprite();

        void newStartPos(int x, int y);

        void setMovementY(float y);
        void setMovementX(float x);
        void setDirection(int direc);

        bool canLeft(vector<vector<int>> &tabMap, float val);
        bool canRight(vector<vector<int>> &tabMap, float val);
        bool canFall(vector<vector<int>> &tabMap, float val);
        bool canJump(vector<vector<int>> &tabMap, float val);

        void animationRun(int direc, int fps);
        void animationJump(int fps);
        void animationFall();
        void animationIdle(int fps);

        void move(float dt, vector<vector<int>> &tabMap, View &view);
        void moveX(float val);
        void moveDown(float val);
        void jump(float val);

        void attack(int fps, Monster1 &monster);
        void animationAttack(int fps);

        void loseLife();
        
};
