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
    Player owner;
    char name[30];
}Railway;

typedef struct{
    int purchasePrice;
    int mortgageValue;
    MortgageStatus mortgageStatus;
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
    int balance;
    int interestRate;
    Player owner;
    Data data;
}Loan;

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
    Loan ownedLoans[22];
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
    Player player;
    Bankrupt isBankrupt;
    Jail inJail;

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
}currentStatus;

typedef struct {
    int currentInflationRate;  
    int currentLoanInterestRate; 
} EconomicState;



void initBoard(Square squares[],currentPlayer players[]);
void initPlayers(Square squares[],currentPlayer players[]);
void gameLoop();
void diceRoll(currentPlayer *player, Square squares[]);
void setOrder(currentPlayer players[],Square squares[]);
char* getPlayer(currentPlayer player);
void rollAndMove(currentPlayer players[], Square squares[],currentStatus *status,EconomicState *econStatus);

int getMaxRent(Square squares[],currentPlayer *cPlayer);
void payRent(currentPlayer players[],currentPlayer *currentPlayer,Square *square,int index);
void bankRupt(currentPlayer *player);


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

void handleJail(Square *square, currentPlayer *player,currentStatus *status,EconomicState *econStatus);
void releaseFromJail(currentPlayer *currentPlayer);
void checkAndReleaseFromJail(currentPlayer *currentPlayer,currentStatus *status);

#endif