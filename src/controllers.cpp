/*
 * controllers.cpp
 *
 *  Created on: Jun 15, 2020
 *      Author: tor
 */

#include "controllers.h"

using namespace Eigen;

static bool tunings_initialized = false;
static const double g = 9.81;
static const double delta_t = 0.004;
static const double pi = 3.14159265;

static void init_tunings(void);
static void prediction(void);
static void correction(void);


Matrix2d P_mat, F_mat, IKH_mat = Matrix2d::Zero();
Matrix2d I_mat = Matrix2d::Identity();
Matrix2d Q_mat = Matrix2d::Zero();
Matrix3d R_mat = Matrix3d::Zero();
Matrix3d HPH_mat = Matrix3d::Zero();
MatrixXd H_mat = MatrixXd::Zero(3,2);
MatrixXd K_mat, T_mat = MatrixXd::Zero(2,3);
Vector3d u_vec, y_vec, h_vec = Vector3d::Zero();
Vector2d x_vec = Vector2d::Zero();


static void init_tunings(void)
{
	Q_mat(0,0) = 0.5;
	Q_mat(1,1) = 0.5;

	R_mat(0,0) =  0.05;
	R_mat(1,1) =  0.05;
	R_mat(2,2) =  0.05;

	x_vec(0) = 0.55*(pi/180);
	x_vec(1) = -4.6*(pi/180);

	tunings_initialized = true;
}

static void prediction(void)
{
	T_mat(0,0) = 1; T_mat(0,1) = sin(x_vec(0))*tan(x_vec(1)); T_mat(0,2) = cos(x_vec(0))*tan(x_vec(1));
	T_mat(1,1) = cos(x_vec(0)); T_mat(1,2) = -sin(x_vec(0));

	F_mat(0,0) = u_vec(1)*cos(x_vec(0))*tan(x_vec(1)) - u_vec(2)*sin(x_vec(0))*tan(x_vec(1));
	F_mat(0,1) = (u_vec(1)*sin(x_vec(0)) - u_vec(2)*cos(x_vec(0)))/(cos(x_vec(1))*cos(x_vec(1)));
	F_mat(1,0) = -u_vec(1)*sin(x_vec(0)) - u_vec(2)*cos(x_vec(0));

	F_mat = (I_mat + delta_t*F_mat);

	x_vec = x_vec + delta_t*T_mat*u_vec;
	P_mat = F_mat*P_mat*F_mat.transpose() + Q_mat*delta_t*delta_t;
}


static void correction(void)
{
	H_mat(0,1) = g*cos(x_vec(1));
	H_mat(1,0) = -g*cos(x_vec(1))*cos(x_vec(0)); H_mat(1,1) = g*sin(x_vec(1))*sin(x_vec(0));
	H_mat(2,0) = g*cos(x_vec(1))*sin(x_vec(0)); H_mat(2,1) = g*sin(x_vec(1))*cos(x_vec(0));

	h_vec(0) = g*sin(x_vec(1)); h_vec(1) = -g*cos(x_vec(1))*sin(x_vec(0)); h_vec(2) = -g*cos(x_vec(1))*cos(x_vec(0));

	HPH_mat = H_mat*P_mat*H_mat.transpose() + R_mat;

	K_mat = P_mat*H_mat.transpose()*HPH_mat.inverse();
	x_vec = x_vec + K_mat*(y_vec - h_vec);

	IKH_mat = I_mat - K_mat*H_mat;
	P_mat = IKH_mat*P_mat*IKH_mat.transpose() + K_mat*R_mat*K_mat.transpose();
}

//Regn ut startvinkel
Vector2d kalman(double* data)
{
	if(!tunings_initialized)
		init_tunings();

	u_vec(0) = data[4]*(pi/180); u_vec(1) = data[5]*(pi/180); u_vec(2) = data[6]*(pi/180);
	y_vec(0) = data[0]; y_vec(1) = data[1]; y_vec(2) = data[2];

	prediction();
	correction();

	delete[] data;
	return x_vec*(180/pi);
}




