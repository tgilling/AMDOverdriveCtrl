History:
--------

V1.2.4  :	"Close to tray" instead of dialog destroy as suggested by David Keogh

V1.2.3  :	new command line switch "--no-warnings" to suppress warning message box at startup
        	patch included (detect if card supports fan speed setting by percentage)
        	patch included (makefile corrected)
		
V1.2.1  :	Bugfix: correct segfault if no perf levels reported

V1.2.0  :	added (yet) undocumented 'AMD Powertune' setting - needs testing!

V1.1.4  :	"save default" button added by SourceForge Member 'logion'

V1.1.3  :	card ident string was wrong in multi GPU setup

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


Credits:
--------

Thanks to Alexey Svistunov and Cengiz Günay for suggesting changes to the makefile.


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


