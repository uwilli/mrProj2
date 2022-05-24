# mrProj2
Mobile Robotics Projekt 2 Semester 4 FHGR.

Group Members: Roman Hanselmann, Urban Willi


## Troubleshooting

### Can't lock /var/run/pigpio.pid
$ sudo rm /var/run/pigpio.pid

### initInitialise: bind to port 8888 failed (Address already in use)
$ sudo lsof -i tcp:8888
$ sudo kill -9 PID

### Cmake : no rule to make target '  '
Change target in sftpToPi_run back to an existing target, run once with new target already saved in cMakefile.
Change back to new target, now it should run without error.
