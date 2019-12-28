// proj2.cpp
/*
    Kevin Nguyen
    ICS46B
    Professor Shindler
*/

#include "proj2.hpp"
#include "LLQueue.hpp"

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

std::map<int, int> assignBusSeats(std::istream & in)
{
    std::string line;       //first line holds the number of window and aisle seats
    getline(in,line);
    int numSeats = atoi(line.c_str());

    //make a vector and queue for W
    //int stores i'th person W, std::string stores person W's preference list
    std::vector <std::pair <int, std::string>> wPpl;   //make a vector so that we can get A's current partner's
                                                        //preference list back when we put them back into the Queue
    LLQueue <std::pair <int, std::string>> wPplQ;
    for(int i=0; i<numSeats; i++)   //fill in the vector and Queue with window people
    {
        getline(in,line);
        wPpl.push_back(std::pair <int, std::string> ((i+1),line));
        wPplQ.enqueue(std::pair <int, std::string> ((i+1),line));
    }

    std::vector <std::pair <bool, std::string>> aPpl;       //bool stores whether A has a partner. True if A has a partner
    for(int i=0; i<numSeats; i++)                           //std::string stores A's preference list
    {
        getline(in,line);
        aPpl.push_back(std::pair <int, std::string> (false, line));
    }

    std::map<int, int> mapping; //the solution

    std::stringstream ss;   //for taking in the preferences

    /*
        while-loop:
            while wPplQ is not empty,
                dequeue the first W
                check first person, A, on their preference list
                if (A doesn't have a partner)
                    put into the map as a pair
                else if(A DOES have a partner)
                    check A's preference list
                    find A's partner
                    if (A prefers W)
                        switch partners
                        put A's current buddy back into the Queue
                    if (A prefers seat partner)
                        update dequeued W's preference list
                        put the dequeued W back into Queue
    */
    while(wPplQ.isEmpty() == false)
    {
        std::pair <int, std::string> deQuedW = wPplQ.front();
        wPplQ.dequeue();

        ss.clear();
        ss.str("");

        ss << deQuedW.second;   //putting W's preference list into ss
        int preferredA;         //the first person on the list W prefers

        ss >> preferredA;

        if(aPpl[preferredA-1].first == false)   //A has no partner
        {
            //pair them
            mapping[deQuedW.first] = preferredA;
            aPpl[preferredA-1].first = true;
        }

        else if(aPpl[preferredA-1].first == true)   //if A has a partner
        {
            ss.clear();
            ss.str("");
            ss << aPpl[preferredA-1].second;    //give stringstream the prefer list of A
            int preferredW;             //the first person on the list A prefers
            ss >> preferredW;

            int aBuddy=-1;          //holds A's current partner
            std::map<int, int>::iterator it = mapping.begin();
            while(aBuddy==-1)
            {
                    if(it->second == preferredA)
                    {
                        aBuddy = it->first; //this is the key, aka Aisle seat's current partner
                    }
                    it++;
            }//end while-loop

            bool switchedBuddy = false; //this is for the last if-statement
                                        //if its true that A switched partners,
                                        //don't put W back into the Queue
            while(preferredW != aBuddy)
            {
                if(deQuedW.first == preferredW)
                {
                    //switch partners
                    mapping.erase(aBuddy);
                    mapping[deQuedW.first] = preferredA;

                    //update preference W's preference list and put back into the Queue
                    wPpl[aBuddy-1].second.substr(2);
                    wPplQ.enqueue(wPpl[aBuddy-1]);

                    switchedBuddy = true;
                }//end if
                ss >> preferredW;
            }//end inner-while-loop

            //if exited while loop, it means A prefers current seat buddy, put deQuedW
            //back into wPpl
            if (switchedBuddy == false)
            {
                deQuedW.second = deQuedW.second.substr(2);
                wPplQ.enqueue(deQuedW);
            }
        }//end else-if

    }//end outer-while-loop

	return mapping;
}
