# mrProj2  
Mobile Robotics Projekt 2 Semester 4 FHGR.

Group Members: Roman Hanselmann, Urban Willi

## Making Pigpiod a service
used [github project](https://github.com/joan2937/pigpio/tree/master/util) of joan2937 

### Correction of his readme:      

create pigpiod.service in /etc/systemd/system  

    $ sudo cp pigpiod.service /usr/local/bin/  
    $ sudo chmod 744 /usr/local/bin/pigpiod.service  
    $ sudo chmod 664 /etc/systemd/system/pigpiod.service  
    $ sudo systemctl daemon-reload           
    $ sudo systemctl enable pigpiod.service



## Troubleshooting

#### Can't lock /var/run/pigpio.pid  
    $ sudo rm /var/run/pigpio.pid

#### initInitialise: bind to port 8888 failed (Address already in use)
	$ sudo lsof -i tcp:8888
	$ sudo kill -9 PID

#### Cmake : no rule to make target '...'
Change target in sftpToPi_run back to an existing target, run once with old target already saved in cMakefile.
Change back to new target, now it should run without error.


#### Git push permission denied
	$ ssh-add githubFHGR.txt
	
#### Raspi ssh agent not running
	$ eval `ssh-agent`
	$ ssh-add githubFHGR.txt





