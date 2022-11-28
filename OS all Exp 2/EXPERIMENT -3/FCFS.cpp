#include<iostream>								//FCFS program
#include<math.h>
using namespace std;
class Process
{
	public:
		char proc_id;
		int at;
		int bt,st,ft;
		int rt,wt;
		float tr;		
		Process()
		{at = 0;}
		void ProcessId()
		{
			cout<<"\nEnter Process_Id : ";
			cin>>proc_id;
		}
		void BurstTime()
		{
			cout<<"\nEnter burst time for the process : ";
			cin>>bt;
		}
		void display()
		{
			cout<<"Process id :"<<proc_id<<" Burst time :"<<bt<<" Starting time :"<<st<<" Finishing time :"<<ft<<" Response time :"<<rt;
			cout<<"Waiting time :"<<wt<<" Turnaround time :"<<tr<<"  Parameter :"<<tr/bt;
			cout<<endl;
		}
		
};

int main()
{
	Process p[5];float s1=0;
	float s2=0;float s3=0;float s4=0;
	int starting = 0;
	for(int i=0;i<=4;i++)
	{
		p[i].ProcessId();
		p[i].BurstTime();
	}
	p[0].st = 0;
	for(int i=1;i<=4;i++)
	{
		p[i].st = p[i-1].st+p[i-1].bt;						//  finding the respective starting time of the processes
	}
	for(int i=1;i<=4;i++)
	{
		p[i].ft = p[i].st+p[i].bt;						//  finding the respective Ending time of the processes
		p[i].rt = p[i].st;						        //  finding the  response time of the processes
		p[i].wt = p[i].st;							//  finding the waiting time of the processes 
	}
	for(int i=0;i<=4;i++)
	{
		p[i].tr = p[i].ft;							//  finding the turnaround time of the processes
	}
	for(int i=0;i<=4;i++)
	{
		s1=s1+p[i].rt;
		s2=s2+p[i].wt;
		s3=s3+p[i].tr;
		s4=s4+((p[i].tr)/(p[i].bt)); 
	}
	for(int i=0;i<=4;i++)
	{
		p[i].display();
	}
	cout<<endl<<endl<<endl;
	cout<<"Average Response time : "<<s1/5<<endl;
	cout<<"Average Waiting time : "<<s2/5<<endl;
	cout<<"Average Turnaround time : "<<s3/5<<endl;
	cout<<"Average Parameter time : "<<s4/5<<endl;
	
	
}
