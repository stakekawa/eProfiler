/*!
 *  \file c_charcombination.cpp
 *
 *  \brief This file contains the implementation of C_CharCombination class
 *  \author Stefano Takekawa s.takekawa_at_gmail.com
 *  \date 2017
 *  \copyright Apache Licence 2.0
 */


#include <utility>             // std::forward
#include "c_charcombination.h"


namespace two {


/*                                                                            */
/* Private data                                                               */
/*                                                                            */


static constexpr TwoKey_t k_keyDefault         = 0x0ll;
static constexpr int      k_nMaxElementsForKey = 8;
static constexpr int      k_nKeyBitsPerElement = 8;


/*                                                                            */
/* Functions                                                                  */
/*                                                                            */


std::ostream& operator<<(std::ostream& p_ostream, const C_CharCombination& p_combination)
{
    p_ostream << "{ ";

    const int l_nElements = p_combination.GetNumberOfElements();
    for (int i = 0; i < l_nElements - 1; ++i)
    {
        p_ostream << static_cast<int>(p_combination.GetElement(i)) << ", ";
    }

    if (0 < l_nElements)
    {
        p_ostream << static_cast<int>(p_combination.GetElement(l_nElements - 1));
    }

    p_ostream << " }";

    return p_ostream;
}


/*                                                                            */
/* Public members                                                             */
/*                                                                            */


C_CharCombination::C_CharCombination() : C_Combination<char>(),
    m_key(k_keyDefault)
{

}


/* explicit */
C_CharCombination::C_CharCombination(const std::vector<char>& p_elements) :
    C_Combination<char>(p_elements),
    m_key(k_keyDefault)
{

}


/* explicit */
C_CharCombination::C_CharCombination(std::vector<char>&& p_elements) :
    C_Combination<char>(std::forward<std::vector<char> >(p_elements)),
    m_key(k_keyDefault)
{

}


/* explicit */
C_CharCombination::C_CharCombination(const std::list<char>& p_elements) :
    C_Combination<char>(p_elements),
    m_key(k_keyDefault)
{

}


C_CharCombination::C_CharCombination(const C_CharCombination& p_orig) :
    C_Combination<char>(p_orig),
    m_key(p_orig.m_key)
{

}


C_CharCombination& C_CharCombination::operator=(const C_CharCombination& p_other)
{
    if (this != &p_other)
    {
        C_Combination<char>::operator=(p_other);
        m_key = p_other.m_key;
    }

    return *this;
}


C_CharCombination::C_CharCombination(C_CharCombination&& p_orig) :
    C_Combination<char>(std::forward<C_CharCombination>(p_orig)),
    m_key(std::move(p_orig.m_key))
{

}


C_CharCombination& C_CharCombination::operator=(C_CharCombination&& p_other)
{
    if (this != &p_other)
    {
        C_Combination<char>::operator=(std::forward<C_CharCombination>(p_other));
        std::swap(m_key, p_other.m_key);
    }

    return *this;
}


/* virtual */
C_CharCombination::~C_CharCombination()
{

}


void C_CharCombination::ComputeKey()
{
    const int l_nMaxElements = std::min(GetNumberOfElements(), k_nMaxElementsForKey);

    m_key = k_keyDefault;

    for (int i = 0; i < l_nMaxElements; ++i)
    {
        const unsigned long l_shift = k_nKeyBitsPerElement * static_cast<unsigned long>(l_nMaxElements - i - 1);

        m_key |= static_cast<TwoKey_t>((0xFF & GetElement(i)) << l_shift);
    }
}


TwoKey_t C_CharCombination::GetKey() const
{
    return m_key;
}


} /* namespace two { */
