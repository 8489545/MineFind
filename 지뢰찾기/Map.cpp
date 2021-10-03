#include "stdafx.h"
#include "Map.h"

Map::Map()
{
    SetCursorPos(0, 0);
    PrevPos.x = 0;
    PrevPos.y = 0;
}

Map::~Map()
{
}

void Map::SetMapScale(int _width, int _height)
{
    width = _width;
    height = _height;

    map = new Tile* [height];

    for (int i = 0; i < height; i++)
    {
        map[i] = new Tile[width];
    }
}

void Map::SettingMine(int mineNum)
{
    while (mineNum--)
    {
        int randX = rand() % width;
        int randY = rand() % height;

        if (map[randY][randX].state != State::MINE)
        {
            map[randY][randX].state = State::MINE;
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
                if (map[y + 1][x].state == State::MINE)
                    count++;
            }
            if (x + 1 < height)
            {
                if (map[y][x + 1].state == State::MINE)
                    count++;
            }
            if (y - 1 > 0)
            {
                if (map[y - 1][x].state == State::MINE)
                    count++;
            }
            if (x - 1 > 0)
            {
                if (map[y][x - 1].state == State::MINE)
                    count++;
            }

            if (y + 1 < width && x + 1 < height)
            {
                if (map[y + 1][x + 1].state == State::MINE)
                    count++;
            }
            if (y - 1 > 0 && x - 1 > 0)
            {
                if (map[y - 1][x - 1].state == State::MINE)
                    count++;
            }
            if (y + 1 < width && x - 1 > 0)
            {
                if (map[y + 1][x - 1].state == State::MINE)
                    count++;
            }
            if (y - 1 > 0 && x + 1 < height)
            {
                if (map[y - 1][x + 1].state == State::MINE)
                    count++;
            }

            if (map[y][x].state != State::MINE)
                map[y][x].state = count;
        }
    }

}

void Map::CursorCtrl()
{
    if (GetAsyncKeyState(VK_UP) & 0x0001 && curPos.y > 0)
    {
        curPos.y--;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x0001 && curPos.y < width - 1)
    {
        curPos.y++;
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x0001 && curPos.x > 0)
    {
        curPos.x--;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x0001 && curPos.x < height - 1)
    {
        curPos.x++;
    }
}

void Map::PrintMap()
{
    system("cls");
    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < height; x++)
        {
            if (y == curPos.y && x == curPos.x)
            {
                cout << "¡å ";
            }
            else if (map[y][x].isOpen == false)
            {
                cout << "¡à ";
            }
            else if (map[y][x].state == State::MINE)
                cout << "¡Ü ";
            else
                cout << map[y][x].state << "  ";
        }
        cout << "\n";
    }
}

bool Map::MoveCheak()
{
    if (PrevPos.x == curPos.x && PrevPos.y == curPos.y)
    {
        return false;
    }
    else
    {
        PrevPos = curPos;
        return true;
    }
}

bool Map::WinCheak()
{
    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < height; x++)
        {
            if (map[y][x].isOpen == false && map[y][x].state != MINE)
                return false;
        }
    }

    return true;
}

void Map::Lose()
{
    SetGameState(true);
    SetPlayerState(false);
}

int Map::GroundCheak()
{
    if (GetAsyncKeyState(VK_RETURN) & 0x0001)
    {
        if (map[curPos.y][curPos.x].isOpen == false)
        {
            map[curPos.y][curPos.x].isOpen = true;

            if (map[curPos.y][curPos.x].state == MINE)
                return -1;
            if (map[curPos.y][curPos.x].state == ZERO)
            {
                OpenNearTiles(curPos.y, curPos.x);
                return 0;
            }
            else
                return 0;
        }
    }
}

void Map::AllOpenTile()
{
    for (int y = 0; y < width; y++)
    {
        for (int x = 0; x < height; x++)
        {
            map[y][x].isOpen = true;
        }
    }
    PrintMap();
}

void Map::SetCursor(int x, int y)
{
    curPos.x = x;
    curPos.y = y;
}

void Map::OpenNearTiles(int x, int y)
{
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    if (x > 0)
    {
        if (map[y][x - 1].state == ZERO && map[y][x - 1].isOpen == false)
        {
            map[y][x - 1].isOpen = true;
            OpenNearTiles(x - 1, y);
        }
        if (y > 0)
        {
            if (map[y - 1][x - 1].state == ZERO && map[y - 1][x - 1].isOpen == false)
            {
                map[y - 1][x - 1].isOpen = true;
                OpenNearTiles(x - 1, y - 1);
            }
        }
        if (y < width - 1)
        {
            if (map[y + 1][x - 1].state == ZERO && map[y + 1][x - 1].isOpen == false)
            {
                map[y + 1][x - 1].isOpen = true;
                OpenNearTiles(x - 1, y + 1);
            }
        }
    }
    if (x < height - 1)
    {
        if (map[y][x + 1].state == ZERO && map[y][x + 1].isOpen == false)
        {
            map[y][x + 1].isOpen = true;
            OpenNearTiles(x + 1, y - 1);
        }
        if (y > 0)
        {
            if (map[y - 1][x + 1].state == ZERO && map[y - 1][x + 1].isOpen == false)
            {
                map[y - 1][x + 1].isOpen = true;
                OpenNearTiles(x + 1, y - 1);
            }
        }
        if (y < width - 1)
        {
            if (map[y + 1][x + 1].state == ZERO && map[y + 1][x + 1].isOpen == false)
            {
                map[y + 1][x + 1].isOpen = true;
                OpenNearTiles(x + 1, y + 1);
            }
        }
    }
    if (y > 0)
    {
        if (map[y - 1][x].state == ZERO && map[y - 1][x].isOpen == false)
        {
            map[y - 1][x].isOpen = true;
            OpenNearTiles(x, y - 1);
        }
    }
    if (y < width - 1)
    {
        if (map[y + 1][x].state == ZERO && map[y + 1][x].isOpen == false)
        {
            map[y + 1][x].isOpen = true;
            OpenNearTiles(x, y + 1);
        }
    }
    return;
}
