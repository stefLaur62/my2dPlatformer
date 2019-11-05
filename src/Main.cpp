#include <SFML/Graphics.hpp>
#include "GameMap.hpp"
#include "Player.hpp"
#include <string>
#include <cmath>
using namespace sf;
using namespace std;
void loadMap(Texture &tileset){
    if (!tileset.loadFromFile("./Ressources/map1.png")){
        cout << "Couldn't load map texture" << endl;
        exit(1);
    } else {
        cout << "LOADED" << endl;
    }
}

void drawMap(RenderWindow &window, Texture &tileset){

    //window.draw(sprite);
}

void gestionEvent(Event &event, Player &player, float deltatime){
    if(event.type== Event::KeyReleased){
        if(event.key.code == Keyboard::D){
            player.setMovementX(0);
        }
        if(event.key.code == Keyboard::Q){
            player.setMovementX(0);
        }
    }
}

void move(View &view, Player &player,float &deltatime,vector<vector<int>> &tabMap){
    if(Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::Q)){
        player.setMovementX(0);
    } else if(Keyboard::isKeyPressed(Keyboard::D)){
        player.setMovementX(1);
    } else if(Keyboard::isKeyPressed(Keyboard::Q)){
        player.setMovementX(-1);
    }
    if(Keyboard::isKeyPressed(Keyboard::Space)){
        player.setMovementY(deltatime);
    }
    player.move(deltatime,tabMap,view);
}

void afficherWin(RenderWindow &window, View &view, string t){
    Font font;
    if (!font.loadFromFile("./Ressources/BebasNeue-Regular.ttf")){
        cout << "Couldn't load font texture" << endl;
        //exit(1);
    }
    Text toDisp;
    toDisp.setFont(font);
    toDisp.setString(t);
    toDisp.setCharacterSize(10);
    toDisp.setPosition(view.getCenter());
    toDisp.setFillColor(Color::Red);
    window.draw(toDisp);
}

int getAverage(int fps[60]){
	int sum=0;

    for(int j=0; j<60; ++j){
            sum+=fps[j];
    }
    return sum/60;
}

void afficherFPS(RenderWindow &window, View &view, float dt){
    Font font;
    if (!font.loadFromFile("./Ressources/BebasNeue-Regular.ttf")){
        cout << "Couldn't load font texture" << endl;
        //exit(1);
    }
    Text toDisp;
    float fps = 1.0 /dt;

    toDisp.setFont(font);
    toDisp.setString(to_string((int)ceil(fps))+ " fps");
    toDisp.setCharacterSize(11);
    Vector2f v(view.getCenter());
    v.x-=view.getSize().x/2;
    v.y-=view.getSize().y/2;
    toDisp.setPosition(v);
    toDisp.setFillColor(Color::White);
    window.draw(toDisp);
}



void gameLoop(RenderWindow &window,View &view){
    Clock clock;
    float deltatime = clock.restart().asSeconds();
    Player player(170,554);
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
                gestionEvent(event,player,deltatime);
            }
        }
        move(view,player,deltatime,gameMap.tabMap);
        window.draw(gameMap.map);
        window.draw(player.sprites[player.actualSprite]);
        window.setView(view);
		
        afficherFPS(window, view, deltatime);
        if(gameMap.hasReachEnd(player.pos[0][0],player.pos[0][1])){
            player.newStartPos(250,300);
            view.setCenter(250,300);
        }
        window.display();
    }
}

int main()
{
    RenderWindow window(VideoMode(1100, 750), "My game!", Style::Fullscreen);
    View view(Vector2f(170, 521), Vector2f(263, 199));
    window.setFramerateLimit(60);
    gameLoop(window,view);

    return 0;
}
