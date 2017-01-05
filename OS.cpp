//
//  main.cpp
//  Lab 2
//
//  Created by Brian Lykes on 10/5/16.
//  Copyright © 2016 Brian Lykes. All rights reserved.
//

#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;


//Struct

struct memory
{//Partition Sizes, Status and Job number allocated
    int mno;
    int msize;
    string mstatus;
    string jobname;
    memory(){ mno = 0; msize = 0; mstatus = " wait"; jobname = ""; }
};
struct job
{//Job numbers and Sizes
    string jname;
    int jsize;
    string jstatus;
    job() { jname = ""; jsize = 0; jstatus = "not allocated"; }
};

//Function protoypes
void printresult(job[], int njobs, memory[], int parts);
void firstfit(job[], int njobs, memory[], int parts);
void bestfit(job[], int njobs, memory[], int parts);
void nextfit(job[], int njobs, memory[], int parts);
void worstfit(job[], int njobs, memory[], int parts);

//main method
int main()
{
    int njobs = 0;//Number of Jobs
    int np = 0;//Number of Partitions
    memory * m;//Array of Memory Locations
    job * j;//Array of jobs
    int temp[5];//Saves Original Partition Sizes
    
    cout << "Enter the number of memory partitions : ";
    cin >> np;
    m = new memory[np];
    for (int i = 0; i<np; i++)
    {
        cout << "Enter the size of each partition : ";
        cin >> m[i].msize;
        temp[i] = m[i].msize;
    }
    cout << endl;
    cout << "Enter the number of jobs : ";
    cin >> njobs;
    j = new job[njobs];
    for (int i = 0; i<njobs; i++)
    {
        j[i].jname = i + 49;
        cout << " Job " << i + 1<<": ";
        cin >> j[i].jsize;
    }
    cout << endl;
    cout << "First Fit:" << endl;
    firstfit(j, njobs, m, np);
    for (int i = 0; i < np; i++){//Resets Values for Next Algorithm
        m[i].mstatus = " wait";
        m[i].jobname = "";
        m[i].msize = temp[i];
    }
    for (int i = 0; i < njobs; i++)
        j[i].jstatus = "not allocated";
    cout << "Best Fit" << endl;
    bestfit(j, njobs, m, np);
    for (int i = 0; i < np; i++){//Resets Values for Next Algorithm
        m[i].mstatus = " wait";
        m[i].jobname = "";
        m[i].msize = temp[i];
    }
    for (int i = 0; i < njobs; i++)
        j[i].jstatus = "not allocated";
    cout << "Next Fit:" << endl;
    nextfit(j, njobs, m, np);
    for (int i = 0; i < np; i++){//Resets Values for Next Algorithm
        m[i].mstatus = " wait";
        m[i].jobname = "";
        m[i].msize = temp[i];
    }
    for (int i = 0; i < njobs; i++)
        j[i].jstatus = "not allocated";
    cout << "Worst Fit" << endl;
    worstfit(j, njobs, m, np);
    for (int i = 0; i < np; i++){//Resets Values for Next Algorithm
        m[i].mstatus = " wait";
        m[i].jobname = "";
        m[i].msize = temp[i];
    }
    for (int i = 0; i < njobs; i++)
        j[i].jstatus = "not allocated";
    
    system("pause");
    return 0;
}

//Function headers
// Prints Each Partition, it's status and the job that's allocated to it
void printresult(job j[], int njobs, memory m[], int np)
{
    int memorywaste = 0;
    int i = 0;
    for (i = 0; i<np; i++)
    {
        memorywaste = memorywaste + m[i].msize;
        cout << "Partition #" << i + 1 << " : " << m[i].jobname << " status :" << m[i].mstatus << endl;
    }
    for (i = 0; i<njobs; i++)
    {
        if (j[i].jname == "not allocated")
            cout << /*i+1*/j[i].jname << ": " << "is in wait" << endl;
    }
    cout << "\n Total memory waste :" << memorywaste << endl;
    cout << endl;
    
}


void firstfit(job j[], int njobs, memory m[], int np)
{
    int i = 0;
    int p = 0;
    while (i != njobs)
    {
        if (m[p].mstatus == "busy")
        {
            p++;
            if (p == np)
            {
                p = 0;
                j[i].jstatus = "not allocated";
                i++;
            }
        }
        else
        {
            if (j[i].jsize <= m[p].msize)
            {
                m[p].msize = (m[p].msize - j[i].jsize);
                m[p].mstatus = "busy";
                m[p].jobname = j[i].jname;
                j[i].jstatus = " allocated ";
                p = 0;
                i++;
            }
            else
            {
                p++;
                if (p == np)
                {
                    p = 0;
                    j[i].jstatus = "not allocated";
                    i++;
                }
            }
        }
    }
    printresult(j, njobs, m, np);
    
}


void bestfit(job j[], int njobs, memory m[], int np)
{
    int i = 0;
    int n = 0;
    int flag = 0;
    int min = -1;
    bool found = false;
    while (i != njobs)
    {
        min = -1;
        found = false;
        for (n = 0; n<np; n++)
        {
            if ((m[n].msize - j[i].jsize) >= 0)
            {
                min = (m[n].msize - j[i].jsize);
                flag = n;
                found = true;
            }
            if (found == true)
                n = np;
        }
        if (min == -1)
        {
            j[i].jstatus = "not allocated";
            i++;
        }
        else
        {
            for (int n = 0; n<np; n++)
            {
                if (min >(m[n].msize - j[i].jsize) && (m[n].msize - j[i].jsize >= 0))
                {
                    min = (m[n].msize - j[i].jsize);
                    flag = n;
                }
            }
            m[flag].msize = (m[flag].msize - j[i].jsize);
            m[flag].jobname = j[i].jname;
            m[flag].mstatus = "busy";
            j[i].jstatus = "allocated";
            i++;
        }
    }
    printresult(j, njobs, m, np);
}


void nextfit(job j[], int njobs, memory m[], int np)
{
    int n = 0;
    int p = 0;
    int temp = 0;
    while (n != njobs)
    {
        if (m[p].mstatus == "busy")
        {
            p++;
            temp++;
            if (p == np)
            {
                p = 0;
            }
            if (temp == np)
            {
                j[n].jstatus = "not allocated";
                n++;
                temp = 0;
            }
        }
        else
        {
            if (j[n].jsize <= m[p].msize)
            {
                m[p].msize = (m[p].msize - j[n].jsize);
                m[p].mstatus = " busy";
                m[p].jobname = j[n].jname;
                j[n].jstatus = "allocated";
                n++;
                p++;
                temp = 0;
                if (p == np)
                    p = 0;
            }
            else
            {
                p++;
                temp++;
                if (p == np)
                {
                    p = 0;
                }
                if (temp == np)
                {
                    j[n].jstatus = "not allocated";
                    n++;
                    temp = 0;
                }
            }
        }
    }
    printresult(j, njobs, m, np);
}

void worstfit(job j[], int njobs, memory m[], int np)
{
    int n = 0;
    int p = 0;
    int max = -1;
    int index = -1;
    for (n = 0; n<njobs; n++)
    {
        max = -1;
        index = -1;
        for (p = 0; p<np; p++)
            if (m[p].msize - j[n].jsize >max && m[p].msize - j[n].jsize >= 0)
            {
                max = m[p].msize - j[n].jsize;
                index = p;
            }
        if (index == -1)
            j[n].jstatus = "not allocated";
        else
        {
            m[index].msize = m[index].msize - j[n].jsize;
            m[index].mstatus = "busy";
            m[index].jobname = m[index].jobname + " & " + j[n].jname;
            j[n].jstatus = "allocated";
        }
    }
    printresult(j, njobs, m, np);
}
