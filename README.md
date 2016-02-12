# welcome-to-the-SLAM
University of Arizona - Senior Engineering Design - ENGR 498 - Autonomous Mapping and Navigation

Sponsor: Dr. Marcellin -  University of Arizona ECE

Team Members: Kevin Fox, Christopher Meyer, Cody Mitts, Jiaxiang Wang, Xander Deputy

Team: 15017

How to deploy code onto RBP2:
-Open up the .sln file with visual studio 2015
-make sure "ARM is selected in the drop-down menu near the top - between debug and remote/local machine. The other options is may appear
  as are x64 or x86 (click that, then choose ARM)
-choose "Remote Machine" from the dropdown next to "ARM".
-Right click on the "SLAM (Universal Windows)" solution, and at the bottom of this menu, click on properties.
-Go to "Configuration Properties -> Debugging"
-Click on "Machine Name" -> "<Locate>"
-On the next prompt, the RBP2 should appear under automatic. If not there, open the RBP2 from the IoT device portal, copy and paste the
  IP address into manual. Make sure to remove the http and the /'s
-Apply
-Run
