#include <SFML/Graphics.hpp>
#include <iostream>

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
        Sprite sprites[12];
        Texture textures[12];
        bool canjump;
        bool isAlive;

        Player(int debX,int debY);
        void loadSprite();

        void newStartPos(int x, int y);

        void setMovementY(float y);
        void setMovementX(float x);

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
};