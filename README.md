# CS300-lab10
Repo for CS300 Lab 10 at UAB

Unfortunately, in its current state I was unable to build with CMake. I've written multiple tests, but found out a little too late (completely my bad) that my ubuntu distro in WSL is locked to CMake 3.10.2 - so I couldn't even build with the Google test framework. Took me about an hour to figure out what the issue was, admittedly.

This is not a very pretty solution. In retrospect, it's probably like 100 lines longer than it actually needs to be, but that would require an almost completely different approach, I think. This program doesn't assume that the input is sorted from lowest to highest, which was admittedly probably what lead to my solution being as large as it is.

(11/14)
I've uploaded this here as proof of my actual work, with plans to figure out how ridiculous this looks at office hours.
Edit: this actually runs into an error while trying to convert the numbers in the string into integers
