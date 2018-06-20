//
// Created by Brendan Berg on 16.06.18.
//

#ifndef NETWORKGAMETEST_MAPHANDLER_HPP
#define NETWORKGAMETEST_MAPHANDLER_HPP


class MapHandler
{
public:

    MapHandler();

    ~MapHandler();

    void print() const;

    void setMap(char* mapData);

private:

    char* m_Map;


};


#endif //NETWORKGAMETEST_MAPHANDLER_HPP
