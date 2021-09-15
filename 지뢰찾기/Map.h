#pragma once
class Map
{
    int** map;
    int width, height;
public:
    Map();
    ~Map();

    
    void SetMapScale(int _width, int _height);
    void SettingMine(int mineNum);

    void PrintMap();

};

