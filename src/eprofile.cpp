/*!
 *  \file eprofile.cpp
 *
 *  \brief This is the source code with the implementation of the main function
           of the eProfile application
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QApplication>
#include <QtTwo/QtTwoDefines.h>
#include <QtTwo/QUnixSignalCatcher.h>
#include <two/c_logger.h>
#include "eprofile.h"
#include "c_mainwindow_imp.h"
#include "c_settings.h"


int main(int argc, char* argv[])
{
    int l_return = EXIT_SUCCESS;

    /* create the logger and set the log threshold */

    LOGGER.SetLogThreshold(two::C_Logger::LoggerLevelEnum::LoggerLevelVerbose);

    /* create the application main loop */

    QApplication l_application(argc, argv);

    /* create the signal handler */

    QUnixSignalCatcher l_signalCather;

    /* connect the signal handler */

    QMetaObject::Connection l_signalCatcherConnection = QTTWO_CONNECT4(&l_signalCather, SIGNAL(Signal(const UnixSignalEnum)), &l_application, SLOT(quit()));

    /* load settings */

    C_Settings::Instance();

    /* create the main window */

    C_MainWindow_IMP l_mainWindow;

    /* run the application */

    l_return = l_application.exec();

    /* disconnect the signal handler */

    QTTWO_DISCONNECT(l_signalCatcherConnection);

    /* save the settings */

    C_Settings::Instance().SaveSettings();

    /* close the log */

    LOGGER << LOGGER_CLOSE;

    return l_return;
}
