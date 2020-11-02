#include "Player.hpp"

Player::Player(int debX,int debY):debX(debX),debY(debY),animationRate(30),animActualRate(30), hp(5){
    //pos 0 = coord
    //pos 1 = movement
    pos[0][0]=debX;
    pos[0][1]=debY;
    pos[1][0]=0;
    pos[1][1]=0;
    canjump=true;
    isAlive=true;
    canAttack=true;
    actualSprite=0;
    loadSprite();
    playerSpeed=70;
    accelerationY=1.3;
}
void Player::loadSprite(){
    if (!textures[0].loadFromFile("./Ressources/Individual Sprites/adventurer-idle-00.png") 
    || !textures[1].loadFromFile("./Ressources/Individual Sprites/adventurer-idle-01.png")
    || !textures[2].loadFromFile("./Ressources/Individual Sprites/adventurer-idle-02.png") 
    || !textures[3].loadFromFile("./Ressources/Individual Sprites/adventurer-idle-03.png")
    || !textures[4].loadFromFile("./Ressources/Individual Sprites/adventurer-jump-01.png")
    || !textures[5].loadFromFile("./Ressources/Individual Sprites/adventurer-jump-02.png")
    || !textures[6].loadFromFile("./Ressources/Individual Sprites/adventurer-jump-03.png")
    || !textures[7].loadFromFile("./Ressources/Individual Sprites/adventurer-run-00.png")
    || !textures[8].loadFromFile("./Ressources/Individual Sprites/adventurer-run-01.png")
    || !textures[9].loadFromFile("./Ressources/Individual Sprites/adventurer-run-02.png")
    || !textures[10].loadFromFile("./Ressources/Individual Sprites/adventurer-run-03.png")
    || !textures[11].loadFromFile("./Ressources/Individual Sprites/adventurer-fall-01.png")
    || !textures[12].loadFromFile("./Ressources/Individual Sprites/adventurer-attack2-02.png")
    || !textures[13].loadFromFile("./Ressources/Individual Sprites/adventurer-attack2-03.png")
    || !textures[14].loadFromFile("./Ressources/Individual Sprites/adventurer-attack2-04.png")
    || !textures[15].loadFromFile("./Ressources/Individual Sprites/adventurer-attack2-05.png")
    ){
        cout << "Couldn't load Player texture" << endl;
        exit(1);
    }
    sprites[0].setTexture(textures[0]);
    sprites[1].setTexture(textures[1]);
    sprites[2].setTexture(textures[2]);
    sprites[3].setTexture(textures[3]);
    sprites[4].setTexture(textures[4]);
    sprites[5].setTexture(textures[5]);
    sprites[6].setTexture(textures[6]);
    sprites[7].setTexture(textures[7]);
    sprites[8].setTexture(textures[8]);
    sprites[9].setTexture(textures[9]);
    sprites[10].setTexture(textures[10]);
    sprites[11].setTexture(textures[11]);
    sprites[12].setTexture(textures[12]);
    sprites[13].setTexture(textures[13]);
    sprites[14].setTexture(textures[14]);
    sprites[15].setTexture(textures[15]);

    sprites[actualSprite].setPosition(Vector2f(pos[0][0], pos[0][1]));
    sprites[actualSprite].setScale(0.8f, 0.8f);
    sprites[actualSprite].setOrigin(sprites[actualSprite].getGlobalBounds().height/2, sprites[actualSprite].getGlobalBounds().width/2);
}
void Player::newStartPos(int x, int y){
    debX=x;
    debY=y;
    pos[0][0]=debX;
    pos[0][1]=debY;
    actualSprite=0;
    lastDirec=1;
    sprites[actualSprite].setPosition(Vector2f(pos[0][0], pos[0][1]));
}

void Player::setMovementY(float dt){
    if(canjump){
        pos[1][1]=80;
        canjump=false;
    }
}
void Player::setMovementX(float x){
    if(pos[1][0]==-1){
        sprites[actualSprite].setScale(-0.8f,0.8f);;
    } else if(pos[1][0]==1){
        sprites[actualSprite].setScale(0.8f, 0.8f);
    }
    pos[1][0]=x;

}

void Player::setDirection(int direction){
    lastDirec = direction;
}

bool isKilling(int &idbloc){
    vector<int> vect{225,295,318,248,273,343,250,320};
    for(int x : vect){
        if(x==idbloc)
            return true;
    }
    return false;
}

bool isSolid(int &idbloc){
    vector<int> vect{71,2,47,13,75,48,25,49,99,8,9,74,98,3,32,10,15,23,278,4,73};
    for(int x : vect){
        if(x==idbloc)
            return true;
    }
    return false;
}

bool Player::canLeft(vector<vector<int>> &tabMap, float val){
    float h = sprites[0].getLocalBounds().height/2;
    float w = sprites[0].getLocalBounds().width/2;
    float dec=5;

    int blocX = ((int) (pos[0][0] - w +dec + val) >> 4);
    int blocY = ((int) (pos[0][1] - h+9)>> 4);
    int blocYB = (((int) (pos[0][1]+ h)) >> 4);
    if(isKilling(tabMap[blocY][blocX])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocY][blocX])){
        return false;
    }
    if(isKilling(tabMap[blocY+1][blocX])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocY+1][blocX])){
        return false;
    }
    if(isKilling(tabMap[blocYB][blocX])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocYB][blocX]))
        return false;
    return true;
}

bool Player::canRight(vector<vector<int>> &tabMap, float val){
    float h = sprites[0].getLocalBounds().height/2;
    float w = sprites[0].getLocalBounds().width/2;
    float dec=5;
    int blocX = ((int) (pos[0][0] + w - dec + val) >> 4);
    int blocY = ((int) (pos[0][1] - h+9) >> 4);
    int blocYB = (((int) (pos[0][1]+ h)) >> 4);
    if(isKilling(tabMap[blocY][blocX])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocY][blocX])){
        return false;
    }
    if(isKilling(tabMap[blocY+1][blocX])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocY+1][blocX])){
        return false;
    }
    if(isKilling(tabMap[blocYB][blocX])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocYB][blocX]))
        return false;
    return true;
}

bool Player::canFall(vector<vector<int>> &tabMap, float val){
    float h = sprites[0].getLocalBounds().height/2;
    float w = sprites[0].getLocalBounds().width/2;
    float dec=5;

    int blocX = ((int) (pos[0][0]-w + dec) >> 4);
    int blocY = (((int) (pos[0][1]+ h + val)) >> 4);
    int blocXD = ((int) (pos[0][0]+ w - dec) >> 4);
    if(isKilling(tabMap[blocY][blocX])){
        isAlive=false;
    }    
    if(isSolid(tabMap[blocY][blocX])){
        return false;
    }
    if(isKilling(tabMap[blocY][blocXD])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocY][blocXD]))
        return false;
    return true;
} 

bool Player::canJump(vector<vector<int>> &tabMap,float val){
    float h = sprites[0].getGlobalBounds().height/4;
    float w = sprites[0].getGlobalBounds().width/2;
    float dec=5;
    int blocX = ((int) (pos[0][0]-w + dec)>> 4);
    int blocY = ((int) (pos[0][1]-h + val) >> 4);
    int blocXD = ((int) (pos[0][0]+w - dec) >> 4);
    if(isKilling(tabMap[blocY][blocX])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocY][blocX])){
        return false;
    }
    if(isKilling(tabMap[blocY][blocXD])){
        isAlive=false;
    }
    if(isSolid(tabMap[blocY][blocXD]))
        return false;
    return true;
}

void Player::animationIdle(int fps){
    if(!pos[1][0] && !pos[1][1]){
        animationRate=fps;
        int prevAnim = actualSprite;
        if(actualSprite>-1 && actualSprite <4){
            animActualRate--;
            if(!animActualRate){
                animActualRate = animationRate;
                if(actualSprite<3)
                    actualSprite++;
                else
                    actualSprite=0;
            }
        } else {
            actualSprite=0;
        }
        sprites[actualSprite].setPosition(sprites[prevAnim].getPosition());
        if(lastDirec==-1)
            sprites[actualSprite].setScale(-0.8f, 0.8f);
        else 
            sprites[actualSprite].setScale(0.8f, 0.8f);
        sprites[actualSprite].setOrigin(sprites[0].getLocalBounds().height/2, sprites[0].getLocalBounds().width/2);
    }
}

void Player::animationRun(int direc,int fps){
    animationRate=fps>>2;
    lastDirec=direc;
    int prevAnim = actualSprite;
    if(!(pos[1][1]>0)){
        if(actualSprite>6 && actualSprite <11){
            animActualRate--;
            if(!animActualRate){
                animActualRate = animationRate;
                actualSprite++;
                if(actualSprite==11)
                    actualSprite=7;
            }
        } else {
            actualSprite=7;
        }
        sprites[actualSprite].setPosition(sprites[prevAnim].getPosition());
        if(direc==-1)
            sprites[actualSprite].setScale(-0.8f, 0.8f);
        else 
            sprites[actualSprite].setScale(0.8f, 0.8f);
        sprites[actualSprite].setOrigin(sprites[0].getLocalBounds().height/2, sprites[0].getLocalBounds().width/2);
    }
}

void Player::animationJump(int fps){
    animationRate=fps>>1;
    int prevAnim = actualSprite;

    if(actualSprite>4 && actualSprite <7){
        animActualRate--;
        if(!animActualRate){
            animActualRate = animationRate;
             if(actualSprite<6)
                actualSprite++;
        }
    } else {
        actualSprite=5;
    }
    sprites[actualSprite].setPosition(sprites[prevAnim].getPosition());
    if(lastDirec==-1)
        sprites[actualSprite].setScale(-0.8f, 0.8f);
    else 
        sprites[actualSprite].setScale(0.8f, 0.8f);
    sprites[actualSprite].setOrigin(sprites[0].getLocalBounds().height/2, sprites[0].getLocalBounds().width/2);
}

void Player::animationFall(){
    sprites[11].setPosition(sprites[actualSprite].getPosition());
    actualSprite=11;
    if(lastDirec==-1)
        sprites[actualSprite].setScale(-0.8f, 0.8f);
    else 
        sprites[actualSprite].setScale(0.8f, 0.8f);
    sprites[actualSprite].setOrigin(sprites[0].getLocalBounds().height/2, sprites[0].getLocalBounds().width/2);
}

void Player::move(float deltatime ,vector<vector<int>> &tabMap, View &view){
    if(!isAlive){
        isAlive=true;
        pos[0][0]=debX;
        pos[0][1]=debY;
        actualSprite=0;
        lastDirec=1;
        hp=5;
        sprites[actualSprite].setPosition(Vector2f(pos[0][0], pos[0][1]));
        view.setCenter(pos[0][0],pos[0][1]);
    }
    if(pos[1][0]==1){
        float val = playerSpeed * deltatime;
        if(canRight(tabMap,val)){
            if(canAttack == true)
                animationRun(1,1/deltatime);
            moveX(val);
            view.move(val,0);
        }
    } else if(pos[1][0]==-1){
        
        float val = -playerSpeed * deltatime;
        if(canLeft(tabMap,val)){
            if(canAttack == true)
                animationRun(-1,1/deltatime);
            moveX(val);
            view.move(val,0);
        }
    }
    //gestion jump / chute
    if(pos[1][1]>0){//jump
        pos[1][1] -= accelerationY;
        float val = -pos[1][1]*0.02;
        if(canJump(tabMap,val)){
            if(canAttack == true)
                animationJump(1/deltatime);
            jump(val);
            view.move(0,val);
        } else {
            pos[1][1]=-1;
        }
        //revoir chute?
    } else {//chute
        float val = playerSpeed * 1.2* deltatime;
        if(canFall(tabMap,val)){
            if(canAttack == true)
                animationFall();
            moveDown(val);
            view.move(0,val);
        } else {
            if(!pos[1][0]){
                sprites[0].setPosition(sprites[actualSprite].getPosition());
                if(lastDirec==-1)
                    sprites[actualSprite].setScale(-0.8f, 0.8f);
                else
                    sprites[actualSprite].setScale(0.8f, 0.8f);
            }
            pos[1][1]=0;
            canjump=true;
        }
    }
    if(canAttack == true)
        animationIdle(1/deltatime);
}

void Player::moveX(float val){
    sprites[actualSprite].move(val, 0.f);
    pos[0][0]+=val;
}

void Player::jump(float val){
    sprites[actualSprite].move(0.f, val);
    pos[0][1]+=val;
}

void Player::moveDown(float val){
    pos[1][1]=-1;
    sprites[actualSprite].move(0.f, val);
    pos[0][1]+=val;
}

void Player::attack(int fps, Monster1 &monster){
    if(canAttack==true){
        canAttack = false;
    } else {
        int x = abs(monster.pos[0][0]-pos[0][0]);
        int y = abs(monster.pos[0][1]-pos[0][1]);
        if(x+y<26)//wait end animation
            monster.isAlive = false;
    }
}

void Player::animationAttack(int fps){
    animationRate=fps>>3;
    if(canAttack==false){
        int prevAnim = actualSprite;
        if(actualSprite < 12)
            actualSprite = 12;
        animActualRate--;
        if(!animActualRate){
            animActualRate = animationRate;
            actualSprite++;
            if(actualSprite==16){
                actualSprite=0;
                canAttack = true;
            }
            sprites[actualSprite].setPosition(sprites[prevAnim].getPosition());
        }
        sprites[actualSprite].setPosition(sprites[prevAnim].getPosition());
        sprites[actualSprite].setOrigin(sprites[0].getLocalBounds().height/2, sprites[0].getLocalBounds().width/2);
        if(lastDirec==-1)
            sprites[actualSprite].setScale(-0.8f, 0.8f);
        else 
            sprites[actualSprite].setScale(0.8f, 0.8f);
    }
}

void Player::loseLife(){
    
    hp--;
    if(!hp){
        isAlive=false;
    }
    cout << "HP:" << hp << endl;
}