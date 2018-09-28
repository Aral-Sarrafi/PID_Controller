#include "PID.h"
#include <cmath>
#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	/*PID parameters*/
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;

	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;
	
	total_error = 0;
	best_error = numeric_limits<double>::max();
	dp = { 0.1*Kp,0.1*Kd,0.1*Ki };


	twiddle = true;
	flag_twiddle_step = false;
	flag_update_total_error = false;
	increase = false;
	decrease = false;

	ignore_step = 100;
	eval_step = 2000;
	step = 1;
	PID_index = 0;

	 
}

void PID::UpdateError(double cte) {
	PID::i_error += cte;
	PID::d_error = cte - PID::p_error;
	PID::p_error = cte;
	/*Update the total error after passing the number of ignore steps*/
	flag_update_total_error = (step % (ignore_step + eval_step)) > ignore_step;
	flag_twiddle_step = step % (ignore_step + eval_step) == 0;

	if (flag_update_total_error) {
		total_error += pow(cte,2);
	}

	if (twiddle && flag_twiddle_step)
	{
		cout << "Step = " << step << endl;
		cout << "Total Error = " << total_error << endl;
		cout << "Best Error = " << best_error << endl;


		if (total_error < best_error) {
			best_error = total_error;
			cout << "The performance is improved!" << endl;
			if (step != ignore_step + eval_step)
			{
				dp[PID_index] *= 1.1;
				 
			}
		}
		// Select the next parameter for the next round of improvement
		PID_index = (PID_index + 1) % 3;

		increase = false;
		decrease = false;


		// Start by trying to increase the parameters
		if (!increase && !decrease)
		{
			AdjustPID(PID_index, dp[PID_index]);
			// Set increase true to keep track that you tried increasing the parameter
			increase = true;
		}
		else if (increase && !decrease)
		{
			AdjustPID(PID_index, -2 * dp[PID_index]);
			decrease = true;
		}
		// If increasing or decreasing the parameter does not improve
		// The performace then:
		// 1- Set the parameter back, 2-choose smaller resolution 3. move on to next parameter
		else
		{
			AdjustPID(PID_index, dp[PID_index]);
			dp[PID_index] *= 0.9;

			PID_index = (PID_index + 1) % 3;
			increase = false;
			decrease = false;
		}
		total_error = 0;
		// Print the new PID controller
		cout << "new PID is designed!" << endl;
		cout << "P = " << Kp << endl;
		cout << "I = " << Ki << endl;
		cout << "D = " << Kd << endl;
	}
	step++;

}

void PID::ComputeControl() {
	PID::control = -PID::Kp * PID::p_error
		- PID::Ki * PID::i_error
		- PID::Kd * PID::d_error;
}

//double PID::TotalError() {
//}

void PID::AdjustPID(int index, double value) {
	if (index == 0) {
		Kp += dp[index];
	}
	else if (index == 1) {
		Kd += dp[index];
	}
	else if (index ==2){
		Ki += dp[index];
	}
}