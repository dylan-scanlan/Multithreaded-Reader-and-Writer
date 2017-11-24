#include <iostream>
#include <thread>
#include <chrono>
#include "SharedObject.h"
using namespace std;

int run = 0;
class DataStored{
public:
	int tid;
	int counter;
	int time;
};
int main(void)
{
	Shared<DataStored> theOrigin("origin");
	std::cout << "I am a reader" << std::endl;
	while(run<=30){
		this_thread::sleep_for(chrono::seconds(1));
		cout<<theOrigin->tid<<" "<<theOrigin->counter<<" "<<theOrigin->time<<endl;
		run++;
	}
}
