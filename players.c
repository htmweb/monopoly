#include "types.h"
#include <stdio.h>
#include <stdlib.h>

currentPlayer players[4];

void initPlayers(Square squares[40]){
    srand(9);

    players[0] = (currentPlayer){
        .ownedItems = {},
        .player = AGGRESSIVE_INVESTOR,
        .ownedLoans = {},
        .ownedInsurance = {},
        .lastPosition = 0,
        .position = 0,
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
        .lastPosition = 0,
        .position = 0,
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
        .lastPosition = 0,
        .position = 0,
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
        .lastPosition = 0,
        .position = 0,
        .money = 30000,    
        .lastTurnVal = 0,
        .currentRound = 0,
        .lastRound = 0
    };

    printf("\nMONOPOLY-LK Simulation \n\n");
    for(int i = 0; i<4; i++){
        printf("Player %d : %s \n", i+1, getPlayer(players[i]));
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
void diceRoll(currentPlayer *player, Square squares[40]){
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
            player->lastPosition = player->position;
            player->position = dice1+dice2;

        }
        printf("%s rolls %d. \n", getPlayer(*player), dice1+dice2);
    
        
    }
}


//player activities
void aggressiveInvestor(Square squares[40]){

}
void conservativeBanker(Square squares[40]){
    
}
void riskTaker(Square squares[40]){
    
}
void oppurtunisticTrader(Square squares[40]){
    
}


void playerActivities(currentPlayer *current_player,Square squares[40]){
    switch(current_player->player){
        case AGGRESSIVE_INVESTOR:
            aggressiveInvestor(squares);
            break;
        case CONSERVATIVE_BANKER:
            conservativeBanker(squares);
            break;
        case RISK_TAKER:
            riskTaker(squares);
            break;
        case OPPORTUNISTIC_TRADER:
            oppurtunisticTrader(squares);
            break;
    }
}