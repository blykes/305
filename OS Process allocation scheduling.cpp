//
//  main.cpp
//  Lab 3 Procs
//
//  Created by Brian Lykes on 10/23/16.
//  Copyright © 2016 Brian Lykes. All rights reserved.
//
//	use -std=c++11 to compile
//	g++ -std=c++11 -o <executable name> <filename.cpp> 

/* 
This program allows the user to input the name of a process, the arrical time, CPU time and priority. 
The output shows these according to algorithm with the average turnaround time for each. 
*/

#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;

struct process
{
    int arrivalt;
    int cput;
    int complt;
    int pr;
    float tart;
    string pname;
    process(){ arrivalt = 0; cput = 0; complt = 0; pr = 0; tart = 0; pname = ""; }
}temp;


int ch;
int totaltime;
int n = 0;
int i = 0;
int j, x;
int cst = 0;
int minct = 0;
int cputime;
float avgtat = 0;


void firstserve(process[], int n);
void shortestjobnext(process[], int n);
void priority(process[], int n);
void print(process[], int n);


int main()
{
    process *a;
    
    cout << "Enter the Number of Processes : ";//Process Input
    cin >> n;
    cout << endl;
    a = new process[n];
    for (int i = 0; i<n; i++)
    {
        cout << endl;
        cout << "Enter the Name of the Process , Arrival Time , CPU Time  and Priority \n";
        cin >> a[i].pname >> a[i].arrivalt >> a[i].cput >> a[i].pr;
        
    }
    
    // Sorting Processes by Arrival time
    for (int i = 0; i<n; i++)
    {
        for (int j = i; j >= 1; j--)
        {
            if (a[j].arrivalt < a[j - 1].arrivalt)
            {
                temp = a[j - 1];
                a[j - 1] = a[j];
                a[j] = temp;
            }
        }
    }
    
    
    //Calculating Total Time
    totaltime += a[0].arrivalt + a[0].cput;
    for (int i = 1; i < n; i++)
    {
        if (a[i].arrivalt > totaltime)
            
            totaltime = a[i].arrivalt;
        totaltime += a[i].cput;
        
    }
    cout << "\n----------- FIRST COME FIRST SERVE------------" << endl;
    firstserve(a, n);
    cout << "\n------------ SHORTEST JOB NEXT ---------------- " << endl;
    shortestjobnext(a, n);
    cout << "\n---------------- PRIORITY SCHEDULING----------------" << endl;
    priority(a, n);
    //system("pause");
    return 0;
}// End of Main

// Print Function for Output
void print(process a[], int n)
{
    int i = 0;
    float avgtat = 0;
    for (i = 0; i<n; i++)
    {
        a[i].tart = a[i].complt - a[i].arrivalt;
    }
    for (i = 0; i<n; i++)
    {
        avgtat += a[i].tart;
    }
    
    avgtat = avgtat / n;
    
    cout << "Name" << "\t Arrival " << "\t CPUTime " << "\t Priority" << "\t Completed" << "\t TA Time \n";
    
    for (i = 0; i<n; i++)
    {
        cout << a[i].pname << "\t " << a[i].arrivalt << "\t\t" << a[i].cput << "\t\t" << a[i].pr << "\t\t" << a[i].complt << "\t\t" << a[i].tart << "\n";
    }
    
    cout << " \n Average Turnaround Time= " << avgtat;
    cout << endl;
} // End of print

// FUNCTION FOR FIRST COME FIRST SERVE
void firstserve(process a[], int n)
{
    process *b,tmp;
    b = new process[n];
    
    for (int i = 0; i < n; i++)//Copying Array of processes for Manipulation
    {
        b[i].arrivalt = a[i].arrivalt;
        b[i].cput = a[i].cput;
        b[i].complt = a[i].complt;
        b[i].pr = a[i].pr;
        b[i].tart = a[i].tart;
        b[i].pname = a[i].pname;
    }
    int i;
    int temp;
    int cputime = b[0].arrivalt;
    b[0].complt = cputime + b[0].cput;
    cputime = b[0].complt;
    
    for (i = 1; i<n; i++)
    {
        temp = b[i].arrivalt;
        if (temp > cputime)
            cputime = temp;
        b[i].complt = cputime + b[i].cput;
        cputime = b[i].complt;
    }
    for (int j = 1; j < n; j++){//Organizing Processes by Completion Time for Output after algoritm is completed.
        for (int i = 0; i < n - 1; i++)
        {
            if (b[i].complt > b[i + 1].complt){
                tmp.arrivalt = b[i].arrivalt;
                b[i].arrivalt = b[i + 1].arrivalt;
                b[i + 1].arrivalt = tmp.arrivalt;
                tmp.complt = b[i].complt;
                b[i].complt = b[i + 1].complt;
                b[i + 1].complt = tmp.complt;
                tmp.cput = b[i].cput;
                b[i].cput = b[i + 1].cput;
                b[i + 1].cput = tmp.cput;
                tmp.pr = b[i].pr;
                b[i].pr = b[i + 1].pr;
                b[i + 1].pr = tmp.pr;
                tmp.tart = b[i].tart;
                b[i].tart = b[i + 1].tart;
                b[i + 1].tart = tmp.tart;
                tmp.pname = b[i].pname;
                b[i].pname = b[i + 1].pname;
                b[i + 1].pname = tmp.pname;
            }
        }
    }
    print(b, n);
}// End of firstserve

//FUNCTION FOR SHORTEST JOB NEXT
void shortestjobnext(process a[], int n)
{
    process *b, tmp;
    b = new process[n];
    
    for (int i = 0; i < n; i++)//Copying Array of processes for Manipulation
    {
        b[i].arrivalt = a[i].arrivalt;
        b[i].cput = a[i].cput;
        b[i].complt = a[i].complt;
        b[i].pr = a[i].pr;
        b[i].tart = a[i].tart;
        b[i].pname = a[i].pname;
    }
    
    int time = 0;
    int x = 0;
    int minct = 0;
    while (time < totaltime)
    {
        int j = 0;
        for (int i = 0; i<n; i++)
        {
            if (b[i].arrivalt <= time)
            {
                j = i + 1;
            }
        }
        if (j>0)
        {
            int x = 0;
            minct = b[0].cput;
            for (int i = 1; i<j; i++)
            {
                if (minct > b[i].cput)
                {
                    x = i;
                    minct = b[i].cput;
                }
            }
            time += b[x].cput;
            b[x].complt = time;
            b[x].cput += 1000; // done so that same CPU Time is not choosen again
            b[x].arrivalt += 1000;// done so that same Arrival Time is not choosen again
        }
        else
        {
            time++;
        }
    }//End of While
    
    for (int i = 0; i<n; i++)
    {
        b[i].cput -= 1000;     // done to restore back to normal time
        b[i].arrivalt -= 1000;// done to restore back to normal time
    }
    for (int j = 1; j < n; j++){//Organizing Processes by Completion Time for Output after algoritm is completed.
        for (int i = 0; i < n - 1; i++)
        {
            if (b[i].complt > b[i + 1].complt){
                tmp.arrivalt = b[i].arrivalt;
                b[i].arrivalt = b[i + 1].arrivalt;
                b[i + 1].arrivalt = tmp.arrivalt;
                tmp.complt = b[i].complt;
                b[i].complt = b[i + 1].complt;
                b[i + 1].complt = tmp.complt;
                tmp.cput = b[i].cput;
                b[i].cput = b[i + 1].cput;
                b[i + 1].cput = tmp.cput;
                tmp.pr = b[i].pr;
                b[i].pr = b[i + 1].pr;
                b[i + 1].pr = tmp.pr;
                tmp.tart = b[i].tart;
                b[i].tart = b[i + 1].tart;
                b[i + 1].tart = tmp.tart;
                tmp.pname = b[i].pname;
                b[i].pname = b[i + 1].pname;
                b[i + 1].pname = tmp.pname;
            }
        }
    }
    
    print(b, n);
    
}// End of shortestjobnext

//FUNCTION FOR PRIORITY ALGORITHM
void priority(process a[], int n)
{
    process *b,tmp;
    b = new process[n];
    for (int i = 0; i < n; i++)//Copying Array of processes for Manipulation
    {
        b[i].arrivalt = a[i].arrivalt;
        b[i].cput = a[i].cput;
        b[i].complt = a[i].complt;
        b[i].pr = a[i].pr;
        b[i].tart = a[i].tart;
        b[i].pname = a[i].pname;
    }
    int  time = 0;
    while (time<totaltime)
    {
        j = 0;
        for (i = 0; i<n; i++)
        {
            if (b[i].arrivalt <= time)
            {
                j = i + 1;
            }
        }
        if (j>0)
        {
            int x = 0;
            int minpr = b[0].pr;
            for (i = 1; i<j; i++)
            {
                if (minpr>b[i].pr)
                {
                    x = i;
                    minpr = b[i].pr;
                }
                else
                    if (minpr == b[i].pr)
                    {
                        if (b[x].arrivalt> b[i].arrivalt)
                        {
                            x = i;
                            minpr = b[i].pr;
                        }
                        else if (b[x].arrivalt == b[i].arrivalt)
                        {
                            if (b[x].cput>b[i].cput)
                            {
                                x = i;
                                minpr = b[i].pr;
                            }
                        }
                    }
            }// End of for loop
            time += b[x].cput;
            b[x].complt = time;
            b[x].pr += 1000;    // done so that same priority is not choosen again
            b[x].arrivalt += 1000; // done so that same arrival time is not choosen again
        }// End of if
        else
        {
            time++;
        }
    }// End of while loop
    for (int i = 0; i<n; i++)
    {
        b[i].pr -= 1000; // done to set it back to normal
        b[i].arrivalt -= 1000;// done to set it back to normal
    }
    for (int j = 1; j < n; j++){//Organizing Processes by Completion Time for Output after algoritm is completed.
        for (int i = 0; i < n - 1; i++)
        {
            if (b[i].complt > b[i + 1].complt){
                tmp.arrivalt = b[i].arrivalt;
                b[i].arrivalt = b[i + 1].arrivalt;
                b[i + 1].arrivalt = tmp.arrivalt;
                tmp.complt = b[i].complt;
                b[i].complt = b[i + 1].complt;
                b[i + 1].complt = tmp.complt;
                tmp.cput = b[i].cput;
                b[i].cput = b[i + 1].cput;
                b[i + 1].cput = tmp.cput;
                tmp.pr = b[i].pr;
                b[i].pr = b[i + 1].pr;
                b[i + 1].pr = tmp.pr;
                tmp.tart = b[i].tart;
                b[i].tart = b[i + 1].tart;
                b[i + 1].tart = tmp.tart;
                tmp.pname = b[i].pname;
                b[i].pname = b[i + 1].pname;
                b[i + 1].pname = tmp.pname;
            }
        }
    }
    
    print(b, n);
    
}// End of priority
