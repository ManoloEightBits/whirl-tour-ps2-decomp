#include "game/Pickup.h"

u32 HashStringCRC32(const char *str);                    // 0x001B1CD0
int SendScriptEvent(u32 eventCrc, int arg1, void *arg2); // 0x001266D0

Vec3f *Pickup::GetPos44()
{
    return &mPos44;
}

Vec3f *Pickup::GetPos50()
{
    return &mPos50;
}

int Pickup::IsState4()
{
    return mState60 == 4;
}

void Pickup::OnCollected(Player *)
{
}

void Pickup::SetFields68_6C(int a, int b)
{
    mField68 = a;
    mField6C = b;
}

void KeyPickup::OnCollected(Player *player)
{
    player->AddKey();
}

void HealthPickup::OnCollected(Player *player)
{
    player->AddHealth(*(f32 *)(mPickupData70 + 0x90));
}

void ScooterPickup::OnCollected(Player *player)
{
    player->AddScooter(mScooterId);
}

void BGMPickup::OnCollected(Player *player)
{
    player->AddBGM(mBGMId);
}

void TransmitterPickup::OnCollected(Player *)
{
}

void SpeedPickup::OnCollected(Player *player)
{
    u8 *data = mPickupData70;
    player->AddSpeedBoost(*(f32 *)(data + 0x8C), *(f32 *)(data + 0x90));
}

void SpinPickup::OnCollected(Player *player)
{
    u8 *data = mPickupData70;
    player->AddSpinBoost(*(f32 *)(data + 0x8C), *(f32 *)(data + 0x90));
}

void JumpPickup::OnCollected(Player *player)
{
    u8 *data = mPickupData70;
    player->AddJumpBoost(*(f32 *)(data + 0x8C), *(f32 *)(data + 0x90));
}

void BalancePickup::OnCollected(Player *player)
{
    u8 *data = mPickupData70;
    player->AddBalanceBoost(*(f32 *)(data + 0x8C), *(f32 *)(data + 0x90));
}

void TimerPickup::OnCollected(Player *)
{
    SendScriptEvent(HashStringCRC32("add_time"), 0, mPickupData70 + 0x8C);
}
