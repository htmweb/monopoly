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
    ELECTRICAL_FAILURE,
    EARTH_QUAKE,
    VANDALISM
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
}EconStatus;

typedef enum{
    NOT_GAME_OVER,
    GAME_OVER
}isGameOver;

typedef enum{
    TOURISM_HYPE,
    FUEL_SHORTAGE,
    HEAVY_FLOODS,
    POLITICAL_RALLY,
    STOCK_MARKET_RISE, 
    ECONOMIC_DOWNTURN, 
    HOUSING_SUBSIDY, 
    INTEREST_RATE_CUT,
    INTEREST_RATE_INCREASE, 
    TAX_AMNESTY, 
    POWER_FAILURE, 
    FOREIGN_FUNDING,
    PORT_EXPANSION, 
    FESTIVAL_SEASON, 
    LABOUR_STRIKE, 
    INSURANCE_DISCOUNT,
    PROPERTY_REVALUATION,
    CURRENCY_DEPRECIATION, 
    GOVERNMENT_GRANT, 
    NATIONAL_DISASTER
    
}activeNationalCardType;

typedef enum{
    TOURISM_BOOM,
    FUEL_CRISIS,
    HEAVY_MONSOON,
    ECONOMIC_RECESSION,
    STOCK_MARKET_BOOM,
    GOVERNMENT_HOUSING_PROGRAMME,
    FOREIGN_INVESTMENT,
    POLITICAL_UNREST
}economicEvents;

typedef enum{
    UNINSURED_DISASTER_HAPPENED,
    NOT_DISASTER_HAPPENED,
    INSURED_DISASTER_HAPPENED
}FinancialLoss;

typedef enum{
    INCREASE_PROPERTY_TAX,
    REDUCE_LOAN_INTEREST,
    HOUSING_SUBSIDY_REGULATION,
    LUXURY_PROPERTY_TAX,
    RAILWAY_MODERNIZATION,
    ELECTRICITY_TARIFF_REVISION,
    INSURANCE_REGULATION,
    ANTI_SPECULATION_ACT
}GovernmentRegulationType;

typedef struct{
    Player player;
    int diceVal;
}Order;

typedef struct{
    int amount;
    int premium;
    int compensation;
    int roundsRemaining;
    int isActive;
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
    int closedUntilRound;
    int isDamaged;
    int repairCost;
    int insuranceId;
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
    int roundsRemaining;
    activeNationalCardType type;
}ActiveNationalEvent;

typedef struct {
    Loan ownedLoan;
    Insurance ownedInsurance[22];
    ActiveNationalEvent activeNationalEvents[20];
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
    FinancialLoss financialLoss;
    Player player;
    Bankrupt isBankrupt;
    Jail inJail;
    activeNationalCardType activeNationalCardType;
    
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
    int currentNationalCardIndex;
    isGameOver gameOver;
}currentStatus;

typedef struct {
    double utilityIncome;
    double hotelIncomeBoost;
    double railwayValueIncrement;
    int currentInflationRate;  
    int currentLoanInterestRate;
    int constructionSuspended;
    int insurancePremiumDiscount;
    int regulationActive;                        
    int regulationRoundsRemaining;               
    int incomeTaxMultiplier;                    
    int luxuryPropertyTaxRate;                    
    int utilityRentMultiplier;                
    int maxUndevelopedProperties;
    EconStatus econStatus; 
    GovernmentRegulationType activeRegulation;
    economicEvents activeEconomicEvent;
} EconomicState;

typedef struct {
    int index;
    int value;
} MortgageItems;

typedef struct {
    char name[30];
    activeNationalCardType type;
}NationalEvent;

void initBoard(Square squares[],currentPlayer players[]);
void initPlayers(Square squares[],currentPlayer players[]);
void gameLoop();
void diceRoll(currentPlayer *player, Square squares[]);
void setOrder(currentPlayer players[],Square squares[]);
char* getPlayer(currentPlayer player);
void rollAndMove(currentPlayer players[], Square squares[],currentStatus *status,EconomicState *econStatus,NationalEvent nationalEvents[]);
void incrementRound(currentStatus *status,currentPlayer players[],Square squares[],EconomicState *econStatus);

int getMaxRent(Square squares[],currentPlayer *cPlayer);
void payRent(currentPlayer players[],currentPlayer *currentPlayer,Square *square,int index,Square squares[],EconomicState *econ);
void payRentAndPrint(int rent,char name[],currentPlayer players[],currentPlayer *owner,currentPlayer *currentPlayer,Square squares[],Square *square);

void buyProperty(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]);
void buyRailway(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]);
void buy(Square squares[], currentPlayer *current_player,int player_index,currentPlayer players[]);

int getPurchasePrice(Square *square);

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
void repayLoan(currentPlayer *player,Square squares[],int amount);
void repayLoanFull(currentPlayer *player,Square squares[]);
void calLoanInterest(currentPlayer *player,Square squares[]);
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

void checkPlayerBankrupt(currentPlayer players[], Square squares[]);
void checkBankrupt(currentPlayer *player, Square squares[]);
void bankRupt(currentPlayer *player, Square squares[]);

int canAffordDebt(currentPlayer *player, Square squares[], int amount);
void raiseCashBySell(currentPlayer *player, Square squares[], int neededAmount);
void collectDebt(currentPlayer *player, currentPlayer *creditor, Square squares[], int amount);

void checkWinner(currentPlayer players[],currentStatus *status,Square squares[]);
void gameDraw(currentPlayer players[],Square squares[],currentStatus *status);

int getTotalPropertyValue(Square squares[], currentPlayer *current_player);
void printWinnerAndExit(currentPlayer *winner, Square squares[]);

void initNationalEvents(NationalEvent nationalEvents[]);
void initEconomicEvents(economicEvents econEvents[]);
void triggerEconomicEvent(EconomicState *econ, Square squares[], economicEvents econEvents[]);

void triggerNationalEvent(currentPlayer *player, currentPlayer players[], Square squares[], NationalEvent nationalEvents[], EconomicState *econ, int *cardIndex);
void updateNationalEvents(currentPlayer players[]);
int hasActiveNationalEvent(currentPlayer *player, activeNationalCardType type);

void purchaseInsurance(Square squares[], currentPlayer *player, int propertyIndex, InsuranceType type);
void checkInsuranceExpiry(currentPlayer players[], Square squares[]);
void triggerDisaster(currentPlayer players[], Square squares[],DisasterType disasters[]);
void repairDamagedProperties(currentPlayer players[], Square squares[]);
int decideInsuranceType(currentPlayer *player, Square squares[], int propertyIndex);
void handleInsurancePurchase(Square squares[], currentPlayer *player);


void handleTax(Square *square, currentPlayer *player, Square squares[], EconomicState *econ);
void applyLuxuryPropertyTax(currentPlayer players[], Square squares[], EconomicState *econ);
void triggerGovernmentRegulation(EconomicState *econ, Square squares[], currentPlayer players[]);
#endif