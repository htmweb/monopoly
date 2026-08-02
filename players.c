#include "types.h"
#include <stdio.h>
#include <stdlib.h>

currentPlayer players[4];
int isFirstRun = 1;

void initPlayers(Square squares[40]){
    srand(9);

    players[0] = (currentPlayer){
        .ownedItems = {},
        .player = AGGRESSIVE_INVESTOR,
        .ownedLoans = {},
        .ownedInsurance = {},
        .position = -1,
        .money = 30000,    
        .lastTurnVal = 0,
        .currentRound = 0,
        .lastRound = 0
    };
    players[1] = (currentPlayer){
        .ownedItems = {},
        .player = CONSERVATIVE_BANKER,
        .ownedLoans = {},
        .ownedInsurance = {},
        .position = -1,
        .money = 30000,    
        .lastTurnVal = 0,
        .currentRound = 0,
        .lastRound = 0
    };
    players[2] = (currentPlayer){
        .ownedItems = {},
        .player = RISK_TAKER,
        .ownedLoans = {},
        .ownedInsurance = {},
        .position = -1,
        .money = 30000,    
        .lastTurnVal = 0,
        .currentRound = 0,
        .lastRound = 0
    };
    players[3] = (currentPlayer){
        .ownedItems = {},
        .player = OPPORTUNISTIC_TRADER,
        .ownedLoans = {},
        .ownedInsurance = {},
        .position = -1,
        .money = 30000,    
        .lastTurnVal = 0,
        .currentRound = 0,
        .lastRound = 0
    };

    printf("\nMONOPOLY-LK Simulation \n\n");
    for(int i = 0; i<4; i++){
        printf("Player %d : %s \n", i, getPlayer(players[i]));
    }
    printf("\n");
    printf("Each player begins with LKR 30,000 \n\n");

    gameLoop(players, squares);
    
}
char* getPlayer(currentPlayer cPlayer){
    switch(cPlayer.player){
        case AGGRESSIVE_INVESTOR:
            return "Aggressive Investor";
        case CONSERVATIVE_BANKER:
            return "Conservative Banker";
        case RISK_TAKER:
            return "Risk Taker";
        case OPPORTUNISTIC_TRADER:
            return "Opportunistic Trader";
    }
}
void setDiceVal(currentPlayer *player, Square squares[40]){
    int dice1 = 0;
    int dice2 = 0;

    int same_val = 1;

    while(same_val == 1){
        dice1 = rand() % 6 + 1;
        dice2 = rand() % 6 + 1;

        int pos = player->position;
    
        Data current_square_data = squares[pos].data;  
    

        if(dice1 == dice2){
            if(current_square_data.special.type == GO_TO_JAIL){
                same_val = 0;
            }
            else{
                same_val = 1;
            }
        }
        else{
            same_val = 0;
            player->position = dice1+dice2;

        }
        printf("%s rolls %d \n", getPlayer(*player), dice1+dice2);
    
        
    }
}

void diceRoll(currentPlayer players[4], Square squares[40]){
   
    Order order[4];

    for(int i = 0; i<4; i++){
        setDiceVal(&players[i], squares);
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
                    setDiceVal(&players[i], squares);
                    setDiceVal(&players[j], squares);
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
        printf("Player %d : %s \n", i, getPlayer(players[order[i].player]));
    }
    printf("\n");

    }