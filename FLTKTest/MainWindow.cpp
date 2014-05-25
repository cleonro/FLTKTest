#include "MainWindow.h"
#include "MainWindowUI.h"
#include <FL/Fl_Text_Buffer.H>

static MainWindow* mainWindow = NULL;
Logger::Logger()
{

}

Logger::~Logger()
{

}

Logger& Logger::instance()
{
	static Logger log;
	return log;
}

void Logger::log(const char* msg)
{
	if(mainWindow == NULL)
	{
		return;
	}
	mainWindow->ui->output->insert(msg);
}

void MainWindow::clearButton_callback(Fl_Button* button, void* data)
{
	((MainWindowUI*)(button->parent()->user_data()))->output->buffer()->text("");
}

MainWindow::MainWindow()
{
	ui = new MainWindowUI;
	if(mainWindow == NULL)
	{
		mainWindow = this;
	}
}

MainWindow::~MainWindow()
{
	delete textBuffer;
	delete ui;
}

void MainWindow::show()
{
	textBuffer = new Fl_Text_Buffer;
	ui->output->buffer(textBuffer);
	ui->output->insert("Output...");
	ui->mainWindow->show();
	
	ui->clearButton->callback((Fl_Callback*)clearButton_callback);
}