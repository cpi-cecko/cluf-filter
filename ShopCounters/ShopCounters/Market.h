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
	Client(int newID, int newNumberOfGoods, bool newHasCreditCard);
};

struct ClientState
{
	int cashDeskPosition; // cash desk index
	int queuePosition; // position in queue
	Client *client;

	int currentTick;

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
	int *numberOfClientsAtCashDesks; // number of clients at each ordinary cash desk
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
	size_t maxClientsPerQueue;

	static int currentClientID;

public:
	Market(int newNumberOfAllCashDesks, size_t newMaxClientsPerQueue);
	void AddClients(Client *clients, int number);
	
	MarketState GetMarketState() const;
	ClientState GetClientState(int clientID) const;

private:
	void AdvanceAllWithOneTick(Queue *clientQueue);

	// Deallocates cash desk queue
	// Rearranges clients starting from the queue with the **least** index and moving on.
	void CloseCashDesk(size_t cashDeskIndex);
	void MoveClients(size_t cashDeskFrom, size_t cashDeskTo, size_t howMany);
	void OpenCashDesk(size_t cashDeskIndex, ClientState *clientsToMove, size_t clientsCount);

	// Returns a **copy** of the clients at the given cash desk
	// The **calee** owns the array
	ClientState* GetClientsAtCashDesk(size_t cashDeskIndex, size_t &clientsCount) const;

	// Removes a specified number of clients from the cash desk and puts them into an array.
	// asserts if the howMany is bigger than the queue's size.
	ClientState* RetrieveLastNClientsAt(size_t cashDeskIndex, size_t howMany);

	void AddClientsToCashDesk(size_t cashDeskIndex, ClientState *clients, size_t howMany);

	void ShuffleClientsToQueues(ClientState *clients, size_t howMany, size_t fromQueueIdx);

	static void AddClientsToQueue(Queue &queue, ClientState *clients, size_t howMany);
	static ClientState* RetrieveLastNClientsFromQueue(Queue &queue, size_t howMany);
};


#endif