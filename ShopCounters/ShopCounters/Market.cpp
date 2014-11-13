#include "Market.h"


Market::Market(int numberOfAllCashDesks)
	: marketState(numberOfAllCashDesks)
{
}

MarketState Market::GetMarketState() const
{
	return marketState;
}

ClientState Market::GetClientState(int clientID)
{
	ClientState resultClientState;
	for (QueueList::iterator queue = clientState.begin(); queue != clientState.end(); ++queue)
	{
		Queue tempQueue;
		while ( ! queue->empty())
		{
			ClientState currentClient = queue->front();
			tempQueue.push(currentClient);
			queue->pop();
			if (currentClient.client->id == clientID)
			{
				resultClientState = currentClient;
			}
		}
		(*queue) = tempQueue;
	}
	return resultClientState;
}

void Market::AddClients(Client *clients, int number)
{
}


////////////
// Client //
////////////
Client::Client(int newID, int newNumberOfGoods, bool newHasCreditCard)
	: id(newID), numberOfGoods(newNumberOfGoods), hasCreditCard(newHasCreditCard)
{
}


/////////////////
// ClientState //
/////////////////
ClientState::ClientState()
	: cashDeskPosition(-1), queuePosition(-1), client(NULL)
{
}

ClientState::ClientState(int newCashDeskPosition, int newQueuePosition, const Client &newClientData)
	: cashDeskPosition(newCashDeskPosition), queuePosition(newQueuePosition)
{
	client = new Client(newClientData.id, newClientData.numberOfGoods, newClientData.hasCreditCard);
}

ClientState::ClientState(const ClientState &other)
{
	if (this != &other)
	{
		CopyFrom(other);
	}
}

ClientState& ClientState::operator=(const ClientState &other)
{
	if (this != &other)
	{
		Destroy();
		CopyFrom(other);
	}
	return *this;
}

ClientState::~ClientState()
{
	Destroy();
}

void ClientState::CopyFrom(const ClientState &other)
{
	cashDeskPosition = other.cashDeskPosition;
	queuePosition = other.queuePosition;
	
	if (client)
	{
		delete client;
	}
	client = new Client(other.client->id, other.client->numberOfGoods, other.client->hasCreditCard);
}

void ClientState::Destroy()
{
	delete client;
}


/////////////////
// MarketState //
/////////////////
MarketState::MarketState(int newNumberOfCashDesks)
	: numberOfCashDesks(0), numberOfClientsAtCashDesks(NULL), numberOfClientsAtExpressCashDesk(0)
{
}

MarketState::MarketState(const MarketState &other)
{
	if (this != &other)
	{
		CopyFrom(other);
	}
}

MarketState& MarketState::operator=(const MarketState &other)
{
	if (this != &other)
	{
		Destroy();
		CopyFrom(other);
	}
	return *this;
}

MarketState::~MarketState()
{
	Destroy();
}

void MarketState::CopyFrom(const MarketState &other)
{
	numberOfCashDesks = other.numberOfCashDesks;
	numberOfClientsAtExpressCashDesk = other.numberOfClientsAtExpressCashDesk;

	if (numberOfClientsAtCashDesks)
	{
		delete [] numberOfClientsAtCashDesks;
	}
	numberOfClientsAtCashDesks = new int[numberOfCashDesks];
	for (size_t i = 0; i < numberOfCashDesks; ++i)
	{
		numberOfClientsAtCashDesks[i] = other.numberOfClientsAtCashDesks[i];
	}
}

void MarketState::Destroy()
{
	delete [] numberOfClientsAtCashDesks;
}