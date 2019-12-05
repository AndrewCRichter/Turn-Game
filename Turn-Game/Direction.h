#pragma once
enum Direction{
    RIGHT,
    DOWNRIGHT,
    DOWN,
    LEFT,
    UPLEFT,
    UP
    //+-[1,0] - RIGHT/LEFT
    //+-[0,1] - UP/DOWN
    //+-[1,1] - DOWNRIGHT/UPLEFT
};

const int DIRECTION_VALUES[6][2] = { { 1, 0},
                                     { 1, 1},
                                     { 0, 1},
                                     {-1, 0},
                                     {-1,-1},
                                     { 0,-1}};


/*
[UL] [UP]
[LT] [##] [RT]
     [DN] [DR]
*/