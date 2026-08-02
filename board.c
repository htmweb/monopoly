#include "types.h"
#include <stdio.h>

Square squares[40];

void initBoard(){
    squares[0] = (Square){
        .type = START,
    
    };
    squares[1] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 60,
                .mortgageValue = 30,
                .baseRental = 2,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 60,
                .mortgageValue = 30,
                .baseRental = 4,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 100,
                .mortgageValue = 50,
                .baseRental = 6,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 100,
                .mortgageValue = 50,
                .baseRental = 6,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 120,
                .mortgageValue = 60,
                .baseRental = 8,
                .houseConstructionCost = 50,
                .hotelConstructionCost = 100,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 140,
                .mortgageValue = 70,
                .baseRental = 10,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .name = "Ceylon Electricity Board"
            }
        }
    };
 
    squares[13] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 140,
                .mortgageValue = 70,
                .baseRental = 10,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 160,
                .mortgageValue = 80,
                .baseRental = 12,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 180,
                .mortgageValue = 90,
                .baseRental = 14,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 180,
                .mortgageValue = 90,
                .baseRental = 14,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 200,
                .mortgageValue = 100,
                .baseRental = 16,
                .houseConstructionCost = 100,
                .hotelConstructionCost = 150,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 220,
                .mortgageValue = 110,
                .baseRental = 18,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 220,
                .mortgageValue = 110,
                .baseRental = 18,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 240,
                .mortgageValue = 120,
                .baseRental = 20,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 260,
                .mortgageValue = 130,
                .baseRental = 22,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 260,
                .mortgageValue = 130,
                .baseRental = 22,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .name = "National Water Supply and Drainage Board"
            }
        }
    };
 
    squares[29] = (Square){
        .type = PROPERTY,
        .data = {
            .property = {
                .purchasePrice = 280,
                .mortgageValue = 140,
                .baseRental = 24,
                .houseConstructionCost = 150,
                .hotelConstructionCost = 200,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 300,
                .mortgageValue = 150,
                .baseRental = 26,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 300,
                .mortgageValue = 150,
                .baseRental = 26,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 320,
                .mortgageValue = 160,
                .baseRental = 28,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 350,
                .mortgageValue = 175,
                .baseRental = 35,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
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
                .purchasePrice = 400,
                .mortgageValue = 200,
                .baseRental = 50,
                .houseConstructionCost = 200,
                .hotelConstructionCost = 250,
                .mortgageStatus = UNMORTGAGED,
                .insuranceStatus = UNINSURED,
                .numberOfBuildings = 0,
                .groupID = 8,
                .owner = -1,
                .name = "Galle Face"
            }
        }
    };

    initPlayers(squares);

}