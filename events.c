#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void initNationalEvents(NationalEvent nationalEvents[]){
    nationalEvents[0] = (NationalEvent){
        .name = "Tourism Hyper Card",
        .type = TOURISM_HYPE
    };
    nationalEvents[1] = (NationalEvent){
        .name = "Fuel Shortage Card",
        .type = FUEL_SHORTAGE
    };
    nationalEvents[2] = (NationalEvent){
        .name = "Heavy Floods Card",
        .type = HEAVY_FLOODS
    };
    nationalEvents[3] = (NationalEvent){
        .name = "Political Rally Card",
        .type = POLITICAL_RALLY
    };
    nationalEvents[4] = (NationalEvent){
        .name = "Stock Market Rise Card",
        .type = STOCK_MARKET_RISE
    };
    nationalEvents[5] = (NationalEvent){
        .name = "Economic Downturn Card",
        .type = ECONOMIC_DOWNTURN
    };
    nationalEvents[6] = (NationalEvent){
        .name = "Hotels Card",
        .type = HOUSING_SUBSIDY
    };
    nationalEvents[7] = (NationalEvent){
        .name = "Interest Rate Cut Card",
        .type = INTEREST_RATE_CUT
    };
    nationalEvents[8] = (NationalEvent){
        .name = "Interest Rate Increase Card",
        .type = INTEREST_RATE_INCREASE
    };
    nationalEvents[9] = (NationalEvent){
        .name = "Tax Amnesty Card",
        .type = TAX_AMNESTY
    };
    nationalEvents[10] = (NationalEvent){
        .name = "Power Failure Card",
        .type = POWER_FAILURE
    };
    nationalEvents[11] = (NationalEvent){
        .name = "Foreign Funding Card",
        .type = FOREIGN_FUNDING
    };
    nationalEvents[12] = (NationalEvent){
        .name = "Port Expansion Card",
        .type = PORT_EXPANSION
    };
    nationalEvents[13] = (NationalEvent){
        .name = "Festival Season Card",
        .type = FESTIVAL_SEASON
    };
    nationalEvents[14] = (NationalEvent){
        .name = "Labour Strike Card",
        .type = LABOUR_STRIKE
    };
    nationalEvents[15] = (NationalEvent){
        .name = "Insurance Discount Card",
        .type = INSURANCE_DISCOUNT
    };
    nationalEvents[16] = (NationalEvent){
        .name = "Property Valuation Card",
        .type = PROPERTY_REVALUATION
    };
    nationalEvents[17] = (NationalEvent){
        .name = "Currency Depreciation Card",
        .type = CURRENCY_DEPRECIATION
    };
    nationalEvents[18] = (NationalEvent){
        .name = "Government Grant Card",
        .type = GOVERNMENT_GRANT
    };
    nationalEvents[19] = (NationalEvent){
        .name = "National Disaster Card",
        .type = NATIONAL_DISASTER
    };
}
void initEconomicEvents(economicEvents econEvents[]){
    econEvents[0] = TOURISM_BOOM;
    econEvents[1] = FUEL_CRISIS;
    econEvents[2] = HEAVY_MONSOON;
    econEvents[3] = ECONOMIC_RECESSION;
    econEvents[4] = STOCK_MARKET_BOOM;
    econEvents[5] = GOVERNMENT_HOUSING_PROGRAMME;
    econEvents[6] = FOREIGN_INVESTMENT;
    econEvents[7] = POLITICAL_UNREST;
}
void triggerEconomicEvent(EconomicState *econ, Square squares[], economicEvents econEvents[]){
    
    int random = rand() % 8;
    econ->activeEconomicEvent = econEvents[random];

    printf("\nEconomic Event\n\n");
    switch(econ->activeEconomicEvent){
        case TOURISM_BOOM:
            printf("Tourism Boom\n");
            printf("Hotels receive double rent.\n");
            printf("Southern coastal properties increase in value by 15%%.\n\n");

            for(int i = 0; i<40; i++){
                if(squares[i].type == PROPERTY){
                    if(squares[i].data.property.numberOfHotels == 1){
                        squares[i].data.property.baseRental = roundOff(squares[i].data.property.baseRental * 2.0);
                    }
                    if(squares[i].data.property.groupID == 6){
                        squares[i].data.property.purchasePrice = roundOff(squares[i].data.property.purchasePrice * 1.15);
                        squares[i].data.property.mortgageValue = roundOff(squares[i].data.property.mortgageValue * 1.15);
                    }
            }
    }
            break;

        case FUEL_CRISIS:
            printf("Fuel Crisis\n");
            printf("Railway rent doubles.\n");
            printf("Property development costs increase by 20%%.\n\n");

            for(int i = 0; i<40; i++){
                switch(squares[i].type){
                    case RAILWAY:
                        squares[i].data.railway.baseRental = roundOff(squares[i].data.railway.baseRental * 2.0);
                    break;
                    case PROPERTY:
                        squares[i].data.property.houseConstructionCost = roundOff(squares[i].data.property.houseConstructionCost * 1.2);
                        squares[i].data.property.hotelConstructionCost = roundOff(squares[i].data.property.hotelConstructionCost * 1.2);
                    break;
               
                }
            }
            break;

        case HEAVY_MONSOON:
            printf("Heavy Floods Card\n");
            printf("Flood risk increases.\n");
            printf("Insurance premiums increase.\n");
            printf("Coastal properties lose 10%% value.\n\n");

            for(int i = 0; i<40; i++){
                switch(squares[i].type){
                    case INSURANCE:
                        squares[i].data.insurance.premium = roundOff(squares[i].data.insurance.premium * 1.1);
                        break;
                    case PROPERTY:
                        if(squares[i].data.property.groupID == 4 || squares[i].data.property.groupID == 6 || squares[i].data.property.groupID == 7){
                            squares[i].data.property.purchasePrice = roundOff(squares[i].data.property.purchasePrice * 0.9);
                            squares[i].data.property.mortgageValue = roundOff(squares[i].data.property.mortgageValue * 0.9);
                        }
                        break;
                }
            }   
            break;

        case ECONOMIC_RECESSION:
            printf("Economic Recession\n");
            printf("Property values decrease by 15%%.\n");
            printf("Rent decreases by 10%%.\n");
            printf("Loan interest increases by 15%%.\n\n");

            for(int i = 0; i<40; i++){
                if(squares[i].type == PROPERTY){
                    squares[i].data.property.baseValue = roundOff(squares[i].data.property.baseValue * 0.85);
                    squares[i].data.property.purchasePrice = roundOff(squares[i].data.property.purchasePrice * 0.85);
                    squares[i].data.property.baseRental = roundOff(squares[i].data.property.baseRental * 0.9);
                }
            }
            econ->currentLoanInterestRate = roundOff(econ->currentLoanInterestRate * 1.15);
            break;

        case STOCK_MARKET_BOOM:
            printf("Stock Market Boom\n");
            printf("Property values increase by 10%%.\n");
            printf("Loan interest decreases by 10%%.\n\n");

            for(int i = 0; i<40; i++){
                if(squares[i].type == PROPERTY){
                    squares[i].data.property.purchasePrice = roundOff(squares[i].data.property.purchasePrice * 1.1);
                }
            }
            econ->currentLoanInterestRate = roundOff(econ->currentLoanInterestRate * 0.9);
            break;

        case GOVERNMENT_HOUSING_PROGRAMME:
            printf("Government Housing Programme\n");
            printf("House construction costs reduced by 25%%.\n\n");

            for(int i = 0; i<40; i++){
                if(squares[i].type == PROPERTY){
                    squares[i].data.property.houseConstructionCost = roundOff(squares[i].data.property.houseConstructionCost * 0.75);
                }
            }
            break;
        case FOREIGN_INVESTMENT:
            printf("Foreign Investment\n");
            printf("Commercial properties increase in value by 20%%.\n\n");

            for(int i = 0; i<40; i++){
                if(squares[i].type == PROPERTY && squares[i].data.property.numberOfHotels == 1){
                    squares[i].data.property.purchasePrice = roundOff(squares[i].data.property.purchasePrice * 1.2);
                }
            }
            break;
        case POLITICAL_UNREST:
            printf("Political Unrest\n");
            printf("Riot probability doubles.\n");
            printf("Hotel occupancy decreases and hotel rent drops by 50%%.\n");
            printf("Business interruption claims increase.\n\n");

            for(int i = 0; i<40; i++){
                if(squares[i].type == PROPERTY && squares[i].data.property.numberOfHotels == 1){
                    squares[i].data.property.baseRental = roundOff(squares[i].data.property.baseRental * 0.5);
                }
            }
        
        break;
    }
}

void triggerNationalEvent(currentPlayer *player, currentPlayer players[], Square squares[], NationalEvent nationalEvents[], EconomicState *econ,int *cardIndex){

    NationalEvent card = nationalEvents[*cardIndex];
    *cardIndex = (*cardIndex + 1) % 20;

    printf("National Event Card\n\n");
    printf("%s\n", card.name);

    int duration = 15; 

    switch(card.type){

        case TOURISM_HYPE:
            printf("Hotels earn double rent for 5 rounds.\n\n");
            duration = 5;
            break;

        case FUEL_SHORTAGE:
            printf("Railway rent doubles for 5 rounds.\n\n");
            duration = 5;
            break;

        case HEAVY_FLOODS: {
            int coastalGroups[] = {4, 6, 7};
            int candidates[40], count = 0;
            for(int i = 0; i < 40; i++){
                if(squares[i].type == PROPERTY){
                    for(int k = 0; k < 3; k++){
                        if(squares[i].data.property.groupID == coastalGroups[k]){
                             candidates[count++] = i;
                        }
                    }
                }
            }
            if(count > 0){
                Property *p = &squares[candidates[rand() % count]].data.property;
                int repairCost = roundOff(p->baseValue * 0.2);
                p->isDamaged = 1;
                p->repairCost = repairCost;
                printf("%s flood damaged. Repair Cost : LKR %d.\n\n", p->name, repairCost);
            }
            duration = 0;
            break;
        }

        case POLITICAL_RALLY: {
            int candidates[40], count = 0;
            for(int i = 0; i < 40; i++){
                if(squares[i].type == PROPERTY){
                    candidates[count++] = i;
                }
            }
            if(count > 0){
                int id = candidates[rand() % count];
                squares[id].data.property.closedUntilRound = 2;
                printf("%s closed for 2 rounds.\n\n", squares[id].data.property.name);
            }
            duration = 2;
            break;
        }

        case STOCK_MARKET_RISE:
            printf("All property values increase by 10%%.\n\n");
            for(int i = 0; i < 40; i++)
                if(squares[i].type == PROPERTY){
                    squares[i].data.property.purchasePrice = roundOff((squares[i].data.property.purchasePrice) * 1.1);
                }
            duration = 15;
            break;

        case ECONOMIC_DOWNTURN:
            printf("Property values decrease by 15%%.\n\n");
            for(int i = 0; i < 40; i++)
                if(squares[i].type == PROPERTY) squares[i].data.property.baseValue = roundOff((squares[i].data.property.baseValue) * 0.85);
            duration = 15;
            break;

        case HOUSING_SUBSIDY:
            for(int i = 0; i < 40; i++){
                if(squares[i].type == PROPERTY){
                    squares[i].data.property.houseConstructionCost = roundOff((squares[i].data.property.houseConstructionCost )* 0.7);
                }
            }
            printf("House construction cost reduced by 30%% for 15 rounds.\n\n");
            duration = 15;
            break;

        case INTEREST_RATE_CUT:
            econ->currentLoanInterestRate = roundOff((econ->currentLoanInterestRate) * 0.98);
            printf("Loan interest reduced by 2%%.\n\n");
            duration = 15;
            break;

        case INTEREST_RATE_INCREASE:
            econ->currentLoanInterestRate = roundOff((econ->currentLoanInterestRate) * 1.02);
            printf("Loan interest increased by 2%%.\n\n");
            duration = 15;
            break;

        case TAX_AMNESTY:
            printf("Each player receives LKR 2,000.\n\n");
            for(int i = 0; i < 4; i++){
                players[i].money += 2000;
            }
            duration = 0;
            break;

        case POWER_FAILURE:
            econ->utilityIncome = 0.5;
            printf("Utility income halved for 3 rounds.\n\n");
            duration = 3;
            break;

        case FOREIGN_FUNDING:
            for(int i = 0; i < 40; i++){
                if(squares[i].type == PROPERTY && squares[i].data.property.numberOfHotels > 0){
                    squares[i].data.property.purchasePrice = roundOff((squares[i].data.property.purchasePrice) * 1.15);
                }
            }
            printf("Commercial property values increase by 15%% for 15 rounds.\n\n");
            duration = 15;
            break;

        case PORT_EXPANSION:
            printf("Railway station values increase by 20%%.\n\n");
            econ->railwayValueIncrement = 1.2;
            duration = 15;
            break;

        case FESTIVAL_SEASON:
            econ->hotelIncomeBoost = 1.5;
            printf("Hotels receive 50%% additional rent for 15 rounds.\n\n");
            duration = 15;
            break;

        case LABOUR_STRIKE:
            econ->constructionSuspended = 2;
            printf("Construction suspended for 2 rounds.\n\n");
            duration = 2;
            break;

        case INSURANCE_DISCOUNT:
            econ->insurancePremiumDiscount = 20;
            printf("Insurance premiums reduced by 20%% .\n\n");
            duration = 15;
            break;

        case PROPERTY_REVALUATION: {
            int groupID = (rand() % 8) + 1;
            printf("Property group %d appreciates by 15%%.\n\n", groupID);
            for(int i = 0; i < 40; i++){
                if(squares[i].type == PROPERTY && squares[i].data.property.groupID == groupID){
                    squares[i].data.property.baseValue = roundOff((squares[i].data.property.baseValue) * 1.15);
                    squares[i].data.property.purchasePrice = roundOff((squares[i].data.property.purchasePrice) * 1.15);
                }   
            }
            duration = 15;
            break;
        }

        case CURRENCY_DEPRECIATION:
            printf("Construction costs increase by 10%%.\n\n");
            for(int i = 0; i < 40; i++){
                if(squares[i].type == PROPERTY){
                    squares[i].data.property.houseConstructionCost = roundOff(squares[i].data.property.houseConstructionCost * 1.1);
                    squares[i].data.property.hotelConstructionCost = roundOff(squares[i].data.property.hotelConstructionCost * 1.1);
                }
            }
            duration = 15;
            break;

        case GOVERNMENT_GRANT: {
            int id = rand() % 4;
            players[id].money += 5000;
            printf("%s receives LKR 5,000.\n\n", getPlayer(players[id]));
            duration = 0;
            break;
        }

        case NATIONAL_DISASTER: {
            int candidates[40];
            int count = 0;
            for(int i = 0; i < 40; i++){
                if(squares[i].type == PROPERTY && (squares[i].data.property.numberOfHouses > 0 || squares[i].data.property.numberOfHotels > 0)){
                    candidates[count++] = i;
                }
            }
            if(count > 0){
                Property *property = &squares[candidates[rand() % count]].data.property;
                int repairCost = roundOff((property->purchasePrice) * 0.1);
                printf("property price %d: ",property->purchasePrice);
                property->isDamaged = 1;
                property->repairCost = repairCost;
                printf("%s damaged. Repair Cost : LKR %d.\n\n", property->name, repairCost);
            }
            duration = 0;
            break;
        }
    }

    if(duration > 0){
        for(int i = 0; i < 20; i++){
            if(player->activeNationalEvents[i].roundsRemaining <= 0){
                player->activeNationalEvents[i].type = card.type;
                player->activeNationalEvents[i].roundsRemaining = duration;
                break;
            }
        }
    }
}

void updateNationalEvents(currentPlayer players[]){
    for(int p = 0; p < 4; p++){
        for(int i = 0; i < 20; i++){
            if(players[p].activeNationalEvents[i].roundsRemaining > 0){
                players[p].activeNationalEvents[i].roundsRemaining--;
            }
        }
    }
}
int hasActiveNationalEvent(currentPlayer *player, activeNationalCardType type){
    for(int i = 0; i < 20; i++){
        if(player->activeNationalEvents[i].roundsRemaining > 0 && player->activeNationalEvents[i].type == type){
            return 1;
        }
    }
    return 0;
}
