/*
 * Copyright (C) Likan Mod 2012-2013 <https://github.com/ChaosDevLikan/>
 * Copyright (C) 3server 2005-2013 <https://cata.3server>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __BATTLEGROUNDIC_H
#define __BATTLEGROUNDIC_H

#include "Battleground.h"

enum eBGICtext
{
    LANG_BG_IC_NODE_ASSAULTED = 12025,
    LANG_BG_IC_NODE_DEFENDED = 12024,
    LANG_BG_IC_NODE_CLAIMED = 12023,
    LANG_BG_IC_NODE_TAKEN = 12020
};

class Battleground;

//enum Buffs
class Transport;

#define BG_IC_NotICBGWeekendHonorTicks      330
#define BG_IC_ICBGWeekendHonorTicks         200
#define BG_IC_TickIntervals                    1000
#define SEND_MSG_NEAR_LOSE                    120
const uint32 BG_IC_TickPoints[2]            = {300, 600} ;

//##########################################
//#Structure utilis? pour stock? les donn?e#
//##########################################
//Structure pour les game object pop au d?marage
struct ICObject{
    uint8 id;        //Id de l'objet dans le BG
    float x;        //Position x,y,z,et orientation
    float y;
    float z;
    float o;
    uint32 entry;    //Id du gameobject
    uint16 state;    //Etat (pour les flag) eBannerState
    bool usable;    //Utilisable au d?but
    uint16 faction; //Faction
    uint8 type;        //Type de gob dans IC  eICObjectType
    uint8 nodeid;    //node id ou porte id
};
struct ICNode{
    uint8 previous;    //Etat pr?c?dant du node (voir eBannerState)
    uint8 current;    //Etat actuel du node (voir eBannerState)
    uint32 timeleft;//Temps restant en ms
    uint32 object_aura;
    uint32 object_flag;
    uint32 worldstate[5];
    uint32 gobentry[5];
};
struct ICDoor{
    uint32 object_build;
    uint32 object_door;
    uint32 state;
    uint32 worldstate[2];
};
struct ICNpc{
    uint8 id;        //Id du npc par rapport au bg
    float x;        //Position x,y,z,et orientation
    float y;
    float z;
    float o;
    uint32 entry;
    uint32 faction;
    uint32 type;
    uint32 respawn;
};
//##################################
//Enum?ration des constante de base
//##################################

enum eIC_Timers
{
    //SPELL_OIL_REFINERY        = 68719,
    //QUARRY            = 68720
    BG_IC_FLAG_CAPTURING_TIME = 60000,
    BG_IC_TIMER_OPEN_DOOR = 30000,
};
enum eIC_Faction
{
    FACTION_ALLIANCE,
    FACTION_HORDE,
    FACTION_NONE         = 35,
    FACTION_NPC_HORDE     = 65,
    FACTION_NPC_ALLIANCE = 80,
    FACTION_GOB_NEUTRAL  = 35,
    FACTION_GOB_HORDE     = 1995,
    FACTION_GOB_ALLIANCE = 1997,
    FACTION_DOOR_HORDE     = 1735,
    FACTION_DOOR_ALLIANCE = 1732,
};
//Voir si utile
enum eIC_BannerElement
{
    BANNER_POLE,
    BANNER_FLAG,
    BANNER_AURA,
};

//######################
//#Enum?ration des node#
//######################
enum eIC_BattlegroundNodes
{
    BG_IC_NODE_DOCK                  = 0,
    BG_IC_NODE_HANGAR              = 1,
    BG_IC_NODE_QUARRY             = 2,    // No Grave
    BG_IC_NODE_REFINERY              = 3,    // No Grave
    BG_IC_NODE_WORKSHOP              = 4,
    BG_IC_BANNER_NODES_COUNT      = 5,
    BG_IC_ALLIANCE_KEEP              = 5,
    BG_IC_HORDE_KEEP              = 6,
    BG_IC_DYNAMIC_NODES_COUNT      = 7,    // dynamic nodes that can be captured

    BG_IC_LAST_RESORT_GV_ALLIANCE = 7,
    BG_IC_LAST_RESORT_GV_HORDE      = 8,

    BG_IC_ALL_NODES_COUNT         = 9,    // all nodes (dynamic and static)
};

//enum BG_IC_Objectives
enum eIC_BannerState
{
    //IC_OBJECTIVE_ASSAULT_BASE   = 245,
    //IC_OBJECTIVE_DEFEND_BASE    = 246
    STATE_NEUTRAL,
    STATE_BANNER_CONT_A,
    STATE_BANNER_CONT_H,
    STATE_BANNER_ALLY,
    STATE_BANNER_HORDE,
};
const ICNode IC_InitNodeData[7]=
{
    {0,0,0,0,0,{4301,4305,4302,4304,4303},{195157,195154,195156,195153,195155}}, //Dock
    {0,0,0,0,0,{4296,4300,4297,4299,4298},{195158,195144,195145,195132,195130}}, //Hangar
    {0,0,0,0,0,{4306,4310,4307,4309,4308},{195338,195335,195337,195334,195336}}, //Quary
    {0,0,0,0,0,{4311,4315,4312,4314,4313},{195343,195340,195342,195339,195341}}, //Refinery
    {0,0,0,0,0,{4294,4229,4293,4228,4230},{195133,195150,195152,195149,195151}}, //Workshop
    {0,0,0,0,0,{4341,4342,4343,4339,4340},{0,195397,195399,195396,195398}}, //Alliance keep
    {0,0,0,0,0,{4346,4347,4348,4344,4345},{0,195392,195394,195391,195393}}  //horde keep
};

// WorldSafeLocs ids for 5 nodes, and for ally, and horde starting location, 2 and 3 stay at 0
const uint32 BG_IC_GraveyardIds[BG_IC_ALL_NODES_COUNT] = {1480, 1481, 0, 0, 1482, 1486, 1485, 1483, 1484};
const uint32 BG_IC_graveInitTeam[BG_IC_ALL_NODES_COUNT] = {0,0,0,0,0,ALLIANCE,HORDE,ALLIANCE,HORDE};
// x, y, z, o
const float BG_IC_SpiritGuidePos[BG_IC_ALL_NODES_COUNT][4] = {
    {629.57f, -279.83f, 11.33f, 0.0f},                   // dock
    {780.729f, -1103.08f, 135.51f, 2.27f},                    // hangar
    {0.0f, 0.0f, 0.0f, 0.0f},                     // no grave
    {0.0f, 0.0f, 0.0f, 0.0f},                     // no grave
    {775.74f, -652.77f, 9.31f, 4.27f},                    // workshop
    {278.42f, -883.20f, 49.89f, 1.53f},                   // alliance starting base
    {1300.91f, -834.04f, 48.91f, 1.69f},                      // horde starting base
    {438.86f, -310.04f, 51.81f, 5.87f},                    // last resort alliance
    {1148.65f, -1250.98f, 16.60f, 1.74f},                    // last resort horde
};

//#######################
//#Enum?ration des porte#
//#######################
enum eIC_DoorList
{
    BG_IC_H_FRONT,
    BG_IC_H_WEST,
    BG_IC_H_EAST,
    BG_IC_A_FRONT,
    BG_IC_A_WEST,
    BG_IC_A_EAST,
    BG_IC_MAXDOOR,
};
enum BG_IC_GateState
{
    BG_IC_GATE_OK,
    BG_IC_GATE_DAMAGED,
    BG_IC_GATE_DESTROYED,
};
const ICDoor IC_InitDoorData[6]=
{
    {0,0,BG_IC_GATE_OK,{4322,4317}},
    {0,0,BG_IC_GATE_OK,{4321,4318}},
    {0,0,BG_IC_GATE_OK,{4320,4319}},
    {0,0,BG_IC_GATE_OK,{4323,4328}},
    {0,0,BG_IC_GATE_OK,{4324,4327}},
    {0,0,BG_IC_GATE_OK,{4325,4326}},
};
//############################
//#Enum?ration des worldstate#
//############################
enum eIC_WorldStates
{
    BG_IC_ALLIANCE_RENFORT_SET    = 4221,
    BG_IC_HORDE_RENFORT_SET        = 4222,
    BG_IC_ALLIANCE_RENFORT        = 4226,
    BG_IC_HORDE_RENFORT            = 4227,
    BG_IC_GATE_FRONT_H_WS_CLOSED= 4317,
    BG_IC_GATE_WEST_H_WS_CLOSED = 4318,
    BG_IC_GATE_EAST_H_WS_CLOSED = 4319,
    BG_IC_GATE_FRONT_A_WS_CLOSED= 4328,
    BG_IC_GATE_WEST_A_WS_CLOSED = 4327,
    BG_IC_GATE_EAST_A_WS_CLOSED = 4326,
    BG_IC_GATE_FRONT_H_WS_OPEN  = 4322,
    BG_IC_GATE_WEST_H_WS_OPEN   = 4321,
    BG_IC_GATE_EAST_H_WS_OPEN   = 4320,
    BG_IC_GATE_FRONT_A_WS_OPEN  = 4323,
    BG_IC_GATE_WEST_A_WS_OPEN   = 4324,
    BG_IC_GATE_EAST_A_WS_OPEN   = 4325,
};

//############################
//#Enum?ration des gameobject#
//############################
//Enum?ration des diff?rent gob utilis? (entry, de gameobject_template)
enum eIC_ObjectEntry
{
    BG_IC_OBJECTID_AURA_A               = 180100,
    BG_IC_OBJECTID_AURA_H               = 180101,
    BG_IC_OBJECTID_AURA_C               = 180102,

    BG_IC_OBJECTID_LAST_DOOR_H            = 195223,
    BG_IC_OBJECTID_LAST_DOOR_A            = 195451,

    BG_IC_OBJECTID_GATE_FRONT_H            = 195494,
    BG_IC_OBJECTID_GATE_WEST_H            = 195495,
    BG_IC_OBJECTID_GATE_EAST_H            = 195496,
    BG_IC_OBJECTID_GATE_FRONT_A            = 195698,
    BG_IC_OBJECTID_GATE_WEST_A            = 195699,
    BG_IC_OBJECTID_GATE_EAST_A            = 195700,

    BG_IC_OBJECTID_GATE_A                = 195703,
    BG_IC_OBJECTID_GATE_H                = 195491,

    BG_IC_OBJECTID_AURA_TELEPORTER_A    = 195701,
    BG_IC_OBJECTID_AURA_TELEPORTER_H    = 195702,
    BG_IC_OBJECTID_TELEPORTER_IN_OUT_H    = 195314,
    BG_IC_OBJECTID_TELEPORTER_OUT_IN_H    = 195313,
    BG_IC_OBJECTID_TELEPORTER_IN_OUT_A    = 195316,
    BG_IC_OBJECTID_TELEPORTER_OUT_IN_A    = 195315,
    BG_IC_OBJECTID_FLAGPOLE                = 195439,

    BG_IC_HORDE_GUNSHIP_PORTAL            = 195326,
    BG_IC_ALLIANCE_GUNSHIP_PORTAL        = 195320,

    BG_IC_OBJECTID_BONFIRE                = 195377,

    BG_IC_OBJECTID_SEAFORIUM            = 195332,

    BG_IC_HORDE_GUNSHIP                    = 195276,
    BG_IC_ALLIANCE_GUNSHIP                = 195121,

    BG_IC_OBJECTID_LITTLE_BOMB            = 195232,

    BG_IC_OBJECTID_TOWER_HORDE            = 195437,
    BG_IC_OBJECTID_TOWER_ALLY            = 195436,

};

enum eIC_ObjectList{
    BG_IC_OBJECT_DOCK    =0,
    BG_IC_OBJECT_HANGAR    =3,
    BG_IC_OBJECT_QUARRY =6,
    BG_IC_OBJECT_REFINERY =9,
    BG_IC_OBJECT_WORKSHOP =12,
    BG_IC_OBJECT_HORDE = 15,
    BG_IC_OBJECT_ALLIANCE = 18,
    BG_IC_OBJECT_DOOR_H_FRONT = 21,
    BG_IC_OBJECT_DOOR_H_WEST = 23,
    BG_IC_OBJECT_DOOR_H_EAST = 25,
    BG_IC_OBJECT_DOOR_A_FRONT = 27,
    BG_IC_OBJECT_DOOR_A_WEST = 29,
    BG_IC_OBJECT_DOOR_A_EAST = 31,
    BG_IC_OBJECT_TELEPORT_H_FRONT_IN  = 33,
    BG_IC_OBJECT_TELEPORT_H_EAST_IN   = 35,
    BG_IC_OBJECT_TELEPORT_H_WEST_IN      = 37,
    BG_IC_OBJECT_TELEPORT_H_FRONT_OUT = 39,
    BG_IC_OBJECT_TELEPORT_H_EAST_OUT  = 41,
    BG_IC_OBJECT_TELEPORT_H_WEST_OUT  = 43,
    BG_IC_OBJECT_TELEPORT_A_FRONT_IN  = 45,
    BG_IC_OBJECT_TELEPORT_A_EAST_IN   = 47,
    BG_IC_OBJECT_TELEPORT_A_WEST_IN   = 49,
    BG_IC_OBJECT_TELEPORT_A_FRONT_OUT = 51,
    BG_IC_OBJECT_TELEPORT_A_EAST_OUT  = 53,
    BG_IC_OBJECT_TELEPORT_A_WEST_OUT  = 55,
    BG_IC_OBJECT_BONFIRE_1    =57,
    BG_IC_OBJECT_BONFIRE_2,
    BG_IC_OBJECT_BONFIRE_3,
    BG_IC_OBJECT_BONFIRE_4,
    BG_IC_OBJECT_BONFIRE_5,
    BG_IC_OBJECT_BONFIRE_6,
    BG_IC_OBJECT_BOMB_1,
    BG_IC_OBJECT_BOMB_2,
    BG_IC_OBJECT_BOMB_3,
    BG_IC_OBJECT_BOMB_4,
    BG_IC_OBJECT_BOMB_5,
    BG_IC_OBJECT_BOMB_6,
    BG_IC_OBJECT_BOMB_7,
    BG_IC_OBJECT_BOMB_8,
    BG_IC_OBJECT_BOMB_L_1,
    BG_IC_OBJECT_BOMB_L_2,
    BG_IC_TOWER_DOOR_1,
    BG_IC_TOWER_DOOR_2,
    BG_IC_TOWER_DOOR_3,
    BG_IC_TOWER_DOOR_4,
    BG_IC_GUNSHIP_TP_1,
    BG_IC_GUNSHIP_TP_2,
    BG_IC_GUNSHIP_TP_3,
    BG_IC_LAST_DOOR_H,
    BG_IC_LAST_DOOR_A_1,
    BG_IC_LAST_DOOR_A_2,
    BG_IC_MAX_OBJECT,
};
enum eIC_ObjectType{
    IC_TYPE_FLAG,
    IC_TYPE_DOOR_H,
    IC_TYPE_DOOR_A,
    IC_TYPE_TELEPORT_H,
    IC_TYPE_TELEPORT_A,
    IC_TYPE_BOMB,
    IC_TYPE_DECORATION,
    IC_TYPE_TOWER_DOOR,
    IC_TYPE_GUNSHIPTELEPORTER,
    IC_TYPE_LAST_DOOR_H,
    IC_TYPE_LAST_DOOR_A,
};

#define MAX_BG_IC_OBJ 51
const ICObject BG_IC_OBJ[MAX_BG_IC_OBJ]=
{
    {BG_IC_OBJECT_DOCK,        725.3065f, -362.270538f, 17.8154f, 0.0f            ,BG_IC_OBJECTID_FLAGPOLE,STATE_NEUTRAL,true,FACTION_GOB_NEUTRAL,IC_TYPE_FLAG,BG_IC_NODE_DOCK},         // dock
    {BG_IC_OBJECT_HANGAR,    808.452f, -999.6443f, 132.381f, 0.0f            ,BG_IC_OBJECTID_FLAGPOLE,STATE_NEUTRAL,true,FACTION_GOB_NEUTRAL,IC_TYPE_FLAG,BG_IC_NODE_HANGAR},         // hangar
    {BG_IC_OBJECT_QUARRY,    225.70f, -1188.39f, 8.03f, 5.58f                ,BG_IC_OBJECTID_FLAGPOLE,STATE_NEUTRAL,true,FACTION_GOB_NEUTRAL,IC_TYPE_FLAG,BG_IC_NODE_QUARRY},         // quarry
    {BG_IC_OBJECT_REFINERY,    1269.744f, -400.933594f, 37.6342f, 0.0f            ,BG_IC_OBJECTID_FLAGPOLE,STATE_NEUTRAL,true,FACTION_GOB_NEUTRAL,IC_TYPE_FLAG,BG_IC_NODE_REFINERY},          // refinery
    {BG_IC_OBJECT_WORKSHOP,    769.27f, -833.53f, 9.57f, 0.0f                    ,BG_IC_OBJECTID_FLAGPOLE,STATE_NEUTRAL,true,FACTION_GOB_NEUTRAL,IC_TYPE_FLAG,BG_IC_NODE_WORKSHOP},          // workshop
    {BG_IC_OBJECT_HORDE,    1284.151f, -704.8736f, 48.917f, 0.0f            ,BG_IC_OBJECTID_FLAGPOLE,STATE_BANNER_HORDE,false,FACTION_GOB_ALLIANCE,IC_TYPE_FLAG,BG_IC_ALLIANCE_KEEP},
    {BG_IC_OBJECT_ALLIANCE,    298.80f, -784.221f, 48.916f, 0.0f                ,BG_IC_OBJECTID_FLAGPOLE,STATE_BANNER_ALLY,false,FACTION_GOB_HORDE,IC_TYPE_FLAG,BG_IC_HORDE_KEEP},

    {BG_IC_OBJECT_DOOR_H_FRONT, 1150.90283f, -762.6059f, 47.50768f, 3.14159274f    ,BG_IC_OBJECTID_GATE_FRONT_H,STATE_NEUTRAL,false,FACTION_DOOR_HORDE,IC_TYPE_DOOR_H,BG_IC_H_FRONT},
    {BG_IC_OBJECT_DOOR_H_WEST, 1217.89929f, -676.947937f, 47.6340752f, 1.57079577f,BG_IC_OBJECTID_GATE_WEST_H,STATE_NEUTRAL,false,FACTION_DOOR_HORDE,IC_TYPE_DOOR_H,BG_IC_H_WEST},
    {BG_IC_OBJECT_DOOR_H_EAST, 1218.743f, -851.154541f, 48.2532845f, -1.57079577f,BG_IC_OBJECTID_GATE_EAST_H,STATE_NEUTRAL,false,FACTION_DOOR_HORDE,IC_TYPE_DOOR_H,BG_IC_H_EAST},
    {BG_IC_OBJECT_DOOR_A_FRONT, 413.479156f, -833.949646f, 48.5237579f, 3.14159274f    ,BG_IC_OBJECTID_GATE_FRONT_A,STATE_NEUTRAL,false,FACTION_DOOR_ALLIANCE,IC_TYPE_DOOR_A,BG_IC_A_FRONT},
    {BG_IC_OBJECT_DOOR_A_WEST, 351.6146f, -762.75, 48.91625f, -1.57079577f        ,BG_IC_OBJECTID_GATE_WEST_A,STATE_NEUTRAL,false,FACTION_DOOR_ALLIANCE,IC_TYPE_DOOR_A,BG_IC_A_WEST},
    {BG_IC_OBJECT_DOOR_A_EAST, 351.024323f, -903.3264f, 48.9247169f, 1.57079577f,BG_IC_OBJECTID_GATE_EAST_A,STATE_NEUTRAL,false,FACTION_DOOR_ALLIANCE,IC_TYPE_DOOR_A,BG_IC_A_EAST},
    {BG_IC_OBJECT_TELEPORT_H_FRONT_IN,1143.25f, -779.598f, 48.628f, 1.640f        ,BG_IC_OBJECTID_TELEPORTER_IN_OUT_H,STATE_NEUTRAL,false,FACTION_GOB_HORDE,IC_TYPE_TELEPORT_H,0},
    {BG_IC_OBJECT_TELEPORT_H_EAST_IN,1235.08f, -857.8f, 48.916f, 3.071f            ,BG_IC_OBJECTID_TELEPORTER_IN_OUT_H,STATE_NEUTRAL,false,FACTION_GOB_HORDE,IC_TYPE_TELEPORT_H,0},
    {BG_IC_OBJECT_TELEPORT_H_WEST_IN, 1236.531f, -669.41f, 48.272f, 0.1047f        ,BG_IC_OBJECTID_TELEPORTER_IN_OUT_H,STATE_NEUTRAL,false,FACTION_GOB_HORDE,IC_TYPE_TELEPORT_H,0},
    {BG_IC_OBJECT_TELEPORT_H_FRONT_OUT,1158.76f, -746.182f, 48.627f, -1.518f    ,BG_IC_OBJECTID_TELEPORTER_OUT_IN_H,STATE_NEUTRAL,false,FACTION_GOB_HORDE,IC_TYPE_TELEPORT_H,0},
    {BG_IC_OBJECT_TELEPORT_H_EAST_OUT, 1233.27f, -844.526f, 48.882f, -0.017f    ,BG_IC_OBJECTID_TELEPORTER_OUT_IN_H,STATE_NEUTRAL,false,FACTION_GOB_HORDE,IC_TYPE_TELEPORT_H,0},
    {BG_IC_OBJECT_TELEPORT_H_WEST_OUT, 1235.52f, -683.871f, 49.3039f, -3.089f    ,BG_IC_OBJECTID_TELEPORTER_OUT_IN_H,STATE_NEUTRAL,false,FACTION_GOB_HORDE,IC_TYPE_TELEPORT_H,0},
    {BG_IC_OBJECT_TELEPORT_A_FRONT_IN, 397.088f, -859.381f, 48.899f, 1.640f        ,BG_IC_OBJECTID_TELEPORTER_IN_OUT_A,STATE_NEUTRAL,false,FACTION_GOB_ALLIANCE,IC_TYPE_TELEPORT_A,0},
    {BG_IC_OBJECT_TELEPORT_A_EAST_IN, 323.539f, -888.361f, 48.919f, 0.034f        ,BG_IC_OBJECTID_TELEPORTER_IN_OUT_A,STATE_NEUTRAL,false,FACTION_GOB_ALLIANCE,IC_TYPE_TELEPORT_A,0},
    {BG_IC_OBJECT_TELEPORT_A_WEST_IN, 326.284f, -777.366f, 49.0208f, 3.124f        ,BG_IC_OBJECTID_TELEPORTER_IN_OUT_A,STATE_NEUTRAL,false,FACTION_GOB_ALLIANCE,IC_TYPE_TELEPORT_A,0},
    {BG_IC_OBJECT_TELEPORT_A_FRONT_OUT,425.675f, -857.090f, 48.510f,-1.605f        ,BG_IC_OBJECTID_TELEPORTER_OUT_IN_A,STATE_NEUTRAL,false,FACTION_GOB_ALLIANCE,IC_TYPE_TELEPORT_A,0},
    {BG_IC_OBJECT_TELEPORT_A_EAST_OUT, 311.920f, -913.972f, 48.815f, 3.089f        ,BG_IC_OBJECTID_TELEPORTER_OUT_IN_A,STATE_NEUTRAL,false,FACTION_GOB_ALLIANCE,IC_TYPE_TELEPORT_A,0},
    {BG_IC_OBJECT_TELEPORT_A_WEST_OUT, 324.635f, -749.128f, 49.360f, 0.017f        ,BG_IC_OBJECTID_TELEPORTER_OUT_IN_A,STATE_NEUTRAL,false,FACTION_GOB_ALLIANCE,IC_TYPE_TELEPORT_A,0},
    {BG_IC_OBJECT_BONFIRE_1,1281.06f,-732.978f,87.7611f,4.63149f                ,BG_IC_OBJECTID_BONFIRE,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_DECORATION,0},
    {BG_IC_OBJECT_BONFIRE_2,1281.26f,-800.212f,87.6619f,4.9535f                    ,BG_IC_OBJECTID_BONFIRE,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_DECORATION,0},
    {BG_IC_OBJECT_BONFIRE_3,1358.13f,-798.515f,87.7575f,1.96114f                ,BG_IC_OBJECTID_BONFIRE,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_DECORATION,0},
    {BG_IC_OBJECT_BONFIRE_4,1358.01f,-731.696f,87.7261f,3.43297f                ,BG_IC_OBJECTID_BONFIRE,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_DECORATION,0},
    {BG_IC_OBJECT_BONFIRE_5,1161.225f, -790.863f, 48.947f,3.43297f            ,BG_IC_OBJECTID_BONFIRE,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_DECORATION,0},
    {BG_IC_OBJECT_BONFIRE_6,1161.225f, -736.131f, 48.844f,3.43297f            ,BG_IC_OBJECTID_BONFIRE,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_DECORATION,0},
    {BG_IC_OBJECT_BOMB_1,1268.30908f, -745.783f, 48.9187775f, 0.785396755f        ,BG_IC_OBJECTID_SEAFORIUM,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_2,1268.50867f, -738.1215f, 48.9175f, -1.04719758f        ,BG_IC_OBJECTID_SEAFORIUM,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_3,1273.066f, -786.572937f, 48.9419174f, -0.94247663f        ,BG_IC_OBJECTID_SEAFORIUM,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_4,1273.849f, -796.2778f, 48.9364281f, -2.75761318f        ,BG_IC_OBJECTID_SEAFORIUM,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_5,297.3212f, -851.321167f, 48.91627f, -0.94247663f        ,BG_IC_OBJECTID_SEAFORIUM,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_6,298.104156f, -861.026062f, 48.916275f, -2.75761318f    ,BG_IC_OBJECTID_SEAFORIUM,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_7,300.371521f, -818.732666f, 48.91625f, 0.785396755f        ,BG_IC_OBJECTID_SEAFORIUM,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_8,302.1354f, -810.7083f, 48.91625f, -1.04719758f            ,BG_IC_OBJECTID_SEAFORIUM,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_L_1,749.250f,-862.724f, 13.357f,1.57865f                ,BG_IC_OBJECTID_LITTLE_BOMB,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_OBJECT_BOMB_L_2,786.712f,-862.724f, 13.1756f,1.57865f                ,BG_IC_OBJECTID_LITTLE_BOMB,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_BOMB,0},
    {BG_IC_TOWER_DOOR_1,1156.88586f, -843.9983f, 48.63224f, 0.732934f            ,BG_IC_OBJECTID_TOWER_HORDE,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_TOWER_DOOR,0},
    {BG_IC_TOWER_DOOR_2,1157.04712f, -682.3604f, 48.6322479f, -0.829132438f        ,BG_IC_OBJECTID_TOWER_HORDE,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_TOWER_DOOR,0},
    {BG_IC_TOWER_DOOR_3,399.801941f, -885.2075f, 50.1938553f, 2.51599526f        ,BG_IC_OBJECTID_TOWER_ALLY,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_TOWER_DOOR,0},
    {BG_IC_TOWER_DOOR_4,401.024048f, -780.723755f, 49.94822f, -2.52896214f        ,BG_IC_OBJECTID_TOWER_ALLY,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_TOWER_DOOR,0},
    {BG_IC_GUNSHIP_TP_1,828.056f, -993.916f, 134.132f, 5.628f                ,0    ,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_GUNSHIPTELEPORTER,0},
    {BG_IC_GUNSHIP_TP_2,738.460f, -1106.996f, 134.7189f, 5.628f                ,0    ,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_GUNSHIPTELEPORTER,0},
    {BG_IC_GUNSHIP_TP_3,672.152f, -1157.334f, 133.704f, 5.628f                ,0    ,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_GUNSHIPTELEPORTER,0},
    {BG_IC_LAST_DOOR_H,1283.181f, -765.937f, 51.042f, 0                        ,BG_IC_OBJECTID_LAST_DOOR_H,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_LAST_DOOR_H,0},
    {BG_IC_LAST_DOOR_A_1,288.084f,-832.6593f, 51.466f,  0                    ,BG_IC_OBJECTID_LAST_DOOR_A,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_LAST_DOOR_A,0},
    {BG_IC_LAST_DOOR_A_2,273.1746f, -832.2653f, 51.4671f, 0                    ,BG_IC_OBJECTID_LAST_DOOR_A,STATE_NEUTRAL,false,FACTION_GOB_NEUTRAL,IC_TYPE_LAST_DOOR_A,0},
};

//######################
//#Enum?ration des sons#
//######################
enum BG_IC_Sounds //TODO:Trouver les bon son
{
    BG_IC_SOUND_NODE_CLAIMED            = 8192,
    BG_IC_SOUND_NODE_CAPTURED_ALLIANCE  = 8173,
    BG_IC_SOUND_NODE_CAPTURED_HORDE     = 8213,
    BG_IC_SOUND_NODE_ASSAULTED_ALLIANCE = 8212,
    BG_IC_SOUND_NODE_ASSAULTED_HORDE    = 8174,
    BG_IC_SOUND_NEAR_VICTORY            = 8456,
};

//#####################
//#Enum?ration des npc#
//#####################
enum BG_IC_CreatureIds
{
    BG_IC_NPCID_SEVENTH_LEGION_DECKHAND                = 36165,//ship A
    BG_IC_NPCID_SEVENTH_LEGION_INFANTRY                = 34919,//alliance keep
    BG_IC_NPCID_SEVENTH_LEGION_MARINE                = 36166,//ship A
    BG_IC_NPCID_ALLIANCE_GUNSHIP_CANNON                = 34929,//ship A
    BG_IC_NPCID_ALLIANCE_GUNSHIP_CAPTAIN            = 34960,//hangar
    BG_IC_NPCID_CATAPULT                            = 34793,
    BG_IC_NPCID_DEMOLISHER                            = 34775,
    BG_IC_NPCID_FLAME_TURRET_H                        = 36356,
    BG_IC_NPCID_FLAME_TURRET_A                        = 34778,
    BG_IC_NPCID_GLAIVE_THROWER_H                    = 35273,
    BG_IC_NPCID_GLAIVE_THROWER_A                    = 34802,
    BG_IC_NPCID_GNOMISH_MECHANIC                    = 35345,//workshop A
    BG_IC_NPCID_GOBLIN_ENGINEERING_CREW                = 36162,//ship H ?
    BG_IC_NPCID_GOBLIN_MECHANIC                        = 35346,//workshop H
    BG_IC_NPCID_HIGH_COMMANDER_HALFORD_WYRMBANE        = 34924,
    BG_IC_NPCID_HORDE_GUNSHIP_CANNON                = 34935,//ship H
    BG_IC_NPCID_HORDE_GUNSHIP_CAPTAIN                = 35003,//ship H
    BG_IC_NPCID_KEEP_CANNON                            = 34944,//alliance & horde keep
    BG_IC_NPCID_KORKRON_GUARD                        = 34918,//horde keep
    BG_IC_NPCID_KORKRON_REAVER                        = 36164,//horde ship
   BG_IC_NPCID_NAVIGATOR_SARACEN                    = 36152,//ship A
    BG_IC_NPCID_NAVIGATOR_TAYLOR                    = 36151,//ship A
    BG_IC_NPCID_OVERLORD_AGMAR                        = 34922,
    BG_IC_NPCID_SIEGE_ENGINE_H                        = 35069,
    BG_IC_NPCID_SIEGE_ENGINE_A                        = 34776,
    BG_IC_NPCID_SIEGE_TURRET_H                        = 36355,
    BG_IC_NPCID_SIEGE_TURRET_A                        = 34777,
};
enum eIC_NpcType{
    IC_TYPE_NONE,
    IC_TYPE_KEEP_GUN,
    IC_TYPE_DEMOLISSER_H,
    IC_TYPE_DEMOLISSER_A,
    IC_TYPE_SIEGE_H,
    IC_TYPE_SIEGE_A,
    IC_TYPE_DOCKVEHICLE_H,
    IC_TYPE_DOCKVEHICLE_A,
};
enum BG_IC_NPCs
{
    //10 premier id reserver pour les npc qui res
    BG_IC_TOWER_A_GUN_1 = 10,
    BG_IC_TOWER_A_GUN_2,
    BG_IC_TOWER_A_GUN_3,
    BG_IC_TOWER_A_GUN_4,
    BG_IC_TOWER_A_GUN_5,
    BG_IC_TOWER_A_GUN_6,
    BG_IC_TOWER_A_GUN_7,
    BG_IC_TOWER_A_GUN_8,
    BG_IC_TOWER_A_GUN_9,
    BG_IC_TOWER_A_GUN_10,
    BG_IC_TOWER_A_GUN_11,
    BG_IC_TOWER_A_GUN_12,
    BG_IC_TOWER_H_GUN_1,
    BG_IC_TOWER_H_GUN_2,
    BG_IC_TOWER_H_GUN_3,
    BG_IC_TOWER_H_GUN_4,
    BG_IC_TOWER_H_GUN_5,
    BG_IC_TOWER_H_GUN_6,
    BG_IC_TOWER_H_GUN_7,
    BG_IC_TOWER_H_GUN_8,
    BG_IC_TOWER_H_GUN_9,
    BG_IC_TOWER_H_GUN_10,
    BG_IC_TOWER_H_GUN_11,
    BG_IC_TOWER_H_GUN_12,
    //Boss horde + 4 add
    BG_IC_NPC_OVERLORD_AGMAR,
    BG_IC_NPC_H_ADD_1,
    BG_IC_NPC_H_ADD_2,
    BG_IC_NPC_H_ADD_3,
    BG_IC_NPC_H_ADD_4,
    //Boss alliance + 4 add
    BG_IC_NPC_HIGH_COMMANDER_HALFORD_WYRMBANE,
    BG_IC_NPC_A_ADD_1,
    BG_IC_NPC_A_ADD_2,
    BG_IC_NPC_A_ADD_3,
    BG_IC_NPC_A_ADD_4,
    //Dock
    BG_IC_CATAPULT_1_H,
    BG_IC_CATAPULT_2_H,
    BG_IC_CATAPULT_3_H,
    BG_IC_CATAPULT_4_H,
    BG_IC_GLAIVE_THROWER_1_H,
    BG_IC_GLAIVE_THROWER_2_H,
    BG_IC_CATAPULT_1_A,
    BG_IC_CATAPULT_2_A,
    BG_IC_CATAPULT_3_A,
    BG_IC_CATAPULT_4_A,
    BG_IC_GLAIVE_THROWER_1_A,
    BG_IC_GLAIVE_THROWER_2_A,
    // Workshop
    BG_IC_DEMOLISHER_H_1,
    BG_IC_DEMOLISHER_H_2,
    BG_IC_DEMOLISHER_H_3,
    BG_IC_DEMOLISHER_H_4,
    BG_IC_DEMOLISHER_A_1,
    BG_IC_DEMOLISHER_A_2,
    BG_IC_DEMOLISHER_A_3,
    BG_IC_DEMOLISHER_A_4,
    BG_IC_SIEGE_ENGINE_H,
    BG_IC_SIEGE_ENGINE_A,
    BG_IC_NPC_MAX,
};
#define MAX_BG_IC_NPC 56

const ICNpc BG_IC_NPC[MAX_BG_IC_NPC]=
{
    {BG_IC_TOWER_A_GUN_1,415.277f,-911.552f,87.9619f,4.64663f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_2,406.047f,-755.747f,87.7159f,1.60951f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_3,416.925f,-754.642f,87.7161f,1.66841f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_4,428.073f,-781.504f,87.7164f,5.87029f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_5,402.085f,-910.381f,87.9619f,4.60793f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_6,424.651f,-880.262f,87.9622f,0.389539f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_7,408.402f,-911.213f,87.9619f,4.58045f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_8,425.612f,-786.81f,87.7164f,5.84336f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_9,426.734f,-885.28f,87.9622f,0.408575f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_10,429.368f,-891.332f,87.9622f,0.413433f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_11,411.235f,-755.277f,87.7156f,1.64348f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_A_GUN_12,430.576f,-776.358f,87.7164f,5.84359f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_ALLIANCE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_1,1135.32f,-841.482f,87.8928f,2.33312f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_2,1143.94f,-833.972f,87.8754f,2.3565f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_3,1138.4f,-836.268f,88.3325f,2.33312f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_4,1166.1f,-858.237f,87.8699f,5.37732f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_5,1157.07f,-865.976f,87.8623f,5.44565f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_6,1159.59f,-660.741f,87.9104f,0.775668f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_7,1166.99f,-668.854f,87.9144f,0.775668f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_8,1162.51f,-863.159f,88.3046f,5.44565f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_9,1164.02f,-664.332f,88.2895f,0.736398f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_10,1141.85f,-691.039f,87.9605f,3.78012f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_11,1135.28f,-682.692f,87.859f,3.78012f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    {BG_IC_TOWER_H_GUN_12,1137.99f,-688.115f,88.3004f,3.85473f    ,BG_IC_NPCID_KEEP_CANNON,FACTION_HORDE,IC_TYPE_KEEP_GUN,RESPAWN_ONE_DAY},
    //Boss horde + 4 add
    {BG_IC_NPC_OVERLORD_AGMAR,1295.29f,-769.952f,69.9586f,0.311803f    ,BG_IC_NPCID_OVERLORD_AGMAR,FACTION_HORDE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    {BG_IC_NPC_H_ADD_1,1296.01f,-773.256f,69.958f,0.292168f            ,BG_IC_NPCID_KORKRON_GUARD,FACTION_HORDE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    {BG_IC_NPC_H_ADD_2,1295.94f,-757.756f,69.9587f,6.02165f            ,BG_IC_NPCID_KORKRON_GUARD,FACTION_HORDE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    {BG_IC_NPC_H_ADD_3,1295.09f,-760.927f,69.9587f,5.94311f            ,BG_IC_NPCID_KORKRON_GUARD,FACTION_HORDE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    {BG_IC_NPC_H_ADD_4,1295.67f,-765.636f,69.9745f,0.048692f        ,BG_IC_NPCID_KORKRON_GUARD,FACTION_HORDE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    //Boss alliance + 4 add
    {BG_IC_NPC_HIGH_COMMANDER_HALFORD_WYRMBANE,224.159f,-831.012f,60.8201f,0.0191563f,BG_IC_NPCID_HIGH_COMMANDER_HALFORD_WYRMBANE,FACTION_ALLIANCE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    {BG_IC_NPC_A_ADD_1,223.969f,-822.958f,60.8151f,0.46337f            ,BG_IC_NPCID_SEVENTH_LEGION_INFANTRY,FACTION_ALLIANCE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    {BG_IC_NPC_A_ADD_2,224.211f,-826.952f,60.8188f,6.25961f            ,BG_IC_NPCID_SEVENTH_LEGION_INFANTRY,FACTION_ALLIANCE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    {BG_IC_NPC_A_ADD_3,223.119f,-838.386f,60.8145f,5.64857f            ,BG_IC_NPCID_SEVENTH_LEGION_INFANTRY,FACTION_ALLIANCE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    {BG_IC_NPC_A_ADD_4,223.889f,-835.102f,60.8201f,6.21642f            ,BG_IC_NPCID_SEVENTH_LEGION_INFANTRY,FACTION_ALLIANCE,IC_TYPE_NONE,RESPAWN_ONE_DAY},
    //Dock
    {BG_IC_CATAPULT_1_H,803.944f, -343.237f, 12.609f,4.71239f        ,BG_IC_NPCID_CATAPULT,FACTION_HORDE,IC_TYPE_DOCKVEHICLE_H,RESPAWN_ONE_DAY},
    {BG_IC_CATAPULT_2_H,797.233f, -343.237f, 12.083f,4.71239f        ,BG_IC_NPCID_CATAPULT,FACTION_HORDE,IC_TYPE_DOCKVEHICLE_H,RESPAWN_ONE_DAY},
    {BG_IC_CATAPULT_3_H,774.005f, -343.237f, 12.115f,4.71239f        ,BG_IC_NPCID_CATAPULT,FACTION_HORDE,IC_TYPE_DOCKVEHICLE_H,RESPAWN_ONE_DAY},
    {BG_IC_CATAPULT_4_H,766.961f, -343.237f, 12.094f,4.71239f        ,BG_IC_NPCID_CATAPULT,FACTION_HORDE,IC_TYPE_DOCKVEHICLE_H,RESPAWN_ONE_DAY},
    {BG_IC_GLAIVE_THROWER_1_H,788.516f,-343.237f,12.598f,4.71239f    ,BG_IC_NPCID_GLAIVE_THROWER_H,FACTION_HORDE,IC_TYPE_DOCKVEHICLE_H,RESPAWN_ONE_DAY},
    {BG_IC_GLAIVE_THROWER_2_H,782.273f,-343.237f,12.602f,4.71239f    ,BG_IC_NPCID_GLAIVE_THROWER_H,FACTION_HORDE,IC_TYPE_DOCKVEHICLE_H,RESPAWN_ONE_DAY},
    {BG_IC_CATAPULT_1_A,803.944f, -343.237f, 12.609f,4.71239f        ,BG_IC_NPCID_CATAPULT,FACTION_ALLIANCE,IC_TYPE_DOCKVEHICLE_A,RESPAWN_ONE_DAY},
    {BG_IC_CATAPULT_2_A,797.233f, -343.237f, 12.083f,4.71239f        ,BG_IC_NPCID_CATAPULT,FACTION_ALLIANCE,IC_TYPE_DOCKVEHICLE_A,RESPAWN_ONE_DAY},
    {BG_IC_CATAPULT_3_A,774.005f, -343.237f, 12.115f,4.71239f        ,BG_IC_NPCID_CATAPULT,FACTION_ALLIANCE,IC_TYPE_DOCKVEHICLE_A,RESPAWN_ONE_DAY},
    {BG_IC_CATAPULT_4_A,766.961f, -343.237f, 12.094f,4.71239f        ,BG_IC_NPCID_CATAPULT,FACTION_ALLIANCE,IC_TYPE_DOCKVEHICLE_A,RESPAWN_ONE_DAY},
    {BG_IC_GLAIVE_THROWER_1_A,788.516f,-343.237f,12.598f,4.71239f    ,BG_IC_NPCID_GLAIVE_THROWER_A,FACTION_ALLIANCE,IC_TYPE_DOCKVEHICLE_A,RESPAWN_ONE_DAY},
    {BG_IC_GLAIVE_THROWER_2_A,782.273f,-343.237f,12.602f,4.71239f    ,BG_IC_NPCID_GLAIVE_THROWER_A,FACTION_ALLIANCE,IC_TYPE_DOCKVEHICLE_A,RESPAWN_ONE_DAY},
    // Workshop
    {BG_IC_DEMOLISHER_H_1,760.571f,-853.102f,12.4412f,1.65484f        ,BG_IC_NPCID_DEMOLISHER,FACTION_HORDE,IC_TYPE_DEMOLISSER_H,0},
    {BG_IC_DEMOLISHER_H_2,752.082f,-853.817f,12.4412f,1.65484f        ,BG_IC_NPCID_DEMOLISHER,FACTION_HORDE,IC_TYPE_DEMOLISSER_H,0},
    {BG_IC_DEMOLISHER_H_3,791.213f,-853.526f,12.4596f,1.5174f        ,BG_IC_NPCID_DEMOLISHER,FACTION_HORDE,IC_TYPE_DEMOLISSER_H,0},
    {BG_IC_DEMOLISHER_H_4,783.065f,-852.904f,12.4552f,1.5174f        ,BG_IC_NPCID_DEMOLISHER,FACTION_HORDE,IC_TYPE_DEMOLISSER_H,0},
    {BG_IC_DEMOLISHER_A_1,760.571f,-853.102f,12.4412f,1.65484f        ,BG_IC_NPCID_DEMOLISHER,FACTION_ALLIANCE,IC_TYPE_DEMOLISSER_A,0},
    {BG_IC_DEMOLISHER_A_2,752.082f,-853.817f,12.4412f,1.65484f        ,BG_IC_NPCID_DEMOLISHER,FACTION_ALLIANCE,IC_TYPE_DEMOLISSER_A,0},
    {BG_IC_DEMOLISHER_A_3,791.213f,-853.526f,12.4596f,1.5174f        ,BG_IC_NPCID_DEMOLISHER,FACTION_ALLIANCE,IC_TYPE_DEMOLISSER_A,0},
    {BG_IC_DEMOLISHER_A_4,783.065f,-852.904f,12.4552f,1.5174f        ,BG_IC_NPCID_DEMOLISHER,FACTION_ALLIANCE,IC_TYPE_DEMOLISSER_A,0},
    {BG_IC_SIEGE_ENGINE_H,773.623f, -884.381f, 16.725f, 1.530f        ,BG_IC_NPCID_SIEGE_ENGINE_H,FACTION_HORDE,IC_TYPE_SIEGE_H,0},
    {BG_IC_SIEGE_ENGINE_A,773.623f, -884.381f, 16.725f, 1.530f        ,BG_IC_NPCID_SIEGE_ENGINE_A,FACTION_ALLIANCE,IC_TYPE_SIEGE_A,0},
};

/*
const float BG_IC_GunshipPortalPositions[4] = {735.34f, -1107.86f, 134.46f, 0.0f};

const float BG_IC_KeepDoorPositions[2][4] =
{
    {1283.17,-765.92,50.8184,3.14159},    // keep door A
    {288.079,-832.54,51.4686,3.14159}    // keep door H
};
*/

enum Buffs
{
    SPELL_OIL_REFINERY        = 68719,
    SPELL_QUARRY            = 68720,
    SPELL_PARACHUTE = 66656,
    SPELL_SLOW_FALL = 12438
};

class BattlegroundICScore : public BattlegroundScore
{
    public:
        BattlegroundICScore() {};
        virtual ~BattlegroundICScore() {};
        uint32 BasesAssaulted;
        uint32 BasesDefended;
};

class BattlegroundIC : public Battleground
{
    friend class BattlegroundMgr;

    public:
        BattlegroundIC();
        ~BattlegroundIC();
        void Update(uint32 diff);

        /* inherited from BattlegroundClass */
        virtual void AddPlayer(Player *plr);
        virtual void StartingEventCloseDoors(){};
        virtual void StartingEventOpenDoors();
        virtual void Reset();

        void FillInitialWorldStates(WorldPacket& data);
        void RemovePlayer(Player *plr,uint64 guid);
        //void HandleAreaTrigger(Player *Source, uint32 Trigger);
        bool SetupBattleground();
        void SpawnLeader(uint32 teamid);
        void SpawnCreatures(uint32 teamid, uint32 from, uint32 to);
        void HandleKillUnit(Creature *unit, Player *killer);
        void HandleKillPlayer(Player *player, Player *killer);
        void EndBattleground(uint32 winner);
        void EventPlayerClickedOnFlag(Player *source, GameObject* /*target_obj*/);
        void EventPlayerCapturedFlag(Player* plr);

        /* Scorekeeping */
        void UpdatePlayerScore(Player *Source, uint32 type, uint32 value, bool doAddHonor = true);
        virtual WorldSafeLocsEntry const* GetClosestGraveYard(Player* player);
        virtual void DoAction(uint32 action, uint64 var);
        void UpdateScore(uint16 team, int16 points);
        Transport* MakeTransport(uint32 entry,uint32 period,std::string name);
        uint32 GetGateIDFromDestroyEventID(uint32 id);
        void SendTransportInit(Player *player);

    private:
    
    	void SpawnNpcType(uint32 type);
        void DeSpawnNpcType(uint32 type);
        void _NodeOccupied(uint8 node,Team team);
        void _NodeDeOccupied(uint8 node);

        /* Gameobject spawning/despawning */
        void _CreateBanner(uint8 node, uint8 type, uint8 teamIndex, bool delay);
        void _DelBanner(uint8 node, uint8 type, uint8 teamIndex);
        void _SendNodeUpdate(uint8 node);

        int32 _GetNodeNameId(uint8 node);

        void DestroyGate(Player* pl, GameObject* /*go*/, uint32 destroyedEvent);

        ICNode m_IC_NodeData[7];
        ICDoor m_IC_DoorData[6];

        uint32 m_Team_Scores[2];

        BG_IC_GateState m_GateStatus[6];
        bool m_OpenDoors;
        uint32 m_uiOpenDoorTimer;
        bool m_ActivMODoors;
        uint32 m_uiActivMODoorsTimer;

        Transport *m_GunshipA,*m_GunshipH;
};
#endif
