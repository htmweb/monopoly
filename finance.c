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
                    netWorth += sq->data.property.purchasePrice;
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

void repayLoan(currentPlayer *player, Square squares[], int amount) {
    if (player->ownedLoan.isActive == 1) {
        if (amount > player->money) {
             amount = player->money;
        }
        if (amount > player->ownedLoan.loanAmount) {
             amount = player->ownedLoan.loanAmount;
        }

        if (amount > 0) {
            player->money -= amount;
            player->ownedLoan.loanAmount -= amount;
            player->loanAmount = player->ownedLoan.loanAmount;

            printf("%s repaid LKR %d.\n", getPlayer(*player), amount);
            printf("Outstanding Loan Balance : LKR %d.\n\n", player->ownedLoan.loanAmount);

            if (player->ownedLoan.loanAmount == 0) {
                for (int i = 0; i < player->ownedLoan.collateralCount; i++) {
                    int squareIndex = player->ownedLoan.collateralIndices[i];
                    Square *sq = &squares[squareIndex];

                    switch (sq->type) {
                        case PROPERTY:
                            sq->data.property.mortgageStatus = UNMORTGAGED;
                            sq->data.property.isLocked = NOT_LOAN_LOCKED;
                            break;
                        case RAILWAY:
                            sq->data.railway.mortgageStatus = UNMORTGAGED;
                            sq->data.railway.isLocked = NOT_LOAN_LOCKED;
                            break;
                        case UTILITY:
                            sq->data.utility.mortgageStatus = UNMORTGAGED;
                            sq->data.utility.isLocked = NOT_LOAN_LOCKED;
                            break;
                    }
                }

                player->ownedLoan.isActive = 0;
                player->isLoanActive = 0;
                player->ownedLoan.collateralCount = 0;
                
                printf("%s has fully repaid the loan. Collateral released.\n\n", getPlayer(*player));
            } else {
                extendLoan(player);
            }
        }
    }
}

void repayLoanFull(currentPlayer *player,Square squares[]) {
    if(player->money >= player->ownedLoan.loanAmount){
        repayLoan(player, squares,player->ownedLoan.loanAmount);
    }
}

void calLoanInterest(currentPlayer *player,Square squares[]) {
    if (player->ownedLoan.isActive == 1) {

        int interest = roundOff(player->ownedLoan.loanAmount * (player->ownedLoan.interestRate / 100.0));
        player->ownedLoan.loanAmount += interest;
        player->loanAmount = player->ownedLoan.loanAmount;
        player->ownedLoan.roundsRemaining--;

        checkBankrupt(player,squares);

    }
}

void checkLoanDefault(currentPlayer *player, Square squares[]) {

    if (player->ownedLoan.isActive == 1 && player->ownedLoan.roundsRemaining <= 0){
        printf("%s has defaulted.\n", getPlayer(*player));

        for (int i = 0; i < player->ownedLoan.collateralCount; i++) {
            Square *sq = &squares[player->ownedLoan.collateralIndices[i]];
            switch (sq->type) {
            case PROPERTY:
            {
                int lostHouses = sq->data.property.numberOfHouses;
                int lostHotels = sq->data.property.numberOfHotels;

                sq->data.property.owner = -1;
                sq->data.property.numberOfHouses = 0;
                sq->data.property.numberOfHotels = 0;
                sq->data.property.insuranceStatus = UNINSURED;
                sq->data.property.mortgageStatus = UNMORTGAGED;
                sq->data.property.isLocked = NOT_LOAN_LOCKED;

                player->propertiesCount--;
                player->numberOfHouses -= lostHouses;
                player->numberOfHotels -= lostHotels;
            }
                break;
            case RAILWAY:
                sq->data.railway.owner = -1;
                sq->data.railway.mortgageStatus = UNMORTGAGED;
                sq->data.railway.isLocked = NOT_LOAN_LOCKED;
                player->railwaysCount--;
                break;
            case UTILITY:
                sq->data.utility.owner = -1;
                sq->data.utility.mortgageStatus = UNMORTGAGED;
                sq->data.utility.isLocked = NOT_LOAN_LOCKED;
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
            printf("Max loan amount : %d\n", getMaxLoanAmount(player, squares));
            
            if((getMaxLoanAmount(player, squares) >= squares[3].data.property.houseConstructionCost)){
                return 1;
            }
        break;

        case CONSERVATIVE_BANKER:
            if(player->money <= getMaxRent(squares,player)){
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
void setLoanInterestRate(EconomicState *econ){
    int rate = 0;
    int inflationRate = econ->currentInflationRate;
    if (inflationRate < 0) {
        rate = 5;
        econ->econStatus = ECONOMIC_BOOM;
    } else if (inflationRate <= 2) {
        rate = 8;
        econ->econStatus = STABLE_ECONOMY;
    } else if (inflationRate <= 5) {
        rate = 10;
        econ->econStatus = MODERATE_INFLATION;
    } else if (inflationRate <= 8) {
        rate = 12;
        econ->econStatus = HIGH_INFLATION;
    } else {
        rate = 15;
        econ->econStatus = ECONOMIC_RECESSION;
    }

    econ->currentLoanInterestRate = rate;
}

int canAffordDebt(currentPlayer *player, Square squares[], int amount) {
    int totalMortgageValue = 0;
    for (int i = 0; i < 40; i++) {
        Square *sq = &squares[i];
        switch (sq->type) {
            case PROPERTY:
                if (sq->data.property.owner == player->player &&
                    sq->data.property.mortgageStatus == UNMORTGAGED &&
                    sq->data.property.isLocked == NOT_LOAN_LOCKED) {
                    totalMortgageValue += sq->data.property.mortgageValue;
                }
                break;
            case RAILWAY:
                if (sq->data.railway.owner == player->player &&
                    sq->data.railway.mortgageStatus == UNMORTGAGED &&
                    sq->data.railway.isLocked == NOT_LOAN_LOCKED) {
                    totalMortgageValue += sq->data.railway.mortgageValue;
                }
                break;
            case UTILITY:
                if (sq->data.utility.owner == player->player &&
                    sq->data.utility.mortgageStatus == UNMORTGAGED &&
                    sq->data.utility.isLocked == NOT_LOAN_LOCKED) {
                    totalMortgageValue += sq->data.utility.mortgageValue;
                }
                break;
        }
    }
    return (player->money + totalMortgageValue) >= amount;
}

void raiseCashByMortgaging(currentPlayer *player, Square squares[], int neededAmount) {
    MortgageItems items[28];
    int count = 0;

    for (int i = 0; i < 40; i++) {
        Square *sq = &squares[i];
        switch (sq->type) {
            case PROPERTY:
                if (sq->data.property.owner == player->player &&
                    sq->data.property.mortgageStatus == UNMORTGAGED &&
                    sq->data.property.isLocked == NOT_LOAN_LOCKED) {
                    
                    items[count].index = i;
                    items[count].value = sq->data.property.mortgageValue;
                    count++;
                }
                break;
            case RAILWAY:
                if (sq->data.railway.owner == player->player &&
                    sq->data.railway.mortgageStatus == UNMORTGAGED &&
                    sq->data.railway.isLocked == NOT_LOAN_LOCKED) {
                    items[count].index = i;
                    items[count].value = sq->data.railway.mortgageValue;
                    count++;
                }
                break;
            case UTILITY:
                if (sq->data.utility.owner == player->player &&
                    sq->data.utility.mortgageStatus == UNMORTGAGED &&
                    sq->data.utility.isLocked == NOT_LOAN_LOCKED) {
                    items[count].index = i;
                    items[count].value = sq->data.utility.mortgageValue;
                    count++;
                }
                break;
        }
    }

    for (int i = 1; i < count; i++) {
        MortgageItems key = items[i];
        int j = i - 1;
        while (j >= 0 && items[j].value > key.value) {
            items[j + 1] = items[j];
            j--;
        }
        items[j + 1] = key;
    }

    int raised = 0;
    for (int i = 0; i < count && raised < neededAmount; i++) {
        Square *sq = &squares[items[i].index];
        switch (sq->type) {
            case PROPERTY:
                player->numberOfHouses -= sq->data.property.numberOfHouses;
                player->numberOfHotels -= sq->data.property.numberOfHotels;
                sq->data.property.numberOfHouses = 0;
                sq->data.property.numberOfHotels = 0;
                sq->data.property.insuranceStatus = UNINSURED;
                sq->data.property.mortgageStatus = UNMORTGAGED;
                sq->data.property.owner = -1;
                player->propertiesCount--;
                break;
            case RAILWAY:
                sq->data.railway.mortgageStatus  = UNMORTGAGED;
                sq->data.railway.owner = -1;
                player->railwaysCount--;
                break;
            case UTILITY: 
                sq->data.utility.mortgageStatus  = UNMORTGAGED;
                sq->data.utility.owner = -1;
                player->utilityCount--;
                break;
        }
        player->money += items[i].value;
        raised += items[i].value;
        printf("%s sold to bank %s for LKR %d.\n", getPlayer(*player), getSquareName(sq), items[i].value);
    }
    printf("\n");
}

void collectDebt(currentPlayer *player, currentPlayer *creditor, Square squares[], int amount) {
    if (player->money >= amount) {
        player->money -= amount;
        if (creditor != NULL){
             creditor->money += amount;
        }
        return;
    }

    if (canAffordDebt(player, squares, amount)){
        raiseCashByMortgaging(player, squares, amount - player->money);
        player->money -= amount;
        if (creditor != NULL){
            creditor->money += amount;
        }
    } else {
        bankRupt(player, squares);
    }
}


void checkBankrupt(currentPlayer *player, Square squares[]){
    if(player->isBankrupt == NOTBANKRUPT){
        int netWorth = getNetWorth(player, squares);
        if (netWorth <= 0) {            
            bankRupt(player, squares);
        }
}
}

void checkPlayerBankrupt(currentPlayer players[], Square squares[]){
    for(int i = 0; i<4; i++){
        checkBankrupt(&players[i],squares);
    }
}

void bankRupt(currentPlayer *player, Square squares[]) {
    
    if(player->isBankrupt == NOTBANKRUPT){
    printf("%s has been declared bankrupt.\n", getPlayer(*player));
    
    for (int i = 0; i < 40; i++) {
        Square *sq = &squares[i];
        switch (sq->type) {
            case PROPERTY:
                if (sq->data.property.owner == player->player) {
                    sq->data.property.numberOfHouses = 0;
                    sq->data.property.numberOfHotels = 0;
                    sq->data.property.insuranceStatus = UNINSURED;
                    sq->data.property.mortgageStatus = UNMORTGAGED;
                    sq->data.property.isLocked = NOT_LOAN_LOCKED;
                    sq->data.property.owner = -1;
                }
                break;
            case RAILWAY:
                if (sq->data.railway.owner == player->player) {
                    sq->data.railway.mortgageStatus = UNMORTGAGED;
                    sq->data.railway.isLocked = NOT_LOAN_LOCKED;
                    sq->data.railway.owner = -1;
                }
                break;
            case UTILITY:
                if (sq->data.utility.owner == player->player) {
                    sq->data.utility.mortgageStatus = UNMORTGAGED;
                    sq->data.utility.isLocked = NOT_LOAN_LOCKED;
                    sq->data.utility.owner = -1;
                }
                break;
        }
    }

    player->propertiesCount = 0;
    player->railwaysCount = 0;
    player->utilityCount = 0;
    player->numberOfHouses = 0;
    player->numberOfHotels = 0;

    player->ownedLoan.isActive = 0;
    player->ownedLoan.loanAmount = 0;
    player->ownedLoan.collateralCount = 0;
    player->loanAmount = 0;
    player->isLoanActive = 0;

    player->money = 0;
    player->isBankrupt = BANKRUPT;

    printf("Remaining assets transferred to the Bank.\n\n");
    
}
}

int getPropertyInsuranceIndex(Square squares[], int squareIndex){
    int id = 0;
    for(int i = 0; i < squareIndex; i++){
        if(squares[i].type == PROPERTY){
            id++;
        }
    }
    return id;
}

void purchaseInsurance(Square squares[], currentPlayer *player,int propertyIndex,InsuranceType type){

    Square *sq = &squares[propertyIndex];

    if(sq->type == PROPERTY && sq->data.property.owner == player->player){

    if(type == BUSINESS_INTERRUPTION && sq->data.property.numberOfHotels == 1){
        return;
    }

    int propertyValue = sq->data.property.purchasePrice;
    int premium = 0;
    int compensation = 0;

    switch(type){
        case BASIC_PROPERTY:
            premium = roundOff(propertyValue * 0.05);
            compensation = 80;
            break;
        case COMPREHENSIVE:
            premium = roundOff(propertyValue * 0.10);
            compensation = 100;
            break;
        case BUSINESS_INTERRUPTION:
            premium = roundOff(propertyValue * 0.15);
            compensation = 100;
            break;
    }

    if(player->money >= premium){
        player->money -= premium;
        sq->data.property.insuranceStatus = INSURED;

        int id = getPropertyInsuranceIndex(squares, propertyIndex);
        player->ownedInsurance[id].amount = propertyValue;
        player->ownedInsurance[id].premium = premium;
        player->ownedInsurance[id].compensation = compensation;
        player->ownedInsurance[id].type = type;
        player->ownedInsurance[id].roundsRemaining = 20;
        player->ownedInsurance[id].isActive = 1;
        sq->data.property.insuranceId = id;

        switch(type){
            case BASIC_PROPERTY:
                printf("Basic Property Insurance purchased.\n");
                break;
            case COMPREHENSIVE:
                printf("Comprehensive Insurance purchased.\n");
                break;
            case BUSINESS_INTERRUPTION:
                printf("Business Interruption Insurance purchased.\n");
                break;
        }
        printf("Property : %s\n", sq->data.property.name);
        printf("Premium : LKR %d.\n\n", premium);
    }
 }
}

void checkInsuranceExpiry(currentPlayer players[], Square squares[]){
    for(int k = 0; k < 4; k++){
        currentPlayer *currentPlayer = &players[k];
        
        for(int i = 0; i < 40; i++){
            if(squares[i].type == PROPERTY && squares[i].data.property.owner == currentPlayer->player && squares[i].data.property.insuranceStatus == INSURED){

            int id = getPropertyInsuranceIndex(squares, i);
            Insurance *policy = &currentPlayer->ownedInsurance[id];

            if(policy->isActive == 1){
                policy->roundsRemaining--;

                if(policy->roundsRemaining == 3){
                    printf("Insurance Expiry\n\n");
                    printf("Insurance policy on %s expires in 3 rounds.\n\n", squares[i].data.property.name);
                }

                if(policy->roundsRemaining <= 0){
                    policy->isActive = 0;
                    squares[i].data.property.insuranceStatus = UNINSURED;
                    squares[i].data.property.insuranceId = -1;

                    printf("Insurance Expiry\n\n");
                    printf("Insurance policy on %s has expired.\n\n", squares[i].data.property.name);
                }
            }
        }
    }
  }
}


void repairDamagedProperties(currentPlayer players[], Square squares[]){
    for(int p = 0; p < 4; p++){
        currentPlayer *currentPlayer = &players[p];

        for(int i = 0; i < 40; i++){
            if(squares[i].type == PROPERTY && squares[i].data.property.owner == currentPlayer->player){
                Property *property = &squares[i].data.property;
                
                if(property->isDamaged == 1 && property->repairCost > 0 && currentPlayer->money >= property->repairCost){
                    int cost = property->repairCost;
                    currentPlayer->money -= cost;
                    property->isDamaged = 0;
                    property->repairCost = 0;

                    printf("Repairs Completed\n\n");
                    printf("%s has been repaired.\n", property->name);
                    printf("Repair Cost : LKR %d.\n\n", cost);
                }

                
            }
        }
    }
}

int decideInsuranceType(currentPlayer *player, Square squares[], int propertyIndex){
    Square *sq = &squares[propertyIndex];

    if(sq->type == PROPERTY && sq->data.property.owner == player->player){
        Property *property = &sq->data.property;
        int isDeveloped = (property->numberOfHouses > 0 || property->numberOfHotels > 0);

        if(property->insuranceStatus == INSURED || isDeveloped == 0){
            return -1;
        }

        switch(player->player){
            case AGGRESSIVE_INVESTOR:
                if(property->numberOfHotels > 0){
                    return COMPREHENSIVE;
                }
                return BASIC_PROPERTY;

            case CONSERVATIVE_BANKER:
                return COMPREHENSIVE;

            case RISK_TAKER:
                if(player->financialLoss == UNINSURED_DISASTER_HAPPENED){
                    return BASIC_PROPERTY;
                }
                return -1;

            case OPPORTUNISTIC_TRADER:
                if(property->baseValue >= 5000){ 
                    return COMPREHENSIVE;
                }
                return -1;
        }
    }


    return -1;
}

void handleInsurancePurchase(Square squares[], currentPlayer *player){
    if(squares[player->position].type == INSURANCE){
        for(int i = 0; i < 40; i++){
            int type = decideInsuranceType(player, squares, i);

            if(type != -1){
                purchaseInsurance(squares, player, i, type);
            }
        }
    }
}

void handleTax(Square *square, currentPlayer *player, Square squares[], EconomicState *econ){
    if(square->type == TAX){
        int taxAmount = roundOff(getNetWorth(player, squares)*0.15);

        if(econ->incomeTaxMultiplier > 0){
            taxAmount = roundOff(taxAmount * (1 + (econ->incomeTaxMultiplier / 100.0)));
        }
        printf("\n%s landed on Income Tax.\n\n", getPlayer(*player));

        if(player->money >= taxAmount){
            player->money -= taxAmount;

            printf("Income Tax Paid : LKR %d.\n", taxAmount);
            printf("Current Balance : LKR %d.\n\n", player->money);
        }
        else{
            printf("Income Tax Due : LKR %d.\n\n", taxAmount);
            collectDebt(player, NULL, squares, taxAmount);
        }

        checkBankrupt(player, squares);
    }
}

void applyLuxuryPropertyTax(currentPlayer players[], Square squares[], EconomicState *econ){
    if(econ->luxuryPropertyTaxRate > 0){
        for(int i = 0; i < 40; i++){
            if(squares[i].type == PROPERTY && squares[i].data.property.numberOfHotels == 1){
                Property *property = &squares[i].data.property;

                int ownerIndex = -1;
                for(int p = 0; p < 4; p++){
                    if(players[p].player == property->owner){
                        ownerIndex = p;
                        break;
                    }
                }

                if(ownerIndex != -1){
                    int tax = roundOff(property->purchasePrice * (econ->luxuryPropertyTaxRate / 100.0));

                    printf("\nLuxury Property Tax\n\n");
                    printf("%s owes LKR %d on %s.\n", getPlayer(players[ownerIndex]), tax, property->name);

                    if(players[ownerIndex].money >= tax){
                        players[ownerIndex].money -= tax;
                        printf("Tax Paid : LKR %d.\n", tax);
                    }else{
                        collectDebt(&players[ownerIndex], NULL, squares, tax);
                    }

                    checkBankrupt(&players[ownerIndex], squares);
                }
            }
        }
    }
}

