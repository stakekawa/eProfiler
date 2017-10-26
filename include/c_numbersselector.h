/*!
 *  \file c_numbersselector.h
 *
 *  \brief This file contains the declaration of the C_NumbersSelector class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef C_NUMBERSSELECTOR_H
#define C_NUMBERSSELECTOR_H


#include <QFrame>


class C_NumbersSelector : public QFrame
{
    Q_OBJECT


public:

    explicit C_NumbersSelector(QWidget* p_parent = Q_NULLPTR);

    virtual ~C_NumbersSelector();


public Q_SLOTS:


private Q_SLOTS:

    void numberButtonToggled(const bool p_toggled);


Q_SIGNALS:

    void selectedNumbers(const std::list<char>& p_numbers);


protected:

    void resizeEvent(QResizeEvent* p_event) override;


private:

    struct NumbersSelectorPrivateData_s;

    NumbersSelectorPrivateData_s* m_data;

    Q_DISABLE_COPY(C_NumbersSelector)


};


#endif // C_NUMBERSSELECTOR_H
