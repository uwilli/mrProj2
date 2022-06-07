# Using the zip and cmake
Create a folder that will be your workspace. Unzip the file on your raspberry pi in this workspace folder.  
In your workspace, create a build folder.  

It should look like this:  
Workspace > source, build  
source > CMakeLists.txt, inc, src

Inside build folder, execute:

	$ cmake ../source  
	$ cmake --build . --target <servo_dev>
  
Build files and executables will be in the build folder.

            
            
