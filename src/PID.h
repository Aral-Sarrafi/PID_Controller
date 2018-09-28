#ifndef PID_H
#define PID_H
#include <vector>
#include <iostream>
#include <numeric>
#include <limits>
class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;  

  /*total error for the pid*/
  double total_error; 
  double best_error;
  /*parameter optimizatio*/
  bool twiddle;
  std::vector<double> dp;

  bool increase;
  bool decrease;
  bool flag_update_total_error;
  bool flag_twiddle_step;

  int step;
  int ignore_step;
  int eval_step;
  int PID_index;

  /*Output control signal*/
  double control;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);
  
  /*I added the compute control signal to compute the output control
  signal in the PID class*/
  void ComputeControl();
  /*
  * Calculate the total PID error.
  */
  //double TotalError();
  void AdjustPID(int index, double);

};


#endif /* PID_H */
