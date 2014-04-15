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

// Returns the amount of exp that is needed for the next level
UINT CPlayer::GetLevelEXP( )
{
	if (Stats->Level <= 15)       return (unsigned int)( ( Stats->Level + 10 )  * ( Stats->Level + 5 )  * ( Stats->Level + 3 ) * 0.7 );
	else if (Stats->Level <= 50)  return (unsigned int)( ( Stats->Level - 5 )   * ( Stats->Level + 2 )  * ( Stats->Level + 2 ) * 2.2 );
	else if (Stats->Level <= 100) return (unsigned int)( ( Stats->Level - 38 )  * ( Stats->Level - 5 )  * ( Stats->Level + 2 ) * 9 );
	else if (Stats->Level <= 139) return (unsigned int)( ( Stats->Level + 220 ) * ( Stats->Level + 34 ) * ( Stats->Level + 27 ) );
	else                     return (unsigned int)( ( Stats->Level - 126 ) * ( Stats->Level - 15 ) * ( Stats->Level + 7 ) * 41 );
}

// check if player can level up
bool CPlayer::CheckPlayerLevelUP( )
{
	//if(Session->Respawned == 2){Log( MSG_INFO, "Checking Levelup" );}
	if (CharInfo->Exp >= GetLevelEXP())
    {
	    //if(Session->Respawned == 2){Log( MSG_INFO, "XP >= GetLevelXP" );}
	    CharInfo->Exp -= GetLevelEXP(); //exp is subtracted anyway whether we reached max or not.
	    //check if max level has been reached
	    if(Stats->Level >= GServer->Config.MaxLevel)
	    {
	        //posibly give extra bonuses here at some point rather than just subtracting exp and returning.
	        return true; // returning true should show the levelup animation still and also set HP and MP to max
	    }
	    Stats->Level++;
	    Stats->HP = GetMaxHP( );
	    Stats->MP = GetMaxMP( );
	    CharInfo->StatPoints += int((Stats->Level*0.8)+10);
        // Proper skill point distribution for Pre-Evo
        if(Stats->Level >= 100 && (Stats->Level % 2) == 0)
        {
            // 5 skill points every 2 levels from 100
            CharInfo->SkillPoints += 5;
        }
        else if(Stats->Level > 22 && ((Stats->Level - 22) % 4) == 0)
        {
            // 5 skill points every 4 levels from 22
            CharInfo->SkillPoints += 5;
        }
        else if(Stats->Level == 22)
        {
            CharInfo->SkillPoints += 4;
        }
        else if(Stats->Level == 18)
        {
            CharInfo->SkillPoints += 3;
        }
        else if(Stats->Level == 14 || Stats->Level == 10)
        {
            CharInfo->SkillPoints += 2;
        }

		BEGINPACKET( pak, 0x79e );
		ADDWORD( pak, clientid );
		ADDWORD( pak, Stats->Level );
		ADDDWORD( pak, CharInfo->Exp );
		ADDWORD( pak, CharInfo->StatPoints );
		ADDWORD( pak, CharInfo->SkillPoints );
		client->SendPacket( &pak );

		RESETPACKET( pak, 0x79e );
		ADDWORD( pak, clientid );
		GServer->SendToVisible( &pak, this );
		SetStats( );
		savedata( );
        //SendLevelUPtoChar(this);
        return true;
	}
	//if(Session->Respawned == 2){Log( MSG_INFO, "XP < GetLevelXP" );}
	return false;
}

bool CPlayer::canUseSkill(CSkills* skill)
{

  // Check for weapon requirements
  int check = 5;
  bool fail = true;
  for (int i = 0; i < 5; i++)
  {
    if (skill->weapon[i] == 0)
    {
      check--;
      continue;
    }
    for (int j = 1; j < 12; j++) { // I'm not sure if 1 - 12 is right for all equipment?
      if (GServer->EquipList[items[j].itemtype].Index[items[j].itemnum]->type == skill->weapon[i])
      {
        fail = false;
        break;
      }
    }
    if (!fail) break;
  }
  if (fail && check)
  {
    if(Session->codedebug) //Debug code
    {
       char buffer[200];
       sprintf ( buffer, "Failed skill check @ weapons. skill = %i", skill->id);
       GServer->SendPM(this, buffer);
    }
    return false;
  }

  // Check job requirement
  fail = true;
  check = 4;
  for (char i = 0; i < 4; i++)
  {
    if (skill->c_class[i]>0)
    {
      switch(skill->c_class[i])
      {
          case cSoldierJob:
               if((CharInfo->Job)/100==1) fail = false;
               break;
          case cMuseJob:
               if((CharInfo->Job)/100==2) fail = false;
               break;
          case cHawkerJob:
               if((CharInfo->Job)/100==3) fail = false;
               break;
          case cDealerJob:
               if((CharInfo->Job)/100==4) fail = false;
               break;
          case cKnightJob:
               if(CharInfo->Job==121) fail = false;
               break;
          case cChampionJob:
               if(CharInfo->Job==122) fail = false;
               break;
          case cMageJob:
               if(CharInfo->Job==221) fail = false;
               break;
          case cClericJob:
               if(CharInfo->Job==222) fail = false;
               break;
          case cRaiderJob:
               if(CharInfo->Job==321) fail = false;
               break;
          case cScoutJob:
               if(CharInfo->Job==322) fail = false;
               break;
          case cBourgeoisJob:
               if(CharInfo->Job==421) fail = false;
               break;
          case cArtisanJob:
               if(CharInfo->Job==422) fail = false;
               break;
          default:
               break;
      }
      if (!fail) break;
    } else
      check--;
  }
  if (fail && check) {
    if(Session->codedebug) //Debug code
    {
       char buffer[200];
       sprintf ( buffer, "Failed skill check @ job. job = %i skill = %i",CharInfo->Job, skill->id);
       GServer->SendPM(this, buffer);
    }
    return false;
  }

  // Check for stat requirements
  fail = false;
  for (char i = 0; i < 2; i++)
  {
    switch (skill->req[i])
    {
      case sLevel:
        if (skill->reqam[i] > Stats->Level) fail = true;
      break;
      case sStrength:
        if (skill->reqam[i] > Attr->Str + Attr->Estr) fail = true;
      break;
      case sDexterity:
        if (skill->reqam[i] > Attr->Dex + Attr->Edex) fail = true;
      break;
      case sIntelligence:
        if (skill->reqam[i] > Attr->Int + Attr->Eint) fail = true;
      break;
      case sConcentration:
        if (skill->reqam[i] > Attr->Con + Attr->Econ) fail = true;
      break;
      case sCharm:
        if (skill->reqam[i] > Attr->Cha + Attr->Echa) fail = true;
      break;
      case sSensibility:
        if (skill->reqam[i] > Attr->Sen + Attr->Esen) fail = true;
      break;
      default:
      break;
    }
  }
  if (fail)
  {
    if(Session->codedebug) //Debug code
    {
       char buffer[200];
       sprintf ( buffer, "Failed skill check @ stats. skill = %i", skill->id);
       GServer->SendPM(this, buffer);
    }
    return false;
  }
  if(Session->codedebug) //Debug code
  {
     char buffer[200];
     sprintf ( buffer, "Skill check successful for skill = %i", skill->id);
     GServer->SendPM(this, buffer);
  }
  // Passed all the tests, can cast skill
  return true;
}


// Send a PM to client with user information
bool CPlayer::GetPlayerInfo( )
{
    char text[50];
    sprintf(text,"Attack: %i | Critical: %i",Stats->Attack_Power, Stats->Critical );
	BEGINPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    sprintf(text,"Defense: %i | Magic Defense: %i",Stats->Defense, Stats->Magic_Defense);
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    sprintf(text,"Accury: %i | Dodge: %i",Stats->Accury,Stats->Dodge );
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    sprintf(text,"aspeed: %i | mspeed: %i",Stats->Attack_Speed,Stats->Move_Speed );
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    sprintf(text,"HP: %i/%i , MP: %i/%i",Stats->HP,Stats->MaxHP,Stats->MP,Stats->MaxMP);
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    sprintf(text,"Position[%i]: (%.0f,%.0f)",Position->Map,Position->current.x,Position->current.y);
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    sprintf(text,"ClientID: %u | CharID: %u", clientid, CharInfo->charid );
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    sprintf(text,"inGame: %i | Logged: %i", Session->inGame, Session->isLoggedIn );
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    sprintf(text,"ClanName[%u]: %s | ClanGrade: %i | ClanRank: %i", Clan->clanid, Clan->clanname, Clan->grade, Clan->clanrank );
	RESETPACKET( pak, 0x0784 );
	ADDSTRING( pak, "[GM]PlayerInfo" );
	ADDBYTE( pak, 0 );
	ADDSTRING( pak, text );
	ADDBYTE( pak, 0 );
	client->SendPacket(&pak);
    return true;
}

// clearn player lists
bool CPlayer::CleanPlayerVector( )
{
    CMap* map = GServer->MapList.Index[Position->Map];
    VisiblePlayers.clear();
	VisibleMonsters.clear();
	VisibleDrops.clear();
	VisibleNPCs.clear();
	return true;
}

// update visibility list
bool CPlayer::VisiblityList( )
{
     if(!this->Session->inGame) return true;
	std::vector<CPlayer*>	newVisiblePlayers;
	std::vector<CDrop*>			newVisibleDrops;
	std::vector<unsigned int>		newVisibleMonsters;
	std::vector<CNPC*>			newVisibleNPCs;
	// Clients
	CMap* map = GServer->MapList.Index[Position->Map];
    for(UINT i=0;i<map->PlayerList.size();i++)
    {
        CPlayer* otherclient = map->PlayerList.at(i);
        if(otherclient == NULL)
            continue;
		if ( this == otherclient || !otherclient->Session->inGame)
		{
            continue;
        }
		float distance = GServer->distance( this->Position->current, otherclient->Position->current );
		if ( GServer->IsVisible( this, otherclient ) )
        {
			if ( distance < MAXVISUALRANGE && !otherclient->isInvisibleMode )
			{
				newVisiblePlayers.push_back( otherclient );
            }
			else
			{
				ClearObject( otherclient->clientid );
            }
		}
        else
        {
			if ( distance < MINVISUALRANGE && !otherclient->isInvisibleMode )
            {
			    newVisiblePlayers.push_back( otherclient );
				otherclient->SpawnToPlayer(this, otherclient);
			}
        }
	}
    // Monsters
    for(UINT i=0;i<map->MonsterList.size();i++)
    {
        CMonster* thismon = map->MonsterList.at( i );
        if(thismon == NULL)
            continue;
		float distance = GServer->distance ( this->Position->current, thismon->Position->current );
		if ( GServer->IsVisible( this, thismon ) )
        {
			if (distance < MAXVISUALRANGE )
			{
                newVisibleMonsters.push_back( thismon->clientid);
            }
			else
			{
				ClearObject( thismon->clientid );
            }
		}
        else
        {
			if ( distance< MINVISUALRANGE )
            {
				newVisibleMonsters.push_back( thismon->clientid);
				thismon->SpawnMonster(this, thismon );
            }
		}
	}
	// Drops
	for(unsigned i=0; i<map->DropsList.size(); i++)
    {
		CDrop* thisdrop = map->DropsList.at(i);
		if(thisdrop == NULL)
		    continue;
        if( time(NULL) - thisdrop->droptime <= GServer->Config.DropDelay )
            continue;
		float distance = GServer->distance( this->Position->current, thisdrop->pos );
		if ( GServer->IsVisible( this, thisdrop ) )
        {
			if ( distance< MAXVISUALRANGE )
			{
				newVisibleDrops.push_back( thisdrop );
            }
			else
			{
				this->ClearObject( thisdrop->clientid );
            }
		}
        else
        {
			if ( distance < MINVISUALRANGE )
            {
                thisdrop->spawned = true;
                newVisibleDrops.push_back( thisdrop );
				GServer->pakSpawnDrop( this, thisdrop );
			}
		}
	}
	// Npcs
	for(unsigned i=0; i<map->NPCList.size(); i++)
    {
		CNPC* thisnpc = map->NPCList.at(i);
		float distance = GServer->distance( this->Position->current, thisnpc->pos );
		if ( GServer->IsVisible( this, thisnpc ) )
        {
			if ( distance < MAXVISUALRANGE )
            {
				newVisibleNPCs.push_back( thisnpc );
            }
			else
			{
        		this->ClearObject( thisnpc->clientid );
            }
		}
        else
        {
			if ( distance < MINVISUALRANGE )
            {
				newVisibleNPCs.push_back( thisnpc );
				GServer->pakSpawnNPC( this, thisnpc );
			}
		}
	}
	VisiblePlayers.clear();
	VisibleDrops.clear();
	VisibleMonsters.clear();
	VisibleNPCs.clear();
	VisiblePlayers = newVisiblePlayers;
	VisibleDrops = newVisibleDrops;
	VisibleMonsters = newVisibleMonsters;
	VisibleNPCs = newVisibleNPCs;
    return true;

}

bool CPlayer::ChangeDialog(unsigned int npc, unsigned int dialog, unsigned int eventid )
{
    CMap* map = GServer->MapList.Index[Position->Map];
    if(map == NULL)
        return true;
    for(unsigned i=0; i<map->NPCList.size(); i++)
    {
        CNPC* thisnpc = map->NPCList.at(i);

        if(thisnpc->npctype == npc)
        {
            //Log(MSG_INFO,"Found NPC %i with dialog %i",thisnpc->npctype, thisnpc->thisnpc->dialogid);
            CNPC* newnpc = thisnpc;
            this->ClearObject( thisnpc->clientid );
            newnpc->thisnpc->dialogid = dialog;
            newnpc->thisnpc->eventid = eventid;
            GServer->ObjVar[npc][0] = eventid;
            VisibleNPCs.push_back( newnpc );
            GServer->pakSpawnNPC( this, newnpc );
        }
    }
    return true;
}


// Returns a free slot in the inventory (0xffff if is full)
UINT CPlayer::GetNewItemSlot( CItem thisitem )
{
    UINT tabsize = 30;
    UINT itemtab = 0;
    switch(thisitem.itemtype)
    {
        case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9://equip
            itemtab = 0;
        break;
        case 10://consumibles
            itemtab = 1;
        break;
        case 11:case 12://etc
            itemtab = 2;
        break;
        case 14://pat
            itemtab = 3;
        break;
        default:
            Log(MSG_WARNING,"unknown itemtype %i", thisitem.itemtype);
            return 0xffff;
         break;
    }
    //useitems and natural
    //first we try to find a slot that already contains some of this item
    //this way the items will always stack if possible.
    if(itemtab == 1 || itemtab == 2)
    {
        for(int i=0;i<30;i++)
        {
            UINT slot=12;
            slot += (tabsize*itemtab)+i;
            if(items[slot].itemnum == thisitem.itemnum && items[slot].itemtype == thisitem.itemtype)
            {
                int totcount = thisitem.count + items[slot].count;
                if(totcount < 1000)
                    return slot;
            }
        }
    }
    //now scan again to find a fully empty slot for mats, useitems and equipable stuff
    //doesn't matter what tab type
    for(int i=0;i<30;i++)
    {
        UINT slot=12;
        slot += (tabsize*itemtab)+i;
        if(items[slot].itemnum==0 &items[slot].count<1)
            return slot;
    }
	return 0xffff;
}

//count storage items
unsigned int CPlayer::Getnstorageitems( CPlayer* thisclient )
{
    UINT count = 0;
    for(UINT i=0;i<160;i++)
    {
        if(thisclient->storageitems[i].count > 0)
            count++;
    }
    return count;
}

// Returns a free slot in the storage (0xffff if is full)
UINT CPlayer::GetNewStorageItemSlot( CItem thisitem )
{
    //first check for a slot that already contains this item if it is stackable
    if(thisitem.itemtype == 10 || thisitem.itemtype == 11 || thisitem.itemtype == 12)
        {
        for(UINT i=0;i<144;i++)
        {
            if(storageitems[i].itemtype == thisitem.itemtype && storageitems[i].itemnum == thisitem.itemnum)
            {
                //now we make sure that the total of the new items plus the ones already there do not exceed 999
                int totalcount = storageitems[i].count + thisitem.count;
                if(totalcount < 1000)
                {
                    return i;
                }
            }
        }
    }
    //so we couldn't find a matching entry to stack onto
    //or the item is unstackable
    //Let's look for an empty slot instead then
    for(UINT i=0;i<144;i++)
    {
        if(storageitems[i].itemtype == 0)
        {

            return i;
        }
    }
	return 0xffff;
}

// Erase a object from the user
bool CPlayer::ClearObject( unsigned int otherclientid )
{
	BEGINPACKET( pak, 0x794 );
	ADDWORD( pak, otherclientid );
	client->SendPacket( &pak );
	return true;
}

// Clean the player values
void CPlayer::RestartPlayerVal( )
{
    ClearBattle( Battle );
    Shop->open = false;
    Trade->trade_target = 0;
    Trade->trade_status = 0;
}

int CPlayer::GetQuestVar(short nVarType, short nVarNO){
  switch(nVarType){
    case 0:
    {
      SQuest* activeQuest = GetActiveQuest();
      if(activeQuest == NULL) return -1;
      return activeQuest->Variables[nVarNO];
    }
    case 0x100:
    {
      SQuest* activeQuest = GetActiveQuest();
      if(activeQuest == NULL) return -1;
      return activeQuest->GetSwitchBit(nVarNO);
    }
    case 0x200://Remaining time
      Log(MSG_DEBUG, "GetQuestVar got remaining quest time");
      return 1;
    case 0x300:
      if(nVarNO >= 5) return -1;
      return quest.EpisodeVar[nVarNO];
    case 0x400:
      if(nVarNO >= 3) return -1;
      return quest.JobVar[nVarNO];
    case 0x500:
      if(nVarNO >= 7) return -1;
      return quest.PlanetVar[nVarNO];
    case 0x600:
      if(nVarNO >= 10) return -1;
      return quest.UnionVar[nVarNO];
    default:
        break;
  }
  return -1;
}

void CPlayer::SetQuestVar(short nVarType, short nVarNO, short nValue){
  switch(nVarType){
    case 0:
    {
      SQuest* activeQuest = GetActiveQuest();
      if(activeQuest == NULL) return;
      activeQuest->Variables[nVarNO] = nValue;
    }
    return;
    case 0x100:
    {
      SQuest* activeQuest = GetActiveQuest();
      if(activeQuest == NULL) return;
      activeQuest->SetSwitchBit(nVarNO, nValue);
    }
    return;
    case 0x300:
      if(nVarNO >= 5) return;
      quest.EpisodeVar[nVarNO] = nValue;
      return;
    case 0x400:
      if(nVarNO >= 3) return;
      quest.JobVar[nVarNO] = nValue;
      return;
    case 0x500:
      if(nVarNO >= 7) return;
      quest.PlanetVar[nVarNO] = nValue;
      return;
    case 0x600:
      if(nVarNO >= 10) return;
      quest.UnionVar[nVarNO] = nValue;
      return;
    default:
    break;
  }
}


int CPlayer::ExecuteQuestTrigger(dword hash)
{
    CQuestTrigger* trigger = NULL;
    CQuestTrigger* nexttrigger = NULL;
    CheckQuest = -1;
    for(unsigned j=0; j < GServer->TriggerList.size(); j++)
    {
        if (GServer->TriggerList.at(j)->TriggerHash == hash)
        {
            trigger = GServer->TriggerList.at(j);
            nexttrigger = GServer->TriggerList.at(j + 1);
            break;
        }
    }
    if (trigger == NULL) return QUEST_FAILURE;

    int success = QUEST_SUCCESS;
    //Log(MSG_DEBUG, "Trigger Executed: %s [%i] hash %i", trigger->TriggerName, trigger->CheckNext, hash);
    if(Session->codedebug)GServer->SendPM(this, "Trigger executed %s[%i]", trigger->TriggerName, trigger->CheckNext);
    for (dword i = 0; i < trigger->ConditionCount; i++)
    {
        int command = trigger->Conditions[i]->opcode;

        if (command > 30 || command < 0) continue;
        success = (*GServer->qstCondFunc[command])(GServer, this, trigger->Conditions[i]->data);
        //Log(MSG_DEBUG, "Condition %03u returned %d", command, success);
        if(Session->codedebug)GServer->SendPM(this, "Condition %03u returned %d", command, success);
        if (success == QUEST_FAILURE)
	    {
            if (!trigger->CheckNext)
		        return success;
            else return ExecuteQuestTrigger(nexttrigger->TriggerHash);
        }
    }
    for (dword i = 0; i < trigger->ActionCount; i++)
    {
        int command = trigger->Actions[i]->opcode;
        if(Session->codedebug)GServer->SendPM(this, "command %03u", command);
        if (command > 30 || command < 0) continue;
        if(Session->codedebug)GServer->SendPM(this, "Still good after command value check");
        success = (*GServer->qstRewdFunc[command])(GServer, this, trigger->Actions[i]->data);
        if(Session->codedebug)GServer->SendPM(this, "reward %03u returned %d", command, success);
        //Log(MSG_DEBUG, "Reward %03u returned %d", command, success);
    }
    return success;
}


// HP/MP Regeneration Function
bool CPlayer::Regeneration()
{
    if (Stats->MaxHP == Stats->HP && Stats->MaxMP == Stats->MP)
    {
       lastRegenTime = 0;
       return true;
    }

    bool is_first_regen = false;
    if (lastRegenTime == 0)
    {
       is_first_regen = true;
    }

    clock_t etime = clock() - lastRegenTime;
    if( etime >= 8 * CLOCKS_PER_SEC && Stats->HP > 0 )
    {
        //Log(MSG_INFO,"Regeneration function. Character %i HP on entry %i", clientid, Stats->HP);
        unsigned int hpamount = GetHPRegenAmount( );
        unsigned int mpamount = GetMPRegenAmount( );
        //if(stance = SITTING)
        //{
        //    hpamount = hpamount * 4;
        //    mpamount = mpamount * 4
        //}
        Stats->HP += hpamount;
        Stats->MP += mpamount;
        if( Stats->HP > Stats->MaxHP)
            Stats->HP = Stats->MaxHP;
        if( Stats->MP > Stats->MaxMP )
            Stats->MP = Stats->MaxMP;
        BEGINPACKET( pak, 0x7ec );
	    ADDWORD( pak, Stats->HP);
	    ADDWORD( pak, Stats->MP );
	    client->SendPacket( &pak );

        if (Stats->MaxHP == Stats->HP && Stats->MaxMP == Stats->MP)
           lastRegenTime = 0;
        else
            lastRegenTime = clock();
        //Log(MSG_INFO,"Regeneration function. Character %i HP on exit %i clock time %i", clientid, Stats->HP, lastRegenTime);
    }
    return true;
}


// Heal Player when use Food/Pots
bool CPlayer::PlayerHeal()
{
    clock_t transtime = clock() - UsedItem->lastRegTime;
    if( UsedItem->usevalue != 0 && transtime >= 0.3 * CLOCKS_PER_SEC )
    {
        if( UsedItem->used < UsedItem->usevalue && Stats->HP > 0 )
        {
            int value = UsedItem->userate;
            if((UsedItem->usevalue - UsedItem->used) < value)
            {
                value = UsedItem->usevalue - UsedItem->used;
            }
            switch( UsedItem->usetype )
            {
                case 16: // HP
                    Stats->HP += value;
                    if(Stats->HP > Stats->MaxHP)
                        Stats->HP = Stats->MaxHP;
                break;
                case 17: // MP
                    Stats->MP += value;
                    if(Stats->MP > Stats->MaxMP)
                        Stats->MP = Stats->MaxMP;
                break;
                case 37: // Skill points
                    CharInfo->SkillPoints += value;
                break;
                case 76: //Stamina
                    CharInfo->stamina += value;
                    if(CharInfo->stamina > 5000)
                        CharInfo->stamina = 5000;
                break;
                default:
                break;
            }
            UsedItem->used += value;
            UsedItem->lastRegTime = clock();
        }
        else
        {
            BEGINPACKET( pak,0x7b7 );
            ADDWORD    ( pak, clientid );
            ADDDWORD   ( pak, GServer->BuildBuffs( this ) );
            switch( UsedItem->usetype )
            {
                case 16: // HP
                    ADDWORD( pak, Stats->HP );
                break;
                case 17: // MP
                    ADDWORD( pak, Stats->MP );
                break;
                case 37: //Skill Points
                    ADDWORD( pak, CharInfo->SkillPoints );
                break;
                case 76: //Stamina
                    ADDWORD( pak, CharInfo->stamina );
                break;
                default:
                break;
            }
            GServer->SendToVisible( &pak, this );
            UsedItem->used = 0;
            UsedItem->usevalue = 0;
            UsedItem->userate = 0;
            UsedItem->usetype = 0;
        }
        BEGINPACKET( pak, 0x7ec );
        ADDWORD( pak, Stats->HP);
        ADDWORD( pak, Stats->MP );
        client->SendPacket( &pak );
    }
    return true;
}

void CPlayer::ReduceABC( )
{
    unsigned int weapontype = 0;
    weapontype = GServer->EquipList[WEAPON].Index[items[7].itemnum]->type;
    switch(weapontype)
    {
        case 231:
            items[132].count--;
            if(items[132].count<=0)
            {
                ClearBattle( Battle );
                ClearItem( items[132] );
            }
        break;
        case 232:
            items[133].count--;
            if(items[133].count<=0)
            {
                ClearBattle( Battle );
                ClearItem( items[133] );
            }
        break;
        case 233:
            items[134].count--;
            if(items[134].count<=0)
            {
                ClearBattle( Battle );
                ClearItem( items[134] );
            }
        break;
        case 271:
            items[132].count--;
            if(items[132].count<=0)
            {
                ClearBattle( Battle );
                ClearItem( items[135] );
            }
        break;
        default:
        break;
    }
}

SQuest* CPlayer::GetActiveQuest( )
{
    for(dword i = 0; i < 10; i++){
      if(quest.quests[i].QuestID != ActiveQuest) continue;
      return &quest.quests[i];
    }
    return NULL;
}

// return party pointer
CParty* CPlayer::GetParty( )
{
    return Party->party;
}

CLAN* CPlayer::GetClan( )
{
  return Clan;
}
// return intelligence
unsigned int CPlayer::GetInt( )
{
    return Attr->Int + Attr->Eint;

}

// add item [return item slot [0xffff if couldn't add it]]
unsigned int CPlayer::AddItem( CItem item )
{
    unsigned int newslot = 0;
    newslot = GetNewItemSlot( item );
    if(newslot != 0xffff)
    {
        if(items[newslot].count > 0)
        {
            unsigned int ntcount = item.count;
            unsigned int utcount = items[newslot].count;
            if(ntcount + utcount > 999)
            {
                item.count = ntcount + utcount - 999;
                items[newslot].count = 999;
                unsigned int otherslot = GetNewItemSlot( item );
                if(otherslot != 0xffff)
                {
                    if(items[otherslot].count != 0) items[otherslot].count += item.count;
                    else items[otherslot] = item;
                    return newslot * 1000 + otherslot;
                }
                else
                {
                    items[newslot].count = utcount;
                    return 0xffff; //not inventory space
                }
            }
            else items[newslot].count = ntcount + utcount;
        }
        else items[newslot] = item;
    }
    return newslot;
}

void CPlayer::UpdateInventory( unsigned int slot1, unsigned int slot2 )
{

    if(slot1 == 0xffff && slot2 == 0xffff) return;              //neither slot is valid
    BEGINPACKET( pak, 0x718 );
    if(slot1 != 0xffff && slot2 != 0xffff) {ADDBYTE( pak, 2 );} //both slots are valid
    else {ADDBYTE( pak, 1 );}                                   //one of the slots is valid
    if(slot1 != 0xffff)
    {
        ADDBYTE    ( pak, slot1);
        ADDWORD    ( pak, GServer->BuildItemHead( items[slot1] ) );
        ADDDWORD   ( pak, GServer->BuildItemData( items[slot1] ) );
    }
    if(slot2 != 0xffff)
    {
        ADDBYTE    ( pak, slot2 );
        ADDWORD    ( pak, GServer->BuildItemHead( items[slot2] ) );
        ADDDWORD   ( pak, GServer->BuildItemData( items[slot2] ) );
    }
    client->SendPacket( &pak );

}

void CPlayer::takeSkillCost( CSkills* skill) {
  for (int i = 0; i < 2; i++)
  {
    if (skill->costtype[i] == 0) continue;
    Log(MSG_INFO, "Skill cost: %i", skill->costamount[i]);
    switch (skill->costtype[i])
	{
      case sHP:
        Stats->HP -= skill->costamount[i];
      break;
      case sMP:
        Stats->MP -= (skill->costamount[i] - (skill->costamount[i] * Stats->MPReduction / 100));
        Log(MSG_INFO, "MP: %i", Stats->MP);
      break;
      case sMoney:
        CharInfo->Zulies -= skill->costamount[i];
      break;
      case sStamina:
        CharInfo->stamina -= skill->costamount[i];
      break;
      case sCartGauge:
        Log(MSG_INFO, "Couldn't take CartGauge, no variable");
      break;
      default:
      break;
    }
  }
}
