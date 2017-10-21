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


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


C_Settings* C_Settings::s_instance = nullptr;
static QSettings* s_settings;


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
        LOGGER_HIGH << "Loading settings..." << LOGGER_ENDL;

        LOGGER_HIGH << "Settings loaded!" << LOGGER_ENDL;
    }
}


void C_Settings::SaveSettings()
{
    if (nullptr != s_settings)
    {
        LOGGER_HIGH << "Saving settings..." << LOGGER_ENDL;

        s_settings->sync();

        LOGGER_HIGH << "Settings saved!" << LOGGER_ENDL;
    }
}



/*                                                                            */
/* Private members                                                            */
/*                                                                            */


C_Settings::C_Settings()
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
}
