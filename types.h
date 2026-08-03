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

typedef enum {
    AGGRESSIVE_INVESTOR,
    CONSERVATIVE_BANKER,
    RISK_TAKER,
    OPPORTUNISTIC_TRADER
} Player;

typedef enum {
    MORTGAGED,
    UNMORTGAGED
}MortgageStatus;

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
    int mortgageValue;
    int baseRental;
    int houseConstructionCost;
    int hotelConstructionCost;
    MortgageStatus mortgageStatus;
    InsuranceStatus insuranceStatus;
    int numberOfBuildings;
    int groupID;
    Player owner;
    char name[30];
}Property;

typedef struct{
    int purchasePrice;
    int mortgageValue;
    MortgageStatus mortgageStatus;
    Player owner;
    char name[30];
}Railway;

typedef struct{
    int purchasePrice;
    int mortgageValue;
    MortgageStatus mortgageStatus;
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
    Player player;
    int lastPosition;
    int position;
    int money;
    int lastTurnVal;
    int currentRound;
    int lastRound;

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


void initBoard();
void initPlayers(Square squares[40]);
void gameLoop(currentPlayer players[4],Square squares[40]);
void diceRoll(currentPlayer *player, Square squares[40]);
void setOrder(currentPlayer players[4],Square squares[40]);
char* getPlayer(currentPlayer player);
void rollAndMove(currentPlayer players[4], Square squares[40]);
void playerActivities(currentPlayer *player,Square squares[40]);

void aggressiveInvestor(Square sqaures[40], currentPlayer *current_player);
void conservativeBanker(Square sqaures[40],currentPlayer *current_player);
void riskTaker(Square sqaures[40], currentPlayer *current_player);
void oppurtunisticTrader(Square sqaures[40], currentPlayer *current_player);

void startAuction(Square *square, currentPlayer players[4]);
void AGG_BIDDING(Auction *auction, currentPlayer *player);
void CON_BIDDING(Auction *auction, currentPlayer *player);
void RISK_BIDDING(Auction *auction, currentPlayer *player);
void OPP_BIDDING(Auction *auction, currentPlayer *player);
#endif