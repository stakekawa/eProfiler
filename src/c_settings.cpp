/*!
 *  \file c_settings.cpp
 *
 *  \brief This file contains the declaration of the C_Settings class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <QSettings>
#include <two/c_logger.h>
#include <QtTwo/QtTwoDefines.h>
#include "c_settings.h"
#include "eprofile.h"


#define SETTINGS_LOCKER      std::lock_guard<std::recursive_mutex> l_lock(m_data->mutex)


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


C_Settings* C_Settings::s_instance = nullptr;
static QSettings* s_settings;

static constexpr float k_fontSizeDefault = 11.f;


/*                                                                            */
/* SettingsData_s struct                                                      */
/*                                                                            */


struct C_Settings::SettingsData_s
{
    float                        fontSize;
    mutable std::recursive_mutex mutex;

    SettingsData_s() :
        fontSize(k_fontSizeDefault),
        mutex()
    { /* empty */ }

    TWO_DISABLE_COPY(SettingsData_s);

    TWO_DISABLE_MOVE(SettingsData_s);

};


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


/* static */
C_Settings& C_Settings::Instance()
{
    if (nullptr == s_instance)
    {
        s_instance = new C_Settings();
    }

    return *s_instance;
}


void C_Settings::LoadSettings()
{
    if (nullptr != s_settings)
    {
        SETTINGS_LOCKER;

        LOGGER_HIGH << "Loading settings..." << LOGGER_ENDL;

        LOGGER_HIGH << "Settings loaded!" << LOGGER_ENDL;
    }
}


void C_Settings::SaveSettings()
{
    if (nullptr != s_settings)
    {
        SETTINGS_LOCKER;

        LOGGER_HIGH << "Saving settings..." << LOGGER_ENDL;

        s_settings->sync();

        LOGGER_HIGH << "Settings saved!" << LOGGER_ENDL;
    }
}


float C_Settings::GetFontSize() const
{
    SETTINGS_LOCKER;

    return m_data->fontSize;
}


void C_Settings::SetFontSize(const float p_fontSize)
{
    SETTINGS_LOCKER;

    m_data->fontSize = p_fontSize;
}


/*                                                                            */
/* Private members                                                            */
/*                                                                            */


C_Settings::C_Settings() :
    m_data(new SettingsData_s())
{
    s_settings = new QSettings(QTTWO_TR(EPROFILE_ORGANIZATION_NAME), QTTWO_TR(EPROFILE_APPLICATION_NAME));

    LoadSettings();
}


C_Settings::~C_Settings()
{
    SaveSettings();

    if (NULL != s_settings)
    {
        delete s_settings;
    }

    if (NULL != m_data)
    {
        delete m_data;
        m_data = NULL;
    }
}
