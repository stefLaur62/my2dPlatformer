#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;
using namespace sf;

class GameMap{
    public:
        vector<vector<int>> tabMap;
        Texture imageMap;
        Sprite map;
        int niveau;
        
        GameMap();
        void readMap();
        void loadNewMap();
        int getHeight(string line);
        int getWidth(string line);
        void getTabMap(string data, int h, int w);
        bool hasReachEnd(int x, int y);
};