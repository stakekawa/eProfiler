/*!
 *  \file c_numbersselection.h
 *
 *  \brief This file contains the declaration of the C_NumbersSelection class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef C_NUMBERSSELECTION_H
#define C_NUMBERSSELECTION_H


#include <QFrame>


class C_NumbersSelection : public QFrame
{
    Q_OBJECT


public:

    explicit C_NumbersSelection(QWidget* p_parent = Q_NULLPTR);

    virtual ~C_NumbersSelection();


public Q_SLOTS:

    void setSelectedNumbers(const std::list<char>& p_numbers);


protected:

    void resizeEvent(QResizeEvent* p_event) override;


private:

    struct NumbersSelectionPrivateData_s;

    NumbersSelectionPrivateData_s* m_data;

    Q_DISABLE_COPY(C_NumbersSelection)


};


#endif // C_NUMBERSSELECTION_H
