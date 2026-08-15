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
//insurance and flood rish to be implemented
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