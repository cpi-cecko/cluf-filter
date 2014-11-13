#ifndef MARKET_H
#define MARKET_H


struct Client
{
	int id;
	int numberOfGoods;
	bool hasCreditCard;
};

struct ClientState
{
	int cashDeskPosition;
	int queuePosition;
	Client *client;
};

struct MarketState
{
	int numberOfCashDesks;
	int *numberOfClientsAtCashDesks;
	int numberOfClientsAtExpressCashDesk;
};

class Market
{
public:
	Market(int numberOfAllCashDesks);
	void AddClient(Client *clients, int number);
	
	MarketState GetMarketState();
	ClientState GetClientState();
};


#endif