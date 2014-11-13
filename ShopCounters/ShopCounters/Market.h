#ifndef MARKET_H
#define MARKET_H


#include <list> // TODO: Use custom impl
#include <queue>


struct Client
{
	int id;
	int numberOfGoods;
	bool hasCreditCard;

	Client(int newID, int newNumberOfGoods, bool newHasCreditCard);
};

struct ClientState
{
	int cashDeskPosition;
	int queuePosition;
	Client *client;

	ClientState();
	ClientState(int newCashDeskPosition, int newQueuePosition, const Client &newClientData);
	ClientState(const ClientState &other);
	ClientState& operator=(const ClientState &other);
	~ClientState();

private:
	void CopyFrom(const ClientState &other);
	void Destroy();
};

struct MarketState
{
	int numberOfCashDesks;
	int *numberOfClientsAtCashDesks;
	int numberOfClientsAtExpressCashDesk;

	MarketState(int newNumberOfCashDesks);
	MarketState(const MarketState &other);
	MarketState& operator=(const MarketState &other);
	~MarketState();

private:
	void CopyFrom(const MarketState &other);
	void Destroy();
};

class Market
{
private:
	typedef std::queue<ClientState> Queue;
	typedef std::list<Queue> QueueList;
	QueueList clientState;
	MarketState marketState;

public:
	Market(int newNumberOfAllCashDesks);
	void AddClients(Client *clients, int number);
	
	MarketState GetMarketState() const;
	ClientState GetClientState(int clientID);
};


#endif