/*
    Kevin Nguyen
    ICS46B
    Professor Shindler
*/

#ifndef __PROJ2_QUEUE_HPP
#define __PROJ2_QUEUE_HPP

#include "runtimeexcept.hpp"

class QueueEmptyException : public RuntimeException 
{
public:
	QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};


template<typename Object>
class LLQueue
{
private:
	// fill in private member data here
    /*
        node is the struct that will go into the Linked List Queue
    */
	struct node
	{
        Object element;
        node* nextNode;
	};
	//Queue has front and back pointers for enqueueing and dequeueing
	node* frontNode;
	node* backNode;
	int count;

public:
	LLQueue();

//	In principle, you should have copy constructors and 
// assignment operators implemented.
// I am not going to require it for this assignment.
//	LLQueue(const LLQueue & st);
//	LLQueue & operator=(const LLQueue & st);
    /*
        ~LLQueue() removes all the nodes in the Queue
    */
	~LLQueue()
	{
		    while(!isEmpty())
		    {
                dequeue();
		    }
	}

	int size() const noexcept;
	bool isEmpty() const noexcept;

	Object & front();
	const Object & front() const;

	void enqueue(const Object & elem);

// does not return anything.  Just removes. 
	void dequeue();
};

/*Constructor:LLQueue()
    initialize frontNode, backNode and count
*/
template<typename Object>
LLQueue<Object>::LLQueue()
{
    frontNode = nullptr;
    backNode = nullptr;
    count = 0;
}

/*size()
    returns the number of elements in the queue.
    Will not change the queue in any way.
*/
template<typename Object>
int LLQueue<Object>::size() const noexcept
{
    return count;
}

/*isEmpty()
    returns bool value
        if count equals zero, queue is empty, return true
        otherwise, queue not empty, return false
*/
template<typename Object>
bool LLQueue<Object>::isEmpty() const noexcept
{
    return (count==0);
}

/*
    front()
    returns the element of front
*/
template<typename Object>
Object & LLQueue<Object>::front()
{
    if(isEmpty())
        throw QueueEmptyException("Queue is empty!");
    return frontNode->element;
}

template<typename Object>
const Object & LLQueue<Object>::front() const
{
    if(isEmpty())
        throw QueueEmptyException("Queue is empty!");
    return frontNode->element;
}

/*
    void enqueue() puts the element into a node and puts the node into the Queue
    if the Queue was empty, front and back node points to that one node
    otherwise, we enqueue from the back and the back node will update to the new
    node in the Queue
*/
template<typename Object>
void LLQueue<Object>::enqueue(const Object & elem)
{
    node* newNode = new node{elem, nullptr};

    if(isEmpty())
    {
        frontNode = newNode;
        backNode = newNode;
    }
    else
    {   //Q not empty
        //insert from the rear
        backNode->nextNode = newNode;
        backNode = newNode;
    }
    count++;        //update count
}

/*
    void dequeue() removes the first node in the queue
    if the queue has one item, when we remove, we need to set the
    front and back to nullptr so nothing weird happens
    otherwise, if there are other nodes in the queue, just update front to be
    the second element in the list.
*/
template<typename Object>
void LLQueue<Object>::dequeue()
{
    if(isEmpty())
    {
        throw QueueEmptyException("Queue is empty! Cannot dequeue!");
    }
    else if(size()==1)
    {
        node* tempNode = frontNode;
        frontNode = nullptr;
        backNode = nullptr;
        delete tempNode;
    }
    else
    {
        node* tempNode = frontNode;
        frontNode = frontNode->nextNode;
        delete tempNode;
    }
    count--;
}


#endif 
