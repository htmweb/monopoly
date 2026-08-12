#ifndef types_H
#define types_H


typedef enum {
    START,
    PROPERTY,
    TAX,
    RAILWAY,
    EVENT,
    SPECIAL,
    UTILITY,
    INSURANCE,
    BANK
} sqType;

typedef enum{
    NOTIN_JAIL,
    IN_JAIL
}Jail;

typedef enum{
    LOAN_LOCKED,
    NOT_LOAN_LOCKED
}LoanStatus;

typedef enum{
    MORTGAGED,
    UNMORTGAGED
}MortgageStatus;

typedef enum{
    NOTBANKRUPT,
    BANKRUPT
} Bankrupt;

typedef enum {
    AGGRESSIVE_INVESTOR,
    CONSERVATIVE_BANKER,
    RISK_TAKER,
    OPPORTUNISTIC_TRADER
} Player;

typedef enum {
    INSURED,
    UNINSURED
}InsuranceStatus;

typedef enum{
    BASIC_PROPERTY,
    COMPREHENSIVE,
    BUSINESS_INTERRUPTION
}InsuranceType;

typedef enum {
    FIRE,
    FLOOD,
    RIOT,
    BUILDING_COLLAPSE,
    ELECTRICAL_FAILURE
}DisasterType;

typedef enum{
    COMMUNITY_DEVELOPMENT_FUND,
    NATIONAL_EVENT_CARD
}EventType;

typedef enum{
    JAIL_JUST_VISITING,
    GO_TO_JAIL,
    FREE_PARKING
}SpecialType;

typedef enum{
    ECONOMIC_BOOM,
    STABLE_ECONOMY,
    MODERATE_INFLATION,
    HIGH_INFLATION,
    ECONOMIC_RECESSION
}EconStatus;

typedef enum{
    HOUSING_SUBSIDY,
    GOVERNMENT_BOND
}activeCardType;

typedef enum{
    NOT_GAME_OVER,
    GAME_OVER
}isGameOver;
//to be

typedef struct{
    Player player;
    int diceVal;
}Order;

typedef struct{
    int amount;
    int premium;
    int compensation;
    InsuranceType type;
    DisasterType disasters[5];
}Insurance;

typedef struct{
    int purchasePrice;
    int baseValue;
    int mortgageValue;
    int baseRental;
    int houseConstructionCost;
    int hotelConstructionCost;
    MortgageStatus mortgageStatus;
    InsuranceStatus insuranceStatus;
    int numberOfHouses;
    int numberOfHotels;
    int groupID;
    Player owner;
    char name[30];
    LoanStatus isLocked;
}Property;

typedef struct{
    int purchasePrice;
    int mortgageValue;
    int baseRental;
    MortgageStatus mortgageStatus;
    LoanStatus isLocked;
    Player owner;
    char name[30];
}Railway;

typedef struct{
    int purchasePrice;
    int mortgageValue;
    MortgageStatus mortgageStatus;
    LoanStatus isLocked;
    Player owner;
    char name[40];
}Utility;

typedef struct{
    EventType type;
    char name[30];
}Event;

typedef struct{
    SpecialType type;
    char name[20];
}Special;

typedef struct{
    char name[30];
}Bank;

typedef struct{
    int amount;
}Tax;

typedef union{
        Property property;
        Railway railway;
        Utility utility;
        Event event;
        Special special;
        Bank bank;
        Insurance insurance;
        Tax tax;

} Data;

typedef struct{
    int loanAmount;        
    int originalAmount;     
    int interestRate;        
    int roundsRemaining;     
    int collateralIndices[26]; 
    int collateralCount;
    int isActive;
} Loan;

typedef struct {
    sqType type;
    Data data;
} Square;

typedef struct {
    Property ownedProperties[22];
    Railway ownedRailways[4];
    Utility ownedUtilities[2];
}Owned;

typedef struct {
    Owned ownedItems;
    Loan ownedLoan;
    Insurance ownedInsurance[22];
    int lastPosition;
    int loanAmount;
    int position;
    int money;
    int lastDieVal;
    int currentRound;
    int lastRound;
    int utilityCount;
    int propertiesCount;
    int railwaysCount;
    int numberOfHotels;
    int jailedTurn;
    int isLoanActive;
    int numberOfHouses;
    Player player;
    Bankrupt isBankrupt;
    Jail inJail;
    activeCardType activeCardType;

}currentPlayer;

typedef struct {
    Property properties[22];
    int groupID;
    int count;
    char color[10];
}propertyGroup;

typedef struct {
    Square square;
    int AGGRESSIVE_INVESTOR_BID;
    int CONSERVATIVE_BANKER_BID;
    int RISK_TAKER_BID;
    int OPPORTUNISTIC_TRADER_BID;
    int currentBid;
    Player lastBidder;
    int status;
}Auction;

typedef struct{
    int rounds;
    int turn;
    isGameOver gameOver;
}currentStatus;

typedef struct {
    EconStatus econStatus;
    int currentInflationRate;  
    int currentLoanInterestRate; 
} EconomicState;

typedef struct {
    int index;
    int value;
} MortgageItems;


void initBoard(Square squares[],currentPlayer players[]);
void initPlayers(Square squares[],currentPlayer players[]);
void gameLoop();
void diceRoll(currentPlayer *player, Square squares[]);
void setOrder(currentPlayer players[],Square squares[]);
char* getPlayer(currentPlayer player);
void rollAndMove(currentPlayer players[], Square squares[],currentStatus *status,EconomicState *econStatus);

int getMaxRent(Square squares[],currentPlayer *cPlayer);
void payRent(currentPlayer players[],currentPlayer *currentPlayer,Square *square,int index,Square squares[]);


void buyProperty(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]);
void buyRailway(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]);
void buy(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]);

void startAuction(Square *square, currentPlayer players[]);
void AGG_BIDDING(Auction *auction, currentPlayer *player,int index);
void CON_BIDDING(Auction *auction, currentPlayer *player,int index);
void RISK_BIDDING(Auction *auction, currentPlayer *player,int index);
void OPP_BIDDING(Auction *auction, currentPlayer *player,int index);

int roundOff(double num);

void applyInflation(Square squares[], EconomicState *econ, int newRate);
int generateInflationRate();
void printMarketCondition(EconomicState *econ);
int getMaxRent(Square squares[],currentPlayer *cPlayer);

void handleJail(Square *square, currentPlayer *player,currentStatus *status,EconomicState *econStatus);
void handleBank(Square squares[],Square *square, currentPlayer *cPlayer,currentStatus *status,EconomicState *econStatus);
void releaseFromJail(currentPlayer *currentPlayer);
void checkAndReleaseFromJail(currentPlayer *currentPlayer,currentStatus *status);

int getNetWorth(currentPlayer *player, Square squares[]);
int getMaxLoanAmount(currentPlayer *player, Square squares[]);
char* getSquareName(Square *square);
int getOwnedItems(Square squares[], currentPlayer *current_player);

void setLoanInterestRate(EconomicState *econ);
int isLoanNeeded(currentPlayer *player, Square squares[], EconomicState *econStatus);
void obtainLoan(currentPlayer *player, Square squares[], int amount, EconomicState *econ);
void repayLoan(currentPlayer *player, int amount);
void repayLoanFull(currentPlayer *player);
void calLoanInterest(currentPlayer *player);
void checkLoanDefault(currentPlayer *player, Square squares[]);
int wantToRepay(Square squares[], currentPlayer *player, EconomicState *econ);
void extendLoan(currentPlayer *player);


int countPropertiesInGroup(Square squares[], int groupID);
int countOwnedInGroup(Square squares[], Player player, int groupID);
int getMinHousesInGroup(Square squares[], Player player, int groupID);
int canBuildHouse(Square squares[], currentPlayer *player, int index);
int canBuildHotel(Square squares[], currentPlayer *player, int index);
void buildHouse(Square squares[], currentPlayer *player, int index);
void buildHotel(Square squares[], currentPlayer *player, int index);
void handleConstruction(Square squares[], currentPlayer *player, EconomicState *econ);

void checkBankrupt(currentPlayer *player, Square squares[]);
void bankRupt(currentPlayer *player, Square squares[]);

int canAffordDebt(currentPlayer *player, Square squares[], int amount);
void raiseCashByMortgaging(currentPlayer *player, Square squares[], int neededAmount);
void collectDebt(currentPlayer *player, currentPlayer *creditor, Square squares[], int amount);

void checkWinner(currentPlayer players[],currentStatus *status,Square squares[]);
void gameDraw(currentPlayer players[],Square squares[],currentStatus *status);

int getTotalPropertyValue(Square squares[], currentPlayer *current_player);
void printWinnerAndExit(currentPlayer *winner, Square squares[]);
#endif