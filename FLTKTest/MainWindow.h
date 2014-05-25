#pragma once

class MainWindowUI;
class Fl_Text_Buffer;
class Fl_Button;

class MainWindow
{
	friend class Logger;
public:
	MainWindow();
	~MainWindow();
	
	void show();

private:
	static void clearButton_callback(Fl_Button* button, void* data);
private:
	MainWindowUI* ui;
	Fl_Text_Buffer* textBuffer;
};


#define LOGGER (Logger::instance())

class Logger
{
public:
	static Logger& instance();
	void log(const char* msg);

private:
	Logger();
	~Logger();
};
