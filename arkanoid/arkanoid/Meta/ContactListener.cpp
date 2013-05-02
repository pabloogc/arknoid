#include "ContactListener.h"
#include "GameObjects\GameObject.h"

ContactListener::ContactListener(void)
{
}


ContactListener::~ContactListener(void)
{
}


void ContactListener::BeginContact(b2Contact* contact){

	GameObject* bodyUserDataA = static_cast<GameObject*>		  
		(contact->GetFixtureA()->GetBody()->GetUserData());
	GameObject* bodyUserDataB = static_cast<GameObject*>
		(contact->GetFixtureB()->GetBody()->GetUserData());

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (bodyUserDataA && bodyUserDataB){
		bodyUserDataA->startContact(bodyUserDataB, contact);
		bodyUserDataB->startContact(bodyUserDataA, contact);
	}

}

void ContactListener::EndContact(b2Contact* contact){
	
	GameObject* bodyUserDataA = static_cast<GameObject*>		  
		(contact->GetFixtureA()->GetBody()->GetUserData());
	GameObject* bodyUserDataB = static_cast<GameObject*>
		(contact->GetFixtureB()->GetBody()->GetUserData());

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if (bodyUserDataA != nullptr && bodyUserDataB != nullptr){
		bodyUserDataA->endContact(bodyUserDataB, contact);
		bodyUserDataB->endContact(bodyUserDataA, contact);
	}
}