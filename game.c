#include "types.h"
#include <stdio.h>
#include <stdlib.h>

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
    auction.RISK_TAKER_BID = purchasePrice;
    auction.OPPORTUNISTIC_TRADER_BID = purchasePrice;

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
            Player winner = auction.lastBidder;
            int winnerIndex = -1;
            for (int i = 0; i < 4; i++) {
                if (players[i].player == winner) {
                    winnerIndex = i;
                    break;
            }
            }

            switch (square->type) {
                case PROPERTY:
                    square->data.property.owner = winner;
                    players[winnerIndex].propertiesCount++;
                    printf("\n%s wins the auction.\n",
                    getPlayer(players[winnerIndex]));
                break;
                case RAILWAY:
                    square->data.railway.owner = winner;
                    players[winnerIndex].railwaysCount++;
                    printf("\n%s wins the auction.\n",
                    getPlayer(players[winnerIndex]));
                break;
                case UTILITY:
                    square->data.utility.owner = winner;
                    players[winnerIndex].utilityCount++;
                    printf("\n%s wins the auction.\n",
                    getPlayer(players[winnerIndex]), square->data.utility.name);
                break;
            }

        printf("\nAuction Ended.\n\n");
        players[winnerIndex].money -= auction.currentBid;
        }

    }

}


void initStatus(currentStatus *status){
    status->rounds = 0;
    status->turn = 0;
    status->currentNationalCardIndex = 0;
    status->gameOver = NOT_GAME_OVER;
}

void incrementRound(currentStatus *status,currentPlayer players[],Square squares[],EconomicState *econStatus){
    int offset = 0;
    int minRounds = 1;
    checkPlayerBankrupt(players,squares);

    for(int i=0; i<4; i++){
        if(players[i].inJail == NOTIN_JAIL && players[i].isBankrupt == NOTBANKRUPT){
            minRounds = players[i].currentRound;
            offset = i;
            break;
        }
    }
    for(int i = 0; i<4; i++){
        if(players[i].inJail == NOTIN_JAIL && minRounds > players[i].currentRound && players[i].isBankrupt == NOTBANKRUPT){
            minRounds = players[i].currentRound;
        }
    }
    if(minRounds >= status->rounds+2 && status->gameOver == NOT_GAME_OVER){
        
        status->rounds++;

        checkInsuranceExpiry(players, squares);
        updateNationalEvents(players);

        for (int i = 0; i < 4; i++) {
            checkLoanDefault(&players[i], squares);
            calLoanInterest(&players[i],squares);
        }
        applyLuxuryPropertyTax(players, squares, econStatus);
        
        printf("==================================\n");
        printf("Round %d Summary\n", status->rounds);
        printf("==================================\n");

        for(int i = 0; i<4; i++){
            int networth = getNetWorth(&players[i], squares);
            printf("Player %d : %s \n", i+1, getPlayer(players[i]));
            printf("Cash : LKR %d.\n", players[i].money);        
            printf("NetWorth : LKR %d.\n", networth);
            printf("Properties : %d.\n", players[i].propertiesCount);
            printf("Hotels : %d.\n", players[i].numberOfHotels);
            printf("Outstanding Loan : LKR %d.\n", players[i].loanAmount);
            printf("--------------------------------\n");

            
            
        }
    printf("\n");
    }
}
void printWinnerAndExit(currentPlayer *winner,Square squares[]){
    printf("\n==================================\n");
    printf("End of the game.\n");
    printf("==================================\n\n");
    printf("GAME OVER\n\n");
    printf("Winner\n%s\n\n", getPlayer(*winner));
    printf("Total cash\nLKR %d.\n\n", winner->money);
    printf("Total Property Value\nLKR %d.\n\n", getTotalPropertyValue(squares,winner));
    printf("Outstanding Loans\n%d\n\n", winner->isLoanActive);
    printf("Networth \nLKR %d.\n\n", getNetWorth(winner,squares));

    exit(0);
}

void checkWinner(currentPlayer players[], currentStatus *status, Square squares[]){
    int losers = 0;
    int lastActive = -1;

    for(int i = 0; i < 4; i++){
        if(players[i].isBankrupt == BANKRUPT){
            losers++;
        } else {
            lastActive = i;
        }
    }

    if(losers >= 3){
        status->gameOver = GAME_OVER;
        if(lastActive != -1){
            printWinnerAndExit(&players[lastActive], squares);
        } else {
            gameDraw(players, squares, status);
        }
    }
}
void gameDraw(currentPlayer players[],Square squares[],currentStatus *status){
    int netWorth = getNetWorth(&players[0], squares);
    currentPlayer *winner = &players[0];

    for(int i=1; i<4; i++){
        int playerNetWorth = getNetWorth(&players[i], squares);
        if(playerNetWorth > netWorth){
            netWorth = playerNetWorth;
            winner = &players[i];
        }
    }
    status->gameOver = GAME_OVER;

    printWinnerAndExit(winner,squares);
}
void initEconStatus(EconomicState *econStatus){
    econStatus->utilityRentMultiplier = 1;
    econStatus->currentInflationRate = 10;
    econStatus->currentLoanInterestRate = 10;
    econStatus->regulationActive = 0;
    econStatus->insurancePremiumDiscount = 0;
    econStatus->constructionSuspended = 0;
    econStatus->railwayValueIncrement = 0;
    econStatus->incomeTaxMultiplier = 1;
    econStatus->luxuryPropertyTaxRate = 0;
    econStatus->utilityIncome = 0;
    econStatus->maxUndevelopedProperties = -1;
}
void gameLoop(){
    srand(1);
    Square squares[40];
    currentPlayer players[4];
    currentStatus status;
    EconomicState econStatus;
    NationalEvent nationalEvents[20];
    economicEvents econEvents[8];
    DisasterType disasters[] = {FIRE, FLOOD, RIOT, BUILDING_COLLAPSE, ELECTRICAL_FAILURE, EARTH_QUAKE,VANDALISM};

    status.gameOver = NOT_GAME_OVER;

    initStatus(&status);
    initEconStatus(&econStatus);
    initNationalEvents(nationalEvents);
    initEconomicEvents(econEvents);
    initBoard(squares,players);
    initPlayers(squares,players);
    setOrder(players,squares);


    int prevRound = 0;

    triggerEconomicEvent(&econStatus,squares,econEvents);
    triggerDisaster(players,squares,disasters);
    applyInflation(squares,&econStatus,generateInflationRate());
    setLoanInterestRate(&econStatus);
    
    
    while(status.rounds<500 && status.gameOver == NOT_GAME_OVER){
            if(prevRound != status.rounds && status.rounds % 10 == 0){
                applyInflation(squares,&econStatus, generateInflationRate());
                triggerDisaster(players,squares,disasters);
            }
            if(prevRound != status.rounds && status.rounds % 20 == 0){
                triggerGovernmentRegulation(&econStatus,squares,players); 
            }
            prevRound = status.rounds;

            setLoanInterestRate(&econStatus);
            rollAndMove(players,squares,&status,&econStatus,nationalEvents);
            
            incrementRound(&status,players,squares,&econStatus);

            if(prevRound != status.rounds && status.rounds % 10 == 0){
                printMarketCondition(&econStatus);
                
            }
            if(prevRound != status.rounds && status.rounds % 15 == 0){
                triggerEconomicEvent(&econStatus,squares,econEvents);
            }
            
            status.turn++;
        
        
    }

    if(status.rounds == 500 && status.gameOver == NOT_GAME_OVER){
        gameDraw(players,squares,&status);
    }
    

    
   
}