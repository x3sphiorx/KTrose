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
#include "worldserver.h"

// from Paul_T
bool CWorldServer::SendPM( CPlayer* thisclient, const char* Format, ... )
{
  char buf[512];
  va_list ap;
  va_start( ap, Format );
  vsprintf( buf, Format, ap );
      BEGINPACKET( pak, 0x0784 );
      ADDSTRING( pak, "Server" );
      ADDBYTE( pak, 0 );
      ADDSTRING( pak, buf );
      ADDBYTE( pak, 0 );
      thisclient->client->SendPacket(&pak);
  va_end( ap );
           return true;
}

// from Paul_T
bool CWorldServer::SendGlobalMSG( CPlayer* thisclient, const char* Format, ... )
{
  char buf[512];
  va_list ap;
  va_start( ap, Format );
  vsprintf( buf, Format, ap );
           BEGINPACKET( pak, 0x0784 );
           ADDSTRING( pak, thisclient->CharInfo->charname );
           ADDBYTE( pak, 0 );
     ADDSTRING( pak, buf );
           ADDBYTE( pak, 0 );
           SendToAll(&pak);
  va_end( ap );
           return true;
}

// NPC Announce to the server
bool CWorldServer::NPCAnnounce( const char msg[200], const char npc[50])
{
    BEGINPACKET( pak, 0x702 );
    ADDSTRING( pak, npc );
	ADDSTRING( pak, "> " );
	ADDSTRING( pak, msg);
	ADDBYTE( pak, 0x00);
	SendToAll( &pak );
	return true;
}

// NPC Whisper to a character
bool CWorldServer::NPCWhisper( CPlayer* thisclient, CMonster* thismon, const char msg[200], const char npc[50] )
{
    BEGINPACKET( pak, 0x0784 );
    ADDSTRING( pak, npc );
    ADDBYTE( pak, 0 );
    ADDSTRING( pak, msg );
    ADDBYTE( pak, 0 );
    thisclient->client->SendPacket(&pak);
    return true;
}

// NPC Shout to the current map
bool CWorldServer::NPCShout( int map, const char msg[200], const char npc[50] )
{
    BEGINPACKET(pak, 0x0785);
	ADDSTRING  ( pak, npc );
	ADDBYTE    ( pak, 0 );
	ADDSTRING  ( pak, msg );
	ADDBYTE    ( pak, 0 );
	SendToMap  ( &pak, map );
	return true;
}

bool CWorldServer::DoSkillScript( CCharacter* character, CSkills* thisskill )
{
     try
     {
        if(thisskill == 0)
            return false;
        if(thisskill->script == 0)
            return false;
        if(thisskill->svalue1 == 0)
            return false;
        fPoint position = RandInCircle( character->Position->current, 1 );
        CMap* map = MapList.Index[character->Position->Map];
        map->AddMonster( thisskill->svalue1, position, character->clientid,0,1 );
        return true;
    }
    catch (...)
    {
         Log(MSG_WARNING, "Error in CWorldServer::DoSkillScript( CCharacter* character, CSkills* thisskill )(serverFunctions.cpp)" );
         return false;
    }
}

// Build Drop. New experimental method.
CDrop* CWorldServer::GetNewDrop( CMonster* thismon )
{
    //Log(MSG_DEBUG,"Monster %i killed. FInding a drop",thismon->montype);
    CPlayer* thisclient = GServer->GetClientByCID(thismon->MonsterDrop->firsthit);
    if(thisclient == NULL)return NULL;
    if( thisclient->Session->codedebug )
            SendPM(thisclient, "Drops function called after killing monster type %i",thismon->montype);

    int randv;
    int i;
    CDrop* newdrop = new (nothrow) CDrop;

    if(newdrop == NULL)
    {
        Log(MSG_WARNING, "newDrop is NULL [getdrop]" );
        return NULL;
    }
    CMDrops* thisdrop = NULL;
    CMDrops* testdrop = NULL;

    newdrop->clientid = GetNewClientID( );
    newdrop->posMap = thismon->Position->Map;
    newdrop->pos = RandInCircle( thismon->Position->current, 3 );
    //newdrop->droptime = time(NULL);
    newdrop->owner = thismon->MonsterDrop->firsthit;
    newdrop->thisparty = thismon->thisparty;
    ClearItem(newdrop->item);



    int droprate = 80; // base drop percentage for monsters your own level
    int DropFloor = Config.BASE_DROP_CHANCE;
    int leveldif = (int)((float)thismon->thisnpc->level - (float)thisclient->Stats->Level);
    float mod = droprate * 0.01 * leveldif;
    int dropchance = int(droprate + mod);
    if(dropchance < DropFloor) dropchance = DropFloor; //always a small chance of a drop even when the mob is more than 20 levels beneath your own
    if(thismon->thisnpc->level == 1)
        dropchance = 80;
    //if( thisclient->Session->codedebug )
    //    SendPM(thisclient, "Drop chance (based on level diference) = %i", dropchance );
    int droprand = GServer->RandNumber(0,100);
    if (droprand > dropchance)
    {
        if( thisclient->Session->codedebug )
            SendPM(thisclient, "Drop rate check failed with %i. No drop this time",droprand);
        return NULL; // no drop here. not this time anyway.
    }


    // Each monster has its own rates for zuly and item drops defined in the stb
    // first check for Zuly drops
    randv = RandNumber( 1, 100);
    //if( thisclient->Session->codedebug )
    //{
    //   SendPM(thisclient, "randv = %i.  money = %i. zulyrate = %i. ", randv,thismon->thisnpc->money,thisclient->Stats->zulydroprate );
    //}
    if(randv <= (thismon->thisnpc->money + thisclient->Stats->zulydroprate)) // zuly drop
    {
        newdrop->type = 1; //zuly
        newdrop->amount = thismon->thisnpc->level * 5 * (Config.ZULY_RATE + thisclient->Stats->zulydroprate) + RandNumber( 1, 10 );
        if( thisclient->Session->codedebug )
        {
           SendPM(thisclient, "Zuly drop selected " );
        }
        return  newdrop;
    }
    //now check for item drops
    //if( thisclient->Session->codedebug )
    //{
    //   SendPM(thisclient, "randv = %i. Item = %i. Itemrate = %i", randv,thismon->thisnpc->item,thisclient->Stats->itemdroprate );
    //}
    if(randv <= (thismon->thisnpc->item + thisclient->Stats->itemdroprate + thismon->thisnpc->money)) // Item drop
    {
        //OK got an item. Now we find which one
        //Map drop or mob drop? map = 50% mob = 50%. Maybe should be configurable or modified by monster data?
        int randv2 = RandNumber( 1, 100);
        if(randv2 <= 50) //map drop
        {
            for(i=0;i<GServer->MDropList.size();i++)
            {
                testdrop =  GServer->MDropList.at(i);
                if(testdrop == NULL) return NULL;
                if(testdrop->Dropid == thismon->Position->Map)
                {
                    thisdrop = testdrop;
                }
            }

            if( thisclient->Session->codedebug )
            {
               SendPM(thisclient, "Map drop selected for map %i. ", thismon->Position->Map );
            }
        }
        else // mob drop
        {
            for(i=0;i<GServer->MDropList.size();i++)
            {
                testdrop =  GServer->MDropList.at(i);
                if(testdrop == NULL) return NULL;
                if(testdrop->Dropid == thismon->thisnpc->dropid)
                {
                    thisdrop = testdrop;
                }
            }
            if( thisclient->Session->codedebug )
            {
               SendPM(thisclient, "Mob drop selected for dropid %i. ", thismon->thisnpc->dropid );
            }
        }
        if(thisdrop == NULL)
        {
            Log(MSG_WARNING, "Thisdrop is NULL [getdrop]" );
            return NULL;
        }
        newdrop->type = 2; //Item
        dword randitem = RandNumber( 1, thisdrop->TotalChance );
        UINT itemindex = 0;
        //if( thisclient->Session->codedebug )
        //{
        //   SendPM(thisclient, "random chance %i", randitem);
        //}

        i=0;
        do
        {
            //if( thisclient->Session->codedebug )
            //{
            //   SendPM(thisclient, "Index: %i Item id: %i chance: %i", i, thisdrop->item[i], thisdrop->RunningTotal[i]);
            //}
            i++;
        }
        while (randitem > thisdrop->RunningTotal[i]);
        itemindex = i;

        if(thisdrop->item[itemindex] == 0)
        {
            Log(MSG_DEBUG, "item at itemindex %i does not exist",itemindex );
            return NULL; //no item listed for this dropid
        }
        //ok we found an item. Now we process it.
        //if( thisclient->Session->codedebug )
        //{
        //   SendPM(thisclient, "Found an item to drop itemindex: %i id: %i. ", itemindex, thisdrop->item[itemindex] );
        //}
        if(thisdrop->item[itemindex] < 100000)
        {
            newdrop->item.itemtype = thisdrop->item[itemindex] / 1000;
            newdrop->item.itemnum = thisdrop->item[itemindex] % 1000;
        }
        else
        {
            newdrop->item.itemtype = thisdrop->item[itemindex] / 1000000;
            newdrop->item.itemnum = thisdrop->item[itemindex] % 1000000;
        }
        //if( thisclient->Session->codedebug )
        //{
        //   SendPM(thisclient, "Item type = %i. item number = %i", newdrop->item.itemtype,newdrop->item.itemnum );
        //}
        newdrop->item.lifespan = 10 + rand()%80;
        switch( newdrop->item.itemtype )
        {
            case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
                newdrop->item.type = GServer->EquipList[newdrop->item.itemtype].Index[newdrop->item.itemnum]->type;
                newdrop->item.raretype = GServer->EquipList[newdrop->item.itemtype].Index[newdrop->item.itemnum]->raretype;
                break;
            case 10:
                newdrop->item.type = GServer->UseList.Index[newdrop->item.itemnum]->type;
                newdrop->item.raretype = 0;
                break;
            case 11:
                newdrop->item.type = GServer->JemList.Index[newdrop->item.itemnum]->type;
                newdrop->item.raretype = 0;
                break;
            case 12:
                newdrop->item.type = GServer->NaturalList.Index[newdrop->item.itemnum]->type;
                newdrop->item.raretype = 0;
                break;
            case 14:
                newdrop->item.type = GServer->PatList.Index[newdrop->item.itemnum]->type;
                newdrop->item.raretype = 0;
                break;
            default:
                Log(MSG_DEBUG, "itemtype %i does not exist",newdrop->item.itemtype );
                return NULL;
                break;
        }
        float dmod = 0; //random number from 0 to 100 made up of 5 sub numbers to keep
        //the average value near to 50
        for(i=0; i<5; i++)
        {
            float r1 = rand()%20;
            dmod += r1;
        }
        newdrop->item.durability = 10 + (int)dmod;
        newdrop->item.appraised = true;
        newdrop->item.stats = 0;
        newdrop->item.count = 1;

        if( newdrop->item.itemtype == 8 || newdrop->item.itemtype == 9 )
        {
            //This probability is now configurable
            int psocked = rand()%101; //Probability of finding a socketed item
            if( psocked < Config.SlotChance) //default should be around 5% needs to be rare
            {
                newdrop->item.socketed = true;
            }
            else
            {
                 newdrop->item.socketed = false;
            }
        }
        else
        {
            newdrop->item.socketed = false;
        }


        int chamod = (int)floor(thisclient->Attr->Cha / 30);
        if(chamod < 0) chamod = 0;
        int basedrop = thisclient->Stats->itemdroprate; //Base number of items to be dropped.
        int maxdrop = basedrop + Config.DropMultiple;
        if(newdrop->item.itemtype == 11) //gems only get 1
            newdrop->item.count = 1;
        if( newdrop->item.itemtype == 10 || newdrop->item.itemtype == 12 )
        {
            newdrop->item.count = RandNumber(basedrop, maxdrop);
            if(thismon->thisnpc->level == 1)
                newdrop->item.count = 1; //limit the drop rate of items from level 1 event mobs
            if(newdrop->item.count == 0)
                newdrop->item.count = 1;
            if(newdrop->item.type == 314) //skillbooks
                newdrop->item.count = 1;
            if(newdrop->item.itemtype == 12)
            {
                newdrop->item.count = RandNumber(1, 6) + RandNumber(0, thisclient->Stats->itemdropcountrate); //basic type 12 items
                //some item types have their own rules
                if(newdrop->item.type == 428) //special skill items such as mana jams and scrolls
                    newdrop->item.count = RandNumber(1, 3);
                if(newdrop->item.itemnum > 300 && newdrop->item.itemnum < 360) //bullets get a lot higher count.
                {
                    newdrop->item.count *= 10;
                    newdrop->item.count += 10;
                }
            }
        }
        else if( newdrop->item.itemtype >1 && newdrop->item.itemtype !=7 && newdrop->item.itemtype < 10)
        {
            // check to see if the item will be refined
            int prefine = rand()%100; //Probability of finding a refined item
            int refinechance = Config.RefineChance;
            if(prefine < refinechance) // default = 5%
            {
                int refinelevel = rand()%101;  //which level of refine do we actually get
                if( refinelevel < 5)        //default 5%
                    newdrop->item.refine = 4 * 16;
                else if( refinelevel < 15 )   //10%
                    newdrop->item.refine = 3 * 16;
                else if(refinelevel < 35 )   // 20%
                    newdrop->item.refine = 2 * 16;
                else                          // 65%
                    newdrop->item.refine = 16;
            }
            else //95%
                newdrop->item.refine = 0;

            int StatChance = Config.StatChance;
            if(newdrop->item.raretype > 0) // it's a blue item
            {
                newdrop->item.durability += 10; //make blues a little more durable
                newdrop->item.appraised = false; //blues need to be appraised
                newdrop->item.stats = RandNumber(0, 29) * 10 + 1; // stats can only be 1,11,21,,,,,291
            }
            else // not a blue item
            {
                int pstats = RandNumber(1, 100);
                if( pstats < StatChance)        // default 5%
                    newdrop->item.stats = RandNumber(0, 29) * 10 + 1; // stats can only be 1,11,21,,,,,291
            }
        }
        newdrop->item.gem = 0;
        if(newdrop->item.count == 0) 
            newdrop->item.count = 1;  //just in case this is causing bugged items.
        if( thisclient->Session->codedebug )
        {
           SendPM(thisclient, "Dropped item type: %i ID: %i count %i", newdrop->item.itemtype, newdrop->item.itemnum,newdrop->item.count);
        }
        return newdrop;

    }
    return NULL;
    // did not qualify to drop anything this time
}

// Build Drop the PY way
CDrop* CWorldServer::GetPYDrop( CMonster* thismon, UINT droptype )
{   //if droptype = 1 then it is a normal drop. if it is 2 then it is a potential side drop.
    //type 2 removed a it is now handled by AIP
    //Log( MSG_INFO, "PYDrops function selected" );
    //Log( MSG_INFO, "monster is %i", thismon->montype );

    CDrop* newdrop = new (nothrow) CDrop;
    if(newdrop == NULL)
    {
        Log(MSG_WARNING, "Error allocing memory [getdrop]" );
        return NULL;
    }
    newdrop->clientid = GetNewClientID( );
    newdrop->posMap = thismon->Position->Map;
    newdrop->pos = RandInCircle( thismon->Position->current, 3 );
    //newdrop->droptime = time(NULL);
    newdrop->owner = thismon->MonsterDrop->firsthit;
    newdrop->thisparty = thismon->thisparty;
    ClearItem(newdrop->item);

    CPlayer* thisclient = GServer->GetClientByCID(thismon->MonsterDrop->firsthit);
    if(thisclient == NULL)return NULL;

    // code to modify drop chance for different levels
    //float charm = 0;
    //float droprate = thismon->thisnpc->dropchance;
    int droprate = Config.DROP_RATE;
    int DropFloor = Config.BASE_DROP_CHANCE;
    int leveldif = (int)((float)thismon->thisnpc->level - (float)thisclient->Stats->Level);
    float mod = droprate * 0.01 * leveldif;
    int dropchance = int(droprate + mod);
    if(dropchance < DropFloor) dropchance = DropFloor; //always a small chance of a drop even when the mob is more than 20 levels beneath your own
    if(thismon->thisnpc->level == 1)
        dropchance = 80;
    if( thisclient->Session->codedebug )
        SendPM(thisclient, "Drop rate (based on level diference) = %i", dropchance );
    int droprand = GServer->RandNumber(0,100);
    if (droprand > dropchance)
    {
        if( thisclient->Session->codedebug )
            SendPM(thisclient, "Drop rate check failed with %i. No drop this time",droprand);
        return NULL; // no drop here. not this time anyway.
    }

    CItemType prob[MDropList.size()];
    bool isdrop = false;
    int n = 0;
    int test = 0;
    long int probmax = 0;
    int itemnumber[MDropList.size()];
    int itemtype[MDropList.size()];
    int probability[MDropList.size()];
    int alternate[MDropList.size()][8];

    if( thismon->IsGhost())
    {
        // Stuff to do if the mob is a ghost of any type
        int selection = 1 + rand()%10;
        if( selection <= 5 )
        {
            newdrop->type = 1; //Drop Zuly.
            newdrop->amount = thismon->thisnpc->level * 10 * Config.ZULY_RATE + RandNumber( 1, 10 );
            return  newdrop;
        }
        else
        {
            for(int i=0; i<SkillbookList.size( ); i++)
            {
                newdrop->type = 2;
                CMDrops* thisdrop = GServer->SkillbookList.at(i);
                if(thisdrop->level_min <= thismon->thisnpc->level &&  thisdrop->level_max >= thismon->thisnpc->level)
                {
                    itemnumber[n] = thisdrop->itemnum;
                    itemtype[n] = thisdrop->itemtype;
                    probability[n] = thisdrop->prob;
                    probmax += thisdrop->prob;
                    n++;
                }
            }
        }
    }
    else // Stuff to do if the mob isn't a ghost
    {
        int dropmode = 0;
        int randv = RandNumber( 1, 100);
        // Each monster has its own rates for zuly and item drops defined in the stb
        // We also add a small amount based on the player's ItemDropRate and ZulyDroprate.
        dropchance = thismon->thisnpc->item + thismon->thisnpc->money + thisclient->Stats->itemdroprate + thisclient->Stats->zulydroprate;
        if( thisclient->Session->codedebug )
        {
           SendPM(thisclient, "randv = %i. total drop chance = %i. money = %i. zulyrate = %i. Item = %i. Itemrate = %i", randv,dropchance,thismon->thisnpc->money,thisclient->Stats->zulydroprate,thismon->thisnpc->item,thisclient->Stats->itemdroprate );
        }
        if(randv > dropchance)return NULL; // did not qualify to drop anything this time
        if(randv <= (thismon->thisnpc->money + thisclient->Stats->zulydroprate)) // zuly drop instead of item drop
        {
            newdrop->type = 1;
            newdrop->amount = thismon->thisnpc->level * 5 * Config.ZULY_RATE + RandNumber( 1, 10 );
            return  newdrop;
        }

        int randomdrop = GServer->RandNumber(1, 100);
        for(int i=0; i<MDropList.size( ); i++)
        {
            isdrop = true; // start out true then eliminate drops later
            CMDrops* thisdrop = GServer->MDropList.at(i);
            if(thisdrop->mob != 0 && thisdrop->mob != thismon->montype)
                isdrop = false;
            if(thisdrop->map != 0 && thisdrop->map != thismon->Position->Map)
                isdrop = false;
            if(thisdrop->level_max > thisdrop->level_min && (thismon->thisnpc->level < thisdrop->level_min || thismon->thisnpc->level > thisdrop->level_max))
                isdrop = false;

            test = GServer->RandNumber(1, 10000);
            if(thisdrop->prob < test)
                isdrop = false;
            if(isdrop == true)
            {
                itemnumber[n] = thisdrop->itemnum;
                itemtype[n] = thisdrop->itemtype;
                alternate[n][0] = 0;
                for(int j=1;i<8;i++)
                {
                    alternate[n][j] = thisdrop->alt[j];
                }
                n++;
            }
        }
    }
    int newn = n;
    if(n == 0)
        return NULL;
    int maxitems = n;
    // randomize the item from the list
    n = GServer->RandNumber(0, maxitems);
    newdrop->item.itemnum = itemnumber[n];
    newdrop->item.itemtype = itemtype[n];
    newdrop->type = 2;
    if( thisclient->Session->codedebug )
    {
       for(int j=0;j<maxitems;j++)
       {
           SendPM(thisclient,"Shortlist item %i, type = %i. id = %i",j, itemtype[j], itemnumber[j]);
       }
       SendPM(thisclient, "Selected item %i. type = %i. id = %i ",n, newdrop->item.itemtype,newdrop->item.itemnum);
    }

    newdrop->item.lifespan = 10 + rand()%80;
    float dmod = 0; //random number from 0 to 100 made up of 5 sub numbers to keep
    //the average value near to 50
    for(int i=0; i<5; i++)
    {
        float r1 = rand()%20;
        dmod += r1;
    }
    newdrop->item.durability = 10 + (int)dmod;
    if( newdrop->item.itemtype == 8 || newdrop->item.itemtype == 9 )
    {
        //This probability is now configurable from WorldServer.conf
        int psocked = rand()%101; //Probability of finding a socketed item
        if( psocked < Config.SlotChance) //default should be around 5% needs to be rare
        {
            newdrop->item.socketed = true;
        }
        else
        {
             newdrop->item.socketed = false;
        }
    }
    else
    {
        newdrop->item.socketed = false;
    }
    //Log( MSG_INFO, "Socket are OK");
    newdrop->item.appraised = false;
    newdrop->item.stats = 0;
    newdrop->item.count = 1;

    //int chamod = 0;
    int chamod = (int)floor(thisclient->Attr->Cha / 30);
    if(chamod < 0) chamod = 0;
    int basedrop = thisclient->Stats->itemdroprate; //Base number of items to be dropped.
    int maxdrop = basedrop + Config.DropMultiple + chamod;
    if(newdrop->item.itemtype == 11) //gems only get 1
        newdrop->item.count = 1;
    if( newdrop->item.itemtype == 10 || newdrop->item.itemtype == 12 )
    {
        newdrop->item.count = RandNumber(basedrop, maxdrop);
        if(thismon->thisnpc->level == 1)
            newdrop->item.count = 1 + chamod; //limit the drop rate of items from level 1 event mobs
        if(newdrop->item.count == 0)
            newdrop->item.count = 1;
        if(newdrop->item.type == 314) //skillbooks
            newdrop->item.count = 1;
        if(newdrop->item.itemtype == 10)
        {
            if(newdrop->item.itemnum >= 441 && newdrop->item.itemnum <= 888)// skillbooks
                newdrop->item.count = 1;
        }

        if(newdrop->item.itemtype == 12)
        {
            newdrop->item.count = RandNumber(0, 6) + RandNumber(0, thisclient->Stats->itemdropcountrate); //basic type 12 items
            //some item types have their own rules
            if(newdrop->item.type == 428) //special skill items such as mana jams and scrolls
                newdrop->item.count = RandNumber(0, 3);
            if(newdrop->item.itemnum > 300 && newdrop->item.itemnum < 360) //bullets get a lot higher count.
            {
                newdrop->item.count *= 10;
                newdrop->item.count += 10;
            }
        }
    }
    else if( newdrop->item.itemtype >1 && newdrop->item.itemtype !=7 && newdrop->item.itemtype < 10)
    {
        // check to see if the item will be refined
        int prefine = rand()%100; //Probability of finding a refined item
        int refinechance = Config.RefineChance;
        if(prefine < refinechance) // default = 5%
        {
            int refinelevel = rand()%101;  //which level of refine do we actually get
            if( refinelevel < 5)        //default 5%
                newdrop->item.refine = 4 * 16;
            else if( refinelevel < 15 )   //10%
                newdrop->item.refine = 3 * 16;
            else if(refinelevel < 35 )   // 20%
                newdrop->item.refine = 2 * 16;
            else                          // 65%
                newdrop->item.refine = 16;
        }
        else //99%
            newdrop->item.refine = 0;

        // will the item be a blue?
        bool blue = false;
        int bluechance1 = RandNumber( 1, 100);
        int bluechance2 = Config.BlueChance + chamod;
        if( thisclient->Session->codedebug )
            Log( MSG_INFO, "Blue chance = %i", bluechance2);
        //This probability is now configurable from WorldServer.conf. CHA also has an effect
        if(bluechance1 < bluechance2) // some percentage of drops will be specials or blues whenever one is available.
        {
            if( thisclient->Session->codedebug )
                Log( MSG_INFO, "Selected a blue item");
            int p = 1;
            while(alternate[n][p] != 0 && p < 8)
            {
                p++;
            }
            if(p > 1) // blues available for this item
            {
                //Log( MSG_INFO, "blue item available");
                p--;
                int bluenum = RandNumber( 1, p);
                newdrop->item.itemnum = alternate[n][bluenum];
                blue = true;
            }
        }
        //is the item a blue or other special or unique type?
        if(newdrop->item.itemtype < 10 || newdrop->item.itemtype == 14) //equipable or PAT
        {
            if(GServer->EquipList[newdrop->item.itemtype].Index[newdrop->item.itemnum]->raretype != 0)
                blue = true;
        }
        // will the items get stats? All blue items will. Uniques count as blues.
        int pstats = rand()%101; //Probability of the item having stats. default = 5%
        if(blue == true)
        {
            pstats = 0;
        }
        int StatChance = Config.StatChance;
        if( pstats < StatChance)        // default 5%
            newdrop->item.stats = RandNumber( 1, 300);
    }
    newdrop->item.gem = 0;
    //newdrop->droptime = clock(); //moved to AddDrop function
    return newdrop;
}


UINT CWorldServer::GetColorExp( UINT playerlevel,UINT moblevel, UINT exp )
{
/*
purple = +16 - 200%
red = +10 - 150%
orange = +4 - 125%
yellow = same - 100%
green = -4 - 80%
blue = -9 - 50%
white = -15 - 20%
*/
    int dif = moblevel - playerlevel;
    //Log(MSG_INFO,"Level dif = %i XP factor is %i",dif,factor);
    if(dif > 15) //purple
        exp = (UINT)floor(exp * 2.0);
    else if(dif > 10) //red
        exp = (UINT)floor(exp * 1.5);
    else if(dif > 4) //orange
        exp = (UINT)floor(exp * 1.25);
    else if(dif >= 0) //yellow
        exp = (UINT)floor(exp * 1);
    else if(dif > -4) //green
        exp = (UINT)floor(exp * 0.8);
    else if(dif > -9) //blue
        exp = (UINT)floor(exp * 0.5);
    if(dif <= -9) //white
        exp = (UINT)floor(exp * 0.2);

    if(playerlevel < 10) // lower the rate for the first 10 levels
        exp = (UINT)floor(exp * 0.5);
    return exp;
}

bool CWorldServer::SendSysMsg( CPlayer* thisclient, string message )
{
	BEGINPACKET( pak, 0x7df );
	ADDBYTE    ( pak, 0xf1 );
	ADDSTRING  ( pak, message.c_str( ));
	ADDBYTE    ( pak, 0x00 );
	thisclient->client->SendPacket( &pak );
    return true;
}


// teleport to specificated map and position
bool CWorldServer::TeleportTo ( CPlayer* thisclient, int map, fPoint position )
{
    if(map > 70)
        return true;
    MapList.Index[map]->TeleportPlayer( thisclient, position, false );
    return true;
}


// Learn Skill
bool CWorldServer::LearnSkill( CPlayer* thisclient, UINT skill, bool cost )
{
/*
0 - ya aprendido
1 - aprendio
2 - no job
3 - falta otro skill
4 - no status points (lvl)
5 - no se puede subir de lvl el skill
6 - numero incorrecto de skill
7 - no tienes suficientes sp
*/
        BEGINPACKET(pak1, 0 );
        BEGINPACKET(pak2, 0 );
        BEGINPACKET(pak3, 0 );
        //int b=1;
        CSkills* thisskill = SkillList.at( skill);
	    char skilltype = thisskill->type;
	    //int skillpoints = thisskill->sp;
	    if(thisclient->Session->codedebug) //Debug code
        {
           char buffer[200];
           sprintf ( buffer, "Attempting to learn a new skill. id = %i skill type = %i Cost to learn = %i", thisskill->id,thisskill->type,thisskill->sp );
           SendPM(thisclient, buffer);
        }
	    int newslot = thisclient->GetNewSkillSlot(skilltype);
	    //CSkills* thisskill = 0;
	    if (newslot != 0xffff)
	    {
		switch(skilltype)
		{
		case 0:
			thisclient->bskills[newslot]= skill;
            if (cost)
                thisclient->CharInfo->SkillPoints -= thisskill->sp;
			RESETPACKET(pak1, 0x7b0);
			ADDBYTE(pak1, 1);
			ADDBYTE(pak1, newslot);
			ADDWORD(pak1, skill);
			ADDWORD(pak1, thisclient->CharInfo->SkillPoints);
			thisclient->client->SendPacket(&pak1);
			thisclient->SetStats();
			return true;
		case 1:
			thisclient->askill[newslot]= skill;
            if (cost)
                thisclient->CharInfo->SkillPoints-=thisskill->sp;
			RESETPACKET(pak2, 0x7b0);
			ADDBYTE(pak2, 1);
			ADDBYTE(pak2, 30+newslot);
			ADDWORD(pak2, skill);
			ADDWORD(pak2, thisclient->CharInfo->SkillPoints);
			thisclient->client->SendPacket(&pak2);
			thisclient->SetStats();
			return true;
		case 2:
			thisclient->pskill[newslot]= skill;
            if (cost)
                thisclient->CharInfo->SkillPoints-=thisskill->sp;
			RESETPACKET(pak3, 0x7b0);
			ADDBYTE(pak3, 1);
			ADDBYTE(pak3, 60+newslot);
			ADDWORD(pak3, skill);
			ADDWORD(pak3, thisclient->CharInfo->SkillPoints);
			thisclient->client->SendPacket(&pak3);
			thisclient->SetStats();
			return true;
        default:
            return false;
		}
	}
	return false;
}

//add / remove a Fairy
void CWorldServer::DoFairyStuff(CPlayer* targetclient, int action)
{
    BEGINPACKET( pak, 0x7dc );
	ADDBYTE( pak, action );
	ADDWORD( pak, targetclient->clientid);
	SendToVisible( &pak, targetclient );
}

void CWorldServer::DoFairyFree( int fairy )
{
    GServer->FairyList.at(fairy)->assigned = false;
    GServer->FairyList.at(fairy)->ListIndex = 0;

    if(GServer->Config.FairyTestMode == 0)
         GServer->FairyList.at(fairy)->WaitTime = GServer->Config.FairyWait * (rand()% GServer->GetFairyRange(1)+ GServer->GetFairyRange(0));

    GServer->FairyList.at(fairy)->LastTime = clock();
}

void CWorldServer::RefreshFairy( )
{
        //fairy: The wait timer should be possibibly bigger when there is few people online.
        if (Config.FairyMode == 1 && ClientList.size() > 2) //if fairy mode on and a few people online
        {
           for (int i=0; i<Config.FairyMax; i++)     // check all fairies
           {
                if ( FairyList.at(i)->LastTime <= ( clock() - (FairyList.at(i)->WaitTime * 60 * CLOCKS_PER_SEC) ) && !FairyList.at(i)->assigned )  // if fairy hour is now
	            {
                    if(ClientList.size() > 2) //stop solo players from getting fairied and screwing up their stats during testing.
                    {
                        int value = rand()%(int)(ClientList.size()-1) + 1;  //choose random value in clientlist
    		            CPlayer* targetclient = (CPlayer*) ClientList.at(value)->player;
    		            if(targetclient == NULL)
    		                return;
                        FairyList.at(i)->ListIndex = value;
    			        FairyList.at(i)->LastTime = clock();
    			        FairyList.at(i)->assigned = true;
    			        FairyList.at(i)->scroll = false;                  // Scroll value set to false. this is NOT a scroll buff fairy
    			        targetclient->Fairy = true;
    			        targetclient->FairyListIndex = i;                 // FairyList index number of our actual fairy
    			        DoFairyStuff(targetclient, 1);                    // spawn fairy to target
    			        targetclient->SetStats();
                    }
                }
			    if ( (FairyList.at(i)->LastTime + (Config.FairyStay*60*CLOCKS_PER_SEC)) <= clock() && FairyList.at(i)->assigned)  // id time for our fairy to go away
    			{
                    CPlayer* oldclient  = (CPlayer*) ClientList.at(FairyList.at(i)->ListIndex)->player;
                    if(FairyList.at(i)->scroll == true) //this is a scroll fairy
                    {
                       GServer->Config.ScrollFairy --; //reduce count of scroll fairies by one
                       if(GServer->Config.ScrollFairy < 0)GServer->Config.ScrollFairy = 0; //Make sure we don't go negative
                       GServer->Config.FairyMax = (int)ceil((float)GServer->ClientList.size() / 50.0) + GServer->Config.ScrollFairy; //recalculate the maximum number of fairies
                       FairyList.at(i)->scroll = false; //reset scroll value
                    }
                    DoFairyFree(i);
                    oldclient->Fairy = false;
                    oldclient->FairyListIndex = 0;
                    DoFairyStuff(oldclient, 0);  // unspawn fairy
                    oldclient->SetStats();
                }
           }
        }
        // this close fairies after their time if GM de activate  fairy mode when some fairies are assigned.
        if (Config.FairyMode == 0 && ClientList.size() > 1){    // if serevr mode off and someone online
             for (int i=0; i<Config.FairyMax; i++)
             {
                 if ( (FairyList.at(i)->LastTime + (Config.FairyStay*60*CLOCKS_PER_SEC)) <= clock() && FairyList.at(i)->assigned)
    			{
                    CPlayer* oldclient  = (CPlayer*) ClientList.at(FairyList.at(i)->ListIndex)->player;
                    DoFairyFree(i);
                    oldclient->Fairy = 0;
                    oldclient->FairyListIndex = 0;
                    DoFairyStuff(oldclient, 0);
                    oldclient->SetStats();
                }
             }
         }
}
