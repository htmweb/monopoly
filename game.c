#include "types.h"
#include <stdio.h>

Order order[4];
int isFirstRun = 1;

void setOrder(currentPlayer players[4], Square squares[40]){

    for(int i = 0; i<4; i++){
        diceRoll(&players[i], squares);
    }
    printf("\n");

    if(isFirstRun){
      for(int i = 0; i<4; i++){
          order[i].player = players[i].player;
          order[i].diceVal = players[i].position;
      }
      for(int i = 0; i<4; i++){
          for(int j = i+1; j<4; j++){
            if(order[i].diceVal <= order[j].diceVal){
                Order temp = order[i];
                order[i] = order[j];
                order[j] = temp;
               
            }
        }
      }
    

    for(int i = 0; i<4; i++){
        for(int j = i+1; j<4; j++){
            if(players[i].position == players[j].position){ 
                int inTie = 1;
                int tmp_order_1 = 0;
                int tmp_order_2 = 0;

                while(inTie){
                    diceRoll(&players[i], squares);
                    diceRoll(&players[j], squares);
                    if(players[i].position != players[j].position){
                        inTie = 0;
                            for(int k = 0; k<4; k++){
                                if(order[k].player == players[i].player){
                                    order[k].player = players[i].player;
                                    order[k].diceVal = players[i].position;
                                    tmp_order_1 = k;
                                }
                               else if(order[k].player == players[j].player){
                                    order[k].player = players[j].player;
                                    order[k].diceVal = players[j].position;
                                    tmp_order_2 = k;
                                }
                                
                                
                            }
                           
                            if((tmp_order_1 > tmp_order_2) && (order[tmp_order_1].diceVal > order[tmp_order_2].diceVal)){
                                Order temp = order[tmp_order_1];
                                order[tmp_order_1] = order[tmp_order_2];
                                order[tmp_order_2] = temp;
                            }
                            else if((tmp_order_1 < tmp_order_2) && (order[tmp_order_1].diceVal < order[tmp_order_2].diceVal)){
                                Order temp = order[tmp_order_1];
                                order[tmp_order_1] = order[tmp_order_2];
                                order[tmp_order_2] = temp;
                            }
                            
                           
                    }
                    
                }
                
                
            }
        }
    }
    }
    isFirstRun = 0;
    printf("\n");
    printf("%s will begin the game.\n", getPlayer(players[order[0].player]));
    
    printf("\n");
    printf("Turn Order : \n");
    for(int i = 0; i<4; i++){
        printf("Player %d : %s \n", i+1, getPlayer(players[order[i].player]));
    }
    printf("\n");

    currentPlayer tmp_players[4];
    for(int k=0; k<4; k++){
        players[k].position = 0;
        players[k].lastPosition = 0;
        tmp_players[k] = players[k];
    }

    for(int i=0; i<4; i++){
        switch(order[i].player){
            case AGGRESSIVE_INVESTOR:
               players[i] = tmp_players[0];
               break;
            case CONSERVATIVE_BANKER:
               players[i] = tmp_players[1];
               break;
            case RISK_TAKER:
               players[i] = tmp_players[2];
               break;
            case OPPORTUNISTIC_TRADER:
               players[i] = tmp_players[3];
               break;
        }
    }

    }



void gameLoop(currentPlayer players[4],Square squares[40]){
    setOrder(players, squares);

    //check order before roll and move
    rollAndMove(players,squares);
    rollAndMove(players,squares);
    rollAndMove(players,squares);
    rollAndMove(players,squares);
    rollAndMove(players,squares);
    rollAndMove(players,squares);
    rollAndMove(players,squares);
}