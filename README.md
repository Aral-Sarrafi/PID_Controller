# PID_Controller
This project is an implementation of PID controller for driving the car in the track. The PID controller generate the desired steering angle for the wheels based on the deviation of the car from the center of the track.

# PID Controller parameter selection
This section discusses how the parameters are selected for the PID controller. For this project first I found an initial set of parameters that make the system stable and then optimized based on those parameters to achieve a better performance using twiddle.

## Selecting the initial values for the PID

**P parameter:** P parameter plays a major role in this problem this parameter make the car to steer towards the center of the track. Increasing P makes the response of the car faster and it gets closer to the center with a steeper angle. However, Increasing P will introduce unwanted oscillations as expected because the car will over shoot after getting back to the center of the track. This problem can be solved by tuning the D parameter. Therefore; I selected P =0.1 after a couple of trial and error rounds. With P = 0.1 the car steers towards the center of the track and will be able to drive up to a certain point, but eventually the oscillations will occur and the system will become unstable.

**In Summary: Increasing P parameter will make the system faster, introduces oscillations and more unstable.**


**D parameter:** In order to eliminate the overshoots tuning the D parameter is very important. The D parameter will take into account that the error has been decreased and decreases the amount of steering angle accordingly which will result in reducing the oscillations. Selecting larger values of D will decrease the oscillations even better, but selecting a very large value of will also increase the response time of the system. Increasing the response time of the system is not desired because the car will fail to make fast maneuvers especially in the turn. After couple of trial and error I selected D = 2.5 as the initial value of D. D = 2.5 will eliminate the oscillations while achieving a fast response time for the system.

**In Summary: Increasing D parameter will make the system response slower, reduces the oscillations and overshooting and more stable.**

**I parameter:** The I parameter is helpful for correcting for the steady state errors in the system. In this simulation selecting a small value for I is desired and large value of I will make the system unstable, because the errors will accumulates and generates a large steering angle. As an initial guess I selected I = 0.00001.

With these parameters, the car will drive the entire track:

**P = 0.1**

**D = 2.5**

**I = 0.00001**

## Optimizing the parameters

After having a set of stable selection of parameters, twiddle method can be used to optimize around the parameters. In this especial simulation, implementing the original twiddle algorithm is not possible and an other version of twiddle should be implemented to update the parameters as the car moves around the track. In this implementation after a certain time steps the algorithm updates a single parameter (P, I, or D) and the algorithm updates all the parameters as the car move around. Therefore, as the car drive around the track a new PID controller will be designed with optimized parameters. The final parameters that I selected after couple of optimization are:

**P = 0.141**

**D = 3.8**

**I = 1.42e-05**

