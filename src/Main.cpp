#include <SFML/Graphics.hpp>
#include "GameMap.hpp"
#include "Player.hpp"
#include <string>
#include <cmath>

using namespace sf;
using namespace std;

int FPSLIMIT = 60;
int MAXTABSIZE = 100;

void gestionEvent(Event &event, Player &player){
    if(event.type== Event::KeyReleased){
        if(event.key.code == Keyboard::D){
            player.setMovementX(0);
        }
        if(event.key.code == Keyboard::Q){
            player.setMovementX(0);
        }
    }
}

void move(View &view, Player &player,float &deltatime,vector<vector<int>> &tabMap,Monster1 &monster){
    if(Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::Q)){
        player.setMovementX(0);
    } else if(Keyboard::isKeyPressed(Keyboard::D)){
        player.setMovementX(1);
        player.setDirection(1);
    } else if(Keyboard::isKeyPressed(Keyboard::Q)){
        player.setMovementX(-1);
        player.setDirection(-1);
    }
    if(Keyboard::isKeyPressed(Keyboard::Space)){
        player.setMovementY(deltatime);
    }
    if(Mouse::isButtonPressed(Mouse::Left)){
        player.attack(1/deltatime, monster);
    }
    player.move(deltatime,tabMap,view);

    
    if(player.canAttack==false){
        player.animationAttack(1/deltatime);
    }


    if(monster.isAlive){
        monster.move(deltatime,tabMap);
        monster.attack(deltatime,player.pos[0]);
        if(!monster.canAttack && monster.dealDamage == true ){
            //check if player close enough
            int x = abs(monster.pos[0][0]-player.pos[0][0]);
            int y = abs(monster.pos[0][1]-player.pos[0][1]);
            monster.dealDamage = false;
            if(x+y<23)
                player.loseLife();
        }
    }
}

void afficherWin(RenderWindow &window, View &view, string t){
    Font font;
    if (!font.loadFromFile("./Ressources/BebasNeue-Regular.ttf")){
        cout << "Couldn't load font texture" << endl;
        exit(1);
    }
    Text toDisp;
    toDisp.setFont(font);
    toDisp.setString(t);
    toDisp.setCharacterSize(10);
    toDisp.setPosition(view.getCenter());
    toDisp.setFillColor(Color::Red);
    window.draw(toDisp);
}

int getAverage(int *tab){
	float sum=0;
    for(int j=0; j<MAXTABSIZE; ++j){
            sum+=tab[j];
    }
    return ceil(sum/MAXTABSIZE);
}

void addFpsToTab(int fps, int *tab, int *tabIndice){
    tab[(*tabIndice)++]=fps;
    if(*tabIndice==MAXTABSIZE){
        *tabIndice=0;
    }
}

void fillTab(int *tab){
    for(int i = 0;i<MAXTABSIZE;++i){
        tab[i]=FPSLIMIT;
    }
}

void afficherFPS(RenderWindow &window, View &view, float &dt, int *tab, int *tabIndice){
    Font font;
    if (!font.loadFromFile("./Ressources/BebasNeue-Regular.ttf")){
        cout << "Couldn't load font texture" << endl;
        exit(1);
    }
    Text toDisp;
    addFpsToTab(ceil(1.0 /dt),tab,tabIndice);
    toDisp.setFont(font);
    toDisp.setString(to_string(getAverage(tab))+ " fps");
    toDisp.setCharacterSize(11);
    Vector2f v(view.getCenter());
    v.x-=view.getSize().x/2;
    v.y-=view.getSize().y/2;
    toDisp.setPosition(v);
    toDisp.setFillColor(Color::White);
    window.draw(toDisp);
}



void gameLoop(RenderWindow &window,View &view){
    int fpsTab[MAXTABSIZE];
    int tabIndice = 0;
    fillTab(fpsTab);

    Clock clock;
    float deltatime = clock.restart().asSeconds();

    Player player(170, 554);
    Monster1 monster(292, 320, 435);
    //Monster1 monster2(292, 320, 400);

    GameMap gameMap = GameMap();
    gameMap.readMap();

    while (window.isOpen())
    {
        
        Event event;
        deltatime = clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else {
                gestionEvent(event,player);
            }
        }

        move(view,player,deltatime,gameMap.tabMap,monster);

        window.draw(gameMap.map);
        window.draw(player.sprites[player.actualSprite]);
        if(monster.isAlive)
            window.draw(monster.sprites[monster.actualSprite]);
        window.setView(view);
		
        afficherFPS(window, view, deltatime, fpsTab, &tabIndice);

        //Go to second map
        if(gameMap.hasReachEnd(player.pos[0][0],player.pos[0][1])){
            player.newStartPos(250,300);
            view.setCenter(250,300);
        }

        window.display();
    }
}


int main()
{
    RenderWindow window(VideoMode(1000, 690), "My game!", Style::Close);
    View view(Vector2f(170, 521), Vector2f(263, 199));
    window.setFramerateLimit(FPSLIMIT);
    gameLoop(window,view);

    return 0;
}
