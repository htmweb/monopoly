#include "types.h"
#include <stdio.h>

Order order[4];
void gameLoop(currentPlayer players[4],Square squares[40]){
    diceRoll(players, squares, order);
}