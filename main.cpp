//Main
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <random>
#include "FCFS.h"
#include "SJF.h"
#include "RoundRobin.h"
#include "Jobs.h"
using namespace std;

//Functions
void randomJobGenerator(int count);
void printTime(double time);

int main()
{
	//Declare variables
	const int trials = 20;
	static int jobAmount[] = { 5, 10, 15 };
	double avg = 0;
	double firstComeFirstServedTime = 0;
	double shortestJobFirstTime = 0;
	double roundRobin_2_Time = 0;
	double roundRobin_5_Time = 0;

	//Create objects from files 
	FCFS firstComeFirstServed;
	SJF shortestJobFirst;
	RoundRobin roundRobin;

	//Handles the algorithms
	for (int size : jobAmount)
	{
		for (int i = 0; i < trials; i++)
		{
			//Get jobs according to size of array
			randomJobGenerator(size);
			
			//Call algorithm from first come first served
			avg = firstComeFirstServed.algorithm();
			cout << "Average turnaround time for First-Come-First-Serve: " << avg << endl << endl;
			//Add to average
			firstComeFirstServedTime += avg;

			//Call algorithm from shortest job first
			avg = shortestJobFirst.algorithm();
			cout << "Average turnaround time for Shortest-Job-First: " << avg << endl << endl;
			//Add to average
			shortestJobFirstTime += avg;

			//Call algorithm from round robin and give it the time slice
			avg = roundRobin.algorithm(2);
			cout << "Average turnaround time for Round - Robin with Time Slice = 2 (RR - 2): " << avg << endl << endl;
			//Add to average
			roundRobin_2_Time += avg;

			//Call algorithm from round robin and give it the time slice
			avg = roundRobin.algorithm(5);
			cout << "Average turnaround time for Round - Robin with Time Slice = 5 (PR - 5): " << avg << endl << endl;
			//Add to average
			roundRobin_5_Time += avg;
		}

		//Output average turnaround times for the algorithms after the trials
		cout << "Average turnaorund times after all the trials: " << endl;
		cout << "The average turnaorund time for First-Come-First-Serve of size " << size << " is " 
			<< firstComeFirstServedTime / trials << endl;
		cout << "The average turnaorund time for Shortest-Job-First of size " << size << " is "
			<< shortestJobFirstTime / trials << endl;
		cout << "The average turnaorund time for Round - Robin with Time Slice = 2 (RR - 2) of size " << size << " is " 
			<< roundRobin_2_Time / trials << endl;
		cout << "The average turnaorund time for Round - Robin with Time Slice = 5 (PR - 5) of size " << size << " is " 
			<< roundRobin_5_Time / trials << endl;

		firstComeFirstServedTime = 0;
		shortestJobFirstTime = 0;
		roundRobin_2_Time = 0;
		roundRobin_5_Time = 0;

		cout << endl << endl;
	}
	return 0;
}

//Generates the random jobs
void randomJobGenerator(int count)
{
	//Create and output to file
	ofstream jobFile("job.txt");

	//Generate random numbers
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<> dis(1, 30);

	//Handles the random jobs
	for (int i = 0; i < count; i++)
	{
		jobFile << "Job" + to_string(i + 1) << endl;

		if (i < (count - 1))
		{
			jobFile << dis(generator) << endl;
		}
		else
		{
			jobFile << dis(generator) << endl;
		}
	}
	//Close the file
	jobFile.close();
}

//Prints the average turnaround time
void printTime(double time)
{
	cout << endl << "The average turnaround time is " << time << endl << endl;
}
