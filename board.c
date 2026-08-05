#include "types.h"
#include <stdio.h>


void initBoard(Square squares[],currentPlayer players[]){
    squares[0] = (Square){
        .type = START,
    
    };
    squares[1] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 1500,
                .baseValue = 1500,
                .mortgageValue = 30,
                .baseRental = 100,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 1,
                .owner = -1,
                .name = "Pettah"
            }
        }
    };
 
    squares[2] = (Square){
        .type = EVENT,
        .data = {
            .event = {
                .type = COMMUNITY_DEVELOPMENT_FUND,
                .name = "Community Development Fund"
            }
        }
    };
 
    squares[3] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 1800,
                .baseValue = 1800,
                .mortgageValue = 30,
                .baseRental = 120,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 1,
                .owner = -1,
                .name = "Maradana"
            }
        }
    };
 
    squares[4] = (Square){
        .type = TAX,
        .data = {
            .tax = {
                .amount = 200
            }
        }
    };
 
    squares[5] = (Square){
        .type = RAILWAY,
        .data = {
            .railway = {
                .purchasePrice = 200,
                .mortgageValue = 100,
                .mortgageStatus = UNMORTGAGED,
                .owner = -1,
                .name = "Colombo Fort Railway Station"
            }
        }
    };
 
    squares[6] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 2500,
                .mortgageValue = 50,
                .baseValue = 2500,
                .baseRental = 180,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 2,
                .owner = -1,
                .name = "Bambalapitiya"
            }
        }
    };
 
    squares[7] = (Square){
        .type = EVENT,
        .data = {
            .event = {
                .type = NATIONAL_EVENT_CARD,
                .name = "National Event Card"
            }
        }
    };
 
    squares[8] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 2700,
                .baseValue = 2700,
                .mortgageValue = 50,
                .baseRental = 200,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 2,
                .owner = -1,
                .name = "Wellawatte"
            }
        }
    };
 
    squares[9] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 3000,
                .baseValue = 3000,
                .mortgageValue = 60,
                .baseRental = 220,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 2,
                .owner = -1,
                .name = "Mount Lavinia"
            }
        }
    };
 
    squares[10] = (Square){
        .type = SPECIAL,
        .data = {
            .special = {
                .type = JAIL_JUST_VISITING,
                .name = "Jail / Just Visiting"
            }
        }
    };
 
    squares[11] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 3500,
                .baseValue = 3500,
                .mortgageValue = 70,
                .baseRental = 260,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 3,
                .owner = -1,
                .name = "Nugegoda"
            }
        }
    };
 
    squares[12] = (Square){
        .type = UTILITY,
        .data = {
            .utility = {
                .purchasePrice = 150,
                .mortgageValue = 75,
                .mortgageStatus = UNMORTGAGED,
                .name = "Ceylon Electricity Board",
                .owner = -1
            }
        }
    };
 
    squares[13] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 3800,
                .baseValue = 3800,
                .mortgageValue = 70,
                .baseRental = 280,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 3,
                .owner = -1,
                .name = "Maharagama"
            }
        }
    };
 
    squares[14] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 4000,
                .baseValue = 4000,
                .mortgageValue = 80,
                .baseRental = 300,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 3,
                .owner = -1,
                .name = "Kottawa"
            }
        }
    };
 
    squares[15] = (Square){
        .type = RAILWAY,
        .data = {
            .railway = {
                .purchasePrice = 200,
                .mortgageValue = 100,
                .mortgageStatus = UNMORTGAGED,
                .owner = -1,
                .name = "Kandy Railway Station"
            }
        }
    };
 
    squares[16] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 4500,
                .baseValue = 4500,
                .mortgageValue = 90,
                .baseRental = 350,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 4,
                .owner = -1,
                .name = "Negombo"
            }
        }
    };
 
    squares[17] = (Square){
        .type = INSURANCE,
        .data = {
            .insurance = {
                .amount = 500,
                .premium = 50,
                .compensation = 250,
                .type = BASIC_PROPERTY,
                .disasters = {FIRE, FLOOD, RIOT, BUILDING_COLLAPSE, ELECTRICAL_FAILURE}
            }
        }
    };
 
    squares[18] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 4700,
                .baseValue = 4700,
                .mortgageValue = 90,
                .baseRental = 370,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 4,
                .owner = -1,
                .name = "Katunayake"
            }
        }
    };
 
    squares[19] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 5000,
                .baseValue = 5000,
                .mortgageValue = 100,
                .baseRental = 400,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 4,
                .owner = -1,
                .name = "Ja-Ela"
            }
        }
    };
 
    squares[20] = (Square){
        .type = SPECIAL,
        .data = {
            .special = {
                .type = FREE_PARKING,
                .name = "Free Parking"
            }
        }
    };
 
    squares[21] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 5500,
                .baseValue = 5500,
                .mortgageValue = 110,
                .baseRental = 450,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 5,
                .owner = -1,
                .name = "Kandy City"
            }
        }
    };
 
    squares[22] = (Square){
        .type = EVENT,
        .data = {
            .event = {
                .type = NATIONAL_EVENT_CARD,
                .name = "National Event Card"
            }
        }
    };
 
    squares[23] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 5800,
                .baseValue = 5800,
                .mortgageValue = 110,
                .baseRental = 480,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 5,
                .owner = -1,
                .name = "Peradeniya"
            }
        }
    };
 
    squares[24] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 6000,
                .baseValue = 6000,
                .mortgageValue = 120,
                .baseRental = 500,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 5,
                .owner = -1,
                .name = "Katugastota"
            }
        }
    };
 
    squares[25] = (Square){
        .type = RAILWAY,
        .data = {
            .railway = {
                .purchasePrice = 200,
                .mortgageValue = 100,
                .mortgageStatus = UNMORTGAGED,
                .owner = -1,
                .name = "Galle Railway Station"
            }
        }
    };
 
    squares[26] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 6500,
                .baseValue = 6500,
                .mortgageValue = 130,
                .baseRental = 600,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 6,
                .owner = -1,
                .name = "Galle Fort"
            }
        }
    };
 
    squares[27] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 6800,
                .baseValue = 6800,
                .mortgageValue = 130,
                .baseRental = 620,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 6,
                .owner = -1,
                .name = "Unawatuna"
            }
        }
    };
 
    squares[28] = (Square){
        .type = UTILITY,
        .data = {
            .utility = {
                .purchasePrice = 150,
                .mortgageValue = 75,
                .mortgageStatus = UNMORTGAGED,
                .name = "National Water Supply and Drainage Board",
                .owner = -1
            }
        }
    };
 
    squares[29] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 7000,
                .baseValue = 7000,
                .mortgageValue = 140,
                .baseRental = 650,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 6,
                .owner = -1,
                .name = "Hikkaduwa"
            }
        }
    };
 
    squares[30] = (Square){
        .type = SPECIAL,
        .data = {
            .special = {
                .type = GO_TO_JAIL,
                .name = "Go To Jail"
            }
        }
    };
 
    squares[31] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 8000,
                .baseValue = 8000,
                .mortgageValue = 150,
                .baseRental = 750,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 7,
                .owner = -1,
                .name = "Jaffna Town"
            }
        }
    };
 
    squares[32] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 8300,
                .baseValue = 8300,
                .mortgageValue = 150,
                .baseRental = 780,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 7,
                .owner = -1,
                .name = "Nallur"
            }
        }
    };
 
    squares[33] = (Square){
        .type = INSURANCE,
        .data = {
            .insurance = {
                .amount = 500,
                .premium = 50,
                .compensation = 250,
                .type = COMPREHENSIVE,
                .disasters = {FIRE, FLOOD, RIOT, BUILDING_COLLAPSE, ELECTRICAL_FAILURE}
            }
        }
    };
 
    squares[34] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 8500,
                .baseValue = 8500,
                .mortgageValue = 160,
                .baseRental = 800,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 7,
                .owner = -1,
                .name = "Trincomalee"
            }
        }
    };
 
    squares[35] = (Square){
        .type = RAILWAY,
        .data = {
            .railway = {
                .purchasePrice = 200,
                .mortgageValue = 100,
                .mortgageStatus = UNMORTGAGED,
                .owner = -1,
                .name = "Jaffna Railway Station"
            }
        }
    };
 
    squares[36] = (Square){
        .type = EVENT,
        .data = {
            .event = {
                .type = NATIONAL_EVENT_CARD,
                .name = "National Event Card"
            }
        }
    };
 
    squares[37] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 10000,
                .baseValue = 10000,
                .mortgageValue = 175,
                .baseRental = 1000,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 8,
                .owner = -1,
                .name = "Nuwara Eliya"
            }
        }
    };
 
    squares[38] = (Square){
        .type = BANK,
        .data = {
            .bank = {
                .name = "Bank of Ceylon"
            }
        }
    };
 
    squares[39] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 12000,
                .baseValue = 12000,
                .mortgageValue = 200,
                .baseRental = 1200,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfHouses = 0,
                .numberOfHotels = 0,
                .groupID = 8,
                .owner = -1,
                .name = "Galle Face"
            }
        }
    };
    

}

int roundOff(double num){
    if(num - (int)num >= 0.5){
        return (int)num + 1;
    }
    else{
        return (int)num;
    }
}

void rollAndMove(currentPlayer players[], Square squares[]){

    for(int i = 0; i<4; i++){
        int passGO = 0;

        diceRoll(&players[i], squares);

        if(players[i].position > 39){
            passGO = 1;
            players[i].position = players[i].position - 40;
        }

        printf("%s moves from Square %d to Square %d.\n",getPlayer(players[i]),players[i].lastPosition,players[i].position);
        
        if(passGO){
            players[i].money += 2000;
            players[i].lastRound = players[i].currentRound;
            players[i].currentRound++;
            
            printf("%s passed GO.\n", getPlayer(players[i]));
            printf("Collected LKR 2000.\n");
            printf("Current Balance : LKR %d.\n", players[i].money);
            passGO = 0;
        }
        printf("\n");
        
        int current_player_position = players[i].position;

        buy(squares,&players[i],i,players);
        payRent(players,&players[i],&squares[current_player_position],i);
        
    }
    
    printf("\n");
}