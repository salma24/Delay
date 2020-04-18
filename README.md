# DelayCalculation
Elmore delay model
A typical approach for modeling a VLSI interconnect is to use the distributed equivalent RC circuit of Fig. 1.


Download : Download full-size image
Fig. 1. Distributed RC model of a VLSI interconnect.

The Elmore delay model explains the delay from input to output of the input signal, which is of a step function type. If the step response of the RC circuit is , 50% point delay of the monotonic step response is the time  that satisfies the following equation:
(1)
In the Elmore model,  is approximated to the mean of the impulse response . If the impulse response is taken as a probability distribution function (pdf), the mean is defined as the first moment of the impulse response [12]:
(2)
Time constant for the Elmore delay for an RC interconnect can be calculated by the formula
(3)
where  is the total number of nodes in the RC equivalent circuit,  is the resistance of the portion of the path to the  and  is the capacitance at node . On the other hand, the Elmore delay is also used to find the dominant low frequency pole of the distributed RC network of Fig. 1. The Laplace transform of the impulse response is
(4)
If  is expanded about , the transfer function can be expressed as [25]
(5)
(6)
The expansion in Eq. (6) can also be expressed as
(7)
The first order moment, , gives the Elmore delay of the circuit. It is clear that, if higher order moments are taken into account, more accurate delay calculations can be performed at the expense of computational effort. The Elmore model tries to estimate the median of the impulse response which is 50% delay of the input step function. For positive skew impulse responses, the median is less than or equal to the mean. Thus, in fact, in the Elmore delay formulation, the mean of the impulse response constitutes an upper bound for the delay, while the median of the impulse response accounts for the arbitrary input waveforms. For step function inputs, the median and the mean are equal and the Elmore delay is used as the 50% delay of the interconnect. In Fig. 2 the VLSI interconnect model and its lumped RC equivalent model are shown.
