//Shortest-Job-First

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Jobs.h"
using namespace std;

class SJF
{
public:
	SJF() = default;

	//Algorithm for Shortest-Job-First
	double algorithm()
	{
		//Declare variables
		int timer = 0;
		double avgTurnAroundTime = 0.0;

		cout << "Shortest-Job-First Algorithm: " << endl;

		//Store jobs in vector
		vector<Jobs> jobs;

		//Get job info from file
		readFile(jobs);

		//Sorts jobs so that the shortest job is first
		sort(jobs.begin(), jobs.end(), [](const Jobs& x, const Jobs& y)
		{
			return x.burst < y.burst;
		});

		//Handles the jobs
		for (Jobs & currentJob : jobs)
		{
			//Match job's start time to the current timer
			currentJob.start = timer;

			//Add burst time to the timer
			timer += currentJob.burst;
			currentJob.burst = 0;

			//Match the job's end time with the current timer
			currentJob.end = timer;

			//Add the end time to the average
			avgTurnAroundTime += currentJob.end;
		}
		printTable(jobs);
		return avgTurnAroundTime / jobs.size();
	}

	//Reads the jobs from the file
	void readFile(vector<Jobs> & jobs)
	{
		//Declare the variables
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
		//Formating and output for the table
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
