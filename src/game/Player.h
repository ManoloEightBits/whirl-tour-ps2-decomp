#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

// Whirl Tour: the object a pickup is handed when collected. The class name is ours (hypothesis);
// only the +0xA4 counter is proven, by 0x00123548 and by KeyPickup::OnCollected calling it.
class Player
{
public:
    void AddKey();  // 0x00123548

    char field_0x00[0xA4];
    int mKeys;  // 0xA4: name is ours; incremented once per key collected
};

#endif
