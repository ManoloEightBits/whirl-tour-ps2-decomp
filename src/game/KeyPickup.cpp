// Whirl Tour: KeyPickup (RTTI name). Slot 3 of its vtable at 0x002846A8, which overrides Pickup's
// empty slot 3 (0x0011CEB0). Names of the virtuals are ours; only the shapes are proven.
class EnvObj
{
public:
    virtual ~EnvObj();
};

#include "game/Player.h"

class Pickup : public EnvObj
{
public:
    Pickup();
    virtual void Reset(void *);          // slot 1, 0x0011CB58 (overridden by KeyPickup)
    virtual void Update(float dt);       // slot 2, 0x0011B3D8
    virtual void OnCollected(Player *);  // slot 3, empty in Pickup
};

class KeyPickup : public Pickup
{
public:
    KeyPickup();
    virtual void Reset(void *);
    virtual void Update(float dt);
    virtual void OnCollected(Player *);
};

void KeyPickup::OnCollected(Player *player)
{
    player->AddKey();
}
