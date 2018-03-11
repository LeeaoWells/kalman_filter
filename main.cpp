#include <iostream>
//#include "json.hpp"
#include "tools.h"
#include <math.h>
#include "FusionEKF.h"
#include<fstream>
#include <string>
#include<sstream>
#include<math.h>

using namespace std;
using namespace Eigen;
using Eigen::MatrixXd;
using Eigen::VectorXd;

vector<VectorXd> measurements;
FusionEKF fusionEKF;
Tools tools_;

int main()
{
	
	//open
	ifstream infile("D:\\ekf_test.txt", ios::in | ios::out | ios::binary);
	if (infile.is_open())cout << "file open" << endl;
	if (!infile.is_open())cout << "file not open" << endl;
	string line;
	MeasurementPackage meas_package;
	//istringstream iss(sensor_measurment);
	stringstream iss;// #include<sstream>
	long long timestamp;

	while (getline(infile, line))
	{
		
		iss << line;
		string sensor_type;
		iss >> sensor_type;
		if (sensor_type.compare("G") == 0)
		{
			meas_package.sensor_type_ = MeasurementPackage::GPS;
			meas_package.raw_measurements_ = VectorXd(3);
			float px;
			float py;
			float pz;
			//GPS��������
			iss >> px;
			iss >> py;
			iss >> pz;
			meas_package.raw_measurements_ << px, py, pz;
			iss >> timestamp;
			meas_package.timestamp_ = timestamp;
			//if(px && py && pz)
			fusionEKF.ProcessMeasurement(meas_package);//�������˲�
		}

		else if (sensor_type.compare("I") == 0)
		{

			meas_package.sensor_type_ = MeasurementPackage::IMU;
			meas_package.raw_measurements_ = VectorXd(6);
			float wx, wy, wz;//���ٶ�
			float alpha,beta,theta;//ŷ����
			float ax,ay,az;//������ٶ�

			
			//�Ǽ��ٶ�
			iss >> wx;
			iss >> wy;
			iss >> wz;
			//iss >> alpha;
			//iss >> beta;
			//iss >> theta;

			//���ٶ�
			iss >> ax;
			iss >> ay;
			iss >> az;
			iss >> timestamp;
			meas_package.raw_measurements_ << ax, ay, az, wx, wy, wz;//alpha, beta, theta, 
			meas_package.timestamp_ = timestamp;
			//if(wx&& wy && wz && ax && ay && az && alpha && beta && theta)
			fusionEKF.ProcessMeasurement(meas_package);//��չ�������˲�
		}
	}
	system("pause");
	return 0;
	

}

