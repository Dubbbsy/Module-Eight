/*
 *  Source.cpp
 *
 *  Date: June 8, 2023
 *  Author: Austin Adams
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;


class ProduceManagement
{
private:
	map<string, int> productFrequency;

public:
	bool checkContains(string input)
	{
		if (productFrequency.count(input) > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void addNewProduct(string input)
	{
		productFrequency.insert(pair<string, int>(input, 1));
	}

	void increaseProductCount(string input)
	{
		productFrequency[input] += 1;
	}

	void printProductListNum()
	{
		map<string, int>::iterator mp = productFrequency.begin();
		while (mp != productFrequency.end())
		{
			cout << mp->first << " " << mp->second << endl;
			++mp;
		}

		cout << endl;
	}

	void printProductListHistogram()
	{
		map<string, int>::iterator mp = productFrequency.begin();
		while (mp != productFrequency.end())
		{
			cout << mp->first << " ";

			for (int i = 0; i < mp->second; i++)
			{
				cout << "*";
			}
			cout << endl;

			++mp;
		}

		cout << endl;
	}

	int getProductFrequency(string input)
	{
		return productFrequency[input];
	}

	void backupProducts()
	{
		fstream backupFile;
		backupFile.open("frequency.dat", ios::out);

		map<string, int>::iterator mp = productFrequency.begin();
		while (mp != productFrequency.end())
		{
			backupFile << mp->first << " " << mp->second << endl;
			++mp;
		}
	}
};

int main()
{
	string input = "";
	ProduceManagement list1;
	
	fstream salesFile;
	salesFile.open("CS210_Project_Three_Input_File.txt");
	fstream backupFile;
	backupFile.open("frequency.dat", ios::out);
	backupFile.close();

	while (!salesFile.eof())
	{
		salesFile >> input;

		if (!list1.checkContains(input))
		{
			list1.addNewProduct(input);
		}
		else
		{
			list1.increaseProductCount(input);
		}
	}
	salesFile.close();

	list1.backupProducts();

	while (input != "4")
	{
		cout << "Select one of the below options:\n1. Search for product\n2. Print list of products and frequency\n3. Print histogram of products and frequency\n4. Exit\n";
		cin >> input;
		cout << endl;

		if (input != "1" && input != "2" && input != "3" && input != "4")
		{
			cout << "Invalid Input.\n";
		}
		else if (input == "1")
		{
			cout << "Enter name of product: ";
			cin >> input;
			
			if (!list1.checkContains(input))
			{
				cout << "No product with this name was found.\n\n";
			}
			else
			{
				cout << "Product frequency is " << list1.getProductFrequency(input) << "\n\n";
			}
		}
		else if (input == "2")
		{
			list1.printProductListNum();
		}
		else if (input == "3")
		{
			list1.printProductListHistogram();
		}
	}
}