
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "file_operation.h"
using namespace std;
struct potcollection
{
	int firstp;
	int secondp;
	int thirdp;
	int fourthp;
};
struct coordinatedata
{
public:
	float x = {};
	float y = {};
	float z = {};
	/*potcollection *index = {};
	coordinatedata(int pointnum0, int formsurface0)
	{
		float *x = new float[pointnum0];
		float *y = new float[pointnum0];
		float *z = new float[pointnum0];
		potcollection *index = new potcollection[pointnum0];
		cout << "struct构造函数" << endl;
	}
	~coordinatedata()
	{
		delete[] x;
		delete[] y;
		delete[] z;
		delete[] index;
		cout << "struct析构函数" << endl;
	}*/

};
int formsurface[] = {
4,5,6,1,
5,8,7,6,
8,14,11,7,
16,14,10,11,
15,16,11,12,
13,15,12,9,
3,13,9,2,
3,4,1,2,
21,22,19,20,
24,21,20,17,
24,23,18,17,
22,23,18,19,
20,19,18,14
};
#define pointnum 24
float xtemp[pointnum] = { 000.0f, 000.0f, 000.0f, 000.0f, 491.5f, 491.5f, 491.5f, 491.5f, 089.2f, 108.3f, 108.3f, 089.2f, 089.2f, 108.3f, 089.2f, 108.3f, 200.0f, 350.0f, 350.0f, 200.0f, 200.0f, 350.0f, 350.0f, 200.0f };
float ytemp[pointnum] = { 000.0f, 483.7f, 483.7f, 000.0f, 000.0f, 000.0f, 483.7f, 483.7f, 483.7f, 483.7f, 458.1f, 458.1f, 483.7f, 483.7f, 458.1f, 458.1f, 260.0f, 260.0f, 200.0f, 200.0f, 200.0f, 200.0f, 260.0f, 260.0f };
float ztemp[pointnum] = { 200.0f, 200.0f, 000.0f, 000.0f, 000.0f, 200.0f, 200.0f, 000.0f, 200.0f, 200.0f, 200.0f, 200.0f, 000.0f, 000.0f, 000.0f, 000.0f, 050.0f, 050.0f, 050.0f, 050.0f, 000.0f, 000.0f, 000.0f, 000.0f };

int Write_Into_Txt(char* filename, bool writeflag);

int main()
{
	char *filename = "./data.txt";
	bool writeflag = true;
	if (Write_Into_Txt(filename, writeflag) == 0)
	{
		return -1;
	}
	fstream datafile;
	datafile.open(filename, ios::out);
	if (!datafile)
	{
		//cerr<<
	}
	datafile.close();
	system("pause");
	
	return 0; 

}
int Write_Into_Txt(char* filename, bool writeflag)
{
	fstream datafile0;
	int surfacenum = sizeof(formsurface) / sizeof(formsurface[0]) / 4;
	cout << "surfacenum" << surfacenum << endl;
	coordinatedata datac[pointnum];
	
	if (writeflag)
	{
		datafile0.open(filename, ios::in | ios::out);
		if (!datafile0)
		{
			cerr << "Can't open the file!" << endl;
			return 0;
		}
		if (!datafile0.fail())
		{//select the four point clockwise to form a face
			for (int i = 0; i < pointnum; i++)
			{
				datac[i].x = xtemp[i];
				datac[i].y = ytemp[i];
				datac[i].z = ztemp[i];
				//cout << "data[" << i << "]\t" << datac[i].x << endl;
				//datafile << setw(2) << datac[i].x << "\t" << datac[i].y << "\t" << datac[i].z << "\n";
			}
			for (int j = 0; j < surfacenum; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					int tempindex = formsurface[j * 4 + k];
					//datafile0 << setw(2) << datac[tempindex - 1].x << "\t" << datac[tempindex - 1].y << "\t" << datac[tempindex - 1].z << "\t";
				}
				//datafile0 << "\n";
			}
			//cout << datac[9].x << "\t" << datac[9].y << "\t" << datac[9].z << "\n";

			datafile0.close();
		}
	}
	return 1;

}
