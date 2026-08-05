#include "types.h"
#include <stdio.h>
#include <stdlib.h>


const int BID_VAL = 250;

void initPlayers(Square squares[40],currentPlayer players[4]){
    srand(0);

    players[0] = (currentPlayer){
        .ownedItems = {},
        .player = AGGRESSIVE_INVESTOR,
        .ownedLoans = {},
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
        .isBankrupt = 0

    };
    players[1] = (currentPlayer){
        .ownedItems = {},
        .player = CONSERVATIVE_BANKER,
        .ownedLoans = {},
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
        .isBankrupt = 0
    };
    players[2] = (currentPlayer){
        .ownedItems = {},
        .player = RISK_TAKER,
        .ownedLoans = {},
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
        .isBankrupt = 0
    };
    players[3] = (currentPlayer){
        .ownedItems = {},
        .player = OPPORTUNISTIC_TRADER,
        .ownedLoans = {},
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
        .isBankrupt = 0
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
            player->lastDieVal = dice1+dice2;

        }
        printf("%s rolls %d. \n", getPlayer(*player), dice1+dice2);
    
        
    }
}
//bidding logics for players
void AGG_BIDDING(Auction *auction, currentPlayer *player,int player_index){
    //check whether if property,...
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

void CON_BIDDING(Auction *auction, currentPlayer *player,int player_index){
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
void RISK_BIDDING(Auction *auction, currentPlayer *player,int player_index){
    //DUMMY
    
}
void OPP_BIDDING(Auction *auction, currentPlayer *player,int player_index){
    //DUMMY
    
}

//rent calculation
void payRentAndPrint(int rent,char name[],currentPlayer players[],currentPlayer *owner,currentPlayer *currentPlayer,Square *square){
    if(rent != 0){
           if(currentPlayer->money >= rent){
               currentPlayer->money -= rent;
               owner->money += rent;
               
               printf("\n%s landed on %s.\n", getPlayer(*currentPlayer),name);
               printf("Rent Paid : LKR %d.\n", rent);
               printf("Owner : %s.\n", getPlayer(*owner));
           }
           else{
             
           }
           
       }
}
 void payRent(currentPlayer players[],currentPlayer *currentPlayer,Square *square,int playerIndex){
       int rent = 0;
       int ownerID = -1;
       Player owner;

       switch(square->type){
           case PROPERTY:
               if(square->data.property.owner != players[playerIndex].player  && square->data.property.mortgageStatus == UNMORTGAGED && square->data.property.owner != -1){
                int baseRent = square->data.property.baseRental;
                int houses = square->data.property.numberOfHouses;
                int hotels = square->data.property.numberOfHotels;
                
                owner = square->data.property.owner;
                
                for(int i=0; i<4; i++){
                        if(players[i].player == owner){
                            ownerID = i;
                            break;
                        }
                    }
                
                if(hotels == 1){
                    rent = 10*baseRent;
                    break;
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
                payRentAndPrint(rent,square->data.property.name,players,&players[ownerID],currentPlayer,square);
               }
               
               break;

            case RAILWAY:
                if(square->data.railway.owner != players[playerIndex].player && square->data.railway.mortgageStatus == UNMORTGAGED && square->data.railway.owner != -1){
                    int baseRent = square->data.railway.baseRental;
                    owner = square->data.railway.owner;

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
                    payRentAndPrint(rent,square->data.railway.name,players,&players[ownerID],currentPlayer,square);
                }

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
                       
                        payRentAndPrint(rent,square->data.utility.name,players,&players[ownerID],currentPlayer,square);
                        
                    }
                }
       }
       
   }
//

void buyProperty(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]){
    int current_pos = current_player->position;

    switch(current_player->player){
        case AGGRESSIVE_INVESTOR:
            if(squares[current_pos].data.property.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.property.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.property.purchasePrice;
                    int maxRentSqID = -1;
                    int maxRent = 0;

                    for(int i=0; i<4; i++){
                        if(squares[i].type == PROPERTY && squares[i].data.property.owner != -1 && squares[i].data.property.mortgageStatus == UNMORTGAGED && squares[i].data.property.owner!=player_index){
                            if(squares[i].data.property.baseRental > maxRent){
                            maxRent = squares[i].data.property.baseRental;
                            maxRentSqID = i;
                            }
                        }
                    }
                    
                    if(remain >= maxRent){
                        squares[current_pos].data.property.owner = AGGRESSIVE_INVESTOR;
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
            //to be continued
        break;
    }
}
void buyRailway(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]){
    int current_pos = current_player->position;

    switch(current_player->player){
        case AGGRESSIVE_INVESTOR:
            if(squares[current_pos].data.property.mortgageStatus == UNMORTGAGED){
                if(squares[current_pos].data.railway.owner == -1){
                    int remain = current_player->money - squares[current_pos].data.railway.purchasePrice;
                    int maxRentSqID = -1;
                    int maxRent = 0;

                    for(int i=0; i<4; i++){
                        if(squares[i].type == PROPERTY && squares[i].data.property.owner != -1 && squares[i].data.property.mortgageStatus == UNMORTGAGED && squares[i].data.property.owner!=player_index){
                            if(squares[i].data.property.baseRental > maxRent){
                            maxRent = squares[i].data.property.baseRental;
                            maxRentSqID = i;
                            }
                        }
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
             if(squares[current_pos].data.property.mortgageStatus == UNMORTGAGED){
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
            //to be continued
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

                    for(int i=0; i<4; i++){
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

                    if(remain >= 0){
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
            //to be continued
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





