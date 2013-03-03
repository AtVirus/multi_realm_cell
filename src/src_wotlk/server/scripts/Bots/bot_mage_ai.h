/*
* Copyright (C) Likan Mod 2012-2013 <https://github.com/ChaosDevLikan/>
* Copyright (C) 3server 2005-2013 <https://cata.3server>
 *
 * World of Warcraft: Cataclysm 
 * You can edit but you can not delete this copyright.
 * 3server Emulator - 3server Database 
 *
 *
 * By Likan Developer Core C++, SQL (FUN, WoTLK, Cata Realm) of 3server Server
 */

#include "bot_ai.h"


uint32 FireBlast_cd;
uint32 BlastWave_cd;
uint32 CounterSpell_cd;
uint32 FrostNova_cd;
uint32 PoM_cd;
uint32 Ward_cd;
uint32 Blizzard_cd;
uint32 DragonBreath_cd;
uint32 Blink_cd;
uint32 Combustion_cd;
uint32 Scorch_cd;
uint32 Potion_cd;
uint32 Evocation_cd;
uint32 Living_Bomb_cd;
uint32 FirstAid_cd;
uint32 GC_Timer;
uint32 blink_timer;
//uint32 wait_timer;

bool CastedDampenMagic;
bool CastedArcaneIntellect;
bool CastedArmor1;
//bool wait;
bool blink;

//arcane spells cooldown
#define ARCANETORRENT_CD 120
#define EVOCATION_CD 4800
#define COUNTERSPELL_CD 240
#define POM_CD 1200
#define BLINK_CD 1500

//fire spells cooldown
#define BLASTWAVE_CD 350
#define DRAGONBREATH_CD 450
#define WARD_CD 300
#define FIREBLAST_CD 650 //8000 if not fire mage
#define COMBUSTION_CD 1800
#define SCORCH_CD 900
#define LIVING_BOMB_CD 600

//frost spells cooldown
#define FROSTNOVA_CD 250
#define CONEOFCOLD_CD 100
#define ICEBLOCK_CD 3000
#define BLIZZARD_CD 300

//arcane spells
#define DAMPENMAGIC     SPELL_DAMPENMAGIC_A[SPELL_LEVEL]
#define MANASHIELD      SPELL_MANASHIELD_A[SPELL_LEVEL]
#define MAGEARMOR       SPELL_MAGEARMOR_A[SPELL_LEVEL]
#define SPELLSTEAL      SPELL_SPELLSTEAL_A[SPELL_LEVEL]
#define ARCANEMISSILES  SPELL_ARCANEMISSILES_A[SPELL_LEVEL]
#define ARCANEINTELLECT SPELL_ARCANEINTELLECT_A[SPELL_LEVEL]
#define ARCANEEXPLOSION SPELL_ARCANEEXPLOSION_A[SPELL_LEVEL]
#define POLYMORPH       SPELL_POLYMORPH_A[SPELL_LEVEL]
#define COUNTERSPELL    2139
#define EVOCATION       12051
#define POM             12043
#define REMCURSE        15729
#define BLINK           38932
#define ARCANETORRENT   28730



//fire spells
#define FIREBALL        SPELL_FIREBALL_A[SPELL_LEVEL]
#define BLASTWAVE       SPELL_BLASTWAVE_A[SPELL_LEVEL]
#define DRAGONBREATH    SPELL_DRAGONBREATH_A[SPELL_LEVEL]
#define FIREBLAST       SPELL_FIREBLAST_A[SPELL_LEVEL]
#define FIREWARD        SPELL_FIREWARD_A[SPELL_LEVEL]
#define PYROBLAST       SPELL_PYROBLAST_A[SPELL_LEVEL]
#define COMBUSTION      SPELL_COMBUSTION_A[SPELL_LEVEL]
#define SCORCH          SPELL_SCORCH_A[SPELL_LEVEL]
#define MOLTENARMOR     30482
#define LIVINGBOMB      SPELL_LIVING_BOMB_A[SPELL_LEVEL]

//frost spells
#define FROSTNOVA       SPELL_FROSTNOVA_A[SPELL_LEVEL]
#define FROSTWARD       SPELL_FROSTWARD_A[SPELL_LEVEL]
#define CONEOFCOLD      SPELL_CONEOFCOLD_A[SPELL_LEVEL]
#define ICEARMOR        SPELL_ICEARMOR_A[SPELL_LEVEL]
#define ICEBLOCK        45438
#define BLIZZARD        SPELL_BLIZZARD_A[SPELL_LEVEL]


//others
#define BONUS_DAMAGE 986 //Spell Bonus
#define BANDAGE 27031
#define MANAPOTION 28499
#define REJUVEPOTION 28517
#define HEALINGPOTION 28495

//arcane spells
uint32 SPELL_DAMPENMAGIC_A[] = { 0, 8450, 8451, 10173, 10173, 10174, 33944, 43015, 43015 };
uint32 SPELL_MANASHIELD_A[] = { 0, 0, 1463, 8495, 10191, 10192, 27131, 43019, 43020 };
uint32 SPELL_MAGEARMOR_A[] = { 0, 0, 0, 6117, 22782, 22783, 27125, 43023, 43024 };
uint32 SPELL_SPELLSTEAL_A[] = { 0, 0, 0, 0, 0, 0, 0, 30449, 30449 };
uint32 SPELL_ARCANEMISSILES_A[] = {5143, 5144, 5145, 8416, 8417, 10212, 27075, 42843, 42846 };
uint32 SPELL_ARCANEINTELLECT_A[] = { 1459, 1460, 1461, 1461, 10156, 10157, 10157, 27126, 42995};
uint32 SPELL_ARCANEEXPLOSION_A[] = { 0, 1449, 8437, 8439, 10201, 10202, 27080, 42990, 42921 };
uint32 SPELL_POLYMORPH_A[] = { 0, 0, 12824, 12824, 12825, 12825, 28271, 28272, 61721 };

//fire spells
uint32 SPELL_FIREBALL_A[] = { 143, 145, 8400, 8401, 10148, 25306, 38692, 42834, 42834 };
uint32 SPELL_BLASTWAVE_A[] = { 0, 0, 0, 11113, 13019, 13020, 13021, 42944, 42945 };
uint32 SPELL_DRAGONBREATH_A[] = { 0, 0, 0, 0, 0, 31661, 31661, 31661, 31661 };
uint32 SPELL_FIREBLAST_A[] = {2136, 2137, 2138, 8412, 10197, 10199, 10199, 10199, 10199 };
uint32 SPELL_FIREWARD_A[] = { 0, 0, 543, 8457, 8458, 10223, 10225, 27128, 43010 };
uint32 SPELL_COMBUSTION_A[] = { 0, 0, 0, 0, 11129, 11129, 11129, 11129, 11129 };
uint32 SPELL_PYROBLAST_A[] = { 0, 0, 11366, 12522, 12525, 12526, 27132, 42890, 42891 };
uint32 SPELL_SCORCH_A[] = { 0, 0, 2948, 8445, 10205, 10207, 27073, 27074, 42859 };
uint32 SPELL_LIVING_BOMB_A[] = { 0, 0, 0, 0, 0, 44457, 44457, 44457, 44457 };

//frost spells
uint32 SPELL_FROSTNOVA_A[] = {0, 122, 865, 6131, 10230, 27088, 42917, 42917, 42917 };
uint32 SPELL_FROSTWARD_A[] = { 0, 0, 6143, 8461, 8462, 10177, 28609, 32796, 43012 };
uint32 SPELL_CONEOFCOLD_A[] = { 0, 0, 120, 8492, 10159, 10161, 27087, 42930, 42931 };
uint32 SPELL_ICEARMOR_A[] = {0, 0, 0, 7302, 7320, 10219, 10220, 27124, 43008  };
uint32 SPELL_BLIZZARD_A[] = { 0, 0, 10, 8427, 10185, 10186, 10187, 27085, 42940 };



