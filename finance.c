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
int getNetWorth(currentPlayer *player, Square squares[]) {
    int netWorth = player->money;

    for (int i = 0; i < 40; i++) {
        Square *sq = &squares[i];
        switch (sq->type) {
            case PROPERTY:
                if (sq->data.property.owner == player->player) {
                    netWorth += sq->data.property.baseValue;
                    netWorth += sq->data.property.numberOfHouses * sq->data.property.houseConstructionCost;
                    netWorth += sq->data.property.numberOfHotels * sq->data.property.hotelConstructionCost;
                }
                break;
            case RAILWAY:
                if (sq->data.railway.owner == player->player) {
                    netWorth += sq->data.railway.purchasePrice;
                }
                break;
            case UTILITY:
                if (sq->data.utility.owner == player->player) {
                    netWorth += sq->data.utility.purchasePrice;
                }
                break;
        }
    }

    netWorth -= player->loanAmount; 

    return netWorth;
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

int getMaxLoanAmount(currentPlayer *player, Square squares[]) {
    int totalMortgageValue = 0;
    for (int i = 0; i < 40; i++) {
        Square *sq = &squares[i];
            switch(sq->type){
                case PROPERTY:
                    if(sq->data.property.isLocked == NOT_LOAN_LOCKED && sq->data.property.owner == player->player && sq->data.property.mortgageStatus == UNMORTGAGED){
                        totalMortgageValue += sq->data.property.mortgageValue;
                    }
                    break;
                case RAILWAY:
                    if(sq->data.railway.isLocked == NOT_LOAN_LOCKED && sq->data.railway.owner == player->player && sq->data.railway.mortgageStatus == UNMORTGAGED){
                        totalMortgageValue += sq->data.railway.mortgageValue;
                    }
                    break;
                case UTILITY:
                    if(sq->data.utility.isLocked == NOT_LOAN_LOCKED && sq->data.utility.owner == player->player && sq->data.utility.mortgageStatus == UNMORTGAGED){
                        totalMortgageValue += sq->data.utility.mortgageValue;
                    }
                    break;
            }
        
    }
    return roundOff(totalMortgageValue * 0.75);
}
int getMortgageValue(Square *square){
    switch(square->type){
        case PROPERTY:
            return square->data.property.mortgageValue;
        case RAILWAY:
            return square->data.railway.mortgageValue;
        case UTILITY:
            return square->data.utility.mortgageValue;
        default:
            return 0;
    }
}
void obtainLoan(currentPlayer *player, Square squares[], int amount, EconomicState *econ){
    if (player->ownedLoan.isActive == 0 && amount >= 0){

    int maxLoan = getMaxLoanAmount(player, squares);
    if (amount > maxLoan){
        amount = maxLoan;
    }

    int requiredCollateralValue = roundOff(amount / 0.75);

    MortgageItems mortgageItems[28];
    int count = 0;

    for (int i = 0; i < 40; i++) {
        Square *sq = &squares[i];
        switch(sq->type){
                case PROPERTY:
                    if(sq->data.property.isLocked == NOT_LOAN_LOCKED && sq->data.property.owner == player->player && sq->data.property.mortgageStatus == UNMORTGAGED){
                        mortgageItems[count].index = i;
                        mortgageItems[count].value = getMortgageValue(sq);
                        count++;
                    }
                    break;
                case RAILWAY:
                    if(sq->data.railway.isLocked == NOT_LOAN_LOCKED && sq->data.railway.owner == player->player && sq->data.railway.mortgageStatus == UNMORTGAGED){
                        mortgageItems[count].index = i;
                        mortgageItems[count].value = getMortgageValue(sq);
                        count++;
                    }
                    break;
                case UTILITY:
                    if(sq->data.utility.isLocked == NOT_LOAN_LOCKED && sq->data.utility.owner == player->player && sq->data.utility.mortgageStatus == UNMORTGAGED){
                        mortgageItems[count].index = i;
                        mortgageItems[count].value = getMortgageValue(sq);
                        count++;
                    break;
         }
        
        
    }
    }

    for (int i = 1; i < count; i++) {
        MortgageItems key = mortgageItems[i];
        int j = i - 1;
        while (j >= 0 && mortgageItems[j].value > key.value) {
            mortgageItems[j + 1] = mortgageItems[j];
            j--;
        }
        mortgageItems[j + 1] = key;
    }

    printf("%s obtained a secured loan.\n", getPlayer(*player));
    printf("Loan Amount : LKR %d.\n\n", amount);
    printf("Collateral :\n");

    int pledgedValue = 0;
    player->ownedLoan.collateralCount = 0;   
    for (int i = 0; (i < count) && (pledgedValue < requiredCollateralValue); i++) {
        int id = mortgageItems[i].index;
        player->ownedLoan.collateralIndices[player->ownedLoan.collateralCount++] = id;
        pledgedValue += mortgageItems[i].value;
        printf("%s\n", getSquareName(&squares[id]));
    }
    printf("\n");

    player->ownedLoan.isActive = 1;
    player->ownedLoan.originalAmount = amount;
    player->ownedLoan.loanAmount = amount;
    player->ownedLoan.interestRate = econ->currentLoanInterestRate;
    player->ownedLoan.roundsRemaining = 20;

    player->money += amount;
    player->loanAmount = player->ownedLoan.loanAmount; 

    printf("Interest Rate : %d%%\n", player->ownedLoan.interestRate);
    printf("Duration : 20 Rounds\n\n");
    }

}

void repayLoan(currentPlayer *player, int amount) {
    if (player->ownedLoan.isActive == 1){
    if (amount > player->money){
         amount = player->money;
    }
    if (amount > player->ownedLoan.loanAmount){
         amount = player->ownedLoan.loanAmount;
    }

    if(amount > 0){
    player->money -= amount;
    player->ownedLoan.loanAmount -= amount;
    player->loanAmount = player->ownedLoan.loanAmount;

    printf("%s repaid LKR %d.\n", getPlayer(*player), amount);
    printf("Outstanding Balance : LKR %d.\n\n", player->ownedLoan.loanAmount);

    if (player->ownedLoan.loanAmount == 0) {
        player->ownedLoan.isActive = 0;
        player->isLoanActive = 0;
        player->ownedLoan.collateralCount = 0;
        printf("%s has fully repaid the loan. Collateral released.\n\n", getPlayer(*player));
    }
    else{
        extendLoan(player);
    }
  }
  }
}

void repayLoanFull(currentPlayer *player) {
    if(player->money >= player->ownedLoan.loanAmount){
        repayLoan(player, player->ownedLoan.loanAmount);
    }
}

void calLoanInterest(currentPlayer *player) {
    if (player->ownedLoan.isActive == 1) {

        int interest = roundOff(player->ownedLoan.loanAmount * (player->ownedLoan.interestRate / 100.0));
        player->ownedLoan.loanAmount += interest;
        player->loanAmount = player->ownedLoan.loanAmount;
        player->ownedLoan.roundsRemaining--;

    }
}

void checkLoanDefault(currentPlayer *player, Square squares[]) {

    if (player->ownedLoan.isActive == 1 && player->ownedLoan.roundsRemaining <= 0){
        printf("%s has defaulted.\n", getPlayer(*player));

        for (int i = 0; i < player->ownedLoan.collateralCount; i++) {
            Square *sq = &squares[player->ownedLoan.collateralIndices[i]];
            switch (sq->type) {
            case PROPERTY:
                sq->data.property.owner = -1;
                sq->data.property.numberOfHouses = 0;
                sq->data.property.numberOfHotels = 0;
                sq->data.property.insuranceStatus = UNINSURED;
                sq->data.property.mortgageStatus = UNMORTGAGED;
                player->propertiesCount--;
                break;
            case RAILWAY:
                sq->data.railway.owner = -1;
                sq->data.railway.mortgageStatus = UNMORTGAGED;
                player->railwaysCount--;
                break;
            case UTILITY:
                sq->data.utility.owner = -1;
                sq->data.utility.mortgageStatus = UNMORTGAGED;
                player->utilityCount--;
                break;
        }
        printf("%s foreclosed.\n", getSquareName(sq));
        
    }

    player->ownedLoan.isActive = 0;
    player->ownedLoan.loanAmount = 0;
    player->ownedLoan.collateralCount = 0;
    player->loanAmount = 0;

    printf("Outstanding debt cleared.\n\n");
}
}

int isLoanNeeded(currentPlayer *player, Square squares[], EconomicState *econStatus) {
    switch (player->player) {
        case AGGRESSIVE_INVESTOR:
            printf("max loan amount : %d\n", getMaxLoanAmount(player, squares));
            
            if((getMaxLoanAmount(player, squares) >= squares[3].data.property.houseConstructionCost)){
                return 1;
            }
        break;

        case CONSERVATIVE_BANKER:
            if(player->money < getMaxRent(squares,player) && getMaxRent(squares,player) > player->money){
                return 1;
            }
        break;

        case RISK_TAKER:
            if(getMaxLoanAmount(player, squares) > 0){
                return 1;
            }
        break;

        case OPPORTUNISTIC_TRADER:
            if((econStatus->currentLoanInterestRate <= 8 && getMaxLoanAmount(player, squares) > 0)){
                return 1;
            }
        break;
    }
    return 0;
}

int wantToRepay(Square squares[], currentPlayer *player, EconomicState *econ) {
    if(player->isLoanActive == 1){
    switch (player->player) {
        case AGGRESSIVE_INVESTOR:
            if(player->money > (2 * player->ownedLoan.loanAmount)){
                return player->money;
            }
            break;
        case CONSERVATIVE_BANKER:
            if(player->money >= 0){
                return player->money;
            }
            break;
        case RISK_TAKER:
            if(getOwnedItems(squares,player) == player->ownedLoan.collateralCount){
                if(player->money >= player->ownedLoan.loanAmount){
                    return player->ownedLoan.loanAmount;
                }
            }
            break;
        case OPPORTUNISTIC_TRADER:
            if(player->money >= getMaxRent(squares,player)+player->ownedLoan.loanAmount){
                return player->ownedLoan.loanAmount;
            }
    }
    return 0;
  }
  return 0;
}
void extendLoan(currentPlayer *player){
    player->ownedLoan.roundsRemaining = 20;
    printf("%s extended the loan period.\n", getPlayer(*player));
    printf("New Duration : 20 Rounds\n\n");
}