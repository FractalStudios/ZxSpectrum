#ifndef _SPRITES_H_
#define _SPRITES_H_

#include "defn.h"

// Definitions and Types.

// Sprite guard sizes.
#define SPRITE_TOP_GUARD_SIZE           7

// Sprite base.
typedef struct _SpriteBase
{
    UINT8   m_widthInBytes;
    UINT8   m_heightInPixels;
    UINT8   m_topGuard [SPRITE_TOP_GUARD_SIZE];
} SpriteBase;

// Masked sprite base.
typedef struct _MaskedSpriteBase
{
    UINT8   m_widthInBytes;
    UINT8   m_heightInPixels;
    UINT8   m_topGuard [2 * SPRITE_TOP_GUARD_SIZE];
} MaskedSpriteBase;

// Masked sprite M1F1_64.
typedef struct _MaskedSpriteM1F1_64
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphData [1 * 64];
} MaskedSpriteM1F1_64;

// Masked sprite M2F1_64.
typedef struct _MaskedSpriteM2F1_64
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphData1 [1 * 64];  // Right or down.
    UINT8   m_glyphData2 [1 * 64];  // Left or up.
} MaskedSpriteM2F1_64;

// Masked sprite M1F1_96.
typedef struct _MaskedSpriteM1F1_96
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphData [1 * 96];
} MaskedSpriteM1F1_96;

// Masked sprite M2F1_96.
typedef struct _MaskedSpriteM2F1_96
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphData1 [1 * 96];  // Right or down.
    UINT8   m_glyphData2 [1 * 96];  // Left or up.
} MaskedSpriteM2F1_96;

// Masked sprite M1F2_96.
typedef struct _MaskedSpriteM1F2_96
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphData [2 * 96];
} MaskedSpriteM1F2_96;

// Masked sprite M2F2_96.
typedef struct _MaskedSpriteM2F2_96
{
    MaskedSpriteBase    m_maskedSpriteBase;
    UINT8   m_glyphData1 [2 * 96];  // Right or down.
    UINT8   m_glyphData2 [2 * 96];  // Left or up.
} MaskedSpriteM2F2_96;

#endif

/******************************* End of File *******************************/
