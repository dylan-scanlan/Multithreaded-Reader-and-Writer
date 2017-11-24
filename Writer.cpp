#include <iostream>
#include <thread>
#include <chrono>
#include "SharedObject.h"
#include <time.h>
#include "Semaphore.h"
using namespace std;

///home/ubuntu/se3313_labs/Lab3/se3313-2017-Lab3-master

bool run = true;

class DataStored{
public:
	int tid;
	int counter;
	int time;
};

//Thread tList[];
void tFunction(int id, int threadTime){
	int i = 0;
	time_t prev = time(0);
	Shared<DataStored> theOrigin("origin");
	Semaphore sem("access");
	Semaphore sem2("reader");
	while(run){
		this_thread::sleep_for(chrono::seconds(threadTime));
		sem.Wait();
		//sem2.Wait();
		double diff = difftime(time(0), prev);
		prev=time(0);		
		theOrigin->tid=id;
		theOrigin->counter=i;
		theOrigin->time=diff;
		//cout<<theOrigin->tid<<" "<<theOrigin->counter<<" "<<theOrigin->time<<endl;
		i++;
		sem2.Signal();
		sem.Signal();
	}
	cout<<"Thread "<<id<<" terminating"<<endl;
}
int main(void)
{
	std::cout << "I am a Writer" << std::endl;
	string input;
	int id=0;
	Shared<DataStored> theOrigin("origin",true);
	Semaphore sem("access",1,true);
	Semaphore sem2("reader",1,true);
	while(run){
		cout << "Would you like to create a writer thread? " << endl;
		cin >> input;
		if(input == "y"){
			cout << "What is the delay time for the new thread? " << endl;
			int threadTime;
			cin >> threadTime;
			thread t(tFunction, id, threadTime);
			t.detach();
			id++;
		}
		else{
			run = false;
		}
	}
	this_thread::sleep_for(chrono::seconds(5));
	cout<<"Main terminating"<<endl;
}
