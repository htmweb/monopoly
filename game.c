#include "types.h"
#include <stdio.h>



void setOrder(currentPlayer players[], Square squares[]){
    Order order[4];
    int isFirstRun = 1;

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


void startAuction(Square *square, currentPlayer players[]){

    int purchasePrice = 0;

    printf("\nAuction Started.\n\n");
    printf("Property :\n");

    switch(square->type){
        case PROPERTY:
            purchasePrice = square->data.property.purchasePrice;
            printf("%s\n\n", square->data.property.name);
        break;
        case RAILWAY:
            purchasePrice = square->data.railway.purchasePrice;
            printf("%s\n\n", square->data.railway.name);
        break;
        case UTILITY:
            purchasePrice = square->data.utility.purchasePrice;
            printf("%s\n\n", square->data.utility.name);
        break;
    }
    

    Auction auction;

    auction.square = *square;
    auction.AGGRESSIVE_INVESTOR_BID = purchasePrice;
    auction.CONSERVATIVE_BANKER_BID = purchasePrice;
    auction.RISK_TAKER_BID = -1;//auction.square.data.property.purchasePrice;
    auction.OPPORTUNISTIC_TRADER_BID = -1;//auction.square.data.property.purchasePrice;
    auction.currentBid = roundOff(purchasePrice * 0.5);
    auction.status = 1;

    printf("Opening Bid : \n");
    printf("LKR %d\n\n",auction.currentBid);

    while(auction.status == 1){
    for(int i = 0; i<4; i++){
        switch(players[i].player){
            case AGGRESSIVE_INVESTOR:
                if(auction.AGGRESSIVE_INVESTOR_BID != -1){
                    AGG_BIDDING(&auction, &players[i],i);
                }
                break;
            case CONSERVATIVE_BANKER:
                if(auction.CONSERVATIVE_BANKER_BID != -1){
                    CON_BIDDING(&auction, &players[i],i);
                }
                break;
            case RISK_TAKER:
                if(auction.RISK_TAKER_BID != -1){
                    RISK_BIDDING(&auction, &players[i],i);
                }
                break;
            case OPPORTUNISTIC_TRADER:
                if(auction.OPPORTUNISTIC_TRADER_BID != -1){
                    OPP_BIDDING(&auction, &players[i],i);
                }
                break;
        }

    }
        
        if(auction.AGGRESSIVE_INVESTOR_BID == -1 && auction.CONSERVATIVE_BANKER_BID == -1 && auction.RISK_TAKER_BID == -1 && auction.OPPORTUNISTIC_TRADER_BID == -1){
            printf("Auction Ended.\n");
            printf("No Bids were placed.\n");
            auction.status = 0;
        }
        else if(auction.status == 0){
            square->data.property.owner = auction.lastBidder;
            printf("%s won the auction for %s with a bid of LKR %d.\n", getPlayer(players[auction.lastBidder]), square->data.property.name, auction.currentBid);
            printf("Auction Ended.\n");
            
        }

    }

}

void bankRupt(currentPlayer *player){

}
void initStatus(currentStatus *status){
    status->rounds = 0;
    status->turn = 0;
}

void incrementRound(currentStatus *status,currentPlayer players[],Square squares[]){
    int offset = 0;
    int minRounds = 1;
    for(int i=0; i<=4; i++){
        if(players[i].inJail == NOTIN_JAIL){
            minRounds = players[i].currentRound;
            offset = i;
            break;
        }
    }
    for(int i = offset; i<4; i++){
        if(players[i].inJail == NOTIN_JAIL && minRounds > players[i].currentRound){
            minRounds = players[i].currentRound;
        }
    }
    if(minRounds == status->rounds +1){
        status->rounds++;
        
        printf("==================================\n");
        printf("Round %d Summary\n", status->rounds);
        printf("==================================\n");

        for(int i = 0; i<4; i++){

            int networth = getNetWorth(&players[i], squares);

            printf("Player %d : %s \n", i+1, getPlayer(players[i]));
            printf("Cash : LKR %d.\n", players[i].money);        
            printf("NetWorth : %d.\n", networth);
            printf("Properties : %d.\n", players[i].propertiesCount);
            printf("Hotels : %d.\n", players[i].numberOfHotels);
            printf("Outstanding Loan : %d.\n", players[i].loanAmount);
            printf("--------------------------------\n");
    }
    printf("\n");
    }
}

void gameLoop(){
    Square squares[40];
    currentPlayer players[4];
    currentStatus status;
    EconomicState econStatus;

    initStatus(&status);
    initBoard(squares,players);
    initPlayers(squares,players);
    setOrder(players, squares);


    int prevRound = 0;


    applyInflation(squares, &econStatus, generateInflationRate());
    
    while(status.rounds<=20 || (players[0].isBankrupt == BANKRUPT && players[1].isBankrupt == BANKRUPT && players[2].isBankrupt == BANKRUPT && players[3].isBankrupt == BANKRUPT)){
        prevRound = status.rounds;
        rollAndMove(players,squares,&status,&econStatus);

        
        incrementRound(&status,players,squares);

        if(prevRound != status.rounds && status.rounds % 10 == 0){
            applyInflation(squares, &econStatus, generateInflationRate());
            printMarketCondition(&econStatus);
        }

        status.turn++;
        
    }
    

    
   
}