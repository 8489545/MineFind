#include "stdafx.h"
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::SetMapScale(int _width, int _height)
{
    width = _width;
    height = _height;

    map = new int* [height];

    for (int i = 0; i < height; i++)
    {
        map[i] = new int[width];
    }
}

void Map::SettingMine(int mineNum)
{
    while (mineNum--)
    {
        int randX = rand() % width;
        int randY = rand() % height;

        if (map[randY][randX] != -1)
        {
            map[randY][randX] = -1;
        }
        else
        {
            mineNum++;
        }   
    }

    
    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < height; x++)
        {
            int count = 0;

            if (y + 1 < width)
            {
                if (map[y + 1][x] == -1)
                    count++;
            }
            if (x + 1 < height)
            {
                if (map[y][x + 1] == -1)
                    count++;
            }
            if (y - 1 > 0)
            {
                if (map[y - 1][x] == -1)
                    count++;
            }
            if (x - 1 > 0)
            {
                if (map[y][x - 1] == -1)
                    count++;
            }

            if (y + 1 < width && x + 1 < height)
            {
                if (map[y + 1][x + 1] == -1)
                    count++;
            }
            if (y - 1 > 0 && x - 1 > 0)
            {
                if (map[y - 1][x - 1] == -1)
                    count++;
            }
            if (y + 1 < width && x - 1 > 0)
            {
                if (map[y + 1][x - 1] == -1)
                    count++;
            }
            if (y - 1 > 0 && x + 1 < height)
            {
                if (map[y - 1][x + 1] == -1)
                    count++;
            }

            if(map[y][x] != -1)
                map[y][x] = count;
        }
    }

}

void Map::PrintMap()
{
    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < height; x++)
        {
            if (map[y][x] == -1)
                cout << "¡Ü ";
            else
                cout << map[y][x] << "  ";
        }
        cout << "\n";
    }
}
