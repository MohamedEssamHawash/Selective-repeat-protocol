#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include<iostream>
using namespace std ;

typedef int queueelemtype ;

class Queue
{
public:
    Queue() ;
    void enqueue (const queueelemtype &item) ;
    queueelemtype dequeue () ;
    bool isempty () ;
    int drop () ;
    queueelemtype frontt() ;
private:
    struct node ;
    typedef node* link ;
    struct node
    {
        link next ;
        queueelemtype elem ;
    };
    int dropped ;
    link frnt ;
    link rear ;
};

Queue ::Queue()
{
    rear=NULL ;
    frnt=NULL ;
    dropped=0 ;
}

void Queue ::enqueue(const queueelemtype &item)
{
    link addednode ;
    int flag=0 ;
    addednode=new node ;
    addednode->elem =item ;
    link ptr ;
    ptr=frnt ;
    if(frnt==NULL)
    {
        addednode->next=NULL ;
        frnt=addednode ;
        rear=addednode ;
    }
    else if (item==frnt->elem)
    {
        dropped++ ;
    }
    else if(item < frnt->elem)
    {
        addednode->next=frnt ;
        frnt=addednode ;
    }
    else
    {
        while(ptr->next != NULL && item > ptr->next->elem)
        {
            ptr=ptr->next ;
        }
        if(ptr->next==NULL)
        {
            flag=1 ;
        }
        if(flag==0 && ptr->next->elem == item)
        {
            dropped++ ;
            delete addednode ;

        }
        else
        {
            addednode->next = ptr->next ;
            ptr->next = addednode ;
            if(addednode->next==NULL)
            {
                rear=addednode ;
            }
        }
    }
}

queueelemtype Queue ::dequeue()
{
    link ptr ;
    ptr=frnt ;
    queueelemtype item ;
    item=ptr->elem ;
    frnt=frnt->next ;
    delete ptr ;
    if(frnt==NULL)
    {
        rear=NULL ;
    }
    return item ;
}

bool Queue ::isempty()
{
    if(frnt==NULL)
    {
        return true ;
    }
    else
    {
        return false ;
    }
}

int Queue ::drop()
{
    return dropped ;
}

queueelemtype Queue ::frontt()
{
    queueelemtype item ;
    item=frnt->elem ;
    return item ;
}

#endif // QUEUE_H_INCLUDED
