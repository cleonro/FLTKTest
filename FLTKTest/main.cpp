// FLTKTest.cpp : Defines the entry point for the console application.
//

#include "MainWindow.h"
#include <FL/Fl.H>

int main(int argc, char **argv)  
{  
 	MainWindow window;

	//Fl::visual(FL_DOUBLE|FL_INDEX);
 	window.show();

	return Fl::run();  
} 