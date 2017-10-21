/*!
 *  \file c_charcombination.h
 *
 *  \brief This file contains the declaration of C_CharCombination class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#ifndef EPROFILE_C_CHARCOMBINATION_H
#define EPROFILE_C_CHARCOMBINATION_H


#include "two/c_combination.h"
#include "two/common.h"


namespace two {


/*!
 *  \brief The C_CharCombination class is the specialization of class
 *         C_Combination for char types
 */
class C_CharCombination : public C_Combination<char>
{


public:


    /*!
     *  \brief Constructor
     */
    C_CharCombination();

    /*!
     *  \brief Constructor using a std::vector of elements
     *
     *  \param p_elements reference to std::vector of elements
     */
    explicit C_CharCombination(const std::vector<char>& p_elements);

    /*!
     *  \brief Constructor using a std::vector of elements
     *
     *  \param p_elements r-value to std::vector of elements
     */
    explicit C_CharCombination(std::vector<char>&& p_elements);

    /*!
     *  \brief Constructor using a std::list of elements
     *
     *  \param p_elements reference to std::list of elements
     */
    explicit C_CharCombination(const std::list<char>& p_elements);

    /*!
     *  \brief Copy constructor
     */
    C_CharCombination(const C_CharCombination& p_orig);

    /*!
     *  \brief Copy assignment
     */
    C_CharCombination& operator=(const C_CharCombination& p_other);

    /*!
     *  \brief Move constructor
     */
    C_CharCombination(C_CharCombination&& p_orig);

    /*!
     *  \brief Move assignment
     */
    C_CharCombination& operator=(C_CharCombination&& p_other);

    /*!
     *  \brief Destructor
     */
    virtual ~C_CharCombination();

    /*!
     *  \brief Compute the key associated with the first 8 char of the combination
     */
    void ComputeKey();

    /*!
     *  \brief Get the the key of the combination
     */
    TwoKey_t GetKey() const;


private:

    TwoKey_t m_key;


};


/*!
 *  \brief Inserction operator
 */
std::ostream& operator<<(std::ostream& p_ostream, const C_CharCombination& p_combination);


} /* namespace two { */


#endif // EPROFILE_C_CHARCOMBINATION_H
