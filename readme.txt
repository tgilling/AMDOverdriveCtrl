
This project is developed by using the "codelite" IDE (www.codelite.org). A workspace for this IDE is included.

Dependencies: 

	AMD Display Library >= 3.0 (http://developer.amd.com/gpu/adlsdk/Pages/default.aspx) 
	extract the ADL Library into the main project folder and rename the ADL folder to "ADL_SDK" 

	wxWidgets 2.8.X or later
	If you install the "codelite" IDE you will probably have all what's necessary.

Building:

	make -f AMDOverdriveCtrl.mk
	or
	use "codelite" 

Creating deb package:

	make_deb.sh

   
