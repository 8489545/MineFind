#pragma once

class Map
{
    Tile** map;
    int width, height;
    POINT curPos;
    POINT PrevPos;
    bool isGameOver;
    bool isPlayerWin;
public:
    Map();
    ~Map();

    bool GetGameState() { return isGameOver; }
    void SetGameState(bool _state) { isGameOver = _state; }

    bool GetPlayerState() { return isPlayerWin; }
    void SetPlayerState(bool _player) { isPlayerWin = _player; }

    void SetMapScale(int _width, int _height);
    void SettingMine(int mineNum);

    void CursorCtrl();

    void PrintMap();
    bool MoveCheak();
    bool WinCheak();
    void Lose();

    int GroundCheak();

    void AllOpenTile();
    void SetCursor(int x, int y);
    void OpenNearTiles(int x,int y);

};

