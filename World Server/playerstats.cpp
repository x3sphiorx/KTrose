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

    depeloped with Main erose/hrose source server + some change from the original eich source
*/
#include "player.h"
#include "worldserver.h"

// Return Dodge
unsigned int CPlayer::GetDodge( )
{
    UINT Dodge = 0;
    Dodge = (UINT)floor(( ((Stats->Level * 0.3) + ((Attr->Dex + Attr->Edex) * 1.9)) + 10 ) * 0.4);
    UINT ClothDodge = 0;

    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0 )
        {
            if (i < 7)
                ClothDodge += items[i].durability;
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_DODGE)
            {
                Dodge += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_DODGE)
            {
                Dodge += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_DODGE)
                    Dodge += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_DODGE)
                    Dodge += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    Dodge += (UINT)floor(ClothDodge*0.3);

    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sDodge )
            {
                if( skill->value2[j] > 0 )
                    Extra += Dodge * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    Dodge += Extra;

    if(Status->Dodge_up!=0xff)
        Dodge += MagicStatus[Status->Dodge_up].Value;
    if(Status->Dodge_down!=0xff)
        Dodge -= MagicStatus[Status->Dodge_down].Value;
    if(Dodge<30)
        Dodge=30;
    return Dodge;
}

// Return Accury
unsigned int CPlayer::GetAccury( )
{
    UINT Accury = 0;
    if(items[7].count==0 )
        Accury = (UINT)floor( (((Attr->Con + Attr->Econ )+10)*0.5) + 15 );
    else
        Accury = (UINT)floor( ((Attr->Con+Attr->Econ+10)*0.8) + ((GServer->EquipList[WEAPON].Index[items[7].itemnum]->quality*0.6) + (items[7].durability*0.8)) );
    UINT extra_refine[10] = { 0, 4, 7, 10, 14, 20, 26, 33, 40, 50};
    if( items[7].refine>0 )
    {
        UINT refine = (UINT)floor((double)(items[7].refine/16));
        if(refine<10)
        {
            Accury += extra_refine[refine];
        }
    }
    for(UINT i=1;i<12;i++)
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_ACCUR)
            {
                Accury += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_ACCUR)
            {
                Accury += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_ACCUR)
                    Accury += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_ACCUR)
                    Accury += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sAccuracy )
            {
                if( skill->value2[j] > 0 )
                    Extra += Accury * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    Accury += Extra;

    if(Status->Accury_up!=0xff)
        Accury += MagicStatus[Status->Dodge_up].Value;
    if(Status->Accury_down!=0xff)
        Accury -= MagicStatus[Status->Accury_down].Value;
    if(Accury<30)
        Accury=30;
    return Accury;
}

// Return Critical
unsigned int CPlayer::GetCritical( )
{
    UINT Critical = 0;
    UINT weapontype = 1;
    if(items[7].itemnum!=0 && items[7].count > 0) // weapon equipped
        weapontype = GServer->EquipList[WEAPON].Index[items[7].itemnum]->type;
    Critical = (UINT)floor(((Attr->Con + Attr->Econ + 20)*0.2) + Attr->Sen + Attr->Esen );
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0)
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_CRITICAL)
            {
                Critical += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_CRITICAL)
            {
                Critical += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_CRITICAL)
                    Critical += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_CRITICAL)
                    Critical += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            //item specific crit boosts
            for(int n=0;n<5;n++)
            {
                if( skill->weapon[n] == weapontype) // item defined in the skill
                {
                    if( skill->value2[j] > 0 )
                        Extra += Critical * skill->value2[j] / 100;
                    if( skill->value1[j] > 0 )
                        Extra += skill->value1[j];
                }
            }
        }
    }
    Critical += Extra;

    if(Fairy)Critical = (unsigned int)floor(Critical*1.2);
    if(Status->Critical_up!=0xff)
        Critical += MagicStatus[Status->Critical_up].Value;
    if(Status->Critical_down!=0xff)
        Critical -= MagicStatus[Status->Critical_down].Value;
    if(Critical<10)
        Critical=10;
    return Critical;
}

// Return Magic Attack based on the weapon currently equipped
unsigned int CPlayer::GetMagicAttack( )
{
    if(GServer->EquipList[WEAPON].Index[items[7].itemnum]->magicattack == 1)
        return 1;
    else
        return 0;
}


// Return Magic Defense
unsigned int CPlayer::GetMagicDefense( )
{
    UINT MagicDefense = 0;
    UINT Extra = 0;
    switch( CharInfo->Job )
    {
        case 121:case 122:
        case 221:case 222:
        case 321:case 322:
        case 421:case 422:
            Extra += 20;
        break;
        default:
        break;
    }
    MagicDefense += (UINT)floor(((Attr->Int + Attr->Eint + 5)*0.6) + ((Stats->Level + 15)*0.8));
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0 )
        {
            if (i < 9 && items[i].itemtype != WEAPON)
                MagicDefense += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->magicresistence;

            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_MRESIST)
            {
                MagicDefense += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_MRESIST)
            {
                MagicDefense += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_MRESIST)
                    MagicDefense += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_MRESIST)
                    MagicDefense += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }

    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sMagicResistance )
            {
                if( skill->value2[j] > 0 )
                    Extra += MagicDefense * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    MagicDefense += Extra;

    if(Status->Magic_Defense_up!=0xff)
        MagicDefense += MagicStatus[Status->Magic_Defense_up].Value;
    if(Status->Magic_Defense_down!=0xff)
        MagicDefense -= MagicStatus[Status->Magic_Defense_down].Value;
    return MagicDefense;
}


// Return Attack
unsigned int CPlayer::GetAttackPower( )
{
    UINT attack = 0;
    UINT weapontype = 0;
    UINT weaponatk = 0;
    UINT Extra = 0;
    UINT skilltype = 0;
    switch(CharInfo->Job)
    {
        case 121:case 122:
        case 221:case 222:
        case 321:case 322:
        case 421:case 422:
            Extra += 30;
        break;
        default:
        break;
    }
	if( items[7].itemnum!=0 && items[7].count > 0 && items[7].durability > 0 )
    {
        UINT extra_refine[10] = {0, 7, 14, 21, 31, 41, 51, 65, 80 , 100};
        weaponatk = GServer->EquipList[WEAPON].Index[items[7].itemnum]->attackpower;
        weapontype = GServer->EquipList[WEAPON].Index[items[7].itemnum]->type;
        if( items[7].refine > 0 )
        {
            UINT refine = (UINT)floor((double)(items[7].refine/16));
            if(refine>0 && refine<10)
            {
                weaponatk += (UINT)floor(extra_refine[refine] * 0.01 * weaponatk);
            }

        }
        if(Session->codedebug)
        {
            Log( MSG_INFO, "Base AP with weapon equipped (includes refines) %i",attack );
        }
    }
    else
    {
        attack += (UINT)floor( ((Attr->Dex + Attr->Edex) * 0.3) + ((Attr->Str + Attr->Estr) * 0.5) + (Stats->Level * 0.2));
        if(Session->codedebug)
        {
            Log( MSG_INFO, "AP unarmed %i",attack );
        }
    }
    switch( weapontype )
    {
        case ONE_HAND_SWORD://one hand sword
        {
            attack += (UINT)floor( (Attr->Str + Attr->Estr) * 0.75 + Stats->Level * 0.2 + ((Attr->Str + Attr->Estr) * 0.05 + 29) * weaponatk * 0.03333334 );
            if(Session->codedebug)
            {
                Log( MSG_INFO, "AP from sword only is %i",attack );
            }
            skilltype = 42;
        }
        break;
        case ONE_HAND_BUNT_SWORD://one hand blunt sword
        {
            attack += (UINT)floor( (Attr->Str + Attr->Estr)*0.75 + Stats->Level*0.2 + ((Attr->Str + Attr->Estr)*0.05 + 29) * weaponatk * 0.03333334 );
            skilltype = 42;
        }
        break;
        case TWO_HAND_SWORD://two hand sword
        {
            attack += (UINT)floor( (Attr->Str + Attr->Estr)*0.75 + Stats->Level*0.2 + ((Attr->Str + Attr->Estr)*0.05 + 29) * weaponatk * 0.03333334 );
            skilltype = 43;
        }
        break;
        case SPEAR://spear
        {
            attack += (UINT)floor( (Attr->Str + Attr->Estr)*0.75 + Stats->Level*0.2 + ((Attr->Str + Attr->Estr)*0.05 + 29) * weaponatk * 0.03333334 );
            skilltype = 43;
        }
        break;
        case TWO_HAND_AXE://two hand axe
        {
            attack += (UINT)floor( (Attr->Str + Attr->Estr)*0.75 + Stats->Level*0.2 + ((Attr->Str + Attr->Estr)*0.05 + 29) * weaponatk * 0.03333334 );
            skilltype = 43;
        }
        break;
        case BOW://bow
        {
            float arrows = 0;
            if(items[132].count>0)
                arrows = GServer->NaturalList.Index[items[132].itemnum]->quality * 0.5;
            attack += (UINT)floor((((Attr->Str + Attr->Estr) + Stats->Level) * 0.1) + ((Attr->Dex + Attr->Edex) * 0.04 + (Attr->Sen + Attr->Esen) * 0.03 + 29) * weaponatk * 0.03333334 + (Attr->Dex+Attr->Edex) * 0.52 + arrows);
            if(Session->codedebug)
            {
                Log( MSG_INFO, "AP from Bow + Arrows only is %i",attack );
            }
            skilltype = 44; //Bow attack power
        }
        break;
        case GUN://gun
        case DUAL_GUN://dual guns
        {
            float bullets = 0;
            if(items[133].count>1)
                bullets = GServer->NaturalList.Index[items[133].itemnum]->quality * 0.8;
            attack += (UINT)floor( (Attr->Con + Attr->Econ)*0.47 + bullets + Stats->Level*0.1 + (Attr->Dex + Attr->Edex)*0.3 + ((Attr->Con + Attr->Econ)*0.04 + (Attr->Sen + Attr->Esen)*0.05 + 29) * weaponatk * 0.03333334);
            skilltype = 45;
        }
        break;
        case LAUNCHER://launcher
        {
            float cannons = 0;
            if(items[134].count>0)
            {
                cannons = GServer->NaturalList.Index[items[134].itemnum]->quality;
            }
            attack += (UINT)floor( cannons*0.8 + Stats->Level*0.1 + (Attr->Str + Attr->Estr)*0.32 + (Attr->Con + Attr->Econ)*0.45 + ((Attr->Con + Attr->Econ)*0.04 + (Attr->Sen + Attr->Esen)*0.05 + 29) * weaponatk * 0.03333334 );
            skilltype = 45;
        }
        break;
        case STAFF://staff
        {
          attack += (UINT)floor( Stats->Level*0.2 + ((Attr->Int + Attr->Eint)+(Attr->Str + Attr->Estr))*0.4 + ((Attr->Int + Attr-> Eint)*0.05 + 29) * weaponatk * 0.03333334 );
            skilltype = 46;
        }
        break;
        case WAND://wand
        {
          attack += (UINT)floor( Stats->Level*0.2 + (Attr->Int + Attr->Eint)*0.6 + ( ((Attr->Sen + Attr->Esen)*0.1 +26) * 0.03703704 * weaponatk )  );
            skilltype = 46;
        }
        break;
        case KATAR://katar
        {
          attack += (UINT)floor( Stats->Level*0.2 + (Attr->Str + Attr->Estr)*0.42 + (Attr->Dex + Attr->Edex)*0.55 + ((Attr->Dex + Attr->Edex)*0.05 + 20) * weaponatk * 0.0476190);
            skilltype = 48;
        }
        break;
        case DOUBLE_SWORD://double sword
        {
            attack += (UINT)floor( Stats->Level*0.2 + (Attr->Str + Attr->Estr)*0.63 + (Attr->Dex + Attr->Edex)*0.45 + ((Attr->Dex + Attr->Edex)*0.05 + 25) * weaponatk * 0.03846154);
            skilltype = 48;
        }
        break;
        case CROSSBOW://crossbow
        {
            float arrows = 0;
            if(items[132].count>0)
                arrows = GServer->NaturalList.Index[items[132].itemnum]->quality*0.5;
            attack += (UINT)floor((((Attr->Str + Attr->Estr)+Stats->Level)*0.1) + ((Attr->Dex + Attr->Edex)*0.04 + (Attr->Sen +Attr->Esen)*0.03 + 29) * weaponatk * 0.03333334 + (Attr->Dex + Attr->Edex)*0.52 + arrows);
            skilltype = 47; //Crossbow Attack Power
        }
        break;
        default:
        break;
    }

    for(UINT i=1;i<12;i++)//cloth stats
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == 18)
            {
                attack += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == 18)
            {
                attack += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == 18)
                    attack += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == 18)
                    attack += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    if(Session->codedebug)
    {
        Log( MSG_INFO, "AP after cloth stats %i",attack );
    }

    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            //weapon specific AP boosts
            for(int n=0;n<5;n++)
            {
                if(weapontype == 0) //no weapon equipped
                {
                    if( skill->buff[j] == 41) //unarmed AP
                    {
                        if( skill->value2[j] > 0 )
                            Extra += attack * skill->value2[j] / 100;
                        if( skill->value1[j] > 0 )
                            Extra += skill->value1[j];
                    }
                }
                else // some kind of weapon equipped
                {
                    if( skill->weapon[n] == weapontype || skill->buff[j] == 18)
                    {
                        int xt1 = 0;
                        int xt2 = 0;
                        if(skill->buff[j] == skilltype)
                        {
                            xt1 = skill->value1[j];
                            xt2 = attack * skill->value2[j] / 100;
                            if(xt1 > xt2)
                                Extra = xt1;
                            else
                                Extra = xt2;
                            //Extra += attack * skill->value2[j] / 100;
                            if(Session->codedebug)
                            {
                                Log( MSG_INFO, "Extra AP from passive %i",Extra );
                            }
                        }
                    }
                }
            }
        }
    }
    attack += Extra;

    if(Session->codedebug)
    {
        Log( MSG_INFO, "AP final value before fairy and buff check is %i",attack );
    }
    if(Fairy)attack = (unsigned int)floor(attack*1.2);
    if(Status->Attack_up!=0xff)
        attack += MagicStatus[Status->Attack_up].Value;
    if(Status->Attack_down!=0xff)
        attack -= MagicStatus[Status->Attack_down].Value;
    //if(attack<30)
    //    attack = 30;
	return attack;
}

// Return Defense
unsigned int CPlayer::GetDefense( )
{
    UINT defense = 0;
    UINT Extra = 0;
    switch( CharInfo->Job )
    {
        case 121:case 122:
        case 221:case 222:
        case 321:case 322:
        case 421:case 422:
            Extra += 25;
        break;
        default:
                break;
    }
    defense += (UINT)floor( (( Attr->Estr + Attr->Str + 5) * 0.35) + ((Stats->Level + 15) * 0.7) );
    UINT extra_refine[10] = {0, 6, 12, 18, 27, 36, 45, 57, 70 , 85};
    for(UINT i=1;i<9;i++)
    {
        if(i==7)
            continue;
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            defense += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->defense;
            if(items[i].refine>0)
            {
                UINT refine = (UINT)floor((double)(items[i].refine/16));
                if(refine<10)
                {
                    defense += (UINT)floor(extra_refine[refine] * 0.01 * GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->defense);
                }
            }
        }
    }
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_DEFENSE)
            {
                defense += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_DEFENSE)
            {
                defense += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats < 500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_DEFENSE)
                    defense += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_DEFENSE)
                    defense += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    // Additional def due to pskills
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0) continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sDefense || skill->buff[j] ==  sDefense2 )
            {
                if( skill->value2[j] > 0 )
                    Extra += defense * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
            //Shield specific def boosts. previously not included.
            for(int n=0;n<5;n++)
            {
                if( skill->weapon[n] == items[8].type && items[8].count > 0) // item defined in the skill is currently equipped in the shield slot
                {
                    if( skill->value2[j] > 0 )
                        Extra += defense * skill->value2[j] / 100;
                    if( skill->value1[j] > 0 )
                        Extra += skill->value1[j];
                }
            }
            // this is BS sShield = 35 and that is "Shield Damage" not defense
            //if (items[8].count > 0 && skill->buff[j] == sShield)
            //{
            //    if( skill->value2[j] > 0 )
            //        Extra += defense * skill->value2[j] / 100;
            //    if( skill->value1[j] > 0 )
            //        Extra += skill->value1[j];
            //}
        }
    }
    defense += Extra;
    if(Fairy) defense = (unsigned int)floor(defense*1.2);
    if(Status->Defense_up!=0xff)
        defense += MagicStatus[Status->Defense_up].Value;
    if(Status->Defense_down!=0xff)
        defense -= MagicStatus[Status->Defense_down].Value;
    return defense;
}

// Return Attack Speed
unsigned int CPlayer::GetAttackSpeed( )
{
    UINT aspeed = 0;
	if( items[7].itemnum!=0 && items[7].count > 0 )
    {
        UINT wpnspd = 0;
        wpnspd = GServer->EquipList[WEAPON].Index[items[7].itemnum]->attackspeed;
        switch(wpnspd)
        {
            case 12: //normal
                aspeed = 88;
            break;
            case 11: //+1
                aspeed = 93;
            break;
            case 10: //+2
                aspeed = 100;
            break;
            case 9: //+3
                aspeed = 107;
            break;
            case 8: //+4
                aspeed = 115;
            break;
            case 7: //+5
                aspeed = 125;
            break;
            case 6: //+6
                aspeed = 136;
            break;
            default:
                break;
        }
        if(Session->codedebug) //Debug code
        {
            GServer->SendPM(this, "Weapon speed %i. Attack speed so far %i",wpnspd,aspeed);
        }
    }
    else
    {
        aspeed = 115;
        if(Session->codedebug) //Debug code
        {
            GServer->SendPM(this, "Attack speed with no weapon %i",aspeed);
        }
    }

    UINT weapontype = 0;
    UINT skilltype = 0;
    weapontype = GServer->EquipList[WEAPON].Index[items[7].itemnum]->type;
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        bool GotWeapon = false; //do I have one of the listed weapons?
        bool GotRightWeapon = false; //Do i have the right one though?
        if( skill->weapon[0] == 0)
        {
            GotWeapon = true;
        }
        else
        {
            for(int n=0;n<5;n++)
            {
                if( skill->weapon[n] != 0 && skill->weapon[n] == weapontype) // item defined in the skill
                {
                    GotWeapon = true;
                }
            }
        }
        if(GotWeapon) //No point checking if we have the RIGHT weapon when we don't have any of them
        {
            for(UINT j = 0; j < 2; j++ )
            {
                GotRightWeapon = false;
                switch(skill->buff[j])
                {
                    case 24: //attackspeed
                        GotRightWeapon = true; //true for all weapons listed
                        break;
                    case 49: //bow speed
                        if(weapontype == 231 || weapontype == 271)
                            GotRightWeapon = true; //true if we have a bow or crossbow
                        break;
                    case 50: //gun speed
                        if(weapontype == 232 || weapontype == 253)
                            GotRightWeapon = true; //true if we have a gun or dual guns
                        break;
                    case 51: //combat weapon speed
                        if(weapontype == 251 || weapontype == 252)
                            GotRightWeapon = true; //true if we have a katar or dual swords
                        break;
                    case 118: //one hand sword attack speed
                        if(weapontype == 211)
                            GotRightWeapon = true; //true if we have a one hand sword
                        break;
                    case 119: //one hand melee weapon attack speed
                        if(weapontype == 212)
                            GotRightWeapon = true; //true if we have a one hand melee weapon
                        break;
                    case 120: //two hand sword attack speed
                        if(weapontype == 221)
                            GotRightWeapon = true; //true if we have a two hand sword
                        break;
                    case 121: //spear attack speed
                        if(weapontype == 222)
                            GotRightWeapon = true; //true if we have a spear
                        break;
                    case 122: //two hand axe attack speed
                        if(weapontype == 223)
                            GotRightWeapon = true; //true if we have an axe
                        break;
                    default:
                        break;
                }
                if(GotRightWeapon)
                {
                    if( skill->value2[j] > 0 )
                        Extra += aspeed * skill->value2[j] / 100;
                    if( skill->value1[j] > 0 )
                        Extra += skill->value1[j];
                    if(Session->codedebug) //Debug code
                    {
                        GServer->SendPM(this, "Attack speed %i added for weapon type %i. Skill ID %i",Extra,weapontype,skill->id);
                    }
                }
            }
        }
    }
    aspeed += Extra;
    if(Session->codedebug) //Debug code
    {
        GServer->SendPM(this, "Attack speed after passives %i",aspeed);
    }

    //active buffs
    if(Status->Haste_up!=0xff)
        aspeed += MagicStatus[Status->Haste_up].Value;
    if(Status->Haste_down!=0xff)
        aspeed -= MagicStatus[Status->Haste_down].Value;
    if(Session->codedebug) //Debug code
    {
        GServer->SendPM(this, "Attack speed after buffs %i",aspeed);
    }

    //cloth stats
    for(UINT i=1;i<12;i++)
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_HASTE)
            {
                aspeed += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_HASTE)
            {
                aspeed += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            //don't need gems. Covered by the stats section
            if(items[i].stats>0 && items[i].stats < 500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_HASTE)
                    aspeed += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_HASTE)
                    aspeed += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    if(Session->codedebug) //Debug code
    {
        GServer->SendPM(this, "Attack speed after cloth stats and gems %i",aspeed);
    }
    return aspeed;
}

// Return Movement Speed
unsigned int CPlayer::GetMoveSpeed( )
{
	UINT mspeed = 425;
    if(!Status->CanRun)
        Status->Stance = WALKING;
    //mspeed += UINT((Attr->Dex)*0.85);
    switch(Status->Stance)
    {
        case WALKING: //walking
            mspeed = 200;
        break;
        case 1:
        case RUNNING: // running
        {
            if( items[6].count != 0 )//Foot
            {
                UINT tspeed = GServer->EquipList[SHOE].Index[items[6].itemnum]->movespeed;
        		 mspeed += ( tspeed - 65 ) * 5;
        		 if(Session->codedebug) //Debug code
                 {
                     GServer->SendPM(this, "Move speed with shoes on %i",mspeed);
                 }
            }
            for(UINT i=0;i<12;i++)//cloth stats [from tomiz]
            {
                if( items[i].count != 0 )
                {
                    if(items[i].itemtype > 9)
                    {
                        Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                        continue;
                    }
                    if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == MOVE_SPEED)
                    {
                        mspeed += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
                    }
                    if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == MOVE_SPEED)
                    {
                        mspeed += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
                    }
                    if(Session->codedebug) //Debug code
                    {
                        GServer->SendPM(this, "Move speed %i after equipment stats for item in slot %i",mspeed,i);
                    }
                }
                if(items[i].stats > 0 && items[i].stats < 500)
                {
                    if(GServer->StatsList[items[i].stats].stat[0] == A_DASH)
                    {
                        mspeed += GServer->StatsList[items[i].stats].value[0];
                    }
                    if(GServer->StatsList[items[i].stats].stat[1] == A_DASH)
                    {
                        mspeed += GServer->StatsList[items[i].stats].value[1];
                    }
                    if(Session->codedebug) //Debug code
                    {
                        GServer->SendPM(this, "Move speed %i after adding extra/gem stats for item in slot %i",mspeed,i);
                    }
                }
            }
            if(Session->codedebug) //Debug code
            {
                GServer->SendPM(this, "Move speed %i after adding all equipped items",mspeed);
            }
			UINT Extra = 0;
            for(UINT i=0;i<30;i++)
            {
                if (pskill[i] == 0) continue;
                CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
                if( skill == NULL )
                    continue;
                for(UINT j = 0; j < 2; j++ )
                {
                    if( skill->buff[j] == sMoveSpeed || skill->buff[j] ==  sMoveSpeed2 )
                    {
                        if( skill->value2[j] > 0 )
                            Extra += mspeed * skill->value2[j] / 100;
                        if( skill->value1[j] > 0 )
                            Extra += skill->value1[j];
                    }
                }
            }
            mspeed += Extra;
            if(Session->codedebug) //Debug code
            {
                GServer->SendPM(this, "Move speed %i after adding passive skills",mspeed);
            }
            Stats->Mspd_base = mspeed;
            if(Fairy)
            {
                mspeed += 110;
                if(Session->codedebug) //Debug code
                {
                    Log( MSG_INFO, "Fairy detected. move speed + 110 %i", mspeed);
                }
            }
            if(Status->Dash_up!=0xff)
            {
                mspeed += MagicStatus[Status->Dash_up].Value;
                if(Session->codedebug) //Debug code
                {
                    GServer->SendPM(this, "Speed buff detected. amount: %i new move speed: %i",MagicStatus[Status->Dash_up].Value, mspeed);
                }
            }
            if(Status->Dash_down!=0xff)
            {
                mspeed -= MagicStatus[Status->Dash_down].Value;

                if(Session->codedebug) //Debug code
                {
                    GServer->SendPM(this, "Speed DE-buff detected. amount: %i new move speed: %i",MagicStatus[Status->Dash_down].Value, mspeed);
                }
            }

        }
        break;
        case DRIVING: //cart or gear
        {
            //Log(MSG_INFO, "player is driving");
            float m_speed = 0;
            int patType = GServer->PatList.Index[items[135].itemnum]->type;
            //if(this->items[135].itemnum > 30 && this->items[135].itemnum < 40 ) //Castle gear body
            if(patType == 512) //Castle gear body
            {
                 m_speed = 1000;
                 float mod1 = (float)GServer->PatList.Index[items[136].itemnum]->speed;
                 mod1 /= 100; //engine
                 float mod2 = (float)GServer->PatList.Index[items[137].itemnum]->speed;
                 mod2 /= 100; // legs
                 m_speed *= mod1;
                 m_speed *= mod2;
                 if(Session->codedebug) //Debug code
                 {
                     GServer->SendPM(this, "Move speed %i riding a Castle Gear",m_speed);
                 }
            }
            else if(patType == 511) //Cart body
            {
                 m_speed = 1000;
                 float mod1 = (float)GServer->PatList.Index[items[136].itemnum]->speed;
                 mod1 /= 100; //engine
                 float mod2 = (float)GServer->PatList.Index[items[137].itemnum]->speed;
                 mod2 /= 100;  //wheels
                 m_speed *= mod1;
                 m_speed *= mod2;
                 // Many accessory items give a speed boost too. Added in after the modifiers
                 if(GServer->PatList.Index[items[138].itemnum]->condition[0] == 23) // accessory
                     m_speed += (float)GServer->PatList.Index[items[138].itemnum]->modifier[0];
                 if(GServer->PatList.Index[items[138].itemnum]->condition[1] == 23) // accessory
                     m_speed += (float)GServer->PatList.Index[items[138].itemnum]->modifier[1];
                 // some frames give a speed boost too. Added in after the modifiers
                 if(GServer->PatList.Index[items[135].itemnum]->condition[0] == 23) // frame
                     m_speed += (float)GServer->PatList.Index[items[135].itemnum]->modifier[0];
                 if(GServer->PatList.Index[items[135].itemnum]->condition[1] == 23) // frame
                     m_speed += (float)GServer->PatList.Index[items[135].itemnum]->modifier[1];
                 // some engines give a speed boost too. Added in after the modifiers
                 if(GServer->PatList.Index[items[136].itemnum]->condition[0] == 23) // engine
                     m_speed += (float)GServer->PatList.Index[items[135].itemnum]->modifier[0];
                 if(GServer->PatList.Index[items[136].itemnum]->condition[1] == 23) // engine
                     m_speed += (float)GServer->PatList.Index[items[135].itemnum]->modifier[1];
                 if(Session->codedebug) //Debug code
                 {
                     GServer->SendPM(this, "Move speed %f riding a Cart",m_speed);
                 }
            }
            else
            {
                Log(MSG_ERROR,"What the heck is this character driving? it is type %i", patType);
            }
            mspeed = (int)floor(m_speed);
            if(Session->codedebug) //Debug code
            {
                GServer->SendPM(this, "Final Speed before fairy buffs added: %i", mspeed);
            }
            Stats->Mspd_base = mspeed;
            if(Fairy)
            {
                //mspeed = (unsigned int)floor(mspeed * 1.2);
                mspeed += 110;
                if(Session->codedebug) //Debug code
                {
                    GServer->SendPM(this, "Fairy detected. move speed * 1.2 %i", mspeed);
                }
            }
        }
        break;
        default:
        break;
    }
    return mspeed;
}

// Return Max HP
unsigned int CPlayer::GetMaxHP( )
{
	if (Stats->Level<1) Stats->Level=1;
	//unsigned int hpmax = (unsigned int)floor(((sqrt(Stats->Level + 20) * (Stats->Level + 5 )) * 3.5) + ((Attr->Str + Attr->Estr) << 1));
    //unsigned int hpmax1 = (unsigned int)floor((0.1555 * Stats->Level * Stats->Level) + (13.812 * Stats->Level) + 45 + ((Attr->Str + Attr->Estr) * 2));

    // Base stats for Visitor
    float multi = 2.36;
    int add1 = 26;
    int add2 = 4;
    // Now change them based on class
    switch (CharInfo->Job) {
      case  jSoldier:
        multi = 3.5;
        add1 = 20;
        add2 = 5;
      break;
      case jKnight:
        multi = 3.5;
        add1 = 28;
        add2 = 5;
      break;
      case jChampion:
        multi = 3.5;
        add1 = 22;
        add2 = 5;
      break;

      case jMuse:
        multi = 2.36;
        add1 = 26;
        add2 = 4;
      break;
      case jMage:
        multi = 2.37;
        add1 = 26;
        add2 = 5;
      break;
      case jCleric:
        multi = 2.4;
        add1 = 26;
        add2 = 7;
      break;


      case jHawker:
        multi = 2.7;
        add1 = 20;
        add2 = 5;
      break;
      case jRaider:
        multi = 3.0;
        add1 = 23;
        add2 = 5;
      break;
      case jScout:
        multi = 2.7;
        add1 = 21;
        add2 = 5;
      break;

      case jDealer:
      case jBourgeois:
      case jArtisan:
        multi = 2.7;
        add1 = 20;
        add2 = 5;
      break;
      default:
                break;
    }
    // Max HP calc from client
    UINT Extra = 0;
    UINT hpmax = (UINT)floor((( sqrt(add1 + Stats->Level) * (add2 + Stats->Level) ) * multi) + ((Attr->Str + Attr->Estr) << 1) );
    // Stat boost for second jobs
    switch( CharInfo->Job )
    {
        case 121:case 122:
        case 221:case 222:
        case 321:case 322:
        case 421:case 422:
            Extra += 300;
        break;
        default:
                break;
    }
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_MAX_HP || GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_HP )
            {
                hpmax += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_MAX_HP || GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_HP )
            {
                hpmax += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_MAX_HP || GServer->StatsList[items[i].stats].stat[0] == A_HP)
                    hpmax += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_MAX_HP || GServer->StatsList[items[i].stats].stat[0] == A_HP)
                    hpmax += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }

    // Additional hp due to pskills
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sMaxHP || skill->buff[j] ==  sMaxHP2 )
            {
                if( skill->value2[j] > 0 )
                    Extra += hpmax * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    hpmax += Extra;
    if(Fairy) hpmax = (unsigned int)floor(hpmax*1.2);
    if(Status->HP_up!=0xff)
        hpmax += MagicStatus[Status->HP_up].Value;
    if(Status->HP_down!=0xff)
        hpmax -= MagicStatus[Status->HP_down].Value;
    return hpmax;
}
// Return Max MP  [fixed by Tomiz] TODO: add cloth stat
unsigned int CPlayer::GetMaxMP( )
{

    if( Stats->Level < 0 )
        Stats->Level = 1;
    UINT maxmp = 0;
    float Mult = 0;
    int JobValue = (int)CharInfo->Job;
    switch(JobValue)
    {
        case 111:
        case 411:
        case 421:
            Mult = 4;
            JobValue = 3;
        break;
        case 122:
            Mult = 5;
            JobValue = -6;
        break;
        case 211:
            Mult = 6;
            JobValue = 0;
        break;
        case 221:
            Mult = 7;
            JobValue = -7;
        break;
        case 222:
            Mult = 6.5;
            JobValue = -4;
        break;
        case 311:
        case 321:
            Mult = 4;
            JobValue = 4; //LMA
        break;
        case 121:
        case 322:
        case 422:
            Mult = 4.5;
            JobValue = 0;
        break;
        default:
            Mult = 3;
            JobValue = 4;
        break;
    }
    maxmp = (UINT)floor((Stats->Level + JobValue) * Mult + ((Attr->Int + Attr->Eint) << 2));


    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_MAX_MP || GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_MP )
            {
                maxmp += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_MAX_MP || GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_MP )
            {
                maxmp += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_MAX_MP || GServer->StatsList[items[i].stats].stat[0] == A_MP)
                    maxmp += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_MAX_MP || GServer->StatsList[items[i].stats].stat[0] == A_MP)
                    maxmp += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }

    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sMaxMP || skill->buff[j] ==  sMaxMP2 )
            {
                if( skill->value2[j] > 0 )
                    Extra += maxmp * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    maxmp += Extra;

    if(Fairy) maxmp = (unsigned int)floor(maxmp*1.2);
    if(Status->MP_up!=0xff)
        maxmp += MagicStatus[Status->MP_up].Value;
    if(Status->MP_down!=0xff)
        maxmp -= MagicStatus[Status->MP_down].Value;

	return maxmp;
}

// Get HP Regeneration Amount
unsigned int CPlayer::GetHPRegenAmount( )
{
    UINT amount = (UINT)ceil ( Stats->MaxHP * 0.02 );
    if( Status->Stance == 1 )
        amount *= 4;
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_HP_REC_RATE)
            {
                amount += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_HP_REC_RATE)
            {
                amount += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_HP_REC_RATE )
                    amount += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_HP_REC_RATE )
                    amount += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sHPRate || skill->buff[j] ==  sHPRecovery ) // Not sure on sHPRate
            {
                if( skill->value2[j] > 0 )
                    Extra += amount * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    amount += Extra;

    return amount;
}

// Get MP Regeneration Amount
unsigned int CPlayer::GetMPRegenAmount( )
{
    UINT amount = (UINT)ceil ( Stats->MaxMP * 0.02 );
    if( Status->Stance == 1 )
        amount *= 4;
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0)
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_MP_REC_RATE)
            {
                amount += amount * GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1] / 100;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_MP_REC_RATE)
            {
                amount += amount * GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1] / 100;
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_MP_REC_RATE )
                    amount += amount * GServer->StatsList[items[i].stats].value[0] / 100;
                if(GServer->StatsList[items[i].stats].stat[1] == A_MP_REC_RATE )
                    amount += amount * GServer->StatsList[items[i].stats].value[1] / 100;
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sMPRate || skill->buff[j] == sMPRecovery )
            {
                if( skill->value2[j] > 0 )
                    Extra += amount * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    amount += Extra;
    return amount;
}

// max weight supported
unsigned int CPlayer::GetMaxWeight( )
{
    UINT weight = 0;
    //weight = ((Attr->Str + Attr->Estr) + (Attr->Str + Attr->Estr)*2) * 2 + Stats->Level+220 + (Stats->Level+220)*4;
    weight = ((Attr->Str + Attr->Estr)*6)+((Stats->Level+220)*5);
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == A_INVENTORY_CAPACITY)
            {
                weight += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == A_INVENTORY_CAPACITY)
            {
                weight += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == A_INVENTORY_CAPACITY )
                    weight += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == A_INVENTORY_CAPACITY )
                    weight += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sMaxWeight || skill->buff[j] ==  sMaxWeight2 )
            {
                if( skill->value2[j] > 0 )
                    Extra += weight * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }

    weight += Extra;
    return weight;
}

// Current weight
unsigned int CPlayer::GetCurrentWeight( )
{
    UINT weight = 0;
    for(UINT i=0;i<MAX_INVENTORY;i++)
    {
        if(items[i].itemtype < 10 && items[i].itemtype > 0)
        {
            weight += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->weight;
        }
        else
        {
            switch(items[i].itemtype)
            {
                case CONSUMIBLE:
                    weight += GServer->UseList.Index[items[i].itemnum]->weight*items[i].count;
                break;
                case JEM:
                    weight += GServer->JemList.Index[items[i].itemnum]->weight*items[i].count;
                break;
                case NATURAL:
                    weight += GServer->NaturalList.Index[items[i].itemnum]->weight*items[i].count;
                break;
                case PAT:
                    weight += GServer->PatList.Index[items[i].itemnum]->weight;
                break;
                default:
                break;
            }
        }
    }
    return weight;
}

// MP Reduction
unsigned int CPlayer::GetMPReduction( )
{
    UINT mpreduction = 0;
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if(items[i].itemtype>9)
        {
            Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
            continue;
        }
        if(items[i].count>0)
        {
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == MP_COST_RED)
            {
                mpreduction += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == MP_COST_RED)
            {
                mpreduction += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == MP_COST_RED )
                    mpreduction += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == MP_COST_RED )
                    mpreduction += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
	UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sMPSpendDecrease )
            {
                if( skill->value2[j] > 0 )
                    Extra += mpreduction * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    mpreduction += Extra;
    return mpreduction;
}

// Max summon capacity
unsigned int CPlayer::GetMaxSummonGauge( )
{
    UINT gauge = 50;
    for(UINT i=1;i<12;i++)//cloth stats [from tomiz]
    {
        if(items[i].itemtype>9)
        {
            Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
            continue;
        }
        if(items[i].count>0)
        {
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == SUMMON_GAUGE)
            {
                gauge += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == SUMMON_GAUGE)
            {
                gauge += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            }
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == MP_COST_RED )
                    gauge += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == MP_COST_RED )
                    gauge += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sExpandSummonGauge )
            {
                if( skill->value2[j] > 0 )
                    Extra += gauge * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    gauge += Extra;

    return gauge;
}

// Extra attributes [str/dex/con/cha/sen/int]
void CPlayer::GetExtraStats( )
{
    Attr->Estr = 0;
    Attr->Edex = 0;
    Attr->Eint = 0;
    Attr->Econ = 0;
    Attr->Esen = 0;
    Attr->Echa = 0;
    for(UINT i=1;i<12;i++)//cloth stats
    {
        if( items[i].count > 0 )
        {
            UINT Stat1 = GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0];
            UINT Stat2 = GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0];
            switch(Stat1)
            {
                case A_STR: Attr->Estr += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1]; break;
                case A_DEX: Attr->Edex += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1]; break;
                case A_INT: Attr->Eint += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1]; break;
                case A_CON: Attr->Econ += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1]; break;
                case A_CHA: Attr->Echa += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1]; break;
                case A_SEN: Attr->Esen += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1]; break;
                default:
                break;
            }
            switch(Stat2)
            {
                case A_STR: Attr->Estr += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1]; break;
                case A_DEX: Attr->Edex += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1]; break;
                case A_INT: Attr->Eint += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1]; break;
                case A_CON: Attr->Econ += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1]; break;
                case A_CHA: Attr->Echa += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1]; break;
                case A_SEN: Attr->Esen += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1]; break;
                default:
                break;
            }
            // Why are we doing jems and stats seperately? they are the same thing O.o
            /*if(items[i].gem != 0) // jem stats
            {
                //somehow a player had a negative value in his gem on an item. Put this code in to patch it.
                if(items[i].gem < 0 || items[i].stats < 0)
                {
                    items[i].gem = 0;
                    items[i].stats = 0;
                }

                UINT Stat1 = GServer->JemList.Index[items[i].gem]!=NULL?GServer->JemList.Index[items[i].gem]->stat1[0]:0;
                UINT Stat2 = GServer->JemList.Index[items[i].gem]!=NULL?GServer->JemList.Index[items[i].gem]->stat2[0]:0;
                switch(Stat1)
                {
                    case STRENGTH: Attr->Estr += GServer->JemList.Index[items[i].gem]->stat1[1]; break;
                    case DEXTERY: Attr->Edex += GServer->JemList.Index[items[i].gem]->stat1[1]; break;
                    case INTELIGENCE: Attr->Eint += GServer->JemList.Index[items[i].gem]->stat1[1]; break;
                    case CONCENTRATION: Attr->Econ += GServer->JemList.Index[items[i].gem]->stat1[1]; break;
                    case CHARM: Attr->Echa += GServer->JemList.Index[items[i].gem]->stat1[1]; break;
                    case SENSE: Attr->Esen += GServer->JemList.Index[items[i].gem]->stat1[1]; break;
                }
                switch(Stat2)
                {
                    case STRENGTH: Attr->Estr += GServer->JemList.Index[items[i].gem]->stat2[1]; break;
                    case DEXTERY: Attr->Edex += GServer->JemList.Index[items[i].gem]->stat2[1]; break;
                    case INTELIGENCE: Attr->Eint += GServer->JemList.Index[items[i].gem]->stat2[1]; break;
                    case CONCENTRATION: Attr->Econ += GServer->JemList.Index[items[i].gem]->stat2[1]; break;
                    case CHARM: Attr->Echa += GServer->JemList.Index[items[i].gem]->stat2[1]; break;
                    case SENSE: Attr->Esen += GServer->JemList.Index[items[i].gem]->stat2[1]; break;
                }
            } */
            if(items[i].stats != 0 && items[i].stats < 500) // this should cover all the gems too
            {
                Stat1 = GServer->StatsList[items[i].stats].stat[0];
                Stat2 = GServer->StatsList[items[i].stats].stat[1];
                switch(Stat1)
                {
                    case STRENGTH: Attr->Estr += GServer->StatsList[items[i].stats].value[0]; break;
                    case DEXTERY: Attr->Edex += GServer->StatsList[items[i].stats].value[0]; break;
                    case INTELIGENCE: Attr->Eint += GServer->StatsList[items[i].stats].value[0]; break;
                    case CONCENTRATION: Attr->Econ += GServer->StatsList[items[i].stats].value[0]; break;
                    case CHARM: Attr->Echa += GServer->StatsList[items[i].stats].value[0]; break;
                    case SENSE: Attr->Esen += GServer->StatsList[items[i].stats].value[0]; break;
                    default:
                break;
                }
                switch(Stat2)
                {
                    case STRENGTH: Attr->Estr += GServer->StatsList[items[i].stats].value[1]; break;
                    case DEXTERY: Attr->Edex += GServer->StatsList[items[i].stats].value[1]; break;
                    case INTELIGENCE: Attr->Eint += GServer->StatsList[items[i].stats].value[1]; break;
                    case CONCENTRATION: Attr->Econ += GServer->StatsList[items[i].stats].value[1]; break;
                    case CHARM: Attr->Echa += GServer->StatsList[items[i].stats].value[1]; break;
                    case SENSE: Attr->Esen += GServer->StatsList[items[i].stats].value[1]; break;
                    default:
                break;
                }
            }
        }
    }
}

float CPlayer::GetAttackDistance( )
{
    if(items[7].count==0) return (float)1;
    float AttackDistance = 0;
    AttackDistance = GServer->EquipList[WEAPON].Index[items[7].itemnum]->attackdistance/100;
    return AttackDistance;
}

// Return XPRate
unsigned int CPlayer::GetXPRate( )
{
    UINT XPRate = 0;
    if(Stats->ItemXPRate == -1)
        return 0; // sends back a rate of 0. Used for exp nulification

    for(UINT i=1;i<12;i++)
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype>9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == XP_RATE)
                XPRate += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == XP_RATE)
                XPRate += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            if(items[i].stats>0 && items[i].stats<500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == XP_RATE)
                    XPRate += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == XP_RATE)
                    XPRate += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    if(Stats->ItemXPRate != 0 && Stats->ItemXPRate != 1 && Stats->ItemXPRate != 2)
        Stats->ItemXPRate = 0;
    XPRate += Stats->ItemXPRate; // add timed XPRate buffs
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == sEXPRate )
            {
                if( skill->value2[j] > 0 )
                    Extra += XPRate * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    CMap* map = GServer->MapList.Index[Position->Map];
    
    XPRate += Extra;

    if(XPRate < 1)
        XPRate = 1;
    XPRate = XPRate * map->mapXPRate;
    //Log( MSG_INFO, "XP rate calculated as = %i", XPRate);
    Log( MSG_INFO, "XPRate: %i Map XP rate: %i for map %i",XPRate,map->mapXPRate, map->id);
    return XPRate;
}

// Return Item Drop Rate
unsigned int CPlayer::GetItemDropRate( )
{
    int itemdroprate = 0;
    for(UINT i=1;i<12;i++)
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype > 9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == 79 ) //ITEM_DROP_RATE
                itemdroprate += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == 79 ) //ITEM_DROP_RATE
                itemdroprate += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            if(items[i].stats > 0 && items[i].stats < 500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == 79 ) //ITEM_DROP_RATE
                    itemdroprate += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == 79 ) //ITEM_DROP_RATE
                    itemdroprate += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == 79 ) //sItemDropIncrease
            {
                if( skill->value2[j] > 0 )
                    Extra += itemdroprate * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    itemdroprate += Extra;
    //Log( MSG_INFO, "item drop rate calculated as = %i", itemdroprate);
    if(itemdroprate < 0)
        itemdroprate = 0;
    //itemdroprate += GServer->Config.DROP_RATE;
    //Log( MSG_INFO, "item drop rate calculated as = %i", itemdroprate);
    //Log( MSG_INFO, "Server item drop rate = %i", GServer->Config.DROP_RATE);
    return itemdroprate;
}

// Return Item Drop count increase
unsigned int CPlayer::GetItemDropCountRate( )
{
    int itemdroprate = 0;
    for(UINT i=1;i<12;i++)
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype > 9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == 63 ) //ITEM_DROP_Count RATE
                itemdroprate += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == 63 ) //ITEM_DROP_Coiunt RATE
                itemdroprate += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            if(items[i].stats > 0 && items[i].stats < 500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == 63 ) //ITEM_DROP_Count RATE
                    itemdroprate += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == 63 ) //ITEM_DROP_Count RATE
                    itemdroprate += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == 63 ) //Item drop Count rate
            {
                if( skill->value2[j] > 0 )
                    Extra += itemdroprate * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    itemdroprate += Extra;
    //Log( MSG_INFO, "item drop rate calculated as = %i", itemdroprate);
    if(itemdroprate < 0)
        itemdroprate = 0;
    //itemdroprate += GServer->Config.DROP_RATE;
    //Log( MSG_INFO, "item drop rate calculated as = %i", itemdroprate);
    //Log( MSG_INFO, "Server item drop rate = %i", GServer->Config.DROP_RATE);
    return itemdroprate;
}

// Return Zuly Drop Rate
unsigned int CPlayer::GetZulyDropRate( )
{
    int zulydroprate = 1;
    for(UINT i=1;i<12;i++)
    {
        if( items[i].count != 0 )
        {
            if(items[i].itemtype > 9)
            {
                Log(MSG_WARNING, "Char %s have equip invalid item: %i,%i", CharInfo->charname, items[i].itemtype, items[i].itemnum );
                continue;
            }
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[0] == 64 ) //ZULY_DROP_RATE
                zulydroprate += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat1[1];
            if( GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[0] == 64 ) //ZULY_DROP_RATE
                zulydroprate += GServer->EquipList[items[i].itemtype].Index[items[i].itemnum]->stat2[1];
            if(items[i].stats > 0 && items[i].stats < 500)
            {
                if(GServer->StatsList[items[i].stats].stat[0] == 64 ) //ZULY_DROP_RATE
                    zulydroprate += GServer->StatsList[items[i].stats].value[0];
                if(GServer->StatsList[items[i].stats].stat[1] == 64 ) //ZULY_DROP_RATE
                    zulydroprate += GServer->StatsList[items[i].stats].value[1];
            }
        }
    }
    UINT Extra = 0;
    for(UINT i=0;i<30;i++)
    {
        if (pskill[i] == 0)
		    continue;
        CSkills* skill = GServer->GetSkillByID( (pskill[i])+(pskilllvl[i]));
        if( skill == NULL )
            continue;
        for(UINT j = 0; j < 2; j++ )
        {
            if( skill->buff[j] == 64 ) //sItemZulyIncrease
            {
                if( skill->value2[j] > 0 )
                    Extra += zulydroprate * skill->value2[j] / 100;
                if( skill->value1[j] > 0 )
                    Extra += skill->value1[j];
            }
        }
    }
    zulydroprate += Extra;
    if(zulydroprate < 1)
        zulydroprate = 1;
    //Log( MSG_INFO, "zuly drop rate calculated as = %i", zulydroprate);
    return zulydroprate;
}




// calculate player stats
void CPlayer::SetStats( )
{
    GetExtraStats( );
    Stats->MaxHP = GetMaxHP( );
    Stats->MaxMP = GetMaxMP( );
    Stats->Attack_Power = GetAttackPower( );
    Stats->Defense = GetDefense( );
    Stats->Critical = GetCritical( );
    Stats->Move_Speed = GetMoveSpeed( );
    //Stats->Mspd_base = GetMoveSpeed(1);
    Stats->Magic_Defense = GetMagicDefense( );
    Stats->magicattack = GetMagicAttack( );
    Stats->Accury = GetAccury( );
    Stats->Dodge = GetDodge( );
    Stats->Attack_Speed = GetAttackSpeed( );
    Stats->Attack_Distance = GetAttackDistance( );
    Stats->MaxWeight = GetMaxWeight( );
    Stats->MaxSummonGauge = GetMaxSummonGauge( );
    Stats->MPReduction = GetMPReduction( );
    Stats->xprate = GetXPRate( );
    Stats->itemdroprate = GetItemDropRate( );
    Stats->itemdropcountrate = GetItemDropCountRate( );
    Stats->zulydroprate = GetZulyDropRate( );
}

