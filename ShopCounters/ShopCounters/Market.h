#ifndef MARKET_H
#define MARKET_H


#include <list> // TODO: Use custom impl
#include <deque>


struct Client
{
	int id;
	int numberOfGoods;
	bool hasCreditCard;

	Client();
	Client(int newNumberOfGoods, bool newHasCreditCard);
};

struct ClientState
{
	int cashDeskPosition; // cash desk index
	int queuePosition; // position in queue
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
	int numberOfCashDesks; // number of currently opened ordinary cash desks
	int *numberOfClientsAtCashDesks; // number of clients at each cash desk
	int numberOfClientsAtExpressCashDesk;

	MarketState(int allCashDesksCount);
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
	typedef std::deque<ClientState> Queue;
	typedef std::list<Queue> QueueList;
	QueueList cashDesks;
	MarketState marketState;

	int numberOfAllCashDesks;
	int maxClientsPerQueue;

	static int currentClientID;

public:
	Market(int newNumberOfAllCashDesks, int newMaxClientsPerQueue);
	void AddClients(Client *clients, int number);
	
	MarketState GetMarketState() const;
	ClientState GetClientState(int clientID) const;

private:
	void AdvanceAllWithOneTick(Queue *clientQueue);

	// Deallocates cash desk queue
	// Rearranges clients starting from the queue with the **least** index and moving on.
	void CloseCashDesk(int cashDeskIndex);
	void MoveClients(int cashDeskFrom, int cashDeskTo, int howMany);
	void OpenCashDesk(int cashDeskIndex, ClientState *clientsToMove, int clientsCount);

	// Returns a **copy** of the clients at the given cash desk
	// The **calee** owns the array
	ClientState* GetClientsAtCashDesk(int cashDeskIndex, size_t &clientsCount) const;

	// Removes a specified number of clients from the cash desk and puts them into an array.
	// asserts if the howMany is bigger than the queue's size.
	ClientState* RetrieveLastNClientsAt(int cashDeskIndex, int howMany);

	void AddClientsToCashDesk(int cashDeskIndex, ClientState *clients, int howMany);

	void ShuffleClientsToQueues(ClientState *clients, int howMany);

	static void AddClientsToQueue(Queue &queue, ClientState *clients, int howMany);
	static ClientState* RetrieveLastNClientsFromQueue(Queue *queue, int howMany);
};


#endif