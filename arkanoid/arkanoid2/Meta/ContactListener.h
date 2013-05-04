#pragma once

#ifndef _CONTACT_LISTNER_H_
#define _CONTACT_LISTNER_H_

#include <Box2D\Box2D.h>

class ContactListener :
	public b2ContactListener
{
public:

	ContactListener(void);
	~ContactListener(void);

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif