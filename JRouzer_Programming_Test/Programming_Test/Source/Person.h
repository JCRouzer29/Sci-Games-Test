////////////////////////////////////////////////////////////////////////////
/*/	
 *	Creator:		Joshua C. Rouzer
 *	Title:			Person Header File
 *	Last Edited:	11/18/2015
 *	Summary:		Person class definition file
/*/
////////////////////////////////////////////////////////////////////////////
#ifndef PERSON_H
#define PERSON_H

class Person{
	//Major variables
	unsigned short m_sBirth;
	unsigned short m_sEnd;
public:
	//Constructors & Destructor
	Person();
	Person(unsigned short sBirth, unsigned short sEnd);
	~Person();

	//Accessors
	unsigned short GetBirth()	{return m_sBirth;	}
	unsigned short GetEnd()		{return m_sEnd;		}

	//Mutators
	void SetBirth(unsigned short sBirth)	{m_sBirth	= sBirth;	}
	void SetEnd	 (unsigned short sEnd)		{m_sEnd		= sEnd;		}

	//Complex Functions
	void Swap();
};

#endif