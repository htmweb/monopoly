#include "types.h"
#include <stdio.h>
#include <stdlib.h>

int generateInflationRate(){
    int rates[] = {-3, 0, 2, 5, 8, 12};
    int rate = rand() % 6;
    return rates[rate];
}
void applyInflation(Square squares[], EconomicState *econState, int newRate) {

    float factor = 1 + (newRate / 100.0);

    for (int i = 0; i < 40; i++) {
        Square *sq = &squares[i];
        switch (sq->type) {
            case PROPERTY:
                sq->data.property.purchasePrice = roundOff(sq->data.property.purchasePrice * factor);
                sq->data.property.baseValue = roundOff(sq->data.property.baseValue * factor);

                sq->data.property.mortgageValue = roundOff(sq->data.property.mortgageValue * factor);
                sq->data.property.baseRental = roundOff(sq->data.property.baseRental * factor);

                sq->data.property.houseConstructionCost = roundOff(sq->data.property.houseConstructionCost * factor);
                sq->data.property.hotelConstructionCost = roundOff(sq->data.property.hotelConstructionCost * factor);
                break;
            case RAILWAY:
                sq->data.railway.purchasePrice = roundOff(sq->data.railway.purchasePrice * factor);
                sq->data.railway.mortgageValue = roundOff(sq->data.railway.mortgageValue * factor);
                break;
            case UTILITY:
                sq->data.utility.purchasePrice = roundOff(sq->data.utility.purchasePrice * factor);
                sq->data.utility.mortgageValue = roundOff(sq->data.utility.mortgageValue * factor);
                break;
            case INSURANCE:
                sq->data.insurance.premium = roundOff(sq->data.insurance.premium * factor);
                sq->data.insurance.compensation = roundOff(sq->data.insurance.compensation * factor);
                break;
        }
    }

    econState->currentInflationRate = newRate;
    econState->currentLoanInterestRate = roundOff(econState->currentLoanInterestRate * factor);

}
void printMarketCondition(EconomicState *econState) {
    printf("==================================\n");
    printf("Current Market Conditions\n");
    printf("==================================\n\n");
    printf("Inflation %%\n");
    printf("------------------\n");
    printf("%d%%\n\n", econState->currentInflationRate);

    printf("Loan Interest Rate\n");
    printf("------------------\n");
    printf("%d%%\n\n", econState->currentLoanInterestRate);
}