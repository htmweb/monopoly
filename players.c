#include "types.h"
#include <stdio.h>
#include <stdlib.h>

currentPlayer players[4];
const int BID_VAL = 250;

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
        .currentRound = 1,
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
        .currentRound = 1,
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
        .currentRound = 1,
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
        .currentRound = 1,
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
            player->position = player->lastPosition + dice1+dice2;

        }
        printf("%s rolls %d. \n", getPlayer(*player), dice1+dice2);
    
        
    }
}
//bidding logics for players
void AGG_BIDDING(Auction *auction, currentPlayer *player){
    if(auction->AGGRESSIVE_INVESTOR_BID != -1 && auction->lastBidder == AGGRESSIVE_INVESTOR){
        if(auction->RISK_TAKER_BID == -1 && auction->OPPORTUNISTIC_TRADER_BID == -1 && auction->CONSERVATIVE_BANKER_BID == -1){
            printf("%s bids won LKR %d.\n", getPlayer(*player), auction->AGGRESSIVE_INVESTOR_BID);
            auction->status = 0;
        }
    }
    else if((auction->currentBid)+BID_VAL <= auction->square.data.property.purchasePrice * 120){
        if((auction->currentBid)+BID_VAL <= player->money){
            auction->AGGRESSIVE_INVESTOR_BID = auction->currentBid + BID_VAL;
            auction->currentBid = auction->currentBid + BID_VAL;
            auction->lastBidder = AGGRESSIVE_INVESTOR;
            printf("%s bids LKR %d.\n", getPlayer(*player), auction->AGGRESSIVE_INVESTOR_BID);
        }
        else{
            auction->AGGRESSIVE_INVESTOR_BID = -1;
        }
    }
    
    else{
        auction->AGGRESSIVE_INVESTOR_BID = -1;
    }
    
}

void CON_BIDDING(Auction *auction, currentPlayer *player){
    if(auction->CONSERVATIVE_BANKER_BID != -1 && auction->lastBidder == CONSERVATIVE_BANKER){
        if(auction->RISK_TAKER_BID == -1 && auction->OPPORTUNISTIC_TRADER_BID == -1 && auction->AGGRESSIVE_INVESTOR_BID == -1){
            printf("%s bids won LKR %d.\n", getPlayer(*player), auction->CONSERVATIVE_BANKER_BID);
            auction->status = 0;
        }
    }

    else if((auction->currentBid)+BID_VAL <= auction->square.data.property.purchasePrice * 120){
        if((auction->currentBid)+BID_VAL <= player->money){
            auction->CONSERVATIVE_BANKER_BID = auction->currentBid + BID_VAL;
            auction->currentBid = auction->currentBid + BID_VAL;
            auction->lastBidder = CONSERVATIVE_BANKER;

            printf("%s place bids LKR %d.\n", getPlayer(*player), auction->CONSERVATIVE_BANKER_BID);
        }
        else{
            auction->CONSERVATIVE_BANKER_BID = -1;
        }
    }
    else{
        auction->CONSERVATIVE_BANKER_BID = -1;
    }
}
void RISK_BIDDING(Auction *auction, currentPlayer *player){
    //DUMMY
    
}
void OPP_BIDDING(Auction *auction, currentPlayer *player){
    //DUMMY
    
}

//player activities
void aggressiveInvestor(Square squares[40], currentPlayer *current_player){

    int current_pos = current_player->position;
    if(squares[current_pos].type == PROPERTY){
        if(squares[current_pos].data.property.mortgageStatus == UNMORTGAGED){
            if(squares[current_pos].data.property.owner == -1){
                int remain = current_player->money - squares[current_pos].data.property.purchasePrice;
                if(remain >= squares[current_pos].data.property.baseRental){
                    squares[current_pos].data.property.owner = 0;
                    current_player->money -= squares[current_pos].data.property.purchasePrice;
                    printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.property.name, squares[current_pos].data.property.purchasePrice);
                    printf("Remaining Balance : LKR %d.\n", current_player->money);
                }
                else{
                    startAuction(&squares[current_pos], players);
                }
            }
            
        }
    }
// end of property purchasing logic
    


}
void conservativeBanker(Square squares[40], currentPlayer *current_player){
    
}
void riskTaker(Square squares[40], currentPlayer *current_player){
    
}
void oppurtunisticTrader(Square squares[40], currentPlayer *current_player){
    
}


void playerActivities(currentPlayer *current_player,Square squares[40]){
    switch(current_player->player){
        case AGGRESSIVE_INVESTOR:
            aggressiveInvestor(squares,current_player);
            break;
        case CONSERVATIVE_BANKER:
            conservativeBanker(squares,current_player);
            break;
        case RISK_TAKER:
            riskTaker(squares,current_player);
            break;
        case OPPORTUNISTIC_TRADER:
            oppurtunisticTrader(squares,current_player);
            break;
    }
}