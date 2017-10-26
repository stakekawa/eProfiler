/*!
 *  \file c_numbersselection.cpp
 *
 *  \brief This file contains the implementation of the C_NumbersSelection class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QLabel>
#include <QResizeEvent>
#include <QtTwo/QtTwoDefines.h>
#include <QtTwo/QtTwoUtils.h>
#include <two/defines.h>
#include "c_numbersselection.h"
#include "eprofile.h"


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


/*                                                                            */
/* NumbersSelectionPrivateData_s struct                                       */
/*                                                                            */


struct C_NumbersSelection::NumbersSelectionPrivateData_s
{
    QLabel*         numbersLabel;
    std::list<char> selectedNumbers;

    NumbersSelectionPrivateData_s() :
        numbersLabel(new QLabel()),
        selectedNumbers()
    { /* empty */ }

    ~NumbersSelectionPrivateData_s()
    {
        deleteWidget(numbersLabel);
    }

    void SetNumbers(const std::list<char>& p_numbers)
    {
        QString l_text(QTTWO_TR("Selected numbers: "));

        if (true == p_numbers.empty())
        {
            l_text += QTTWO_TR("none.");
        }
        else
        {
            for (const char l_number : p_numbers)
            {
                l_text += QString::number(l_number) + QString(" ");
            }

            l_text[l_text.size() - 1] = '.';
        }

        numbersLabel->setText(l_text);
    }

    TWO_DISABLE_COPY(NumbersSelectionPrivateData_s)

    TWO_DISABLE_MOVE(NumbersSelectionPrivateData_s)

};


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* explicit */
C_NumbersSelection::C_NumbersSelection(QWidget* p_parent /* = Q_NULLPTR */) :
    QFrame(p_parent),
    m_data(new NumbersSelectionPrivateData_s())
{
    m_data->numbersLabel->setParent(this);
    m_data->numbersLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_data->SetNumbers(std::list<char>());
}


/* virtual */
C_NumbersSelection::~C_NumbersSelection()
{
    if (NULL != m_data)
    {
        delete m_data;
        m_data = NULL;
    }
}


/*                                                                            */
/* Public slots                                                               */
/*                                                                            */


void C_NumbersSelection::setSelectedNumbers(const std::list<char>& p_numbers)
{
    if (NULL != m_data)
    {
        m_data->SetNumbers(p_numbers);
    }
}


/*                                                                            */
/* Protected members                                                          */
/*                                                                            */


/* virtual */
void C_NumbersSelection::resizeEvent(QResizeEvent* p_event)
{
    if (Q_NULLPTR != p_event)
    {
        const float l_width  = p_event->size().width();
        const float l_height = p_event->size().height();

        if (Q_NULLPTR != m_data->numbersLabel)
        {
            m_data->numbersLabel->QTTWO_RESIZE(l_width, l_height);
            m_data->numbersLabel->QTTWO_MOVE(0.f, (static_cast<int>(l_height) - m_data->numbersLabel->height()) / 2);
        }

        p_event->accept();
    }
}
