 #include "GameMap.hpp"



GameMap::GameMap(){
    if (!imageMap.loadFromFile("./Ressources/map1.png")){
        cout << "Erreur chargement carte "<<endl;
    }
    map.setTexture(imageMap);
    niveau = 0;
}

int getNextInt(string &data,int* deb){
    string val;
    val.push_back(data[*deb]);
    (*deb)++;
    while(isdigit(data[*deb])){
        val.push_back(data[(*deb)++]);
    }
    (*deb)++;
    return stoi(val);
}

void GameMap::getTabMap(string data, int h, int w){
    int deb=17;
    for(int i = 0;i<h;i++){
        vector <int> v;
        for(int j = 0;j<w;j++){
            v.push_back(getNextInt(data,&deb));
        }
        tabMap.push_back(v);
    }
}

void GameMap::readMap(){
    string line, dataLine;
    int height,width;
    string mapName;
    if(!niveau)
        mapName="map1.json";
    if(niveau==1)
        mapName="map2.json";
    ifstream file("./Ressources/"+mapName);
    if (file.is_open()){
        getline (file,line);
        height = getHeight(line);
        while ( getline (file,line) ){
            if(line.find("data")==10)
                dataLine = line;
            if(line.find("width")==2)
                width = getWidth(line);
        }
        file.close();
    }
    getTabMap(dataLine,height,width);

}
int GameMap::getHeight(string line){
    line = line.substr(11,line.size());
    return stoi(line);
}

int GameMap::getWidth(string line){
    line = line.substr(9,line.size());
    return stoi(line);
}

void GameMap::loadNewMap(){
    tabMap.clear();
    //if selon niveau
    if (!imageMap.loadFromFile("./Ressources/map2.png")){
        cout << "Erreur chargement carte "<<endl;
    }
    map.setTexture(imageMap);
    readMap();
}
bool GameMap::hasReachEnd(int x, int y){
    //niveau 1
    if(!niveau){
        if(x>1092 && x <1110 && y >492 && y < 532){
            niveau++;
            loadNewMap();
            return true;
        }
    }
    return false;
}