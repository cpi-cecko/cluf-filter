#include "Market.h"

#include <assert.h>


int Market::currentClientID = 0;


Market::Market(int newNumberOfAllCashDesks, size_t newMaxClientsPerQueue)
	: numberOfAllCashDesks(newNumberOfAllCashDesks), maxClientsPerQueue(newMaxClientsPerQueue), 
	  marketState(numberOfAllCashDesks)
{
	cashDesks.resize(numberOfAllCashDesks);
}

MarketState Market::GetMarketState() const
{
	return marketState;
}

ClientState Market::GetClientState(int clientID) const
{
	ClientState resultClientState;
	for (QueueList::const_iterator queue = cashDesks.begin(); queue != cashDesks.end(); ++queue)
	{
		for (Queue::const_iterator queueItem = queue->begin(); queueItem != queue->end(); ++queueItem)
		{
			if (queueItem->client->id == clientID)
			{
				return *queueItem;
			}
		}
	}
	return resultClientState;
}

// On every invocation of this method a 'tick' passes.
// Clients get reordered if necessary and new people come in.
void Market::AddClients(Client *clients, int number)
{
	assert (number > 0 && clients);

	// Cleans up old clients
	for (QueueList::iterator queue = cashDesks.begin(); queue != cashDesks.end(); ++queue)
	{
		while ( ! queue->empty())
		{
			if (queue->front().client->hasCreditCard || queue->front().currentTick > 1)
			{
				queue->pop_front();
			}
			else
			{
				AdvanceAllWithOneTick(&*queue);
				break;
			}
		}
	}

	// Manipulate clients *evil grin*
	for (size_t idx = 0; idx < number; ++idx)
	{
		if (clients[idx].numberOfGoods == 0)
		{
			continue;
		}
		else if (clients[idx].numberOfGoods <= 3 && 
			marketState.numberOfClientsAtExpressCashDesk < maxClientsPerQueue * 2)
		{
			++marketState.numberOfClientsAtExpressCashDesk;
			ClientState newClientState(cashDesks.size(), cashDesks.back().size() + 1, clients[idx]);
			cashDesks.back().push_back(newClientState);
		}
		else
		{
			size_t queueIdx = 0;
			for (QueueList::iterator queue = cashDesks.begin(); queue != cashDesks.end(); ++queue, ++queueIdx)
			{
				size_t queueSize = queue->size();
				if (queueSize + 1 > maxClientsPerQueue)
				{
					ClientState *halfClients = RetrieveLastNClientsFromQueue(*queue, queueSize / 2);
					assert (halfClients);
					ShuffleClientsToQueues(halfClients, queueSize / 2);
					delete [] halfClients;
				}
				else if (queueSize + 1 < maxClientsPerQueue / 10)
				{
					CloseCashDesk(queueIdx); // TODO: Could break the precioussss iterators
				}
				else // magnificent code follows!
				{
					// Yo dawg, I heard you like iterating, so I put and iterator loop inside your iterator loop
					// so you can iterate while iterating.
					size_t queueIdx2 = 0;
					for (QueueList::iterator queue2 = cashDesks.begin(); queue2 != cashDesks.end(); ++queue2)
					{
						if (queueIdx != queueIdx2 && 
							queue->size() - queue2->size() > maxClientsPerQueue / 8)
						{
							int diff = queue->size() - queue2->size();
							Queue *queueToHalve = diff > 0 ? &*queue : &*queue2;
							ClientState *halfClients = 
								RetrieveLastNClientsFromQueue(*queueToHalve, queueToHalve->size() / 2);
							assert (halfClients);
							ShuffleClientsToQueues(halfClients, queueToHalve->size() / 2);
							delete [] halfClients;
						}
					}
				}

				ClientState newClientState(queueIdx, queueSize, clients[idx]);
				queue->push_back(newClientState);
			}
		}

		++currentClientID;
	}
}

void Market::AdvanceAllWithOneTick(Queue *clientQueue)
{ 
	assert (clientQueue);

	// Hack for emulating ticks
	for (Queue::iterator queueItem = clientQueue->begin(); queueItem != clientQueue->end(); ++queueItem)
	{
		++queueItem->currentTick;
	}
}

void Market::CloseCashDesk(size_t cashDeskIndex)
{
	assert (cashDeskIndex < marketState.numberOfCashDesks);
	size_t clientsCount = 0;
	ClientState *clientsAtCashDesk = GetClientsAtCashDesk(cashDeskIndex, clientsCount);
	assert (clientsAtCashDesk);

	size_t queueIdx = 0;
	for (QueueList::iterator queue = cashDesks.begin();
	     queue != cashDesks.end() && clientsCount > 0;
		 ++queue, ++queueIdx)
	{
		if (queueIdx != cashDeskIndex && 
			marketState.numberOfClientsAtCashDesks[queueIdx] < maxClientsPerQueue)
		{
			int currentClients = marketState.numberOfClientsAtCashDesks[queueIdx];
			size_t toAdd = clientsCount;
			if (clientsCount > maxClientsPerQueue - currentClients)
			{
				toAdd = maxClientsPerQueue - currentClients;
				marketState.numberOfClientsAtCashDesks[queueIdx] += toAdd;
				clientsCount -= toAdd;
			}
			else
			{
				marketState.numberOfClientsAtCashDesks[queueIdx] += clientsCount;
				clientsCount = 0;
			}

			for (size_t clIdx = 0; clIdx < toAdd; ++clIdx)
			{
				clientsAtCashDesk[clIdx].cashDeskPosition = queueIdx;
				clientsAtCashDesk[clIdx].queuePosition = queue->size();
				queue->push_back(clientsAtCashDesk[clIdx]);
			}
		}
		else
		{
			queue->clear();
		}
	}

	delete [] clientsAtCashDesk;

	marketState.numberOfClientsAtCashDesks[cashDeskIndex] = -1;
}

void Market::MoveClients(size_t cashDeskFrom, size_t cashDeskTo, size_t howMany)
{
	ClientState *clientsToMove = new ClientState[howMany];
	clientsToMove = RetrieveLastNClientsAt(cashDeskFrom, howMany);
	assert (clientsToMove);

	AddClientsToCashDesk(cashDeskTo, clientsToMove, howMany);

	delete [] clientsToMove;
}

void Market::OpenCashDesk(size_t cashDeskIndex, ClientState *clientsToMove, size_t clientsCount)
{
	assert (marketState.numberOfClientsAtCashDesks[cashDeskIndex] == -1); // will crash; add check
	assert (clientsCount < maxClientsPerQueue);
	
	marketState.numberOfClientsAtCashDesks[cashDeskIndex] = clientsCount;

	if (cashDesks.size() < cashDeskIndex)
	{
		Queue newQueue;
		AddClientsToQueue(newQueue, clientsToMove, clientsCount);
		return;
	}

	AddClientsToCashDesk(cashDeskIndex, clientsToMove, clientsCount);
}

ClientState* Market::GetClientsAtCashDesk(size_t cashDeskIndex, size_t &clientsCount) const
{
	size_t queueIdx = 0;
	for (QueueList::const_iterator queue = cashDesks.begin(); queue != cashDesks.end(); ++queue, ++queueIdx)
	{
		if (queueIdx == cashDeskIndex)
		{
			ClientState *queueClients = new ClientState[queue->size()];
			for (Queue::const_iterator queueItem = queue->begin(); queueItem != queue->end(); ++queueItem)
			{
				queueClients[queueIdx] = *queueItem;
			}
			return queueClients;
		}
	}

	return NULL;
}

ClientState* Market::RetrieveLastNClientsAt(size_t cashDeskIndex, size_t howMany)
{
	size_t queueIdx = 0;
	for (QueueList::iterator queue = cashDesks.begin(); queue != cashDesks.end(); ++queue, ++queueIdx)
	{
		if (queueIdx == cashDeskIndex)
		{
			assert (howMany < queue->size());

			ClientState *queueClients = new ClientState[queue->size()];
			for (size_t clIdx = 0; clIdx < howMany; ++clIdx)
			{
				queueClients[clIdx] = queue->back(); 
				queue->pop_back();
			}
			return queueClients;
		}
	}

	return NULL;
}

ClientState* Market::RetrieveLastNClientsFromQueue(Queue &queue, size_t howMany)
{
	ClientState *retrieved = new ClientState[howMany];
	for (size_t idx = 0; idx < howMany; ++idx)
	{
		retrieved[idx] = queue.back();
		queue.pop_back();
	}
	return retrieved;
}

void Market::AddClientsToCashDesk(size_t cashDeskIndex, ClientState *clients, size_t howMany)
{
	size_t queueIdx = 0;
	for (QueueList::iterator queue = cashDesks.begin(); queue != cashDesks.end(); ++queue, ++queueIdx)
	{
		if (queueIdx == cashDeskIndex)
		{
			assert (howMany + queue->size() < maxClientsPerQueue);
			for (size_t clIdx = 0; clIdx < howMany; ++clIdx)
			{
				queue->push_back(clients[clIdx]);
			}
			return;
		}
	}
}

void Market::ShuffleClientsToQueues(ClientState *clients, size_t howMany)
{
	for (QueueList::iterator queue = cashDesks.begin(); queue != cashDesks.end(); ++queue)
	{
		if (queue->size() + howMany <= maxClientsPerQueue)
		{
			AddClientsToQueue(*queue, clients, howMany);
			return;
		}
		else
		{
			int toAddCount = maxClientsPerQueue - queue->size();
			AddClientsToQueue(*queue, clients, toAddCount);
			howMany = howMany - toAddCount;
			clients = &clients[toAddCount];
		}
	}
}

void Market::AddClientsToQueue(Queue &queue, ClientState *clients, size_t howMany)
{
	for (size_t clIdx = 0; clIdx < howMany; ++clIdx)
	{
		queue.push_back(clients[clIdx]);
	}
}


////////////
// Client //
////////////
Client::Client()
	: id(-1), numberOfGoods(-1), hasCreditCard(false)
{
}

Client::Client(int newNumberOfGoods, bool newHasCreditCard)
	: id(-1), numberOfGoods(newNumberOfGoods), hasCreditCard(newHasCreditCard)
{
}


/////////////////
// ClientState //
/////////////////
ClientState::ClientState()
	: cashDeskPosition(-1), queuePosition(-1), client(NULL), currentTick(0)
{
}

ClientState::ClientState(int newCashDeskPosition, int newQueuePosition, const Client &newClientData)
	: cashDeskPosition(newCashDeskPosition), queuePosition(newQueuePosition), currentTick(0)
{
	client = new Client(newClientData.numberOfGoods, newClientData.hasCreditCard);
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
	currentTick = other.currentTick;
	
	if (client)
	{
		delete client;
	}
	client = new Client(*other.client);
}

void ClientState::Destroy()
{
	delete client;
}


/////////////////
// MarketState //
/////////////////
MarketState::MarketState(int allCashDesksCount)
	: numberOfCashDesks(1), numberOfClientsAtExpressCashDesk(0)
{
	numberOfClientsAtCashDesks = new int[allCashDesksCount];
	for (size_t i = 0; i < allCashDesksCount; ++i)
	{
		numberOfClientsAtCashDesks[i] = -1;
	}
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