/*!
 *  \file c_numbersselector.cpp
 *
 *  \brief This file contains the implementation of the C_NumbersSelector class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QPushButton>
#include <QResizeEvent>
#include <QtTwo/QtTwoDefines.h>
#include <QtTwo/QtTwoUtils.h>
#include <two/defines.h>
#include "c_numbersselector.h"
#include "eprofile.h"


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


/*                                                                            */
/* NumbersSelectorPrivateData_s struct                                        */
/*                                                                            */


struct C_NumbersSelector::NumbersSelectorPrivateData_s
{

    std::array<QPushButton*, static_cast<size_t>(k_nLottoNumbers)> numbersPushButtons;
    std::list<char>                                                selectedNumbers;

    NumbersSelectorPrivateData_s() :
        numbersPushButtons(),
        selectedNumbers()
    {
        for (int i = 0; i < k_nLottoNumbers; ++i)
        {
            numbersPushButtons[static_cast<size_t>(i)] = new QPushButton(QString::number(i + 1));
            numbersPushButtons[static_cast<size_t>(i)]->setCheckable(true);
            numbersPushButtons[static_cast<size_t>(i)]->setChecked(false);
        }
    }

    ~NumbersSelectorPrivateData_s()
    {
        for (QPushButton*& l_pushButton : numbersPushButtons)
        {
            deleteWidget(l_pushButton);
        }
    }

    TWO_DISABLE_COPY(NumbersSelectorPrivateData_s)

    TWO_DISABLE_MOVE(NumbersSelectorPrivateData_s)

};


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* explicit */
C_NumbersSelector::C_NumbersSelector(QWidget* p_parent /* = Q_NULLPTR */) :
    QFrame(p_parent),
    m_data(new NumbersSelectorPrivateData_s())
{
    qRegisterMetaType< std::list<char> >("std::list<char>");

    static_assert(k_nSelectorRows * k_nSelectorCols == k_nLottoNumbers, "Number of rows times number of columns should be equal to number of lotto numbers");

    for (int i = 0; i < k_nSelectorRows; ++i)
    {
        for (int j = 0; j < k_nSelectorCols; ++j)
        {
            m_data->numbersPushButtons[static_cast<size_t>(i * k_nSelectorCols + j)]->setParent(this);
            QTTWO_CONNECT4(m_data->numbersPushButtons[static_cast<size_t>(i * k_nSelectorCols + j)], SIGNAL(toggled(bool)), this, SLOT(numberButtonToggled(const bool)));
        }

    } /* for (int i = 0; i < k_nRows; ++i) */
}


/* virtual */
C_NumbersSelector::~C_NumbersSelector()
{
    if (NULL != m_data)
    {
        delete m_data;
        m_data = NULL;
    }
}


/*                                                                            */
/* Private slots                                                              */
/*                                                                            */


void C_NumbersSelector::numberButtonToggled(const bool p_toggled)
{
    const QObject* l_object = QObject::sender();

    if (Q_NULLPTR != l_object)
    {
        const QPushButton* l_pushButton = qobject_cast<const QPushButton*>(l_object);

        if (Q_NULLPTR != l_pushButton)
        {
            QString l_text = l_pushButton->text();

            l_text.remove('&');

            bool l_converted = false;

            const int l_number = l_text.toInt(&l_converted);

            if (true == l_converted)
            {
                if (true == p_toggled)
                {
                    m_data->selectedNumbers.push_back(static_cast<char>(0xFF & l_number));
                    m_data->selectedNumbers.sort();
                }
                else
                {
                    std::list<char>::iterator it_number = m_data->selectedNumbers.begin();

                    while (m_data->selectedNumbers.end() != it_number)
                    {
                        if (l_number == *it_number)
                        {
                            it_number = m_data->selectedNumbers.erase(it_number);
                        }
                        else
                        {
                            ++it_number;
                        }
                    }
                }

                emit selectedNumbers(m_data->selectedNumbers);

            } /* if (true == l_converted) */

        } /* if (Q_NULLPTR != l_pushButton) */

    } /* if (Q_NULLPTR != l_object) */
}


/*                                                                            */
/* Protected members                                                          */
/*                                                                            */


/* virtual */
void C_NumbersSelector::resizeEvent(QResizeEvent* p_event)
{
    if (NULL != p_event)
    {
        const float l_width      = p_event->size().width();
        const int   l_buttonSize = static_cast<int>(l_width / static_cast<float>(k_nSelectorCols));

        configureQPushButtons(this, l_buttonSize, l_buttonSize);

        for (int i = 0; i < k_nSelectorRows; ++i)
        {
            for (int j = 0; j < k_nSelectorCols; ++j)
            {
                m_data->numbersPushButtons[static_cast<size_t>(i * k_nSelectorCols + j)]->QTTWO_MOVE(static_cast<float>(j) * l_buttonSize, static_cast<float>(i) * l_buttonSize);
            }

        } /* for (int i = 0; i < k_nRows; ++i) */

        p_event->accept();
    }
}
