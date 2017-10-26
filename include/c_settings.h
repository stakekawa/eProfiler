/*!
 *  \file c_settings.h
 *
 *  \brief This file contains the declaration of the C_Settings class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef EPROFILE_C_SETTINGS_H
#define EPROFILE_C_SETTINGS_H


#include "two/defines.h"


class C_Settings
{


public:

    /*!
     *  \brief Get the instance of the singleton
     */
    static C_Settings& Instance();

    /*!
     *  \brief Load the settings from storage
     */
    void LoadSettings();

    /*!
     *  \brief Save the settings to storage
     */
    void SaveSettings();

    /*!
     *  \brief Get the application font size
     */
    float GetFontSize() const;

    /*!
     *  \brief Set the application font size
     */
    void SetFontSize(const float p_fontSize);


private:

    /*!
     *  \brief Constructor. Private due to singleton design pattern
     */
    C_Settings();

    /*!
     *  \brief Destructor
     */
    ~C_Settings();

    static C_Settings* s_instance;

    struct SettingsData_s;

    SettingsData_s* m_data;

    TWO_DISABLE_COPY(C_Settings)

    TWO_DISABLE_MOVE(C_Settings)


};


#endif // EPROFILE_C_SETTINGS_H

