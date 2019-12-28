
#include "gtest/gtest.h"
#include "LLQueue.hpp"
#include "proj2.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <map>


namespace{


// NOTE:  these are not intended as exhaustive tests.
	// This should get you started testing.
	// You should make your own additional tests for both queue
	// and for bus seats -- we certainly will be grading based
	// on more than just these five.

TEST(QueueTest, Test1)
{
	LLQueue<int> a;
	a.enqueue(5);
	EXPECT_TRUE( a.front() == 5 );
}

TEST(QueueTest, Test2)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	EXPECT_TRUE( a.front() == 5 );
}


TEST(QueueTest, Test3)
{
	LLQueue<int> a;
	a.enqueue(5);
	a.enqueue(3);
	a.dequeue();
	EXPECT_TRUE( a.front() == 3 );
}


TEST(BusSeats, Test1)
{
	std::string test4str = "3\n";
	test4str += "1 2 3\n2 3 1\n3 1 2\n";
	test4str += "1 2 3\n1 2 3\n1 2 3\n";
	std::istringstream stream( test4str );
	std::map<int, int> re = assignBusSeats( stream );
	EXPECT_TRUE( re.at(1) == 1 and re.at(2) == 2 && re.at(3) == 3 );
}


TEST(BusSeats, Test2)
{
	std::string test5str = "4\n";
	test5str += "2 4 1 3\n3 1 4 2\n2 3 1 4\n4 1 3 2\n";
	test5str += "2 1 4 3\n4 3 1 2\n1 4 3 2\n2 1 4 3";
	std::istringstream stream( test5str );
	std::map<int, int> re = assignBusSeats( stream );
	EXPECT_TRUE( re.at(1) == 4 and re.at(2) == 3 and re.at(3) == 2 && re.at(4) == 1 );
}

}