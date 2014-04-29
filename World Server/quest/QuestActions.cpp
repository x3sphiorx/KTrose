// Props to ExJam for this code :D Ported to OSpRose by Drakia
#include "../WorldServer.h"

dword GetRewardValue(dword function, dword amount, CPlayer* client, word nDupCNT)
{
	switch(function)
    {
		case 0:
		{
			dword tempVal = amount + 0x1E;
            tempVal *= client->Attr->Cha + 0x0a; // We need to add a way to get all stats totals (Including buff, E, etc) - Drakia
			tempVal *= (100 & 0xFFFF);//World Rate
			tempVal *= 0x14;//Fame + 0x14
			tempVal = ((tempVal / (client->Stats->Level + 0x46)) / 0x7530) + amount;
			return tempVal;
		}
		break;
		case 1:
		{
			dword tempVal = (client->Stats->Level + 3) * amount;
			tempVal *= (client->Attr->Cha >> 1) + client->Stats->Level + 0x28;
			tempVal *= (100 & 0xFFFF);//World Rate
			return tempVal / 0x2710;
		}
		break;
		case 2:
			return (amount * nDupCNT);
		break;
		case 3:
		case 5:
		{
			dword tempVal = amount + 0x14;
			tempVal *= client->Attr->Cha + 0x0a;
			tempVal *= (100 & 0xFFFF);//World Rate
			tempVal *= 0x14;//Fame + 0x14
			tempVal = ((tempVal / (client->Stats->Level + 0x46)) / 0x7530) + amount;
			return tempVal;
		}
		break;
		case 4:
		{
			dword tempVal = amount + 0x2;
			tempVal *= (client->Attr->Cha + client->Stats->Level + 0x28);
			tempVal *= 0x28;//Fame + 0x28
			tempVal *= (100 & 0xFFFF);//World Rate
			return tempVal / 0x222E0;
		}
		break;
		case 6:
		{
			dword tempVal = amount + 0x14;
			tempVal *= client->Attr->Cha + client->Stats->Level;
			tempVal *= 0x14;//Fame + 0x14
			tempVal *= (100 & 0xFFFF);//World Rate
			return (tempVal / 0x2DC6C0) + amount;
		}
		break;
		default:
                break;
	}
	return amount;
}

//Update Quest
QUESTREWD(000)
{
	//dword iQuestSN        pos 0x00
	//byte btOp             pos 0x04
    GETREWDDATA(000);
	switch(data->btOp)//0 remove, 1 start, 2 replace quest keep items, 3 replace quest delete items, 4 select
	{
        case 0:
		{
            if( client->questdebug )
                server->SendPM(client, "Remove Quest: %u", data->iQuestSN);
            if (client->ActiveQuest == data->iQuestSN) client->ActiveQuest = 0;
			for(dword i = 0; i < 10; i++)
            {
				if(client->quest.quests[i].QuestID != data->iQuestSN) continue;
    			memset(&client->quest.quests[i], 0, sizeof(SQuest));
    			break;
 			}
        }
		break;
		case 1:
		{
            if( client->questdebug )
                server->SendPM(client, "Start Quest: %u", data->iQuestSN);
			for(dword i = 0; i < 10; i++)
            {
			    if(client->quest.quests[i].QuestID == data->iQuestSN) return QUEST_SUCCESS;
				if(client->quest.quests[i].QuestID != 0) continue;
				memset(&client->quest.quests[i], 0, sizeof(SQuest));
				client->quest.quests[i].QuestID = data->iQuestSN;
				client->quest.quests[i].StartTime = time(NULL);
				break;
			}
			client->ActiveQuest = data->iQuestSN;
		}
		break;
		case 2:
		{
            if( client->questdebug )
                server->SendPM(client, "Replace Quest, keep items: %u", data->iQuestSN);
			for(dword i = 0; i < 10; i++)
            {
				if(client->quest.quests[i].QuestID != client->ActiveQuest) continue;
				client->quest.quests[i].QuestID = data->iQuestSN;
				client->quest.quests[i].StartTime = time(NULL);
				break;
            }
			client->ActiveQuest = data->iQuestSN;
		}
		break;
		case 3:
		{
            if( client->questdebug )
                server->SendPM(client, "Replace Quest, delete items: %u", data->iQuestSN);
			for(dword i = 0; i < 10; i++)
            {
				if(client->quest.quests[i].QuestID != client->ActiveQuest) continue;
				memset(&client->quest.quests[i], 0, sizeof(SQuest));
				client->quest.quests[i].QuestID = data->iQuestSN;
				client->quest.quests[i].StartTime = time(NULL);
				break;
            }
			client->ActiveQuest = data->iQuestSN;
		}
		break;
		case 4:
		{
            if( client->questdebug )
                server->SendPM(client, "Select Quest: %u", data->iQuestSN);
			client->ActiveQuest = data->iQuestSN;
		}
		break;
		default:
                break;
	}
	return QUEST_SUCCESS;
}

//Update Quest Items
QUESTREWD(001)
{
    //dword uiItemSN;    pos 0x00
	//byte btOp;         pos 0x04
	//word nDupCNT;      pos 0x06
	//byte btPartyOpt;   pos 0x0a
    GETREWDDATA(001);
    if( client->questdebug )server->SendPM(client, "Update Quest Item (uiItemSN: %u btOp: %u nDupCNT: %u)", data->uiItemSN, data->btOp, data->nDupCNT);
	CItem tmpItem;
	tmpItem.itemtype = data->uiItemSN / 1000;
	tmpItem.itemnum = data->uiItemSN % 1000;
	tmpItem.count = data->nDupCNT;

	SQuest* curQuest = client->GetActiveQuest();
	if(curQuest == NULL)
    {
	    //Log(MSG_DEBUG, "Couldn't find active quest, wtf? Id %u", client->ActiveQuest);
	    return QUEST_FAILURE;
    }
	curQuest->AddItem(&tmpItem, data->btOp);
    return QUEST_SUCCESS;
}

//Set Quest Variable
QUESTREWD(002)
{
    GETREWDDATA(002);
    //dword iDataCnt;    pos 0x00
	//dword iType;       pos 0x04 union. This or
	//short m_mVarNo     pos 0x04 this +
	//word m_wVarTYPE;   pos 0x06                Type of quest variable
                                                 //   0  GetVarType = "ActiveQuest"
                                                 //   16  GetVarType = "SwitchBit"
                                                 //   32  GetVarType = "Remaining Time"
                                                 //   48  GetVarType = "EpisodeVar"
                                                 //   64  GetVarType = "JobVar"
                                                 //   80  GetVarType = "PlanetVar"
                                                 //   96  GetVarType = "UnionVar"
	//word nValue;       pos 0x08
	//byte btOp;         pos 0x0a

	for(dword i = 0; i < data->iDataCnt; i++)
    {
		dword address = i * sizeof(STR_QUEST_DATA);
		address += (dword)data;
		address += 4;
		STR_QUEST_DATA* curQst = (STR_QUEST_DATA*)address;
        if( client->questdebug )
            server->SendPM(client, "Set quest var[%#04x][%i] - %i (Op: %i)", curQst->m_wVarTYPE, curQst->m_wVarNO, curQst->nValue, curQst->btOp );
        word nValue = curQst->nValue;
		word tempValue = client->GetQuestVar(curQst->m_wVarTYPE, curQst->m_wVarNO);
		OperateValues<word>(curQst->btOp, &tempValue, curQst->nValue);
		client->SetQuestVar(curQst->m_wVarTYPE, curQst->m_wVarNO, tempValue);
    }
	return QUEST_SUCCESS;
}

//Update Stats
QUESTREWD(003)
{
	GETREWDDATA(003);
	//dword iDataCnt;              pos 0x00
	//dword iType;                 pos 0x04
	//dword iValue;                pos 0x08
	//byte btOp;                   pos 0x0c
	for(dword i = 0; i < data->iDataCnt; i++)
    {
		//dword address = i * 0x0C;
		//address += (dword)data;
		//address += 4;
		//STR_ABIL_DATA* curAbil = (STR_ABIL_DATA*)address;
        if( client->questdebug )
            server->SendPM(client, "Update stat[%i] %i (Op: %i)", data->iType, data->iValue, data->btOp);
        switch( data->iType )
		{
		    case 2: //Gender
            {
			    if(!OperateValues<int>(data->btOp, (int*)&client->CharInfo->Sex, data->iValue))
				    return QUEST_FAILURE;
				//client->CharInfo->Sex = data->iValue;
                //BEGINPACKET( pak, 0x720 );
                //ADDWORD( pak, 2 );
                //ADDWORD( pak, client->CharInfo->Sex );
                //ADDWORD( pak, 0 );
                //GServer->SendToVisible( &pak, client );
                //client->client->SendPacket( &pak );
                //RESETPACKET( pak, 0x0730 );
                //ADDWORD( pak, 5 );
                //ADDWORD( pak, 0xa24d );
                //ADDWORD( pak, 0x40b3 );
               	//GServer->SendToVisible( &pak, client );
                //client->client->SendPacket( &pak );
                client->quicksave();
            }
			break;
		    case 4: //job
		    {
			    if(!OperateValues<int>(data->btOp, (int*)&client->CharInfo->Job, data->iValue))
				    return QUEST_FAILURE;
			    BEGINPACKET(pak, 0x721 );
			    ADDWORD(pak, data->iType );
			    ADDDWORD(pak, data->iValue );
			    client->client->SendPacket( &pak );
			    client->quicksave();
		    }
			break;
		    case 5: //union
            {
			    if (!OperateValues<int>(data->btOp, (int*)&client->Union_s->unionvar[0], data->iValue))
                    return QUEST_FAILURE;
                BEGINPACKET(pak, 0x721 );
                ADDWORD(pak, data->iType );
                ADDDWORD(pak, data->iValue );
                client->client->SendPacket( &pak );
                client->quicksave();
                //Log(MSG_DEBUG,"Client Union changed");
            }
			break;
			case 8: // face
			{
                if (!OperateValues<int>(data->btOp, (int*)&client->CharInfo->Face, data->iValue))
                    return QUEST_FAILURE;
                BEGINPACKET(pak, 0x721);
                ADDWORD(pak, 8);
                ADDWORD(pak, client->CharInfo->Face);
                ADDWORD(pak, 0);
                GServer->SendToVisible( &pak, client );
                //client->client->SendPacket(&pak);
                RESETPACKET(pak, 0x0730);
                ADDWORD(pak, 5);
                ADDWORD(pak, 0xa24d);
                ADDWORD(pak, 0x40b3);
                GServer->SendToVisible( &pak, client );
                //client->client->SendPacket(&pak);
                client->quicksave();
            }
            break;
            case 9: // Hair
            {
                if (!OperateValues<int>(data->btOp, (int*)&client->CharInfo->Hair, data->iValue))
                    return QUEST_FAILURE;
                BEGINPACKET(pak, 0x721);
                ADDWORD(pak, 9);
                ADDWORD(pak, client->CharInfo->Hair);
                ADDWORD(pak, 0);
                GServer->SendToVisible( &pak, client );
                //client->client->SendPacket(&pak);
                RESETPACKET(pak, 0x0730);
                ADDWORD(pak, 5);
                ADDWORD(pak, 0xa24d);
                ADDWORD(pak, 0x40b3);
                GServer->SendToVisible( &pak, client );
                //client->client->SendPacket(&pak);
                client->quicksave();
            }
			case 81: // Union points for junon order
            case 82:
            case 83: // Union points for righteous crusaders
            case 84:
            case 85:
            case 86:
            case 87: // Union 7 points used for tracking previous memberships
            case 88:
            case 89: //kuro-Tejina Union points
            case 90:
            {
                if (!OperateValues<int>(data->btOp, (int*)&client->Union_s->unionvar[data->iType - 80], data->iValue))
                    return QUEST_FAILURE;
                BEGINPACKET(pak, 0x720 );
                ADDWORD(pak, data->iType );
                ADDDWORD(pak, data->iValue );
                client->client->SendPacket( &pak );

                if(data->iType == 89) //update the database if the quest just gave KTPoints
                {
                    GServer->DB->QExecute("UPDATE accounts SET ktpoints=%i WHERE id=%i AND password='%s'",
                        client->Session->KTPoints,client->Session->userid, client->Session->password);
                }
            }
            break;
		    case 10: //strength
			    if(!OperateValues<int>(data->btOp, (int*)&client->Attr->Str, data->iValue))
				    return QUEST_FAILURE;
			break;
		    case 11: //dexterity
			    if(!OperateValues<int>(data->btOp, (int*)&client->Attr->Dex, data->iValue))
				    return QUEST_FAILURE;
			break;
		    case 12: //inteligence
			    if(!OperateValues<int>(data->btOp, (int*)&client->Attr->Int, data->iValue))
				    return QUEST_FAILURE;
			break;
		    case 13: //concentration
			    if(!OperateValues<int>(data->btOp, (int*)&client->Attr->Con, data->iValue))
				    return QUEST_FAILURE;
			break;
		    case 14: //charm
			    if(!OperateValues<int>(data->btOp, (int*)&client->Attr->Cha, data->iValue))
				    return QUEST_FAILURE;
			break;
		    case 15: //sense
			    if(!OperateValues<int>(data->btOp, (int*)&client->Attr->Sen, data->iValue))
				    return QUEST_FAILURE;
			break;
			case 30: // set global XP rate
			{
			    GServer->Config.EXP_RATE = data->iValue;
			    return QUEST_SUCCESS;
            }
			break;
		    case 31: //level
			    if(!OperateValues<int>(data->btOp, (int*)&client->Stats->Level, data->iValue))
				    return QUEST_FAILURE;
			break;
		    case 32: // Stat points
			    if(!OperateValues<int>(data->btOp, (int*)&client->CharInfo->StatPoints, data->iValue))
				    return QUEST_FAILURE;
			break;
			case 37: // Skill points
			    if(!OperateValues<int>(data->btOp, (int*)&client->CharInfo->SkillPoints, data->iValue))
				    return QUEST_FAILURE;
			break;
		    //case sMoney:
			    //if(!OperateValues<int>(data->btOp, (int*)&client->CharInfo->Zulies, data->iValue))
				    //return QUEST_FAILURE;
			//break;
		    case 40: //money
            {
                if(!OperateValues<int>(data->btOp, (int*)&client->CharInfo->Zulies, data->iValue))
                    return QUEST_FAILURE;
			    // Send zuly update packet
                BEGINPACKET(pak, 0x71D);
                ADDQWORD( pak, client->CharInfo->Zulies );
                client->client->SendPacket( &pak );
            }
            break;
		    default:
			    Log(MSG_WARNING, "Type Unknown: '%i'", data->iType);
			break;
		}
	}
	return QUEST_SUCCESS;
}

//Set Quest Variable
QUESTREWD(004)
{
	return QUEST_REWD_002(server, client, raw);
}

    //Give Reward
QUESTREWD(005)
{
	GETREWDDATA(005);
	//byte btTarget;            // pos 0x00
    //union
    //{
	//	byte btEquation;      // pos 0x02 apparently should be 0x01
	//	word nEquation;
	//};
	//byte btEquation;          // pos 0x01
	//word nEquation;           // pos 0x02
	//int iValue;               // pos 0x04
	//dword iItemSN;            // pos 0x06
	//union
    //{
	//	byte btPartyOpt;      // pos 0x0a
	//	word nPartyOpt;
	//};
	//word nItemOpt;            // pos 0x0c
	//word nSkill. Co-opting nItemOpt as a skill id
	word nSkill = data->nItemOpt;
	if( client->questdebug )
        server->SendPM(client, "Quest reward 005 using equation %i", data->btEquation);
	switch(data->btTarget)
    {
		case 0://EXP
		{
            if( client->questdebug )
                server->SendPM(client, "Give EXP: %i", data->iValue);
			client->CharInfo->Exp += GetRewardValue(data->btEquation, data->iValue, client, 0);
			BEGINPACKET(pak, 0x79b);
			ADDDWORD(pak, client->CharInfo->Exp);
			ADDDWORD(pak, client->CharInfo->stamina);
			ADDWORD (pak, 0);
    		client->client->SendPacket(&pak);
        }
		break;
		case 1://Zuly
		{
            if( client->questdebug )
                server->SendPM(client, "Give Zuly: %i", data->iValue);
            unsigned int j = client->CheckQuest;
            int itemcount = client->quest.quests[j].Items[0].count;
            if( client->questdebug )
                server->SendPM(client, "Items returned: %i", itemcount);
            //int Zulyreward = GetRewardValue(data->btEquation, data->iValue, client, itemcount);
            // temp fix
            int Zulyreward = data->iValue;
            if(itemcount > 0 )                  //this is for cases where multiple items are handed in for fetch quest.
                Zulyreward = data->iValue * itemcount;
            client->CharInfo->Zulies += Zulyreward;
			//client->CharInfo->Zulies += GetRewardValue(data->btEquation, data->iValue, client, 1);//dunno nDupCount for this one!
			BEGINPACKET(pak, 0x71D);
			ADDQWORD(pak, client->CharInfo->Zulies);
			client->client->SendPacket(&pak);
		}
		break;
		case 2://Item
		{
			CItem nItem;
			nItem.itemtype = data->iItemSN / 1000;
			nItem.itemnum = data->iItemSN % 1000;
			if(nItem.IsStackable())
            {
			    nItem.count = GetRewardValue(data->btEquation, data->iValue, client, 0);
			}
            else
            {
				nItem.count = 1;
            }
            if( client->questdebug )
                server->SendPM(client, "Give item [%i][%i]x%i", nItem.itemtype, nItem.itemnum, nItem.count);
            nItem.durability = GServer->STB_ITEM[nItem.itemtype-1].rows[nItem.itemnum][29];
			nItem.gem = 0;
			nItem.stats = 0;
			nItem.refine = 0;
			nItem.socketed = 0;
			nItem.lifespan = 100;
			nItem.appraised = 1;
			dword slot = client->AddItem(nItem);
			if (slot == 0xffff)  // Fail
			{
                BEGINPACKET( pak, 0x7a7);
                ADDWORD(pak, 0x00);
                ADDBYTE(pak, 0x03);
                ADDBYTE(pak, 0x00);
                client->client->SendPacket(&pak);
            }
            else // Success
            {
                BEGINPACKET( pak, 0x71f);
                ADDBYTE(pak, 0x01);
                ADDBYTE(pak, slot);
                ADDWORD(pak, client->items[slot].GetPakHeader( ) );
                ADDDWORD(pak, client->items[slot].GetPakData( ) );
                client->client->SendPacket(&pak);
			}
		}
		break;
		case 3://Recieve Buff. start battle so that AIP can actually do the buffing based on RefVar values
		{
		    CCharacter* monster = GServer->GetMonsterByID(client->NPCvar,client->Position->Map);
		    monster->StartAction( client, SKILL_ATTACK, nSkill );
		}
		default:
                break;
	}
	return QUEST_SUCCESS;
}

//Restore HP/MP
QUESTREWD(006)
{
	//dword iPercentOfHP       pos 0x00
	//dword iPercentOfMP       pos 0x04
	//byte btPartyOpt          pos 0x08
    GETREWDDATA(006);
    if( client->questdebug )
        server->SendPM(client, "Restore %i%% HP, %i%% MP", data->iPercentOfHP, data->iPercentOfMP);
	client->Stats->HP = (long int)((float)client->Stats->MaxHP / 100.0f) * data->iPercentOfHP;
	client->Stats->MP = (long int)((float)client->Stats->MaxHP / 100.0f) * data->iPercentOfMP;
	return QUEST_SUCCESS;
}

//Teleport
QUESTREWD(007)
{
	//dword iZoneSN;     pos 0x00
	//dword iX;          pos 0x04
	//dword iY;          pos 0x08
	//byte btPartyOpt;   pos 0x0d
    GETREWDDATA(007);
	fPoint thispoint;
	thispoint.x = floor(((float)data->iX)/100);
	thispoint.y = floor(((float)data->iY)/100);
    if( client->questdebug )
        server->SendPM(client, "Teleport [%i][%f][%f]", data->iZoneSN, thispoint.x, thispoint.y);
	GServer->TeleportTo(client, data->iZoneSN, thispoint);
	return QUEST_SUCCESS;
}

//Spawn Monster
QUESTREWD(008)
{
    //dword iMonsterSN   pos 0x00
	//dword iHowMany     pos 0x04
	//	byte btWho       pos 0x08 or
	//	int iWho         pos 0x08
	//dword iZoneSN      pos 0x0a
	//dword iX           pos 0x0e
	//dword iY           pos ox11
	//dword iRange       pos 0x15
	//dword iTeamNo      pos 0x19
    GETREWDDATA(008);
    fPoint position;
    dword mapId;
    if(data->iX == 0 || data->iY == 0 || data->iZoneSN == 0)
    {
        position.x = client->Position->current.x;
        position.y = client->Position->current.y;
        mapId = client->Position->Map;
    }
    else
    {
        position.x = data->iX / 100;
        position.y = data->iY / 100;
        mapId = data->iZoneSN;
    }
	for(dword i = 0; i < data->iHowMany; i++)
    {
		fPoint pos = GServer->RandInCircle( position, data->iRange );
        if( client->questdebug )
            server->SendPM(client, "Spawn mob[%i] @ %f, %f", data->iMonsterSN, pos.x, pos.y);
		CMap* map = GServer->MapList.Index[mapId];
		CMonster* mon = map->AddMonster( data->iMonsterSN, pos, 0, 0 , 1 );
		if(data->iMonsterSN > 750 && data->iMonsterSN < 755) // ghost rackies = non aggresive
        {
            mon->thisnpc->aggresive = 0;
        }
        else
        {
            mon->thisnpc->aggresive = 999; // Force the mob to be agressive.
        }
		mon->lastSighCheck = 0; // Force sight check instantly.
    }
	return QUEST_SUCCESS;
}

//Execute Quest Trigger
QUESTREWD(009)
{
	//word shNameLen            pos 0x00
	//string szNextTriggerSN    pos 0x02
    GETREWDDATA(009);
	char* tempName = reinterpret_cast<char*>(&data->szNextTriggerSN) - 2;
	dword hash = MakeStrHash(tempName);
    if( client->questdebug )
        server->SendPM(client, "Execute Quest Trigger %s[%d] [%08x]", tempName, data->shNameLen, hash);
	return client->ExecuteQuestTrigger(hash);
    //return QUEST_SUCCESS;
}

//Reset Stats
QUESTREWD(010)
{
    if( client->questdebug )
        server->SendPM(client, "Reset Stats");
	client->CharInfo->StatPoints = 0;
	client->Attr->Str = 15;
	client->Attr->Dex = 15;
	client->Attr->Int = 15;
	client->Attr->Con = 15;
	client->Attr->Cha = 10;
	client->Attr->Sen = 10;
	for(int i = 2; i <= client->Stats->Level; i++)
    {
		client->CharInfo->StatPoints += 10;
		client->CharInfo->StatPoints += i / 2;
	}
	return QUEST_SUCCESS;
}

//Update Object Var
QUESTREWD(011)
{
	GETREWDDATA(011);
	/*if(data->btWho == 0) //npc
	{
        CMonster* monster = reinterpret_cast<CMonster*>(entity);
	    if(monster == NULL) return QUEST_FAILURE;
	    if(data->nVarNo > 19) return AI_FAILURE;
	    short tempval = GServer->ObjVar[monster->thisnpc->refNPC][data->nVarNo];
	    switch(data->btOp)
        {
            case 5:
                tempval = data->iValue;
            break;
            case 6:
                tempval += data->iValue;
            break;
            case 7:
                tempval -= data->iValue;
            case 9:
                tempval++;
            break;
            default:
                return QUEST_FAILURE;
            break;
        }
        if(tempval < 0)tempval = 0;
        GServer->ObjVar[monster->thisnpc->refNPC][data->nVarNo] = tempval;
        return QUEST_SUCCESS;
    }
    else if(data->btWho == 1) // event
    {
        //need to write the event code still it seems. Seems easy enough
        return QUEST_FAILURE;
    }*/


    /*if(entity->_EntityType != ENTITY_NPC) return QUEST_FAILURE;

	if(data->btWho == 0){//Npc
		CNpc* thisNpc = reinterpret_cast<CNpc*>(entity);
		thisNpc = thisNpc->SelectedNpc;
		if(thisNpc == NULL) return QUEST_FAILURE;

		short VarValue = thisNpc->ObjVar.GetVar(data->nVarNo);
		OperateValues(data->btOp, &VarValue, (short)data->iValue);
		thisNpc->ObjVar.SetVar(data->nVarNo, VarValue);
	}else if(data->btWho == 1){//Event
		short VarValue = server->EventVar.GetVar(data->nVarNo);
		OperateValues(data->btOp, &VarValue, (short)data->iValue);
		server->EventVar.SetVar(data->nVarNo, VarValue);
	}


	return QUEST_SUCCESS;*/
	//byte btWho;          pos 0x00
	//word nVarNo;         pos 0x02
	//dword iValue;        pos 0x04 this was an int but ints only hold 2 bytes so btop would be out of position
	//byte btOp;           pos 0x08 btop definitely at position 0x08 so had to adjust iValue
	int tempval;
    if(data->btWho == 0)
	{
        if(data->nVarNo > 19) return AI_FAILURE;
    	tempval = GServer->ObjVar[client->NPCvar][data->nVarNo];
    	//Log(MSG_INFO,"Just checking. NPCvar = %i", client->NPCvar);
        switch( data->btOp )
    	{
            case 5:
                tempval = data->iValue;
                break;
            case 6:
                tempval += data->iValue;
                break;
            case 7:
                tempval -= data->iValue;
                break;
            case 9:
                tempval++;
                break;
            default:
                return QUEST_FAILURE;
            break;
        }
    }
    else if(data->btWho == 1) //event
    {
        // not sure what to do here yet
        return QUEST_FAILURE;
    }
    GServer->ObjVar[client->NPCvar][data->nVarNo] = tempval;
	return QUEST_SUCCESS;
}

//NPC Speak
QUESTREWD(012)
{
	//if(entity->_EntityType != ENTITY_NPC) return QUEST_FAILURE;
	GETREWDDATA(012);
/*
	CNpc* thisNpc = reinterpret_cast<CNpc*>(entity);
	if(thisNpc->SelectedNpc == NULL) return QUEST_FAILURE;
	std::map<dword, char*>::iterator triggerITR = server->NpcNames.find(thisNpc->SelectedNpc->NpcID);
	if(triggerITR == server->NpcNames.end()) return QUEST_FAILURE;

	char* npcName = triggerITR->second;
	char* sayStr = server->lngQst->GetLTBStr(data->iStrID);
	if(sayStr == NULL) return QUEST_FAILURE;
	if(data->btMsgType == 1){
		//Shout
		CPacket pakout(0x785);
		pakout.Add<string>(npcName);
		pakout.Add<string>(sayStr);
		server->SendPacketToZone(thisNpc, &pakout);
	}else if(data->btMsgType == 2){
		//Announce
		CPacket pakout(0x702);
		pakout.AddBytes((byte*)npcName, strlen(npcName));
		pakout.Add<byte>('>');
		pakout.Add<string>(sayStr);
		server->SendPacketToZone(thisNpc, &pakout);
	}
	delete [] sayStr;*/

	dword npcId = 0;
    //if(entity->_EntityType == ENTITY_NPC)
    //CMonster* thisMonster = reinterpret_cast<CMonster*>(entity);
    switch(data->btMsgType)
    {
        case 0: //whisper to client
            // don't think this is possible. No way to get a character to send it to??
        break;
        case 1: //shout to map
            Log(MSG_INFO,"Quest -- NPC Shouts LTB string %i to map %i",data->iStrID,client->Position->Map);
            GServer->NPCShout(client->Position->Map,GServer->Ltbstring[data->iStrID].QuestLTB,GServer->Ltbstring[data->iStrID].QuestNpcName);
        break;
        case 2: //announce to server.
            Log(MSG_INFO,"Quest -- NPC announces LTB string %i to map %i",data->iStrID,client->Position->Map);
            GServer->NPCAnnounce(GServer->Ltbstring[data->iStrID].QuestLTB,GServer->Ltbstring[data->iStrID].QuestNpcName);
        break;
        default:
                break;
    }

	return QUEST_SUCCESS;
	// This is cool and all, but we lack the stuff to do it - Drakia
	// Not any more - PY
}

//Execute Quest Trigger
QUESTREWD(013)
{
	//	byte btWho               pos 0x00
	//	int iWho                 pos 0x00
	//dword iSec                 pos 0x02
	//word nNameLength           pos 0x06
	//string szTriggerName       pos 0x08
	//dword m_HashNextTrigger    pos 0x06 + nNameLength?
	//looks like a quest trigger to me
	GETREWDDATA(013);
	char* tempName = reinterpret_cast<char*>(&data->szTriggerName) - 2;
	dword hash = MakeStrHash(tempName);
    if( client->questdebug )
        server->SendPM(client, " RWD 013 Execute Quest Trigger %s[%d] [%08x]", tempName, data->nNameLength, hash);
	//suppress the actual execution for now just to be sure
    return client->ExecuteQuestTrigger(hash);
    return QUEST_SUCCESS;
}

//Learn Skill
QUESTREWD(014)
{
	//	byte btOp        pos 0x00
	//	int iOp          pos 0x00
	//dword iSkillNo     pos 0x02
    GETREWDDATA(014);
    if( client->questdebug )
        server->SendPM(client, "Learn skill: %i", data->iSkillNo);
    GServer->LearnSkill(client, data->iSkillNo, false);
	return QUEST_SUCCESS;
}

//Set Quest Flag
QUESTREWD(015)
{
	GETREWDDATA(015);
	//word nSN;      0x00
	//byte btOp;     0x02
    if( client->questdebug )
        server->SendPM(client, "Set QFlag[%i]=%i", data->nSN, data->btOp);
	client->quest.SetFlag(data->nSN, (data->btOp == 1)?true:false);
	// PY method
	//client->quest.Qflags[data->nSN] == data->btOp;
	// PY end
	return QUEST_SUCCESS;
}

//Unknown
QUESTREWD(016)
{
    //word nGroupSN         pos 0x00
    return QUEST_SUCCESS;
}

//Reset All Quest Flags
QUESTREWD(017)
{
    if( client->questdebug )
        server->SendPM(client, "Reset all quest flags");
	//memset(&client->quest.flags, 0, 64);
	// PY method
	for(UINT i=0;i<1000;i++)
	{
        for(int j=0;j<8;j++)
        {
            client->quest.Qflags[i][j] = 0;
        }
    }
	// PY end
	return QUEST_SUCCESS;
}

//Send Announcement
QUESTREWD(018)
{
    //dword iStrID       pos 0x00
	//word nCnt          pos 0x04
	//string Data        pos 0x06
	//why isn't this coded? looks simple enough
    GETREWDDATA(018);
	char* tempName = reinterpret_cast<char*>(&data->Data) - 2;
    if( client->questdebug )
        server->SendPM(client, " RWD 018 Send announcement %s", tempName);
	Log(MSG_INFO,"Announcement to all %s",tempName);
    GServer->NPCAnnounce(tempName,"Quest NPC");
    return QUEST_SUCCESS;
}

//Execute Quest Trigger in Other Map
QUESTREWD(019)
{
	//this is going to be a pain
	//it runs a quest trigger that would appear to be sent to every player in the designated zone

	//word nZoneNo;           //pos 0x00
	//word nTeamNo;           //pos 0x02
	//word nTriggerLength;    //pos 0x04 This is definitely NOT the length of the following name. PY
	//string TriggerName;     //pos 0x06 + nTriggerlength more bytes. Name always appears to be 17 bytes long
	//dword m_HashTrigger;
    //word m_HashTrigger;     //pos 0x17 only has 2 bytes not 4. PY

    // let's check the values first
    GETREWDDATA(019);
    //Log(MSG_DEBUG,"Execute Quest trigger: %s for zone %i. Hash: %i",data->TriggerName, data->nZoneNo, data->m_HashTrigger);

	/*CMap* map = GServer->MapList.Index[data->nZoneNo];
	if(map == NULL) return QUEST_SUCCESS;
	if( map->PlayerList.size()<1 ) return QUEST_SUCCESS;
	for(UINT j=0;j<map->PlayerList.size();j++)
    {
        CPlayer* player = map->PlayerList.at(j);
        player->ExecuteQuestTrigger(data->m_HashTrigger);
    }
    return QUEST_SUCCESS;*/

    char* tempName = reinterpret_cast<char*>(&data->TriggerName) - 2;
    dword hash = MakeStrHash(tempName);
    CMap* map = GServer->MapList.Index[data->nZoneNo];
    if(map == NULL) return QUEST_SUCCESS;
    if( map->PlayerList.size()<1 ) return QUEST_SUCCESS;
    for(UINT j=0;j<map->PlayerList.size();j++)
    {
        CPlayer* player = map->PlayerList.at(j);
        player->ExecuteQuestTrigger(hash);
    }

    return QUEST_SUCCESS;
}

//PvP Status
QUESTREWD(020)
{
	GETREWDDATA(020);
	//byte btNoType;         pos 0x00

    return QUEST_SUCCESS;
}

//Set Respawn Position
QUESTREWD(021)
{
	//dword iX               pos 0x00
	//dword iY               pos 0x04
	GETREWDDATA(020);
	client->Position->saved = client->Position->Map;
    return QUEST_SUCCESS;
}

//Unknown
QUESTREWD(022)
{
	//word nZonNo            pos 0x00
	//byte btOp              pos 0x02
    return QUEST_SUCCESS;
}

//Raise Clan Grade - This is not the least bit efficient - Drakia
QUESTREWD(023)
{
    GETREWDDATA(023);
    if( client->questdebug )
        server->SendPM(client, "Raise clan grade");
    for(UINT i=0;i<GServer->MapList.Map.size();i++)
    {
        CMap* map = GServer->MapList.Map.at(i);
        if( map->PlayerList.size()<1 )
            continue;
        for(UINT j=0;j<map->PlayerList.size();j++)
        {
            CPlayer* player = map->PlayerList.at(j);
            if( player->Clan->clanid != client->Clan->clanid ) continue;
            player->Clan->grade++;

            //load clan info in char server
	        BEGINPACKET( pak, 0x7e0 );
    	    ADDBYTE    ( pak, 0xfb ); //action to update clan informacion (charserver)
    	    ADDWORD    ( pak, player->Clan->clanid );
    	    ADDWORD    ( pak, player->Clan->grade );
            GServer->SendISCPacket( &pak );

            //Send to other players
            RESETPACKET( pak, 0x7e0 );
            ADDBYTE    ( pak, 0x35 );
            ADDWORD    ( pak, player->clientid );
            ADDWORD    ( pak, player->Clan->clanid);
            ADDWORD    ( pak, 0x0000 );//???
            ADDWORD    ( pak, player->Clan->back );
            ADDWORD    ( pak, player->Clan->logo );
            ADDBYTE    ( pak, player->Clan->grade );//clan grade
            ADDBYTE    ( pak, 0x06 );//clan rank
            ADDSTRING  ( pak, player->Clan->clanname );
            ADDBYTE    ( pak, 0x00 );
            GServer->SendToVisible( &pak, player );
        }
    }
    GServer->DB->QExecute("UPDATE list_clan SET grade=%i WHERE id=%i", client->Clan->grade, client->Clan->clanid);
	return QUEST_SUCCESS;
}

//Clan Money
QUESTREWD(024)
{
	//int iMONEY                  pos 0x00
	//byte btOP                   pos 0x02
	GETREWDDATA(024);
    return QUEST_SUCCESS;
}

//Clan Points
QUESTREWD(025)
{
	//short nPOINT                pos 0x00
	//byte btOP                   pos 0x02
    GETREWDDATA(025);
    return QUEST_SUCCESS;
}

//Clan Skill
QUESTREWD(026)
{
	GETREWDDATA(026);
    //word nSkillNo;         pos 0x00
	//byte btOP;             pos 0x02
	//do something (based on btOp) with a clan skill id = data->nSkillNo
	if( client->questdebug )server->SendPM(client, "Clan skill rwd[026] skill id: %i btOP: %i",data->nSkillNo,data->btOP);
    return QUEST_SUCCESS;
}

//Clan Contribution
QUESTREWD(027)
{
	GETREWDDATA(027);
    //short nCONT;           pos 0x00
	//byte btOP;             pos 0x02
	if( client->questdebug )server->SendPM(client, "Clan Contribution rwd[026] nCONT: %i btOP: %i",data->nCONT,data->btOP);

    return QUEST_SUCCESS;
}

//Clan Teleportation - Again, not efficient. Maybe keep a list of pointers to clan members? - Drakia
QUESTREWD(028)
{
    //dword iRange;           pos 0x00
	//word nZoneNo;           pos 0x04
	//dword iX;               pos 0x06
	//dword iY;               pos 0x0a
    GETREWDDATA(028);
    fPoint telepos;
    fPoint newPos;
    telepos.x = data->iX/100;
    telepos.y = data->iY/100;
    if( client->questdebug )
        server->SendPM(client, "Clan teleport to [%i][%f][%f]", data->nZoneNo, telepos.x, telepos.y);
    for(UINT i=0;i<GServer->MapList.Map.size();i++)
    {
        CMap* map = GServer->MapList.Map.at(i);
        if( map->PlayerList.size()<1 )
            continue;
        for(UINT j=0;j<map->PlayerList.size();j++)
        {
            CPlayer* player = map->PlayerList.at(j);
            if( player->Clan->clanid != client->Clan->clanid ) continue;
            newPos = GServer->RandInCircle(telepos, data->iRange);
            GServer->TeleportTo(player, data->nZoneNo, newPos );
        }
    }
	return QUEST_SUCCESS;
}

QUESTREWD(029) //execute client quest trigger (LUA)
{
    GETREWDDATA(029);
    char* tempName = reinterpret_cast<char*>(&data->LuaName) - 2;
	dword hash = MakeStrHash(tempName);
    if( client->questdebug )
        server->SendPM(client, "Execute Client LUA %s[%d] [%08x]", tempName, data->strLen, hash);
	//return client->ExecuteQuestTrigger(hash);
	//need to code a packet here. on evo it's 0x7f8. Don't even know if we use one here
    Log(MSG_DEBUG,"ran quest action 29");
    return QUEST_SUCCESS;
}

QUESTREWD(030) //Reset skills
{
    //Log(MSG_DEBUG,"ran quest action 30");
    for(int i=0;i<30;i++)
    {
        //give one sp for every active skill present
        if(client->askill[i] != 0)
        {
            client->CharInfo->SkillPoints += 1;
        }
        client->askill[i] = 0;
        //give SP equal to the level of the active skill. Actual level is always 1 more than this
        client->CharInfo->SkillPoints += client->askilllvl[i];
        client->askilllvl[i] = 0;
        //give one sp for every passive skill present
        if(client->pskill[i] != 0)
        {
            client->pskill[i] = 0;
            client->CharInfo->SkillPoints += 1;
        }
        //give SP equal to the level of the passive skill. Actual level is always 1 more than this
        client->CharInfo->SkillPoints += client->pskilllvl[i];
        client->pskilllvl[i] = 0;
    }
    client->savedata();
    return QUEST_SUCCESS;
}
