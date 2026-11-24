// Whirl Tour: KeyPickup (RTTI name). Slot 3 of its vtable at 0x002846A8, which overrides Pickup's
// empty slot 3 (0x0011CEB0). Names of the virtuals are ours; only the shapes are proven.
class EnvObj
{
public:
    virtual ~EnvObj();
};

class Player;  // name is ours: the object a pickup is handed when it is collected

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

void GiveKey(Player *player);  // 0x00123548, not yet decompiled

void KeyPickup::OnCollected(Player *player)
{
    GiveKey(player);
}
