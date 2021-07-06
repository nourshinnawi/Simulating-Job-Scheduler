//Round - Robin with Time Slice = 2 (RR - 2)
//Round - Robin with Time Slice = 5 (RR - 5)

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include "Jobs.h"
using namespace std;

class RoundRobin
{
public:

	RoundRobin() = default;

	//Algorithm for Round Robin
	double algorithm(int timeSlice)
	{
		//Declare variables
		int timer = 0;
		int index = 0;
		int deletedTasks = 0;
		double avgTurnAroundTime = 0.0;

		cout << "Round Robin Algorithm Time slice " + to_string(timeSlice) << ": " << endl;
		
		//Store jobs in vector
		vector<Jobs>jobs;

		//Get job info from file
		readFile(jobs);
		
		//Create copy of jobs so that the list can be added to
		vector<Jobs>list = jobs;

		//Handles tasks that are left
		while (deletedTasks != jobs.size()) 
		{
			//Get the job's current index in the list
			Jobs &currentJob = list[index];

			//Set the start time
			currentJob.start = timer;

			if ((currentJob.burst - timeSlice) < 0)
			{
				//Add remaining burst time to the timer
				timer += currentJob.burst;

				//Set the ending time and end the job
				currentJob.end = timer;
				currentJob.burst = 0;

				//Add end time to the average turnaround time
				avgTurnAroundTime += currentJob.end;

				//Increment for deleted tasks
				deletedTasks++;
			}
			else if ((currentJob.burst - timeSlice) == 0)
			{
				//Add the time slice to the timer
				timer += timeSlice;

				//Set burst time to timer and end the job
				currentJob.burst = timer;
				currentJob.end = 0;

				//Add end time to the average turnaround time
				avgTurnAroundTime += currentJob.end;

				//Increment for deleted tasks
				deletedTasks++;
			}
			else
			{
				//Add the time slice to the timer
				timer += timeSlice;

				//Remove burst time by time slice
				currentJob.burst -= timeSlice;

				//Set the end time to the timer
				currentJob.end = timer;

				//Add current job to the back of the list
				list.push_back(currentJob);
			}
			//Increment for the next job
			index++;
		}
		printTable(list);
		return avgTurnAroundTime / jobs.size();
	}

	//Reads the jobs from the file
	void readFile(vector<Jobs> & jobs)
	{
		//Declare variables
		string name;
		int burst;
		ifstream inputFile("job.txt");

		while (!inputFile.eof())
		{
			//Get the job's name
			getline(inputFile, name);

			//End if no job
			if (name.empty())
			{
				break;
			}

			//Read in burst time and clear input buffer
			inputFile >> burst;
			inputFile.ignore(numeric_limits<streamsize>::max(), '\n');

			//Create the job and add to vector
			Jobs job;
			job.name = name;
			job.burst = burst;
			jobs.push_back(job);
		}
		//Close the file
		inputFile.close();
	}

	//Prints the schedule table
	void printTable(const vector<Jobs>& jobs)
	{
		//Format and output for the table
		cout << left << setw(12) << "Job Name"
			<< setw(14) << "Start Time"
			<< setw(12) << "End Time"
			<< setw(19) << "Job Completion" << endl;

		//Handles the jobs
		for (const Jobs & job : jobs)
		{
			//Format and output job info
			cout << left << setw(12) << job.name
				<< setw(14) << job.start
				<< setw(12) << job.end;

			//Handles the completed job
			if (job.burst == 0)
			{
				//Format and output the job completion
				cout << setw(19) << job.name + " completed at @" + to_string(job.end);
			}
			cout << endl;
		}
		cout << endl;
	}
};
