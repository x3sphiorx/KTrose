/*
    Rose Online Server Emulator
    Copyright (C) 2006,2007 OSRose Team http://www.osrose.net

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

    developed with Main erose/hrose source server + some change from the original eich source
*/
#include "character.h"
#include "worldserver.h"

// return true if this character is monster
bool CCharacter::IsMonster( )
{
    if(CharType == 2 || CharType == 3)
        return true;
    return false;
}

// return true if this character is player
bool CCharacter::IsPlayer( )
{
    if(CharType == 1)
        return true;
    return false;
}

//return true if this character is an NPC
bool CCharacter::IsNPC( )
{
    if(CharType == 4)
        return true;
    return false;
}

// return true if HP is lower to 1
bool CCharacter::IsDead( )
{
    if(Stats->HP <= 0)
        return true;
    return false;
}

// return true if this character is summon
bool CCharacter::IsSummon( )
{
    if(this == NULL) return false;
    if(CharType == 3)// this line is erroring. No idea why
        return true;
    return false;
}

// Virtual function [return item drop]
CDrop* CCharacter::GetDrop( )
{
    return NULL;
}

// start action [attack]
void CCharacter::StartAction( CCharacter* Target, BYTE action, UINT skillid)
{

    BEGINPACKET( pak, 0 );
    switch(action)
    {
        case NORMAL_ATTACK:
        {
            //Log( MSG_INFO, "case NORMAL_ATTACK");
            if(Target == NULL)return;
            RESETPACKET( pak, 0x798 );
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, Target->clientid );
            ADDWORD    ( pak, Stats->Move_Speed );
            ADDFLOAT   ( pak, Target->Position->current.x * 100 );
            ADDFLOAT   ( pak, Target->Position->current.y * 100 );
            Battle->target = Target->clientid;
            Battle->atktarget = Target->clientid;
            Battle->atktype = action;
            Battle->skilltarget = 0;
            Battle->bufftarget = 0;
            Battle->skillid = 0;
            Position->destiny  = Target->Position->current;
            Position->lastMoveTime = clock();
        }
        break;
        case SKILL_ATTACK: //Log( MSG_INFO, "case SKILL_ATTACK");
        case SKILL_BUFF:
        {
        	if(Target == NULL)return;
            RESETPACKET( pak, 0x7b3 );
        	ADDWORD    ( pak, clientid );
        	ADDWORD    ( pak, Target->clientid );
        	ADDWORD    ( pak, skillid );
        	ADDWORD    ( pak, 0x0000 );
            ADDFLOAT   ( pak, Target->Position->current.x * 100 );
            ADDFLOAT   ( pak, Target->Position->current.y * 100 );
            Battle->target = Target->clientid;

            if(action == SKILL_ATTACK)
            {
                //Log( MSG_INFO, "case SKILL_ATTACK");
                Battle->skilltarget = Target->clientid;
                Battle->bufftarget = 0;
            }
            else
            {
                //Log( MSG_INFO, "case SKILL_BUFF");
                Battle->bufftarget = Target->clientid;
                Battle->skilltarget = 0;
            }

            Battle->atktype = action;
            Position->destiny  = Target->Position->current;
            Battle->skillid = skillid;
            Position->lastMoveTime = clock();
        }
        break;
        case SKILL_AOE://Log( MSG_INFO, "case SKILL_AOE");
        case BUFF_SELF://Log( MSG_INFO, "case BUFF_SELF");
        case BUFF_AOE:
        {
            //Log( MSG_INFO, "case BUFF_AOE");
            RESETPACKET( pak, 0x7b2);
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, skillid );
            Battle->atktype = action;
            Battle->skillid = skillid;
            //Log( MSG_INFO, "BUFF_AOE packet sent");
        }
        break;
        case AOE_TARGET:
        {
            //Log( MSG_INFO, "case AOE_TARGET");
            //Target is NULL for this function when cast by a player
            //Target is NOT NULL when it comes from a monster
            if(Target != NULL) //monster attack
            {
                Position->skilltargetpos.x = Target->Position->current.x;
                Position->skilltargetpos.y = Target->Position->current.y;
            }
            RESETPACKET( pak, 0x7b4 );
            ADDWORD    ( pak, clientid );
            ADDWORD    ( pak, skillid );
            ADDFLOAT   ( pak, Position->skilltargetpos.x * 100 );
            ADDFLOAT   ( pak, Position->skilltargetpos.y * 100 );
            Battle->atktype = action;
            Battle->skillid = skillid;
            Battle->skilltarget = 0;
            Battle->bufftarget = 0;
        }
        break;
        default:
            return;
        break;
    }
    GServer->SendToVisible( &pak, this );
    Battle->contatk = true;

    //Log(MSG_INFO,"Battle Attacktype = %i",Battle->atktype);
    return;
}

bool CCharacter::IsOnBattle( )
{
    if(Battle->atktype == 0)
    {
        if(Battle->iscasting == 1)
        {
            clock_t etime = clock() - Battle->lastAtkTime;
            if( etime < CLOCKS_PER_SEC * 100 / Stats->Attack_Speed )
            {
                //Log(MSG_DEBUG,"Iscasting is true while NOT in battle. Reset to false.");
                Battle->iscasting = 0;
                return false;
            }
        }
        return false;
    }
    switch(Battle->atktype)
    {
        case NORMAL_ATTACK:
        {
            if(Battle->atktarget != 0) return true;
        }
        break;
        case SKILL_ATTACK:
        case AOE_TARGET:
        {
            if(Battle->skilltarget != 0 && Battle->skillid != 0) return true;
        }
        break;
        case SKILL_BUFF:
        {
            if(Battle->bufftarget != 0 && Battle->skillid != 0) return true;
        }
        break;
        case SKILL_AOE:
        //case SKILL_SELF: //no such skill type
        case BUFF_SELF:
        case BUFF_AOE:
        {
            if(Battle->skillid != 0) return true;
        }
        break;
        default: return false;
    }
}

bool CCharacter::CanAttack( )
{

    clock_t etime = clock() - Battle->lastAtkTime;
    if (Stats->Attack_Speed < 1)
    {
        Log( MSG_INFO, "weapon with no attackspeed.");
        return false;
    }
    if(Battle->iscasting == 1)
    {
        if( etime < CLOCKS_PER_SEC * 25 / Stats->Attack_Speed ) //should make the delay 4 times longer
        {
            //if(IsPlayer())
            //    Log(MSG_INFO,"Cannot use magic attack yet. Last attack time = %i",Battle->lastAtkTime);
            return false;
        }
        else
        {
            Battle->iscasting = 0;
            //if(IsPlayer())
            //    Log(MSG_INFO,"OK Now we can use a new (magic or normal) attack.");
            return true;
        }
    }
    else //normal attack
    {
        if( etime < CLOCKS_PER_SEC * 100 / Stats->Attack_Speed )
        {
            //if(IsPlayer())
            //    Log(MSG_INFO,"Cannot attack yet. Last attack time = %i",Battle->lastAtkTime);
            return false;
        }
        //if(IsPlayer())
        //    Log(MSG_INFO,"OK Now we can use a normal attack");
    }
    return true;
}

// return true if target is reached
bool CCharacter::IsTargetReached( CCharacter* Enemy, CSkills* skill )
{
    CMap* map = GServer->MapList.Index[Position->Map];
    if(map == NULL)return false;
    float distance = GServer->distance( Position->current, Enemy->Position->current );
    if(skill == NULL) //it's a normal attack
    {
        if(distance <= Stats->Attack_Distance)
        {
            return true;
        }
        else
        {
            Position->destiny = Enemy->Position->current;
        }
    }
    else
    {
        if(distance <= skill->range)
        {
            return true;
        }
        else
        {
            Position->destiny = Enemy->Position->current;
        }
    }
    //Log(MSG_INFO,"Monster cannot attack. Too far away");
    return false;
}

// return true if the character is moving
bool CCharacter::IsMoving( )
{
    if(Position->current.x == Position->destiny.x && Position->current.y == Position->destiny.y )
        return false;
    return true;
}

// VIRTUAL [add player damage]
void CCharacter::AddDamage( CCharacter* enemy, long int hitpower)
{

}

// return character target
CCharacter* CCharacter::GetCharTarget( )
{
    CCharacter* thistarget = GServer->MapList.Index[Position->Map]->GetCharInMap( Battle->target );
    if (thistarget != NULL)
        return thistarget;
    //if I don't currently have a target then return the character who just hit me
    return GServer->MapList.Index[Position->Map]->GetCharInMap( Battle->hitby );
}

// VIRTUAL [reduce ammon/bullets/cannons]
void CCharacter::ReduceABC( )
{

}

// VIRTUAL [get extra buff value]
int CCharacter::GetEVBuff( )
{
    return 0;
}

// VIRTUAL [return intelligence]
unsigned int CCharacter::GetInt( )
{
    return 15;
}


// Check For Debuffs
void CCharacter::RefreshBuff( )
{
    bool bflag = false;
    for( UINT i=0;i<30;i++)
    {
        if(MagicStatus[i].Buff == 0) continue;
        clock_t etime = clock() - MagicStatus[i].BuffTime;
        if( etime >= MagicStatus[i].Duration * CLOCKS_PER_SEC )
        {
            switch(MagicStatus[i].Status)
            {
                case 18: // attack power up
                case 19: // attack power down
                case 48: // attack power up
                    if(i<15)
                        Status->Attack_up = 0xff;
                    else
                        Status->Attack_down = 0xff;
                    Stats->Attack_Power = GetAttackPower( );
                break;
                case 20: // def up
                case 21: // def down
                case 49: // def up
                    if(i<15)
                        Status->Defense_up= 0xff;
                    else
                        Status->Defense_down = 0xff;
                    Stats->Defense = GetDefense( );
                break;
                case 24: //accuracy up
                case 25: //accuracy down
                case 51: //attack accuracy up.
                    if(i<15)
                        Status->Accury_up= 0xff;
                    else
                        Status->Accury_down = 0xff;
                    Stats->Accury = GetAccury( );
                break;
                case 22: // macic resistance up
                case 23: // magic resistance down
                case 50: // magic resistance up
                    if(i<15)
                        Status->Magic_Defense_up = 0xff;
                    else
                        Status->Magic_Defense_down = 0xff;
                    Stats->Magic_Defense = GetMagicDefense( );
                break;
                case 28: //dodge up
                case 29: //dodge down
                case 53: //dodge rate up
                    if(i<15)
                        Status->Dodge_up = 0xff;
                    else
                        Status->Dodge_down = 0xff;
                    Stats->Dodge = GetDodge( );
                break;
                case 14: //dash
                case 15: //slow
                case 46: //movement speed increased
                    if(i<15)
                        Status->Dash_up = 0xff;
                    else
                        Status->Dash_down = 0xff;
                    Stats->Move_Speed = GetMoveSpeed( );
                break;
                case 16: // haste attack
                case 17: // slow attack
                case 47: // attack speed up
                    if(i<15)
                        Status->Haste_up = 0xff;
                    else
                        Status->Haste_down = 0xff;
                    Stats->Attack_Speed = GetAttackSpeed( );
                break;
                case 26: // crit up
                case 27: // crit down
                case 52: // crit up
                    if(i<15)
                        Status->Critical_up = 0xff;
                    else
                        Status->Critical_down = 0xff;
                    Stats->Critical = GetCritical( );
                break;
                case 12: // max HP up
                case 44: // max HP up
                    if(i<15)
                        Status->HP_up = 0xff;
                    else
                        Status->HP_down = 0xff;
                    Stats->MaxHP = GetMaxHP( );
                break;
                case 13: // max MP up
                case 45: // max MP up
                    if(i<15)
                        Status->MP_up = 0xff;
                    else
                        Status->MP_down = 0xff;
                    Stats->MaxMP = GetMaxMP( );
                break;
                case 32: // faint
                     Status->Stuned = 0xff;
                     Status->CanAttack = true;
                     //printf("removing stun\n");
                break;
                case 7: case 8: case 9: case 10: case 11: //poisoned
                     Status->Poisoned = 0xff;
                     //printf("removing poison\n");
                break;
                case 30: // muted
                     Status->Muted = 0xff;
                     Status->CanCastSkill = true;
                break;
                case 31: // sleep May need to be fixed later to accomodate multiple status effects.
                     Status->Sleep = 0xff;
                     Status->CanMove = true;
                     Status->CanCastSkill = true;
                     Status->CanAttack = true;
                break;
                case 54: //A_GMExtra_Damage:
                case 36: //A_Extra_Damage:
                     if(i<15)
                     {
                        Status->ExtraDamage_up = 0xff;
                        Stats->ExtraDamage = 0xff;
                     }
                     else
                     {
                         Status->ExtraDamage_down = 0xff;
                         Stats->ExtraDamage = 0xff;
                     }

                break;
                case 56: // Taunt
                     Status->Taunt = 0xff;
                break;
            }

            MagicStatus[i].Status = 0;
            MagicStatus[i].Buff = 0;
            MagicStatus[i].BuffTime = 0;
            MagicStatus[i].Duration = 0;
            MagicStatus[i].Value = 0;
            bflag = true;
        }
        else if (MagicStatus[i].Status >= 7 && MagicStatus[i].Status <= 11 && etime > 1*CLOCKS_PER_SEC) //Do poison dmg every 1.5 seconds
        {
             Stats->HP -= MagicStatus[i].Status; //Actually take 7, 8, 9, 10 or 11 from the health. Based on the Status itself
             MagicStatus[i].BuffTime += 1*CLOCKS_PER_SEC;
             MagicStatus[i].Duration -= 1;
             //printf("did %i poison dmg to the player, still %i seconds and %i HP remain \n", MagicStatus[i].Status, MagicStatus[i].Duration, Stats->HP);

             //A bunch of messy code to send dmg packet
             BEGINPACKET( pak, 0x7b6 );
             ADDWORD    ( pak, clientid );
             ADDWORD    ( pak, 0 );
             ADDDWORD   ( pak, 0x000007f8 );
             ADDBYTE    ( pak, 0x00 );
             ADDDWORD   ( pak, MagicStatus[i].Status );

             //If Enemy is killed
             if( IsDead())
             {
                 //printf("char died\n");
                 CDrop* thisdrop = NULL;
                 ADDDWORD   ( pak, 16 );
                 if( !IsSummon( ) && !IsPlayer( ))
                 {
                     thisdrop = GetDrop( );
                     if( thisdrop!=NULL)
                     {
                         ADDFLOAT   ( pak, thisdrop->pos.x*100 );
                         ADDFLOAT   ( pak, thisdrop->pos.y*100 );
                         if( thisdrop->type==1)
                         {
                             ADDDWORD( pak, 0xccccccdf );
                             ADDDWORD( pak, thisdrop->amount );
                         }
                         else
                         {
                             ADDDWORD   ( pak, GServer->BuildItemHead( thisdrop->item ) );
                             ADDDWORD   ( pak, GServer->BuildItemData( thisdrop->item ) );
                         }
                         ADDWORD    ( pak, thisdrop->clientid );
                         ADDWORD    ( pak, thisdrop->owner );
                         CMap* map = GServer->MapList.Index[thisdrop->posMap];
                         map->AddDrop( thisdrop );
                     }
                 }
                 GServer->SendToVisible( &pak, this, thisdrop );
             }

             //If enemy is still alive
             else
             {
                 ADDDWORD   ( pak, 4 );
                 GServer->SendToVisible( &pak, this );
             }
         }
    }
    if(bflag)
    {
        BEGINPACKET( pak,0x7b7 );
        ADDWORD    ( pak, clientid );
        ADDDWORD   ( pak, GServer->BuildBuffs( this ) );
        GServer->SendToVisible( &pak, this );
    }
}

// VIRTUAL [return party pointer]
CParty* CCharacter::GetParty( )
{
    return NULL;
}

// VIRTUAL [return clan pointer]
CLAN* CCharacter::GetClan( )
{
    return NULL;
}

bool CCharacter::IsAttacking( )
{
    if(IsOnBattle( ))
    {
        switch(Battle->atktype)
        {
            case SKILL_BUFF:
            case BUFF_SELF:
            case BUFF_AOE:
                return false;
        }
    }
    else return false;
    return true;
}
