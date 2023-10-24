# Udemy Course "Design Patterns in modern C++"

## System Setup
+ If you want to compile under linux, you need to have boost installed. E.g. under Ubuntu:
	- `$ sudo apt install libboost-dev`
+ If you want to compile under windows with the cl compiler and open the project with visual studio:
	- Unpack and compile boost:
		* Download thet latest windows version of boost as a `.zip` file under https://www.boost.org/users/history/version_1_83_0.html
		* Unpack the `.zip`
		* Open the folder where you unzipped the boost folder within powershell or cmd
		* Execute `./bootstrap.bat` and then execute `./b2`
		* Now boost will be compiled
		* Make sure you save the path that is shown after the compilation is done. These two paths need to be added to your `Path` variable of your windows machine
	- Set the `PATH` variable of your developer prompt
		* Go to Search --> "Systemumgebungsvariablen bearbeiten" --> "Umgebungsvariablen" --> Benutzerdefinierte Variablen --> Add to `Path`
		* Restart Visual Studio --> Now boost will be found by cmake within your visual studio
		* Alternatively do the following with `setx`: https://stackoverflow.com/questions/5898131/set-a-persistent-environment-variable-from-cmd-exe

# TODOs
+ Reimplement the observer pattern homework with the generic approach instead of limiting it to the concrete implementation
+ Composite Homework again with CRTP