# fake_odom


The following programs publishes "fake" odometry information to the "fake_odom_topic" topic. 
In this case the odometry information published by "fake_odom_topic" traces a circular path. The position information published is basically the non-stationary goal that your turtlebot must move towards. In other words, you are expected to subscribe to this topic and program your robot to iteratively move towards the coordinates published by this topic while avoiding objects using the RGBD sensor.
