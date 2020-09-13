# Theo
C++ Code to determine UTM coordinates from 2-D image

Theo Update:  9/8/2020

The current revision of Theo is version 0.9 dated Sept. 8, 2020

A number of new features are included and the UTM geometry has been recoded.  After the fourth fiducial is ‘Number Clicked’, a wait cursor appears while the UTMx and UTMy of every accessible point on the camera image is computed.  After that a <Ctrl> click on a point just does a look up in these computed numbers and computes the range and azimuth and fills in the corresponding boxes at the bottom of the screen.

To use Theo, 
    1. click on Choose Location to select the .loc file for the image(s) you plan to process.
    2. Click on Load Photo to load a photo that is associated with the selected .loc file
    3. If necessary, review the thumbnail image that shows the four fiducial locations for this .loc
    4. Number the four fiducials making sure that the last one, number four, is the foreground fiducial.
    5. After the wait cursor goes back to the Arrow Cursor, you are ready to <Ctrl> click on ships and boats etc.

I recommend setting up your project with a number of folders organized as follows:
 
TheoProjectFiles

code	images	  locfiles 	README	theoOutput

You will see paths to some of these folders in the screenshot on the next page.

Put the Theo C++ code folder in the code folder.  Make sure you have the current versions of theo.cpp, theo.h and theo.ui (version 0.9 dated Sept. 8, 2020).  When Qt compiles the code it will create various build folders in the code directory.  The program will run fastest if you compile a Release version which is selected in the Qt programming interface at the lower left.

I am working on displaying UTM_East and UTM_North lines superimposed on the images.  This is mostly for debugging the geometry but if you wish to see these lines, put the number 10 in the box below the Recalculate button.

To add new locations to your Theo Project:
    1. Construct a .loc file with your fiducial details.
    2. Create an image with arrows pointing to your fiducials and save it as a .jpg (not .JPG at the moment) and put this image in the locfiles folder
    3. Put the images you wish in a folder that could be the images folder or you could create a subfolder for each separate location that you will be analyzing.


Please send me any comments, suggestions or bug-reports etc.  v v e i r s @ coloradocollege.edu
