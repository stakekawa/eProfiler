/*!
 *  \file c_mainwindow_imp.cpp
 *
 *  \brief This file contains the declaration of the C_MainWindow_IMP class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QApplication>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QtTwo/QDpiHelper.h>
#include <QtTwo/QtTwoDefines.h>
#include <QtTwo/QtTwoUtils.h>
#include <two/c_logger.h>
#include "c_mainwindow_imp.h"
#include "c_numbersselection.h"
#include "c_numbersselector.h"
#include "c_settings.h"
#include "eprofile.h"


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* explicit */
C_MainWindow_IMP::C_MainWindow_IMP(QWidget* p_parent /* = Q_NULLPTR */) :
    QMainWindow(p_parent),
    m_ui(new Ui::C_MainWindow()),
    m_numbersSelector(Q_NULLPTR),
    m_numbersSelection(Q_NULLPTR)
{
    m_ui->setupUi(this);

    DrawGeometry();

    /* show the main window on construction */

    QMainWindow::show();

    /* after the main window is shown compute the aspect ratio */

    QDpiHelper::setAspectRatio(this);

    LOGGER_HIGH << "Aspect ratio is" << QDpiHelper::aspectRatio() << "and DPI is" << QDpiHelper::dpi(this) << LOGGER_ENDL;

    QFont l_font = QApplication::font();
    l_font.setPointSize(C_Settings::Instance().GetFontSize());
    QApplication::setFont(l_font);

    const float l_width  = k_mainWindowWidth  * QDpiHelper::aspectRatio();
    const float l_height = k_mainWindowHeight * QDpiHelper::aspectRatio();

    this->QTTWO_SIZE_MIN(l_width, l_height);

    QTTWO_CONNECT4(m_ui->m_actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    QTTWO_CONNECT4(m_numbersSelector, SIGNAL(selectedNumbers(const std::list<char>&)), m_numbersSelection, SLOT(setSelectedNumbers(const std::list<char>&)));
}


/* virtual */
C_MainWindow_IMP::~C_MainWindow_IMP()
{
    deleteWidget(m_numbersSelector);
    deleteWidget(m_numbersSelection);

    delete m_ui;
    m_ui = NULL;
}


/*                                                                            */
/* Protected members                                                          */
/*                                                                            */


/* virtual */
void C_MainWindow_IMP::closeEvent(QCloseEvent* p_event)
{
    if (NULL != p_event)
    {
        LOGGER_DEBUG << "C_MainWindow_IMP::closeEvent accepted" << LOGGER_ENDL;
        p_event->accept();
    }
}


/* virtual */
void C_MainWindow_IMP::resizeEvent(QResizeEvent* p_event)
{
    if (NULL != p_event)
    {
        const float l_margin                 = k_marginNormal * QDpiHelper::aspectRatio();

        const float l_width                  = static_cast<float>(p_event->size().width());
        const float l_height                 = static_cast<float>(p_event->size().height());

        const float l_menuBarHeight          = static_cast<float>(m_ui->m_menuBar->height());
        const float l_statusBarHeight        = static_cast<float>(m_ui->m_statusBar->height());

        const float l_centralWidgetWidth     = l_width;
        const float l_centralWidgetHeight    = l_height - l_menuBarHeight - l_statusBarHeight;

        const float l_leftPanelWidth         = k_leftPanelWidth * QDpiHelper::aspectRatio();

        const float l_numbersSelectorWidth   = l_leftPanelWidth;
        const float l_numbersSelectorHeight  = static_cast<float>(k_numberButtonSize * k_nSelectorRows) * QDpiHelper::aspectRatio();

        const float l_numbersSelectionWidth  = l_leftPanelWidth;
        const float l_numbersSelectionHeight = k_numberButtonSize * QDpiHelper::aspectRatio();

        m_ui->m_centralWidget->QTTWO_RESIZE(l_centralWidgetWidth, l_centralWidgetHeight);
        m_ui->m_centralWidget->QTTWO_MOVE(0.f, l_menuBarHeight);

        if (NULL != m_numbersSelector)
        {
            m_numbersSelector->QTTWO_RESIZE(l_numbersSelectorWidth, l_numbersSelectorHeight);
            m_numbersSelector->QTTWO_MOVE(l_margin, l_margin);
        }

        if (NULL != m_numbersSelection)
        {
            m_numbersSelection->QTTWO_RESIZE(l_numbersSelectionWidth, l_numbersSelectionHeight);
            m_numbersSelection->QTTWO_MOVE(l_margin, l_numbersSelectorHeight + l_margin);
        }

        p_event->accept();
    }
}


/*                                                                            */
/* Private members                                                            */
/*                                                                            */


void C_MainWindow_IMP::DrawGeometry()
{
    m_numbersSelector  = new C_NumbersSelector(m_ui->m_centralWidget);
    m_numbersSelection = new C_NumbersSelection(m_ui->m_centralWidget);
}
