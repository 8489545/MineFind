#include"stdafx.h"


int main()
{
    Map map;
    srand(time(NULL));

    map.SetGameState(false);
    map.SetMapScale(30, 30);
    map.SettingMine(50);
    map.PrintMap();

    while (map.GetGameState() == false)
    {
        map.CursorCtrl();
        if (map.GroundCheak() == -1)
        {
            map.AllOpenTile();
            map.Lose();
        }
        if (map.MoveCheak())
            map.PrintMap();

        if (map.WinCheak())
        {
            map.SetGameState(true);
            map.SetPlayerState(true);
        }
        
    }

    if (map.GetPlayerState())
        cout << "YOU WIN!!!";
    else
        cout << "YOU LOSE...";
    
    return 0;
}
