#include "types.h"
#include <stdio.h>
#include <stdlib.h>


const int BID_VAL = 250;

void initPlayers(Square squares[40],currentPlayer players[4]){
    players[0] = (currentPlayer){
        .player = AGGRESSIVE_INVESTOR,
        .ownedInsurance = {},
        .lastPosition = 0,
        .position = 0,
        .money = 30000,    
        .lastDieVal = 0,
        .currentRound = 1,
        .lastRound = 0,
        .utilityCount = 0,
        .propertiesCount = 0,
        .railwaysCount = 0,
        .isBankrupt = NOTBANKRUPT,
        .jailedTurn = -1,
        .inJail = NOTIN_JAIL,
        .isLoanActive = 0

    };
    players[1] = (currentPlayer){
        .player = CONSERVATIVE_BANKER,
        .ownedInsurance = {},
        .lastPosition = 0,
        .position = 0,
        .money = 30000,    
        .lastDieVal = 0,
        .currentRound = 1,
        .lastRound = 0,
        .utilityCount = 0,
        .propertiesCount = 0,
        .railwaysCount = 0,
        .isBankrupt = NOTBANKRUPT,
        .jailedTurn = -1,
        .inJail = NOTIN_JAIL,
        .isLoanActive = 0
    };
    players[2] = (currentPlayer){
        .player = RISK_TAKER,
        .ownedInsurance = {},
        .lastPosition = 0,
        .position = 0,
        .money = 30000,    
        .lastDieVal = 0,
        .currentRound = 1,
        .lastRound = 0,
        .utilityCount = 0,
        .propertiesCount = 0,
        .railwaysCount = 0,
        .isBankrupt = NOTBANKRUPT,
        .jailedTurn = -1,
        .inJail = NOTIN_JAIL,
        .isLoanActive = 0
    };
    players[3] = (currentPlayer){
        .player = OPPORTUNISTIC_TRADER,
        .ownedInsurance = {},
        .lastPosition = 0,
        .position = 0,
        .money = 30000,    
        .lastDieVal = 0,
        .currentRound = 1,
        .lastRound = 0,
        .utilityCount = 0,
        .propertiesCount = 0,
        .railwaysCount = 0,
        .isBankrupt = NOTBANKRUPT,
        .jailedTurn = -1,
        .inJail = NOTIN_JAIL,
        .isLoanActive = 0
    };

    printf("\nMONOPOLY-LK Simulation \n\n");
    for(int i = 0; i<4; i++){
        printf("Player %d : %s \n", i+1, getPlayer(players[i]));
    }
    printf("\n");
    printf("Each player begins with LKR 30,000 \n\n");

    
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

void diceRoll(currentPlayer *player, Square squares[]){
    int dice1 = 0;
    int dice2 = 0;
    
    int same_val = 1;
    
    while(same_val == 1){
        dice1 = rand() % 6 + 1;
        dice2 = rand() % 6 + 1;

        int pos = player->position;
    
        Data current_square_data = squares[pos].data;  
    

        if(dice1 == dice2){
            if(current_square_data.special.type == JAIL_JUST_VISITING && player->inJail == IN_JAIL){
                same_val = 0;
                releaseFromJail(player);
            }
            else{
                same_val = 1;
            }
        }
        else{
            same_val = 0;
            if(player->inJail == NOTIN_JAIL){
                player->lastPosition = player->position;
                player->position = player->lastPosition + dice1+dice2;
                player->lastDieVal = dice1+dice2;
            }
            

        }

        
    }
    if(player->inJail == NOTIN_JAIL){
            printf("%s rolls %d. \n", getPlayer(*player), dice1+dice2);
    }
}

void AGG_BIDDING(Auction *auction, currentPlayer *player,int player_index){
    if(auction->AGGRESSIVE_INVESTOR_BID != -1 && auction->lastBidder == AGGRESSIVE_INVESTOR){
        if(auction->RISK_TAKER_BID == -1 && auction->OPPORTUNISTIC_TRADER_BID == -1 && auction->CONSERVATIVE_BANKER_BID == -1){
            printf("%s bids won LKR %d.\n", getPlayer(*player), auction->AGGRESSIVE_INVESTOR_BID);
            auction->status = 0;
        }
    }
    else if(auction->currentBid+BID_VAL <= auction->square.data.property.purchasePrice * 1.2){
        if((auction->currentBid)+BID_VAL <= player->money){
            auction->AGGRESSIVE_INVESTOR_BID = auction->currentBid + BID_VAL;
            auction->currentBid = auction->currentBid + BID_VAL;
            auction->lastBidder = AGGRESSIVE_INVESTOR;
            printf("%s bids LKR %d.\n\n", getPlayer(*player), auction->AGGRESSIVE_INVESTOR_BID);
        }
        else{
            auction->AGGRESSIVE_INVESTOR_BID = -1;
            printf("%s withdraws.\n", getPlayer(*player));
        }
    }
    else if(auction->square.type == PROPERTY && auction->square.data.property.owner == -1 && auction->square.data.property.mortgageStatus == UNMORTGAGED && (auction->square.data.property.groupID == 6 || auction->square.data.property.groupID == 8)){
        if((auction->currentBid)+BID_VAL <= player->money){
            auction->AGGRESSIVE_INVESTOR_BID = auction->currentBid + BID_VAL;
            auction->currentBid = auction->currentBid + BID_VAL;
            auction->lastBidder = AGGRESSIVE_INVESTOR;
            printf("%s bids LKR %d.\n\n", getPlayer(*player), auction->AGGRESSIVE_INVESTOR_BID);
        }
        else{
            auction->AGGRESSIVE_INVESTOR_BID = -1;
            printf("%s withdraws.\n", getPlayer(*player));
        }
    }
    else{
        auction->AGGRESSIVE_INVESTOR_BID = -1;
    }
    
}

void CON_BIDDING(Auction *auction, currentPlayer *player,int player_index){
    if(auction->CONSERVATIVE_BANKER_BID != -1 && auction->lastBidder == CONSERVATIVE_BANKER){
        if(auction->RISK_TAKER_BID == -1 && auction->OPPORTUNISTIC_TRADER_BID == -1 && auction->AGGRESSIVE_INVESTOR_BID == -1){
            auction->status = 0;
        }
    }

    else if((auction->currentBid)+BID_VAL <= auction->square.data.property.purchasePrice){
        if((auction->currentBid)+BID_VAL <= player->money){
            auction->CONSERVATIVE_BANKER_BID = auction->currentBid + BID_VAL;
            auction->currentBid = auction->currentBid + BID_VAL;
            auction->lastBidder = CONSERVATIVE_BANKER;

            printf("%s place bids LKR %d.\n\n", getPlayer(*player), auction->CONSERVATIVE_BANKER_BID);
        }
        else{
            auction->CONSERVATIVE_BANKER_BID = -1;
            printf("%s withdraws.\n", getPlayer(*player));
        }
    }
    else{
        auction->CONSERVATIVE_BANKER_BID = -1;
        printf("%s withdraws.\n", getPlayer(*player));
    }
}
void RISK_BIDDING(Auction *auction, currentPlayer *player,int player_index){
    if(auction->RISK_TAKER_BID != -1 && auction->lastBidder == RISK_TAKER){
        if(auction->AGGRESSIVE_INVESTOR_BID == -1 && auction->CONSERVATIVE_BANKER_BID == -1 && auction->OPPORTUNISTIC_TRADER_BID == -1){
            auction->status = 0;
        }
    }
    else if((auction->currentBid) + BID_VAL <= player->money){
        auction->RISK_TAKER_BID = auction->currentBid + BID_VAL;
        auction->currentBid = auction->currentBid + BID_VAL;
        auction->lastBidder = RISK_TAKER;
        printf("%s bids LKR %d.\n\n", getPlayer(*player), auction->RISK_TAKER_BID);
    }
    else{
        auction->RISK_TAKER_BID = -1;
        printf("%s withdraws.\n", getPlayer(*player));
    }
    
}
void OPP_BIDDING(Auction *auction, currentPlayer *player,int player_index){

    if(auction->OPPORTUNISTIC_TRADER_BID != -1 && auction->lastBidder == OPPORTUNISTIC_TRADER){
        if(auction->AGGRESSIVE_INVESTOR_BID == -1 && auction->CONSERVATIVE_BANKER_BID == -1 && auction->RISK_TAKER_BID == -1){
            auction->status = 0;
        }
    }
    else if((auction->currentBid) + BID_VAL <= auction->square.data.property.purchasePrice || auction->square.data.property.purchasePrice < auction->square.data.property.baseValue){
        if((auction->currentBid) + BID_VAL <= player->money){
            auction->OPPORTUNISTIC_TRADER_BID = auction->currentBid + BID_VAL;
            auction->currentBid = auction->currentBid + BID_VAL;
            auction->lastBidder = OPPORTUNISTIC_TRADER;
            printf("%s bids LKR %d.\n\n", getPlayer(*player), auction->OPPORTUNISTIC_TRADER_BID);
        }
        else{
            auction->OPPORTUNISTIC_TRADER_BID = -1;
            printf("%s withdraws.\n", getPlayer(*player));
        }
    }
    else{
        auction->OPPORTUNISTIC_TRADER_BID = -1;
        printf("%s withdraws.\n", getPlayer(*player));
    }
    
}


void payRentAndPrint(int rent,char name[],currentPlayer players[],currentPlayer *owner,currentPlayer *currentPlayer,Square squares[],Square *square){
    if(rent != 0){
           if(currentPlayer->money >= rent){
               currentPlayer->money -= rent;
               owner->money += rent;
               
               printf("\n%s landed on %s.\n", getPlayer(*currentPlayer),name);
               printf("Rent Paid : LKR %d.\n", rent);
               printf("Owner : %s.\n\n", getPlayer(*owner));
           }
           else{
              collectDebt(currentPlayer, owner, squares, rent);
           }
           checkBankrupt(currentPlayer,squares);
           
       }
}
 void payRent(currentPlayer players[],currentPlayer *currentPlayer,Square *square,int playerIndex,Square squares[],EconomicState *econ){
       int rent = 0;
       int ownerID = -1;
       Player owner;

       switch(square->type){
           case PROPERTY:
               if(square->data.property.owner != players[playerIndex].player  && square->data.property.mortgageStatus == UNMORTGAGED && square->data.property.owner != -1 && square->data.property.isDamaged == 0){
                int baseRent = square->data.property.baseRental;
                int houses = square->data.property.numberOfHouses;
                int hotels = square->data.property.numberOfHotels;
                
                owner = square->data.property.owner;
                int ownerIndex = -1;
                for(int i=0; i<4; i++){
                    if(players[i].player == square->data.property.owner){
                        ownerIndex = i;
                    break;
                    }
                }

                int tourismHyperCard = hasActiveNationalEvent(&players[ownerIndex], TOURISM_HYPE);
                int festivalCard = hasActiveNationalEvent(&players[ownerIndex],FESTIVAL_SEASON);
                int hotelRentFactor = 1;
                if(tourismHyperCard == 1){
                    hotelRentFactor += econ->hotelIncomeBoost;
                    if(hotelRentFactor <=0){
                        hotelRentFactor = 1;
                    }
                }
                if(festivalCard == 1){
                    hotelRentFactor += econ->hotelIncomeBoost;
                    if(hotelRentFactor <=0){
                        hotelRentFactor = 1;
                    }
                }
                
                for(int i=0; i<4; i++){
                        if(players[i].player == owner){
                            ownerID = i;
                            break;
                        }
                    }
                
                if(hotels == 1){
                    rent = 10*baseRent*hotelRentFactor;
                }
                switch(houses){
                    case 0:
                      rent = baseRent;
                      break;
                    case 1:
                      rent = baseRent * 2;
                      break;
                    case 2:
                      rent = baseRent * 3;
                      break;
                    case 3:
                      rent = baseRent * 5;
                      break;
                    case 4:
                      rent = baseRent * 7;
                      break;
                }
                payRentAndPrint(rent,square->data.property.name,players,&players[ownerID],currentPlayer,squares,square);
               }
               
               break;

            case RAILWAY:
                if(square->data.railway.owner != players[playerIndex].player && square->data.railway.mortgageStatus == UNMORTGAGED && square->data.railway.owner != -1){
                    int baseRent = square->data.railway.baseRental;
                    
                    owner = square->data.railway.owner;
                    int rentFactor = 1;
                    int ownerIndex = -1;
                    for(int i=0; i<4; i++){
                        if(players[i].player == square->data.property.owner){
                            ownerIndex = i;
                        break;
                        }
                    }
                    int isCardActive = hasActiveNationalEvent(&players[ownerIndex], PORT_EXPANSION);
                    if(isCardActive == 1){
                        rentFactor = econ->railwayValueIncrement;
                        if(rentFactor <=0){
                            rentFactor = 1;
                        }
                    }
                    for(int i=0; i<4; i++){
                        if(players[i].player == owner){
                            ownerID = i;
                            break;
                        }
                    }
                    int ownedRailways = players[ownerID].railwaysCount;
                    switch(ownedRailways){
                        case 1:
                            rent = 250;
                            break;
                        case 2:
                            rent = 500;
                            break;
                        case 3:
                            rent = 1000;
                            break;
                        case 4:
                            rent = 2000;
                            break;
                    }
                    rent = roundOff(rent*rentFactor);
                    payRentAndPrint(rent,square->data.railway.name,players,&players[ownerID],currentPlayer,squares,square);
                }
                break;

            case UTILITY:
                if(square->data.utility.owner != players[playerIndex].player && square->data.utility.mortgageStatus == UNMORTGAGED && square->data.utility.owner != -1){
                    owner = square->data.utility.owner;

                    for(int i=0; i<4; i++){
                        if(players[i].player == owner){
                            ownerID = i;
                            break;
                        }
                    }
                    int ownedUtilities = players[ownerID].utilityCount;
                    if(ownedUtilities != 0){
                        if(ownedUtilities == 1){
                            rent = 4*currentPlayer->lastDieVal;

                        }
                        else{
                            rent = 10*currentPlayer->lastDieVal;
                        }
                        if(econ->utilityRentMultiplier > 0){
                            rent = roundOff(rent*(1 + (econ->utilityRentMultiplier/100.0))); 
                        } 
                        payRentAndPrint(rent,square->data.utility.name,players,&players[ownerID],currentPlayer,squares,square);
                        
                    }
                }
                break;
       }
       
   }

int getMaxRent(Square squares[],currentPlayer *cPlayer) {
    int maxRent = 0;
    for (int i = 0; i < 40; i++) {
        if (squares[i].type == PROPERTY && squares[i].data.property.owner != cPlayer->player && squares[i].data.property.owner != -1 && squares[i].data.property.baseRental > maxRent) {
            maxRent = squares[i].data.property.baseRental;
        }
    }
    return maxRent;
}

int getOwnedItems(Square squares[], currentPlayer *current_player) {
    int items = 0;
    for(int i=0; i<40; i++){
        switch(squares[i].type){
            case PROPERTY:
                if(squares[i].data.property.owner == current_player->player && squares[i].data.property.mortgageStatus == UNMORTGAGED && squares[i].data.property.isLocked == NOT_LOAN_LOCKED){
                    items++;
                }
            break;
            case RAILWAY:
                if(squares[i].data.railway.owner == current_player->player && squares[i].data.railway.mortgageStatus == UNMORTGAGED && squares[i].data.railway.isLocked == NOT_LOAN_LOCKED){
                    items++;
                }
            break;
            case UTILITY:
                if(squares[i].data.utility.owner == current_player->player && squares[i].data.utility.mortgageStatus == UNMORTGAGED && squares[i].data.utility.isLocked == NOT_LOAN_LOCKED){
                    items++;
                }
            break;
        }
    }
    return items;
}
int getTotalPropertyValue(Square squares[], currentPlayer *current_player){
    int value = 0;
    for(int i=0; i<40; i++){
        switch(squares[i].type){
            case PROPERTY:
                if(squares[i].data.property.owner == current_player->player){
                    value += squares[i].data.property.purchasePrice;
                }
            break;
            case RAILWAY:
                if(squares[i].data.railway.owner == current_player->player){
                    value += squares[i].data.railway.purchasePrice;
                }
            break;
            case UTILITY:
                if(squares[i].data.utility.owner == current_player->player){
                    value += squares[i].data.utility.purchasePrice;
                }
            break;
        }
    }
    return value;
}
void buyProperty(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]){
    int current_pos = current_player->position;

    switch(current_player->player){
        case AGGRESSIVE_INVESTOR:
            if(squares[current_pos].data.property.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.property.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.property.purchasePrice;
                    int oneRentBuffer = squares[current_pos].data.property.baseRental;
                    if(remain >= oneRentBuffer){
                        squares[current_pos].data.property.owner = AGGRESSIVE_INVESTOR;
                        current_player->money -= squares[current_pos].data.property.purchasePrice;
                        current_player->propertiesCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.property.name, squares[current_pos].data.property.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                }
        else{
            startAuction(&squares[current_pos], players);
        }
    
    }
        break;

        case CONSERVATIVE_BANKER:
            if(squares[current_pos].data.property.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.property.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.property.purchasePrice;
                    int cash = current_player->money;

                    if(remain >= roundOff(cash*0.5)){
                        squares[current_pos].data.property.owner = CONSERVATIVE_BANKER;
                        current_player->money -= squares[current_pos].data.property.purchasePrice;
                        current_player->propertiesCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.property.name, squares[current_pos].data.property.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;

        case RISK_TAKER:
             if(squares[current_pos].data.property.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.property.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.property.purchasePrice;

                    if(remain >= 0){
                        squares[current_pos].data.property.owner = RISK_TAKER;
                        current_player->money -= squares[current_pos].data.property.purchasePrice;
                        current_player->propertiesCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.property.name, squares[current_pos].data.property.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;
        case OPPORTUNISTIC_TRADER:
            if(squares[current_pos].data.property.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.property.owner == -1){
                    if(squares[current_pos].data.property.baseRental > squares[current_pos].data.property.houseConstructionCost){
                    
                        int remain = current_player->money - squares[current_pos].data.property.purchasePrice;

                        if(remain >= 0){
                            squares[current_pos].data.property.owner = OPPORTUNISTIC_TRADER;
                            current_player->money -= squares[current_pos].data.property.purchasePrice;
                            current_player->propertiesCount++;
                            printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.property.name, squares[current_pos].data.property.purchasePrice);
                            printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                        }
                        else{
                            startAuction(&squares[current_pos], players);
                        }
                    }
                }
            }
        break;
    }
}
void buyRailway(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]){
    int current_pos = current_player->position;

    switch(current_player->player){
        case AGGRESSIVE_INVESTOR:
            if(squares[current_pos].data.railway.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.railway.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.railway.purchasePrice;
                    int ownedRailways = players[player_index].railwaysCount;
                    int maxRent = 250;
                    switch(ownedRailways){
                        case 1:
                            maxRent = 250;
                            break;
                        case 2:
                            maxRent = 500;
                            break;
                        case 3:
                            maxRent = 1000;
                            break;
                        case 4:
                            maxRent = 2000;
                            break;
                    }

                    if(remain >= maxRent){
                        squares[current_pos].data.railway.owner = AGGRESSIVE_INVESTOR;
                        current_player->money -= squares[current_pos].data.railway.purchasePrice;
                        current_player->railwaysCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.railway.name, squares[current_pos].data.railway.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;

        case CONSERVATIVE_BANKER:
            if(squares[current_pos].data.railway.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.railway.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.railway.purchasePrice;
                    int cash = current_player->money;

                    if(remain >= roundOff(cash*0.5)){
                        squares[current_pos].data.railway.owner = CONSERVATIVE_BANKER;
                        current_player->money -= squares[current_pos].data.railway.purchasePrice;
                        current_player->railwaysCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.railway.name, squares[current_pos].data.railway.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;

        case RISK_TAKER:
             if(squares[current_pos].data.railway.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.railway.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.railway.purchasePrice;

                    if(remain >= 0){
                        squares[current_pos].data.railway.owner = RISK_TAKER;
                        current_player->money -= squares[current_pos].data.railway.purchasePrice;
                        current_player->railwaysCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.railway.name, squares[current_pos].data.railway.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;
        case OPPORTUNISTIC_TRADER:
            if(squares[current_pos].data.railway.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.railway.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.railway.purchasePrice;

                    if(remain >= 0 && current_player->railwaysCount == 0){
                        squares[current_pos].data.railway.owner = OPPORTUNISTIC_TRADER;
                        current_player->money -= squares[current_pos].data.railway.purchasePrice;
                        current_player->railwaysCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.railway.name, squares[current_pos].data.railway.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        
        break;
    }
}
void buyUtility(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]){
    int current_pos = current_player->position;

    switch(current_player->player){
        case AGGRESSIVE_INVESTOR:
            if(squares[current_pos].data.utility.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.utility.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.utility.purchasePrice;
                    int maxRentSqID = -1;
                    int maxRent = 0;

                    for(int i=0; i<40; i++){
                        if(squares[i].type == PROPERTY && squares[i].data.property.owner != -1 && squares[i].data.property.mortgageStatus == UNMORTGAGED && squares[i].data.property.owner!=player_index){
                            if(squares[i].data.property.baseRental > maxRent){
                            maxRent = squares[i].data.property.baseRental;
                            maxRentSqID = i;
                            }
                        }
                    }

                    if(remain >= maxRent){
                        squares[current_pos].data.utility.owner = AGGRESSIVE_INVESTOR;
                        current_player->money -= squares[current_pos].data.utility.purchasePrice;
                        current_player->utilityCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.utility.name, squares[current_pos].data.utility.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;

        case CONSERVATIVE_BANKER:
            if(squares[current_pos].data.utility.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.utility.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.utility.purchasePrice;
                    int cash = current_player->money;

                    if(remain >= roundOff(cash*0.5)){
                        squares[current_pos].data.utility.owner = CONSERVATIVE_BANKER;
                        current_player->money -= squares[current_pos].data.utility.purchasePrice;
                        current_player->utilityCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.utility.name, squares[current_pos].data.utility.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;

        case RISK_TAKER:
             if(squares[current_pos].data.utility.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.utility.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.utility.purchasePrice;

                    if(remain >= 0 && current_player->utilityCount == 0){
                        squares[current_pos].data.utility.owner = RISK_TAKER;
                        current_player->money -= squares[current_pos].data.utility.purchasePrice;
                        current_player->utilityCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.utility.name, squares[current_pos].data.utility.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;
        case OPPORTUNISTIC_TRADER:
            if(squares[current_pos].data.utility.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.utility.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.utility.purchasePrice;

                    if(remain >= 0){
                        squares[current_pos].data.utility.owner = OPPORTUNISTIC_TRADER;
                        current_player->money -= squares[current_pos].data.utility.purchasePrice;
                        current_player->utilityCount++;
                        printf("%s purchases %s for LKR %d.\n", getPlayer(*current_player), squares[current_pos].data.utility.name, squares[current_pos].data.utility.purchasePrice);
                        printf("Remaining Balance : LKR %d.\n\n", current_player->money);
                    }
                    else{
                        startAuction(&squares[current_pos], players);
                    }
                }
            }
        break;
    }
}
void buy(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]){
    int current_pos = current_player->position;
    //property buying logic
    switch(squares[current_pos].type){
        case PROPERTY:
            buyProperty(squares,current_player,player_index,players);
        break;
        case RAILWAY:
            buyRailway(squares,current_player,player_index,players);
        break;
        case UTILITY:
            buyUtility(squares,current_player,player_index,players);
        break;
    }
}

void handleJail(Square *square, currentPlayer *cPlayer,currentStatus *status,EconomicState *econStatus) {
    
      if(square->type == SPECIAL && square->data.special.type == GO_TO_JAIL){
        cPlayer->inJail = IN_JAIL;
        cPlayer->position = 10;
        cPlayer->jailedTurn = status->turn;
        printf("%s has been sent to Jail.\n", getPlayer(*cPlayer));

        if(cPlayer->player == AGGRESSIVE_INVESTOR || cPlayer->player == RISK_TAKER){
            if(cPlayer->money >= 300){
                cPlayer->money -= 300;
                cPlayer->inJail = NOTIN_JAIL;
                printf("%s has been released from jail after paying 300 LKR.\n", getPlayer(*cPlayer));
            }
        }
        else if(cPlayer->player == OPPORTUNISTIC_TRADER){
            if(cPlayer->money >= 300 && econStatus->currentInflationRate <= 2){
                cPlayer->money -= 300;
                cPlayer->inJail = NOTIN_JAIL;
                printf("%s has been released from jail after paying 300 LKR.\n", getPlayer(*cPlayer));
            }
        }

      }


}
void releaseFromJail(currentPlayer *currentPlayer){
    if(currentPlayer->inJail == IN_JAIL){
        currentPlayer->inJail = NOTIN_JAIL;
        printf("%s has been released from jail.\n", getPlayer(*currentPlayer));
    }
}
void checkAndReleaseFromJail(currentPlayer *currentPlayer,currentStatus *status){
    if(currentPlayer->inJail == IN_JAIL){
        if(currentPlayer->jailedTurn +4 == status->turn){
            currentPlayer->inJail = NOTIN_JAIL;
            printf("%s has been released from jail after 3 turns.\n", getPlayer(*currentPlayer));
        }
    }
}
void handleBank(Square squares[],Square *square, currentPlayer *cPlayer,currentStatus *status,EconomicState *econStatus) {
    if(square->type == BANK){    
        if(cPlayer->isLoanActive == 1){
            int repayAmount = wantToRepay(squares,cPlayer,econStatus);
            if(repayAmount != 0){
                switch(cPlayer->player){
                    case AGGRESSIVE_INVESTOR:
                        repayLoan(cPlayer,squares,repayAmount);
                        break;
                    case CONSERVATIVE_BANKER:
                        repayLoan(cPlayer,squares,repayAmount);
                        break;
                    case RISK_TAKER:
                        repayLoan(cPlayer,squares,repayAmount);
                        break;
                    case OPPORTUNISTIC_TRADER:
                        repayLoan(cPlayer,squares,repayAmount);
                        break;
                }
            }
        }
        else if(isLoanNeeded(cPlayer,squares,econStatus) == 1){
            obtainLoan(cPlayer,squares,cPlayer->money,econStatus);
            cPlayer->isLoanActive = 1;
        }
    }
}




int countPropertiesInGroup(Square squares[], int groupID){
    int count = 0;
    for (int i = 0; i < 40; i++) {
        if (squares[i].type == PROPERTY && squares[i].data.property.groupID == groupID) {
            count++;
        }
    }
    return count;
}

int countOwnedInGroup(Square squares[], Player player, int groupID){
    int count = 0;
    for (int i = 0; i < 40; i++) {
        if (squares[i].type == PROPERTY && squares[i].data.property.groupID == groupID &&
            squares[i].data.property.owner == player) {
            count++;
        }
    }
    return count;
}

int getMinHousesInGroup(Square squares[], Player player, int groupID){
    int minHouses = 4;
    for (int i = 0; i < 40; i++) {
        if (squares[i].type == PROPERTY && squares[i].data.property.groupID == groupID &&
            squares[i].data.property.owner == player) {
            if (squares[i].data.property.numberOfHouses < minHouses) {
                minHouses = squares[i].data.property.numberOfHouses;
            }
        }
    }
    return minHouses;
}


int canBuildHouse(Square squares[], currentPlayer *player, int index){
    Property *property = &squares[index].data.property;

    if(property->owner == player->player && property->mortgageStatus == UNMORTGAGED && property->numberOfHouses < 4 && property->numberOfHotels == 0){
        if (countOwnedInGroup(squares, player->player, property->groupID) == countPropertiesInGroup(squares, property->groupID)){
            if (property->numberOfHouses <= getMinHousesInGroup(squares, player->player, property->groupID)){
                 return (player->money >= property->houseConstructionCost);
            }
        }
    }  
    return 0;
}

int canBuildHotel(Square squares[], currentPlayer *player, int index){
    Property *property = &squares[index].data.property;

    if(property->owner == player->player && property->mortgageStatus == UNMORTGAGED && property->numberOfHouses == 4 && property->numberOfHotels == 0){
        if(countOwnedInGroup(squares, player->player, property->groupID) == countPropertiesInGroup(squares, property->groupID)){
          return (player->money >= property->hotelConstructionCost);
        }
    }
    return 0;
}

void buildHouse(Square squares[], currentPlayer *player, int index){
    Property *property = &squares[index].data.property;

    player->money -= property->houseConstructionCost;
    property->numberOfHouses++;
    player->numberOfHouses++;

    printf("%s constructed one house on %s.\n", getPlayer(*player), property->name);
    printf("Construction Cost : LKR %d.\n\n", property->houseConstructionCost);
}

void buildHotel(Square squares[], currentPlayer *player, int index){
    Property *property = &squares[index].data.property;

    player->money -= property->hotelConstructionCost;
    property->numberOfHouses = 0;
    property->numberOfHotels = 1;
    player->numberOfHotels++;

    printf("%s upgraded %s to a Hotel.\n\n", getPlayer(*player), property->name);
    
}


void handleConstruction(Square squares[], currentPlayer *player, EconomicState *econ){
    int index = player->position;

    if(squares[index].type == PROPERTY && squares[index].data.property.owner == player->player){

    int wantsToBuild = 0;
    int inflationLow = 0;
    int subsidyActive = 0;
    
    switch (player->player) {
        case AGGRESSIVE_INVESTOR:
            wantsToBuild = 1;
            break;

        case CONSERVATIVE_BANKER:
            wantsToBuild = 1;
            break;

        case RISK_TAKER:
            wantsToBuild = 1;
            break;

        case OPPORTUNISTIC_TRADER: {
            
            inflationLow = (econ->currentInflationRate <= 0);
            subsidyActive = hasActiveNationalEvent(player, HOUSING_SUBSIDY);
            wantsToBuild = (inflationLow || subsidyActive);
            break;
        }
    }

    if (wantsToBuild){       
        if (canBuildHotel(squares, player, index)){
            if (player->player == CONSERVATIVE_BANKER && player->ownedLoan.isActive == 0) {
                buildHotel(squares, player, index);
            }else if(player->player != CONSERVATIVE_BANKER && player->player != OPPORTUNISTIC_TRADER){
                buildHotel(squares, player, index);
            }else{
                if(inflationLow){
                    buildHotel(squares, player, index);
                }
            }
        }

        if (canBuildHouse(squares, player, index)){
            buildHouse(squares, player, index);
        }
    }
}
}