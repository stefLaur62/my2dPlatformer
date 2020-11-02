#include "Monster1.hpp"

Monster1::Monster1(int debX,int debY,int finX):debX(debX),debY(debY),animationRate(30),animActualRate(30){
    //pos 0 = coord
    //pos 1 = movement
    pos[0][0]=debX;
    pos[0][1]=debY;
    pos[1][0]=1;
    pos[1][1]=0;

    moveposX[0]=debX;
    moveposX[1]=finX;

    isAlive=true;
    canAttack=true;
    actualSprite=0;
    loadSprite();
    moveSpeed=10;
}

void Monster1::loadSprite(){
    if (!textures[0].loadFromFile("./Ressources/Monster/skeleton/Skeleton Idle.png") 
    || !textures[1].loadFromFile("./Ressources/Monster/skeleton/Skeleton Walk.png")
    || !textures[2].loadFromFile("./Ressources/Monster/skeleton/Skeleton Attack.png")
    ){
        cout << "Couldn't load Skeleton texture" << endl;
        exit(1);
    }
    sprites[0].setTexture(textures[0]);
    sprites[1].setTexture(textures[1]);
    sprites[2].setTexture(textures[2]);

    sprites[0].setTextureRect(IntRect(0, 0, 24, 32));
    sprites[1].setTextureRect(IntRect(0, 0, 22, 33));
    sprites[2].setTextureRect(IntRect(0, 0, 46, 36));

    sprites[actualSprite].setPosition(Vector2f(pos[0][0], pos[0][1]));
    sprites[actualSprite].setScale(0.8f, 0.8f);
    sprites[0].setOrigin(sprites[0].getGlobalBounds().height/2, sprites[0].getGlobalBounds().width/2);
    sprites[1].setOrigin(sprites[1].getGlobalBounds().height/2, sprites[1].getGlobalBounds().width/2);
    sprites[2].setOrigin(sprites[2].getGlobalBounds().height/2, sprites[2].getGlobalBounds().width/2);
}



void Monster1::setMovementX(float x){
    if(pos[1][0]==-1){
        sprites[actualSprite].setScale(-0.8f,0.8f);;
    } else if(pos[1][0]==1){
        sprites[actualSprite].setScale(0.8f, 0.8f);
    }
    pos[1][0]=x;

}

void Monster1::setDirection(int direction){
    lastDirec = direction;
}



void Monster1::animationRun(int direc,int fps){
    animationRate=fps>>2;
    lastDirec=direc;
    if(!(pos[1][1]>0)){
        int prevAnim = actualSprite;
        if(actualSprite!=1){
            actualSprite = 1;
            spriteDec = 0;
        }
        animActualRate--;
        if(!animActualRate){
            animActualRate = animationRate;
            if(spriteDec<12)
                spriteDec++;
            else
                spriteDec=0;
        }
        if(prevAnim==2)
            sprites[actualSprite].setPosition(sprites[prevAnim].getPosition().x,sprites[prevAnim].getPosition().y+3);
        else 
            sprites[actualSprite].setPosition(sprites[prevAnim].getPosition());

        sprites[actualSprite].setTextureRect(IntRect(0+spriteDec*22, 0, 22, 33));

        if(lastDirec==-1)
            sprites[actualSprite].setScale(-0.8f, 0.8f);
        else 
            sprites[actualSprite].setScale(0.8f, 0.8f);
        // sprites[actualSprite].setOrigin(sprites[actualSprite].getLocalBounds().height/2, sprites[actualSprite].getLocalBounds().width/2);
    }
}

void Monster1::move(float deltatime ,vector<vector<int>> &tabMap){
    if(canAttack==true){
        if(pos[1][0]==1){
            float val = moveSpeed * deltatime;
                animationRun(1,1/deltatime);
            moveX(val);
            if(pos[0][0]>=moveposX[1])
                pos[1][0]=-1;
        } else if(pos[1][0]==-1){
            float val = -moveSpeed * deltatime;
                animationRun(-1,1/deltatime);
            moveX(val);
            if(pos[0][0]<=moveposX[0])
                pos[1][0]=1;
        }
    } else {
        animationAttack(1/deltatime);
    }
}

void Monster1::moveX(float val){
    sprites[actualSprite].move(val, 0.f);
    pos[0][0]+=val;
}

bool Monster1::attack(int fps, float playerPos[]){
    int x = abs(pos[0][0]-playerPos[0]);
    int y = abs(pos[0][1]-playerPos[1]);
    if(canAttack==true && x+y<30){
        canAttack = false;
        if(pos[0][0]<playerPos[0])
            lastDirec = 1;
        else {
            lastDirec = -1;
        }
        return true;
    }
    return false;
}

void Monster1::animationAttack(int fps){
    animationRate=fps>>3;
    if(canAttack==false){
        int prevAnim = actualSprite;
        if(actualSprite!=2){
            actualSprite = 2;
            spriteDec = 0;
            sprites[actualSprite].setPosition(sprites[prevAnim].getPosition().x,sprites[prevAnim].getPosition().y-3);
        } else {
            sprites[actualSprite].setPosition(sprites[prevAnim].getPosition());
        }
        animActualRate--;
        if(!animActualRate){
            animActualRate = animationRate;
            if(spriteDec<7){
                spriteDec++;
            } else{
                dealDamage=true;
                spriteDec=0;
                canAttack=true;
            }
        }
        sprites[actualSprite].setTextureRect(IntRect(0+spriteDec*43, 0, 43, 36));
        if(lastDirec==-1)
            sprites[actualSprite].setScale(-0.8f, 0.8f);
        else 
            sprites[actualSprite].setScale(0.8f, 0.8f);
        sprites[actualSprite].setOrigin(sprites[1].getLocalBounds().height/2, sprites[1].getLocalBounds().width/2);
    }
}