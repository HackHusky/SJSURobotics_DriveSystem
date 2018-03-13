# README #

### Demo ###
SJSU Robotics Drivesystem firmware demo video 

Demo 1 : https://youtu.be/dM38TOp2UUA

Demo 2 : https://youtu.be/Z22I8oZJUFw

### Framework ###

##### General #####
* The framework make commands ONLY work in Linux. If you have a windows computer. Please install a VM of Linux using VM Workstation. If your computer is not fast enough for a VM then you will have to dual boot. Also, for VM's, make sure you use a 32 bit version of Linux.

### Setting Up ESP Loader ###

##### For Linux #####

1. Install the required package to compile with esp-idf.  
Terminal command: sudo apt-get install git wget make libncurses-dev flex bison gperf python python-serial  

2. Set your PATH variables in .profile to add paths to the esp-idf and the xtensa toolchain. The .profile file is hidden in the Home directory and can be found by pressing ctrl+h when in Home. Once you update the paths, you must either restart your bash or your system in order for the changes to take effect. 
**The lines to add are:**  
export PATH=$PATH:$(directory path to controlsystems2018)/controlsystems2018/esp-idf/xtensa-esp32-elf/bin    
export IDF_PATH=(directory path to controlsystems2018)/controlsystems2018/esp-idf  
**Example lines:**  
export PATH=$PATH:$HOME/Documents/2017-2018/controlsystems2018/esp-idf/xtensa-esp32-elf/bin  
export IDF_PATH=~/Documents/2017-2018/controlsystems2018/esp-idf   

### Make Commands ###

* `make menuconfig PROJECT_NAME=<Subsystem name>` - Open the config menu for the ESP32 toolchain.
* `make app-flash PROJECT_NAME=<Subsystem folder name>` - Flash your program onto the ESP32.
* `make app PROJECT_NAME=<Subsystem folder name>` - Build your program.
* `make monitor PROJECT_NAME=<Subsystem folder name>` - Creates all serial monitor with ESP32.

### Make Process ###
1. After coding your project, perform a `make menuconfig PROJECT_NAME=<Subsystem name>` to access the SDK configuration menu.
2. Navigate to and select Serial Flash Config and make sure the serial port setting is the port that the ESP32 is connected to.
3. Save the settings and exit.
4. Perform a `make app-flash PROJECT_NAME=<Subsystem folder name>` to build and upload your program to the ESP32.
	* if you only want to build the program, then perform `make app PROJECT_NAME=<Subsystem folder name>` 
