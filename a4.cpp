#include <iostream>
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <locale>
#include <ctype.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>


using namespace std;

int main(int argc , char *argv[])
{
    if(argc<6)
    {
        cout<<"Invalid Configuration";
        return 0 ;
    }
    int pflag=0 ;
    int cflag=0 ;
    for(int i=1 ; i<4 ; i++)
    {
        for(int j=0 ; argv[i][j]!=0 ; j++)
        {
            switch(argv[i][j])
            {
            case '0':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break ;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            default:
                cflag=1;
            }
        }
    }
    if(cflag==1)
    {
        cout<<"Invalid Configuration";
        return 0 ;
    }
    if(pow(2,atoi(argv[1]))-1<atoi(argv[3]))
    {
        cout<<"Invalid Configuration";
        return 0 ;
    }
    for (int u=5 ; u<argc ; u++)
    {
        if(atoi(argv[u])>=pow(2,atoi(argv[1])))
        {
            pflag=1 ;
        }
    }
    for(int a=5 ; a<argc ; a++)
    {
        for (int b=0 ; argv[a][b]!=0 ; b++)
        {
            switch(argv[a][b])
            {
            case '0':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            default:
                pflag=1 ;
            }
        }
    }
    if(pflag==1)
    {
        cout<<"Invalid Packet";
        return 0 ;
    }

    int SeqNumOfBits=atoi(argv[1]) ;
    int WinSizeBits=atoi(argv[2]) ;
    int initSeq=atoi(argv[3]) ;
    int windowsize , MaxSeqNu ;
    int expected=initSeq ;
    int out_dropped=0 ;
    windowsize=pow(2,WinSizeBits) ;
    MaxSeqNu=pow(2,SeqNumOfBits)-1 ;
    int lowallow=expected ;
    int highallow=lowallow+windowsize-1 ;
    int recievearray[100] ;
    int waitarray[100] ;
    int dw=0 ;
    int zr=0 ;
    Queue wait ;
    Queue rec ;
    int var;
    if(strcmp(argv[4],":")!=0)
    {
        cout<<"Invalid Configuration";
        return 0 ;
    }
    if(WinSizeBits>SeqNumOfBits)
    {
        cout<<"Invalid Configuration";
        return 0 ;
    }
    for(int j=5 ; j<argc ; j++)
    {
        var=atoi(argv[j]) ;
        //first initialization j=5
        // if argc-1 is zero and the zero not in sequence
        if(j==argc-1 && var==0)
        {
            if(var==expected)
            {

            }
            else
            {
                out_dropped++ ;
                continue ;
            }
        }
        if(j==5)
        {
            if(var==expected)
            {
                rec.enqueue(var) ;
                expected=var+1 ;
                lowallow=expected ;
                highallow=lowallow+windowsize-1 ;
            }
            else
            {
                if(var<lowallow || (var>highallow || var>MaxSeqNu))
                {
                    out_dropped++ ;

                }
                else
                {
                    wait.enqueue(var) ;
                }
            }
        }// END of j=5
        else
        {
            // check empty of receive
            if(rec.isempty()==1)
            {
                //check queue receive insertion
                if(var==expected)
                {
                    rec.enqueue(var) ;
                    expected=var+1 ;
                    lowallow=expected ;
                    highallow=lowallow+windowsize-1 ;
                    // check for the waiting list
                    if(wait.isempty()==0)
                    {
                        while(wait.frontt()==expected)
                        {
                            expected=wait.frontt()+1 ;
                            lowallow=expected ;
                            highallow=lowallow+windowsize-1;
                            rec.enqueue(wait.dequeue()) ;
                            if(wait.isempty()==1)
                            {
                                break ;
                            }
                        }
                    }
                    else
                    {

                    }
                }
                else
                {
                    if(var<lowallow || (var>highallow || var>MaxSeqNu))
                    {
                        out_dropped++ ;
                    }
                    else
                    {
                        wait.enqueue(var) ;
                    }
                }
            }
            // if receiver is not empty
            else
            {
                if(var<lowallow || (var>highallow || var>MaxSeqNu))
                {
                    out_dropped++ ;
                }
                else
                {
                    if(var==expected)
                    {
                        rec.enqueue(var) ;
                        expected=var+1 ;
                        lowallow=expected ;
                        highallow=lowallow+windowsize-1 ;
                        if(wait.isempty()==0)
                        {
                            while(wait.frontt()==expected)
                            {
                                expected=wait.frontt()+1 ;
                                lowallow=expected ;
                                highallow=lowallow+windowsize-1 ;
                                rec.enqueue(wait.dequeue()) ;
                                if(wait.isempty()==1)
                                {
                                    break ;
                                }
                            }
                        }
                        else
                        {

                        }
                    }
                    else
                    {
                        if(var<lowallow || (var>highallow || var>MaxSeqNu))
                        {
                            out_dropped++ ;
                        }
                        else
                        {
                            wait.enqueue(var) ;
                        }
                    }
                }
            }
        }
        if(j!=argc-1)
        {
            if(atoi(argv[j+1])==0)
            {
                // if the expected is zero
                if(expected==0)
                {
                    continue ;
                }
                // check if the the arrayrec will be used
                if(expected==MaxSeqNu+1)
                {
                    while(!rec.isempty())
                    {
                        recievearray[zr]=rec.dequeue();
                        zr++ ;
                    }
                    expected=0 ;
                    lowallow=expected ;
                    highallow=lowallow+windowsize-1 ;
                }
                // check if the zero not in sequence
                else
                {
                    while(! wait.isempty())
                    {
                        waitarray[dw]=wait.dequeue();
                        dw++ ;
                    }
                    lowallow=0 ;
                    highallow=lowallow+windowsize-1 ;
                }
            }// if not equal zero do nothing
            else
            {

            }
        }
        // check if reaching the maximum sequence number
        if(expected==MaxSeqNu+1)
        {
            expected=0 ;
            lowallow=expected ;
            highallow=lowallow+windowsize-1 ;
            while(!rec.isempty())
            {
                recievearray[zr]=rec.dequeue();
                zr++ ;
            }
            while(!wait.isempty())
            {
                waitarray[dw]=wait.dequeue() ;
                dw++ ;
            }
        }
    }

    cout<<"R " ;
    for(int k=0 ; k<zr ; k++)
    {
        cout<<recievearray[k]<<" " ;
    }
    while(!rec.isempty())
    {
        cout<<rec.dequeue();
        cout<<" ";
    }
    cout<<"E "<<expected<<" W " ;
    for(int k=0 ; k<dw ; k++)
    {
        cout<<waitarray[k]<<" " ;
    }
    while(!wait.isempty())
    {
        cout<<wait.dequeue() ;
        cout<<" ";
    }
    cout<<"D# "<<out_dropped ;


    return 0;
}
