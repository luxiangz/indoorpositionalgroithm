
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "file_operation.h"
using namespace std;
int main()
{
	//int space_wall_number=0;//the number of walls in space
	//cout << "The number of walls in space:"<<endl;
	//cin >> space_wall_number;
	char *filename = "./data.txt";
	fstream datafile;//file include the datas of space
	datafile.open("./data.txt", ios::in | ios::out);
	if (!datafile)
	{
		cerr << "Error opening file!" << endl;
		return -1;
	}
	if (!datafile.fail())
	{	
		/*datafile << "This is a line.\n";
		datafile << "This is another line.\n";*/

		//write the alphabet in the file
		char a = 'a';
		int i;
		for (i = 0; i < 26; i++)
		{
			datafile << setw(2) << i << "\t" << a << "\n";
			a++;
		}

		int maxrow = CountDataRow(filename);
		float *tempcoor = new float[maxrow];
		char *tempcoorchar = new char[maxrow];

		//test find the special row
		//cout << maxrow << endl;
		//string filerow_con = ReadDataRow(filename, 2);
		//cout << filerow_con.c_str() << endl;
		datafile.seekp(ios::beg);//move the pointer to the header
		int i0 = 0;
		while (!datafile.eof())
		{
			datafile >> tempcoor[i0];
			datafile >> tempcoorchar[i0];
			i0++;
		}
		datafile.close();	
		for (i0 = 0; i0 < maxrow; i0++)
			cout << tempcoor[i0] << "\t" << tempcoorchar[i0] << "\n";

		delete[]tempcoor;
		delete[]tempcoorchar;
	}

	
	//while (!datafile.eof())
	{
		//datafile.getline()
	}
	system("pause");
	
	return 0; 

}

