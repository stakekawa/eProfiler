/*!
 *  \file c_mainwindow_imp.h
 *
 *  \brief This file contains the declaration of the C_MainWindow_IMP class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef EPROFILE_C_MAINWINDOW_IMP_H
#define EPROFILE_C_MAINWINDOW_IMP_H


#include <QMainWindow>
#include "ui_c_mainwindow.h"


class C_NumbersSelection;
class C_NumbersSelector;


class C_MainWindow_IMP : public QMainWindow
{
    Q_OBJECT


public:

    explicit C_MainWindow_IMP(QWidget* p_parent = Q_NULLPTR);

    virtual ~C_MainWindow_IMP();


protected:

    void closeEvent(QCloseEvent* p_event) override;

    void resizeEvent(QResizeEvent* p_event) override;


private:

    void DrawGeometry();

    Ui::C_MainWindow*   m_ui;
    C_NumbersSelector*  m_numbersSelector;
    C_NumbersSelection* m_numbersSelection;

    Q_DISABLE_COPY(C_MainWindow_IMP)


};


#endif // EPROFILE_C_MAINWINDOW_IMP_H

