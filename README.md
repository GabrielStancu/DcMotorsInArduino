# DcMotorsInArduino

Small Arduino project where we use a distance sensor to detect an object in front of our robot. It uses 2 DC motors to activate 2 wheels (simulated) to move towards the object. The servomotor is used only for marking the reaching of the object. 
Depending on the distance, the robot accelerates or decelerates: if the object is further away, the robot moves faster and it breaks as it approaches the object.
If the object is reached, the DC motors are turned off and the servomotor is turned on to mark the reach of our goal. 
If the object starts moving again, the robot is turned on and it starts following the object again. It can only track objects in front of him. 
Because we used the tinkercad simulator, we had to simulate numerically the approaching process. 

For viewing the circuit layout, see the CircuitScheme.png image.
