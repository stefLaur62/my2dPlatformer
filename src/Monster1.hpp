#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;


class Monster1{
    public:
        float pos[2][2];


        int debX;
        int debY;

        int moveposX[2];

        int moveSpeed;
        int actualSprite;
        int spriteDec;// sprite number in spritesheet

        int lastDirec;
        int animationRate;
        int animActualRate;

        Sprite sprites[3];
        Texture textures[3];
        bool isAlive;
        
        //ATTACK
        bool canAttack;
        bool dealDamage;

        Monster1(int debX,int debY,int finX);
        void loadSprite();


        void setMovementX(float x);
        void setDirection(int direc);

        void animationRun(int direc, int fps);

        void move(float dt, vector<vector<int>> &tabMap);
        void moveX(float val);

        bool attack(int fps, float playerPos[]);
        void animationAttack(int fps);

};
