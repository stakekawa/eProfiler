/*!
 *  \file c_mainwindow_imp.cpp
 *
 *  \brief This file contains the declaration of the C_MainWindow_IMP class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QCloseEvent>
#include <QtTwo/QDpiHelper.h>
#include <QtTwo/QtTwoDefines.h>
#include <two/c_logger.h>
#include "c_mainwindow_imp.h"


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* explicit */
C_MainWindow_IMP::C_MainWindow_IMP(QWidget* p_parent /* = Q_NULLPTR */) :
    QMainWindow(p_parent),
    m_ui(new Ui::C_MainWindow())
{
    m_ui->setupUi(this);

    /* show the main window on construction */

    QMainWindow::show();

    /* after the main window is shown compute the aspect ratio */

    QDpiHelper::setAspectRatio(this);

    LOGGER_HIGH << "Aspect ratio is" << QDpiHelper::aspectRatio() << "and DPI is" << QDpiHelper::dpi(this) << LOGGER_ENDL;

    QTTWO_CONNECT4(m_ui->m_actionQuit, SIGNAL(triggered()), this, SLOT(close()));
}


/* virtual */
C_MainWindow_IMP::~C_MainWindow_IMP()
{
    delete m_ui;
    m_ui = NULL;
}


/*                                                                            */
/* Protected members                                                          */
/*                                                                            */


void C_MainWindow_IMP::closeEvent(QCloseEvent* p_closeEvent)
{
    if (NULL != p_closeEvent)
    {
        LOGGER_DEBUG << "C_MainWindow_IMP::closeEvent accepted" << LOGGER_ENDL;
        p_closeEvent->accept();
    }
}
