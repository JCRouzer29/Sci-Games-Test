////////////////////////////////////////////////////////////////////////////
/*/	
 *	Creator:		Joshua C. Rouzer
 *	Title:			Person source file
 *	Last Edited:	11/18/2015
 *	Summary:		Function definition for Person class
/*/
////////////////////////////////////////////////////////////////////////////

#include "Person.h"

Person::Person(){
	m_sBirth = 0;
	m_sEnd = 32767;
}

Person::Person(unsigned short sBirth, unsigned short sEnd){
	m_sBirth = sBirth;
	m_sEnd = sEnd;
}

Person::~Person(){}

//Swaps the m_sBirth and m_sEnd variable's values
void Person::Swap(){
	m_sBirth ^= m_sEnd;
	m_sEnd ^= m_sBirth;
	m_sBirth ^= m_sEnd;
}