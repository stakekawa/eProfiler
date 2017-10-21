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


};


#endif // EPROFILE_C_SETTINGS_H

