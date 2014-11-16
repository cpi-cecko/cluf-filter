#include <iostream>


#include "Market.h"


/*
	Искрено се извинявам, че не използвах собствена имплементация на контейнерите.
	Не прецених правилно времето, което ще ми отнеме да напиша домашното
	и като резултат се концентрирах най-вече върху имплементацията.
	В крайна сметка се е получило нещо горе долу работещо.
	Note to self: СДП не е толкова лесно. Трябва да отделя повече време.
*/

#define TEST_TICK(expression, tick) \
	if ((expression)) \
	{ \
		std::cout << "\tTick " << tick << " success!" << std::endl; \
	} \
	else \
	{ \
		std::cout << "\tTick " << tick << " FAIL!" << std::endl; \
	}

void TestTwoCashDesks()
{
	std::cout << "\n\nTestTwoCashDesks begins\n\n";

	Market newMarket(3, 10);

	const size_t TICK_ONE_SIZE = 1;
	Client clientsTickOne[TICK_ONE_SIZE] = { Client(3, false) }; 
	newMarket.AddClients(clientsTickOne, TICK_ONE_SIZE);

	MarketState marketState = newMarket.GetMarketState();
	TEST_TICK (marketState.numberOfCashDesks == 1 && 
			   marketState.numberOfClientsAtCashDesks[0] == 0 &&
			   marketState.numberOfClientsAtExpressCashDesk == 1, "one")

	const size_t TICK_TWO_SIZE = 1;
	Client clientsTickTwo[TICK_TWO_SIZE] = { Client(4, true) };
	newMarket.AddClients(clientsTickTwo, TICK_TWO_SIZE);

	marketState = newMarket.GetMarketState();
	TEST_TICK (marketState.numberOfCashDesks == 1 && 
			   marketState.numberOfClientsAtCashDesks[0] == 1 &&
			   marketState.numberOfClientsAtExpressCashDesk == 1, "two")

	const size_t TICK_THREE_SIZE = 1;
	Client clientsTickThree[TICK_THREE_SIZE] = { Client(10, false) };
	newMarket.AddClients(clientsTickThree, TICK_THREE_SIZE);

	marketState = newMarket.GetMarketState();
	TEST_TICK (marketState.numberOfCashDesks == 1 &&
			   marketState.numberOfClientsAtCashDesks[0] == 1 &&
			   marketState.numberOfClientsAtExpressCashDesk == 0, "three")

	const size_t TICK_FOUR_SIZE = 9;
	Client clientsTickFour[TICK_FOUR_SIZE] = 
	{
		Client(4, false), Client(2, true), Client(5, true),
		Client(1, false), Client(10, true), Client(0, true),
		Client(0, false), Client(1, true), Client(2, false)
	};
	newMarket.AddClients(clientsTickFour, TICK_FOUR_SIZE);

	marketState = newMarket.GetMarketState();
	TEST_TICK (marketState.numberOfCashDesks == 1 &&
			   marketState.numberOfClientsAtCashDesks[0] == 4 &&
			   marketState.numberOfClientsAtExpressCashDesk == 4, "four")

	const size_t TICK_FIVE_SIZE = 10;
	Client clientsTickFive[TICK_FIVE_SIZE];
	for (size_t i = 0; i < TICK_FIVE_SIZE; ++i)
	{
		clientsTickFive[i] = Client(10, true);
	}
	newMarket.AddClients(clientsTickFive, 10);

	marketState = newMarket.GetMarketState();
	TEST_TICK (marketState.numberOfCashDesks == 2 &&
			   marketState.numberOfClientsAtCashDesks[0] == 6 && marketState.numberOfClientsAtCashDesks[1] == 6 &&
			   marketState.numberOfClientsAtExpressCashDesk == 3, "five")

	const size_t TICK_SIX_SIZE = 30;
	Client clientsTickSix[TICK_SIX_SIZE];
	for (size_t i = 0; i < TICK_SIX_SIZE; ++i)
	{
		if (i < 5)
		{
			clientsTickSix[i] = Client(5, false);
		}
		else if (i < 7)
		{
			clientsTickSix[i] = Client(2, true);
		}
		else if (i < 27)
		{
			clientsTickSix[i] = Client(3, false);
		}
		else if (i < 30)
		{
			clientsTickSix[i] = Client(4, true);
		}
	}
	newMarket.AddClients(clientsTickSix, TICK_SIX_SIZE);

	marketState = newMarket.GetMarketState();
	TEST_TICK (marketState.numberOfCashDesks == 1 &&
			   marketState.numberOfClientsAtCashDesks[0] == 10 &&
			   marketState.numberOfClientsAtExpressCashDesk == 20, "six")

	const size_t TICK_SEVEN_SIZE = 10;
	Client clientsTickSeven[TICK_SEVEN_SIZE];
	for (size_t i = 0; i < TICK_SEVEN_SIZE; ++i)
	{
		if (i < 7)
		{
			clientsTickSeven[i] = Client(7, false);
		}
		else if (i < 10)
		{
			clientsTickSeven[i] = Client(4, false);
		}
	}
	newMarket.AddClients(clientsTickSeven, TICK_SEVEN_SIZE);

	marketState = newMarket.GetMarketState();
	TEST_TICK (marketState.numberOfCashDesks == 2 &&
			   marketState.numberOfClientsAtCashDesks[0] == 10 && marketState.numberOfClientsAtCashDesks[1] == 7 &&
			   marketState.numberOfClientsAtExpressCashDesk == 18, "seven")

	const size_t TICK_EIGHT_SIZE = 2;
	Client clientsTickEight[TICK_EIGHT_SIZE];
	for (size_t i = 0; i < TICK_EIGHT_SIZE; ++i)
	{
		clientsTickEight[i] = Client(2, true);
	}
	newMarket.AddClients(clientsTickEight, TICK_EIGHT_SIZE);

	marketState = newMarket.GetMarketState();
	TEST_TICK (marketState.numberOfCashDesks == 2 &&
			   marketState.numberOfClientsAtCashDesks[0] == 7 && marketState.numberOfClientsAtCashDesks[1] == 6 &&
			   marketState.numberOfClientsAtExpressCashDesk == 2, "eight")

	std::cout << "\n\nTestTwoCashDesks ends\n\n";
}


int main()
{
	TestTwoCashDesks();

	return 0;
}