#include "quaternion.h"
#include <math.h>

#define Kp 0.8f		// ����ϵ��
#define Ki 0.001f	// ����ϵ��
#define T 0.008f	// ��������

float Angle_X_Quaternion;
float Angle_Y_Quaternion;
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;			// ��Ԫ��
float exInt = 0.0f, eyInt = 0.0f, ezInt = 0.0f; 			// �������

void CalAngle_Quaternion(float gx, float gy, float gz, float ax, float ay, float az){
	float norm;
    float vx, vy, vz;
    float ex, ey, ez;

    // ����������
    norm = sqrt(ax*ax + ay*ay + az*az);      
    ax /= norm;
    ay /= norm;
    az /= norm;      

    // ���Ʒ��������
    vx = 2*(q1*q3 - q0*q2);
    vy = 2*(q0*q1 + q2*q3);
    vz = q0*q0 - q1*q1 - q2*q2 + q3*q3; 

    // ���������ͷ��򴫸��������ο�����֮��Ľ���˻����ܺ�
    ex = ay*vz - az*vy;
    ey = az*vx - ax*vz;
    ez = ax*vy - ay*vx;

    // ������������������
    exInt += ex*Ki;
    eyInt += ey*Ki;
    ezInt += ez*Ki; 

    // ������������ǲ���
    gx += Kp*ex + exInt;
    gy += Kp*ey + eyInt;
    gz += Kp*ez + ezInt; 

    // ������Ԫ���ʺ�������
	q0 += (-q1*gx - q2*gy - q3*gz)*T*0.5f;
	q1 += (q0*gx + q2*gz - q3*gy)*T*0.5f;
	q2 += (q0*gy - q1*gz + q3*gx)*T*0.5f;
	q3 += (q0*gz + q1*gy - q2*gx)*T*0.5f;   

    // ��������Ԫ
    norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    q0 /= norm;
    q1 /= norm;
    q2 /= norm;
    q3 /= norm;

    Angle_X_Quaternion = asin(2*(q0*q2 - q1*q3)) * 57.3f;
	Angle_Y_Quaternion = atan2(2*q2*q3 + 2*q0*q1, 1 - 2*q1*q1 - 2*q2*q2) * 57.3;
}
