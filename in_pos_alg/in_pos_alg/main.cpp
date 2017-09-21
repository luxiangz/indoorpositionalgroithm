
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>

#include "stdlib.h"
#include "file_operation.h"
#include "datawritein.h"
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
#define dimension 3
float xtemp[pointnum] = { 000.0f, 000.0f, 000.0f, 000.0f, 491.5f, 491.5f, 491.5f, 491.5f, 089.2f, 108.3f, 108.3f, 089.2f, 089.2f, 108.3f, 089.2f, 108.3f, 200.0f, 350.0f, 350.0f, 200.0f, 200.0f, 350.0f, 350.0f, 200.0f };
float ytemp[pointnum] = { 000.0f, 483.7f, 483.7f, 000.0f, 000.0f, 000.0f, 483.7f, 483.7f, 483.7f, 483.7f, 458.1f, 458.1f, 483.7f, 483.7f, 458.1f, 458.1f, 260.0f, 260.0f, 200.0f, 200.0f, 200.0f, 200.0f, 260.0f, 260.0f };
float ztemp[pointnum] = { 200.0f, 200.0f, 000.0f, 000.0f, 000.0f, 200.0f, 200.0f, 000.0f, 200.0f, 200.0f, 200.0f, 200.0f, 000.0f, 000.0f, 000.0f, 000.0f, 050.0f, 050.0f, 050.0f, 050.0f, 000.0f, 000.0f, 000.0f, 000.0f };

int Write_Into_Txt(char* filename, bool writeflag);

int main()
{
	//char *a=NULL;
	//cout << "a的长度   "<<sizeof(a) << endl;
	char *filename = "./data.txt";
	bool writeflag = false;
	if (Write_Into_Txt(filename, writeflag) == 0)
	{
		return -1;
	}

	fstream datafile;
	int pli_norm_num = 1;
	int distance_origin_num = 1;
	int plpoi_maxmin_num = 2;
	int planepointnum = 4;//the number of points consituted a planes
	int column = (planepointnum + plpoi_maxmin_num + pli_norm_num)*dimension + distance_origin_num;
	int row = CountDataRow(filename);
	const int basestationnum = 4;
	datareadinfo datatxt(basestationnum,row,column);
#ifdef debug
	cout << "row " << row << endl;
#endif // debug
	float distanceme[basestationnum] = { 7.5f, 895.4f, 56.9f, 78.5f};
	float basecoor_temp[basestationnum][dimension] = {
		{ 0.0f, 12.0f, 16.0f },
		{ 1.0f, 13.0f, 17.0f },
		{ 2.0f, 14.0f, 18.0f },
		{ 3.0f, 15.0f, 19.0f } };
	float *basecoor = &basecoor_temp[0][0];
	datatxt.Set_Measure_Data(distanceme);
	datatxt.Set_Basestation_Coor(basecoor);
	float tagetcoor = 0.0f;
#ifdef debug
	datatxt.Read_1dTo2d(basecoor, 3, 2, tagetcoor,dimension);//prevent exceeding the array size
	cout << "tagetcoor: "<<tagetcoor << endl;
#endif // debug

	datafile.open(filename, ios::in);//ios::in represents read,ios::out represents write,and once this step is done,the contents of the file wiil be cleared.
	if (!datafile)
	{
		cerr << "Error opening file,read!" << endl;
		return -2;
	}
	//int num_sort = 0;
	if (!datafile.fail())
	{
		int columntemp = 0;
		for (int readhighline = 0 ; readhighline < row; readhighline++)
		{
			string linetemp = ReadDataRow(filename, readhighline+1);
			string floatemp;
			//cout << linetemp << endl;
			for (auto c : linetemp)
			{
				if (isspace(c))
				{//equivalent to the transfer of data in the file assigned to the array转置
					datatxt.planes[columntemp][readhighline] = (float)atof(floatemp.c_str());
					//float atest = (float)atof(floatemp.c_str());
					//cout << atest << endl;
					//cout << "datatex.p" << datatxt.planes << endl; //[columntemp][readhighline]
					//cout << "datatex.b" << datatxt.basestation_coor << endl;
					//cout << "datatex.m" << datatxt.measuredata << endl;
					floatemp = "";
					columntemp++;
					//cout << floatemp << endl;
				}
				else
				{
					floatemp += c;
				}
			}
			columntemp = 0;
		}
		//After_R_W2Planes();	
	}
	datafile.close();//read the data in the file
#ifdef debug
	for (int i = 0; i < column; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			cout << datatxt.planes[i][j] << "\t";
		}
		cout << endl;
	}
#endif // debug

	system("pause");
	return 0; 
}
int Write_Into_Txt(char* filename, bool writeflag)
{
	fstream datafile0;
	int surfacenum = sizeof(formsurface) / sizeof(formsurface[0]) / 4;
#ifdef debug
	cout << "surfacenum" << surfacenum << endl;
#endif
	coordinatedata datac[pointnum];
	
	if (writeflag)
	{
		datafile0.open(filename, ios::in | ios::out);
		if (!datafile0)
		{
			cerr << "Can't open the file,write!" << endl;
			return 0;
		}
		if (!datafile0.fail())
		{//select the four point clockwise to form a face
			for (int i = 0; i < pointnum; i++)
			{
				datac[i].x = xtemp[i];
				datac[i].y = ytemp[i];
				datac[i].z = ztemp[i];
#ifdef debug
				cout << "data[" << i << "]\t" << datac[i].x << endl;
				//datafile << setw(2) << datac[i].x << "\t" << datac[i].y << "\t" << datac[i].z << "\n";
#endif
			}
			for (int j = 0; j < surfacenum; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					int tempindex = formsurface[j * 4 + k];
					datafile0 << datac[tempindex - 1].x << "\t" << datac[tempindex - 1].y << "\t" << datac[tempindex - 1].z << "\t";
				}
				datafile0 << "\n";
			}
			//cout << datac[9].x << "\t" << datac[9].y << "\t" << datac[9].z << "\n";
			//datafile0 << "what happend?" << "\n";
			datafile0.close();
		}
	}
	return 1;

}
