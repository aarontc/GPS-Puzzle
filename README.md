GPS-Puzzle
==========

[Teensy](http://www.pjrc.com/teensy/index.html) project for blinking LEDs to encode GPS coordinates for a geocaching puzzle.


Building on Windows
-------------------
1. Get WinAVR from http://winavr.sourceforge.net/.
1. Install WinAVR, taking care to enable the option that will update your PATH environment variables.
1. Open a command window and CD to the Source directory.
1. Type "make"


Flashing the program onto Teensy
--------------------------------
1. Connect the Teensy to your PC with a USB cable.
1. Get the Teensy Loader from http://www.pjrc.com/teensy/loader.html.
1. Open the Teensy Loader and select File -> Open Hex File.
1. Select the HEX file you built previously, or use the example one distributed in the repository.
1. Press the reset button on the Teensy to load the code.

Customizing the coordinates
---------------------------
The GPS coordinate numbers used in the public version of this code are nonsensical values counting from 1 to 15, so as to avoid disclosing the actual coordinates. To use this project for your actual GPS puzzle, you'll want to update the values in GPSBlink.cpp, in the set_up_lights function.
