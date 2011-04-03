History:
--------

V1.1.2  :	choose GPU through command line switch (--adapter-index)

V1.1.1  :	Bugfix release

V1.1.0  :	new feature: Change color temperature (inspired by "f.lux" 
		and "redshift")

V1.0.3  :	check for supported HW features and disable parts of the program 
		if necessary

V1.0.2  :	corrected some minor deb packaging problems

V1.0.1  :	add some sanity checks at program startup and eventually report
 		problems 
		created simple makefile for compiling without codelite

V1.0.0	:	initial public release


Notes:
------

This project is developed by using the "codelite" IDE (www.codelite.org). 
A workspace for this IDE is included.

Dependencies: 

	AMD Display Library >= 3.0 
	(http://developer.amd.com/gpu/adlsdk/Pages/default.aspx) 

	extract the ADL Library into the main project folder and rename the ADL
 	folder to "ADL_SDK" 

	wxWidgets 2.8.10 or later
	If you install the "codelite" IDE you will probably have all what's
	necessary.

Building and installing:

	'make && make install'

Uninstalling:

	'make uninstall'

Creating deb package:

	'make deb'

Creating source tarball:

	'make dist' 
	or 
	'make dist_adl'		(include ADL_SDK folder)


