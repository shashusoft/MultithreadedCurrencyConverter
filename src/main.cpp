#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <thread>

bool GENERATE_CSV_FINISHED = false;
int CURRENCY_COUNT 		   = 10000;

void generateCSV()
{
	std::ofstream ipFile("input.txt");
	if (ipFile.is_open())
	{
		for (int i = 0; i < CURRENCY_COUNT; i++)
		{
			ipFile << rand() % 100 << ",";
			if (i % 50 == 0)
			{
				ipFile << std::endl;
			}
		}
		ipFile.close();
	}
	GENERATE_CSV_FINISHED = true;
}

void readCSV()
{
	std::ifstream ipFile("input.txt");
	std::vector<std::string> stringVector;
	while(ipFile)
	{
		std::string ipString;
		if (!getline(ipFile, ipString)) break;
		std::istringstream sStream(ipString);
		while(sStream)
		{
			std::string sString;
			if (!getline( sStream, sString, ',' )) break;
      		stringVector.push_back(sString);
		}
	}
	for (int i = 0; i < stringVector.size(); i++)
	{
		std::cout << stringVector[i] << std::endl;
	}
}

int main(int argc, char* argv[])
{
	std::cout << "******************************************" << std::endl;
	std::cout << "*****Multithreaded currency converter*****" << std::endl;
	std::cout << "*****Developer: Atish Patange*****" 		  << std::endl;
	std::cout << "******************************************" << std::endl;
	std::cout << "./converter 'ip file' " << std::endl;

	// generate sample comma separated file with user defined values
	std::thread t1(generateCSV);
	if (t1.joinable())	
	{
		t1.join();
	}
	if(GENERATE_CSV_FINISHED)
	{
		std::thread t2(readCSV);
		if (t2.joinable())
		{
			t2.join();
		}
	}
}

