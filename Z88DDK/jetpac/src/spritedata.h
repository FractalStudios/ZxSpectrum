#ifndef _SPRITE_DATA_H_
#define _SPRITE_DATA_H_

#include "sprites.h"

// Jetman sprite.
typedef struct _JetmanSprite
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphDataWalkingRight [4 * 128];
    UINT8   m_glyphDataWalkingLeft [4 * 128];
    UINT8   m_glyphDataFlyingRight [4 * 128];
    UINT8   m_glyphDataFlyingLeft [4 * 128];
} JetmanSprite;

// Rocket sprite.
typedef struct RocketSprite
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphDataBottom [1 * 96];
    UINT8   m_glyphDataMiddle [1 * 96];
    UINT8   m_glyphDataTop [1 * 96];
} RocketSprite;

// Cloud sprite.
typedef struct _CloudSprite
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphData [3 * 144];
} CloudSprite;


// Globals.

extern  JetmanSprite        g_jetman;
extern  RocketSprite        g_rocketU1;
extern  RocketSprite        g_rocketU2;
extern  RocketSprite        g_rocketU3;
extern  RocketSprite        g_rocketU4;
extern  CloudSprite         g_cloud;
extern  MaskedSpriteM1F1_64 g_goldBar;
extern  MaskedSpriteM1F1_96 g_fuel;
extern  MaskedSpriteM1F1_96 g_radiationCanister;
extern  MaskedSpriteM1F1_96 g_triangle;
extern  MaskedSpriteM1F1_96 g_dome;
extern  MaskedSpriteM1F1_96 g_crystal;
extern  MaskedSpriteM2F2_96 g_nastyMeteor;
extern  MaskedSpriteM2F2_96 g_nastyFurball;
extern  MaskedSpriteM2F1_64 g_nastyPlane;
extern  MaskedSpriteM1F1_64 g_nastyFlyingSaucer;
extern  MaskedSpriteM1F2_96 g_nastyBall;
extern  MaskedSpriteM1F1_96 g_nastySatellite;
extern  MaskedSpriteM2F1_96 g_nastyMilleniumFalcon;
extern  MaskedSpriteM1F1_96 g_nastyBlob;
extern  MaskedSpriteM1F2_96 g_rocketSmokeTrail;

#endif

/******************************* End of File *******************************/
