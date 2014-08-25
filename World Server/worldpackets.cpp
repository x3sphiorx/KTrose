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

//  Send Characters information
void CWorldServer::pakPlayer( CPlayer *thisclient )
{
     unsigned cbyte = 0;
    CRespawnPoint* thisrespawn = GetRespawnByID( thisclient->Position->respawn );
    if(thisclient->Position->saved == 20&&thisrespawn->destMap!=20)
        thisclient->Position->saved = 22;
    if(thisrespawn != NULL)
    {
        thisclient->Position->destiny = thisrespawn->dest;
        thisclient->Position->current = thisclient->Position->destiny;
        //Log(MSG_DEBUG,"(pakPlayer) Destiny and current set to X: %f Y: %f.",thisclient->Position->current.x,thisclient->Position->current.y);
        thisclient->Position->Map = thisrespawn->destMap;
    }
    else
    {
        thisclient->Position->destiny.x = 5300;
        thisclient->Position->destiny.y = 5200;
        thisclient->Position->current = thisclient->Position->destiny;
        thisclient->Position->Map = 1;
    }
    CMap* map = MapList.Index[thisclient->Position->Map];
    map->AddPlayer( thisclient );
    BEGINPACKET(pak, 0x715);
    ADDBYTE( pak, thisclient->CharInfo->Sex );                 // Sex
    ADDWORD( pak, thisclient->Position->Map );                 // Map
    ADDFLOAT( pak, thisclient->Position->current.x*100 );      // Pos X
    ADDFLOAT( pak, thisclient->Position->current.y*100 );      // Pos Y
    ADDWORD( pak, thisclient->Position->saved );
    ADDDWORD( pak, thisclient->CharInfo->Face );               // Face
    ADDDWORD( pak, thisclient->CharInfo->Hair );               // Hair
    ADDDWORD( pak, BuildItemShow(thisclient->items[2]) );      // Cap
    ADDDWORD( pak, BuildItemShow(thisclient->items[3]) );      // Body
    ADDDWORD( pak, BuildItemShow(thisclient->items[5]) );      // Gloves
    ADDDWORD( pak, BuildItemShow(thisclient->items[6]) );      // Boots
    ADDDWORD( pak, BuildItemShow(thisclient->items[1]) );      // Face
    ADDDWORD( pak, BuildItemShow(thisclient->items[4]) );      // Back
    ADDDWORD( pak, BuildItemShow(thisclient->items[7]) );      // Weapon
    ADDDWORD( pak, BuildItemShow(thisclient->items[8]) );      // SubWeapon
    ADDBYTE( pak, 0x01 );                                      // Birth Stone
    ADDBYTE( pak, 0x00 );
    ADDBYTE( pak, 0x00 );
    ADDWORD( pak, thisclient->CharInfo->Job );                 // Job
    ADDBYTE( pak, thisclient->Union_s->unionvar[0]);           // Union Variable [0]
    ADDBYTE( pak, 0x00 );                                      //rank
    ADDBYTE( pak, 0x00 );                                      //fame
    ADDWORD( pak, thisclient->Attr->Str );                     // Str
    ADDWORD( pak, thisclient->Attr->Dex );                     // Dex
    ADDWORD( pak, thisclient->Attr->Int );                     // Int
    ADDWORD( pak, thisclient->Attr->Con );                     // Con
    ADDWORD( pak, thisclient->Attr->Cha );                     // Cha
    ADDWORD( pak, thisclient->Attr->Sen );                     // Sen
    ADDWORD( pak, thisclient->Stats->HP );                     // Current HP
    ADDWORD( pak, thisclient->Stats->MP );                     // Current MP
    ADDWORD( pak, thisclient->CharInfo->Exp );                 // Exp
    ADDWORD( pak, 0x0000 );
    ADDWORD( pak, thisclient->Stats->Level );                  // Level
    ADDWORD( pak, thisclient->CharInfo->StatPoints );          // Stat Points
    ADDWORD( pak, thisclient->CharInfo->SkillPoints );         // Skill Points
    ADDBYTE( pak, 0x64 );                                      // Body Size
    ADDBYTE( pak, 0x64 );                                      // Head Size
    ADDWORD( pak, 0x0000 );
    ADDWORD( pak, 0x0000 );
    ADDWORD( pak, 0x0000 );
    ADDWORD( pak, 0x0000 );
    ADDWORD( pak, thisclient->Union_s->unionvar[1] );//union points Junon Order
    ADDWORD( pak, thisclient->Union_s->unionvar[2] );//union points
    ADDWORD( pak, thisclient->Union_s->unionvar[3] );//union points
    ADDWORD( pak, thisclient->Union_s->unionvar[4] );//union points
    ADDWORD( pak, thisclient->Union_s->unionvar[5] );//union points
    ADDWORD( pak, thisclient->Union_s->unionvar[6] );//union points
    ADDWORD( pak, thisclient->Union_s->unionvar[7] );//union points
    ADDWORD( pak, thisclient->Union_s->unionvar[8] );//union points
    ADDWORD( pak, thisclient->Union_s->unionvar[9] );//union points
    ADDWORD( pak, thisclient->Union_s->unionvar[10] );//union point
    ADDWORD( pak, 0x0000 );
    ADDWORD( pak, 0x0000 );
    ADDWORD( pak, 0x0000 );
    ADDWORD( pak, 0x0000 );
    ADDBYTE( pak, 0x00 );
    ADDWORD( pak, thisclient->CharInfo->stamina );                       // Stamina

    for(short i=0; i<326; i++)
        ADDBYTE( pak, 0x00 );
  for (char i=0; i<30; i++)
        ADDWORD( pak, thisclient->bskills[i] );//Basic skills
    for (char i=0; i<30; i++)
        ADDWORD( pak, thisclient->askill[i]+thisclient->askilllvl[i] );//Active skills
    for (char i=0; i<30; i++)
        ADDWORD( pak, thisclient->pskill[i]+thisclient->pskilllvl[i] );//Passive skills
    for(short i=0; i<60; i++)//unused ????
        ADDBYTE( pak, 0 );
    for (char i=0; i<32; i++)
        ADDWORD( pak, thisclient->quickbar[i] );        // QUICKBAR ROW 1 STARTS
    ADDWORD( pak, thisclient->CharInfo->charid );
    ADDWORD( pak, 0x00 );
    for(unsigned j = 0; j < strlen(thisclient->CharInfo->charname); j++)
    {
        ADDBYTE(pak, thisclient->CharInfo->charname[j] );
    }

    ADDBYTE( pak, 0x00 );
    ADDBYTE( pak, 0x00 );
    thisclient->client->SendPacket( &pak );
}

//  Send Inventory Information
void CWorldServer::pakInventory( CPlayer *thisclient )
{
    unsigned cbyte=0;
	STARTPACKET(pak, 0x716, 854 );
	SETQWORD( pak, 0x000, thisclient->CharInfo->Zulies );
	cbyte += 8;
	for(unsigned j=0; j<140; j++)
    {
       	//Log(MSG_INFO,"slot: %i itemid: %i type: %i count: %i",j, thisclient->items[j].itemnum,thisclient->items[j].itemtype,thisclient->items[j].count);
        SETWORD( pak, cbyte+0, BuildItemHead( thisclient->items[j] ) );
       	SETDWORD( pak, cbyte+2, BuildItemData( thisclient->items[j] ) );
		cbyte += 6;
	}
	cbyte-= 6;
    thisclient->client->SendPacket( &pak );
}

//  Send Quest information
void CWorldServer::pakQuestData( CPlayer *thisclient )
{
    //Log( MSG_DEBUG, "Starting pakQuestData");
    CPacket pakout;
    //Log( MSG_DEBUG, "creating packet");
    pakout.StartPacket( 0x71b );
    //Log( MSG_DEBUG, "Starting packet");
    for(dword i = 0; i < 5; i++) pakout.AddWord(thisclient->quest.EpisodeVar[i]);
	//Log( MSG_DEBUG, "added episode vars");
    for(dword i = 0; i < 3; i++) pakout.AddWord(thisclient->quest.JobVar[i]);
	//Log( MSG_DEBUG, "added job vars");
    for(dword i = 0; i < 7; i++) pakout.AddWord(thisclient->quest.PlanetVar[i]);
	//Log( MSG_DEBUG, "added planet vars");
    for(dword i = 0; i < 10; i++) pakout.AddWord(thisclient->quest.UnionVar[i]);
    //Log( MSG_DEBUG, "added union vars");
    for( unsigned i = 0; i < 10; i++ )
    {
        //Log( MSG_DEBUG, "starting main loop %i",i);
        pakout.AddWord( thisclient->quest.quests[i].QuestID );
        //Log( MSG_DEBUG, "added quest ID");
        long int Time = 0;
        //Log( MSG_DEBUG, "Initialized Time");
        //Log( MSG_DEBUG, "This Quest quest id = %i",thisclient->quest.quests[i].QuestID);
        //Log( MSG_DEBUG, "This Quest STB quest id = %i",STB_QUEST.rows[thisclient->quest.quests[i].QuestID][1]);
        if (thisclient->quest.quests[i].QuestID > 0 && STB_QUEST.rows[thisclient->quest.quests[i].QuestID][1] > 0)
        {
            //Log( MSG_DEBUG, "client has a timed quest");
            Time += thisclient->quest.quests[i].StartTime; // Start time
            Time += STB_QUEST.rows[thisclient->quest.quests[i].QuestID][1] * 10; // Time to finish
            Time -= time(NULL); // Current time
            if (Time < 0) Time = 0; // Time is up
            Time /= 10; // Divide to get 10's of seconds
            //Log( MSG_DEBUG, "Timed variables set %i",Time);
        }
        //Log( MSG_DEBUG, "end of time quest conditional");
        pakout.AddDWord( Time ); // Time Left
        //Log( MSG_DEBUG, "Time added");

        for(dword j = 0; j < 10; j++) pakout.AddWord(thisclient->quest.quests[i].Variables[j]);
        //Log( MSG_DEBUG, "added quest vars");
        for(dword j = 0; j < 4; j++) pakout.AddByte(thisclient->quest.quests[i].Switches[j]);
        //Log( MSG_DEBUG, "added quest switches");
        for(dword j = 0; j < 6; j++)
        {
            if (thisclient->quest.quests[i].Items[j].itemnum != 0)
            {
                pakout.AddWord( thisclient->quest.quests[i].Items[j].GetPakHeader() );
                pakout.AddDWord( thisclient->quest.quests[i].Items[j].GetPakData() );
            }
            else
            {
                pakout.AddWord( 0 );
                pakout.AddDWord( 0 );
            }
        }
    }
    //Log( MSG_DEBUG, "finished main quest loop");
    // testing out new PY quest flag method
    for( unsigned i = 0; i < 0x40; i++ )
    {
        byte tempval = 0;
        for(int j=0;j<8;j++)
        {
            tempval += (byte)thisclient->quest.Qflags[i][j] * (int)pow(2,j);
        }
        pakout.AddByte(tempval);
        //pakout.AddByte( thisclient->quest.flags[i] );
    }
    //Log( MSG_DEBUG, "finished quest flags");
    // Wishlist? - Not Implemented
    for (unsigned i = 0; i < 180; i++)
        pakout.AddByte( 0 );
    //Log( MSG_DEBUG, "Finished loading all the stuff into pakout");
    thisclient->client->SendPacket( &pakout );
}

// Handle quest triggers
bool CWorldServer::pakQuestTrigger( CPlayer* thisclient, CPacket* pak )
{
  byte action = pak->GetByte( 0 );
  // action 1 = send text
  // action 2 = delete quest
  // action 3 = get quest
  // action 4 = unknown
  // action 5 = success

  byte slot = pak->GetByte( 1 );
  dword hash = pak->GetDWord( 2 );

  if( thisclient->questdebug ) SendPM( thisclient, "Event Trigger recieved [%08x] Action %i", hash, action);

  if (action == 2)
  {
      if( thisclient->questdebug ) SendPM( thisclient, "Delete quest - Slot %i", slot);
      for (dword i = slot; i < 9; i++) thisclient->quest.quests[i] = thisclient->quest.quests[i+1];
      thisclient->quest.quests[9].Clear();
      CPacket pakout(0x730);
      pakout.AddByte(0x03);
      pakout.AddByte(slot);
      pakout.AddDWord(hash);
      thisclient->client->SendPacket(&pakout);
      return true;
  }
  if (action != 3) return false;
  int success = thisclient->ExecuteQuestTrigger(hash);
  CPacket pakout(0x730);
  pakout.AddByte(success);
  pakout.AddByte(0);
  pakout.AddDWord(hash);
  thisclient->client->SendPacket(&pakout);
  return true;
}

//  Get this user set up with the encryption and stuff
bool CWorldServer::pakDoIdentify( CPlayer *thisclient, CPacket *P )
{
	MYSQL_ROW row;
	thisclient->Session->userid = GETDWORD((*P), 0);
	memcpy( thisclient->Session->password, &P->Buffer[4], 32 );
	MYSQL_RES *result = DB->QStore("SELECT username,lastchar,accesslevel,zulystorage,ktpoints,newpoints,logtime,totlogtime FROM accounts WHERE id=%i AND password='%s'", thisclient->Session->userid, thisclient->Session->password);
    if(result==NULL) return false;
	if (mysql_num_rows( result ) != 1)
    {
		Log( MSG_HACK, "Someone tried to connect to world server with an invalid account" );
		DB->QFree( );
		return false;
	}
	Log( MSG_DEBUG, "Loading Session Data" );
	row = mysql_fetch_row(result);
	strncpy( thisclient->Session->username, row[0],16 );
	strncpy( thisclient->CharInfo->charname, row[1],16 );
	thisclient->Session->accesslevel = atoi(row[2]);
	thisclient->CharInfo->Storage_Zulies = atoi( row[3] );
	thisclient->Session->KTPoints = atoi(row[4]);       //load KTPoints
	thisclient->Session->NewPoints = atoi(row[5]);      //load newPoints. This is where additional KTPoints are added when they are purchased
	thisclient->Session->logtime = atoi(row[6]);        //current log time in hours.
	thisclient->Session->TotalLogTime = atoi(row[7]);   //total log time for this account
	thisclient->Session->award = 0;
	thisclient->Session->RespawnChoice = 0;
	thisclient->Session->Respawned = 0;
	thisclient->Session->inGame = true;
    DB->QFree( );
    if(thisclient->Session->NewPoints != 0)
	{
        // Add NewPoints to KTPoints
        //Log( MSG_DEBUG, "Loaded up some new KTPoints and stuff" );
        thisclient->Session->KTPoints += thisclient->Session->NewPoints;
        // Set newpoints to zero both here and in the database
        thisclient->Session->NewPoints = 0;
        GServer->DB->QExecute("UPDATE accounts SET newpoints=%i, ktpoints=%i WHERE id=%i AND password='%s'",
                    thisclient->Session->NewPoints,thisclient->Session->KTPoints,thisclient->Session->userid, thisclient->Session->password);
        //GServer->DB->QExecute("UPDATE accounts SET ktpoints=%i WHERE id=%i AND password='%s'",
        //            thisclient->Session->KTPoints,thisclient->Session->userid, thisclient->Session->password);
    }
    if (thisclient->Session->logtime >= Config.KTPointRate) //make the KTPoint reward system variable
    {
        while(thisclient->Session->logtime > Config.KTPointRate)
        {
            thisclient->Session->logtime -= Config.KTPointRate;
            thisclient->Session->award ++;
        }
        thisclient->Session->KTPoints += thisclient->Session->award;
        //thisclient->Union_s->unionvar[9] = thisclient->Session->KTPoints;
        GServer->DB->QExecute("UPDATE accounts SET ktpoints=%i,logtime=%i WHERE id=%i AND password='%s'",
            thisclient->Session->KTPoints, thisclient->Session->logtime, thisclient->Session->userid, thisclient->Session->password);
    }

	if(!thisclient->loaddata( )) return false;
	Log( MSG_INFO, "User '%s'(#%i) logged in with character '%s'", thisclient->Session->username, thisclient->Session->userid, thisclient->CharInfo->charname);
	BEGINPACKET( pak, 0x070c );
	ADDBYTE    ( pak, 0 );
	ADDDWORD   ( pak, 0x87654321 );
	ADDDWORD   ( pak, 0x00000000 );
	thisclient->client->SendPacket( &pak );
    pakPlayer(thisclient);
    //Log( MSG_DEBUG, "ran pakPlayer");
    pakInventory(thisclient);
    //Log( MSG_DEBUG, "ran pakInventory");
    pakQuestData(thisclient);
    //Log( MSG_DEBUG, "ran pakQuestData");

    RESETPACKET( pak, 0x7de );
    ADDWORD ( pak, 0x1001 ); // 0x1001 to 0x1013 (game plan?)
    ADDDWORD ( pak, 2 ); // options (plan time?) [2 = unlimited]
    thisclient->client->SendPacket( &pak );

	// Welcome message to the server
	RESETPACKET( pak, 0x702 );
	ADDSTRING  ( pak, Config.WELCOME_MSG );
	ADDBYTE    ( pak, 0 );
	thisclient->client->SendPacket( &pak );
	SendSysMsg( thisclient, "Pre-Evolution server presented by SpiritFox productions and Kuro-Tejina " );
	thisclient->SetStats( );

	if(thisclient->Session->award != 0)
	{
        char buffer[200];
        sprintf ( buffer, "You have been awarded %i KTPoints for time logged into the server",thisclient->Session->award);
        SendSysMsg(thisclient, buffer);

    }
	return true;

}


//  Give the user an ID
bool CWorldServer::pakDoID( CPlayer* thisclient, CPacket* P )
{
	// Assign a new id to this person
   	thisclient->clientid = GetNewClientID();
	if (thisclient->clientid <= 0)
    {
		Log( MSG_WARNING, "User '%s'(#%i) denied access. Server is full.", thisclient->Session->username, thisclient->Session->userid );
		return false;
	}
	Log( MSG_INFO, "User '%s'(#%i) assigned id #%i", thisclient->Session->username, thisclient->Session->userid, thisclient->clientid );
    //Log( MSG_DEBUG, "User Session Ingame = %i", thisclient->Session->inGame);
    //thisclient->Session->inGame = true;
    if( thisclient->Party->party )
    {
        BEGINPACKET( pak, 0x7d5 );
        ADDDWORD   ( pak, thisclient->CharInfo->charid );
        ADDWORD    ( pak, thisclient->clientid );
        ADDWORD    ( pak, thisclient->GetMaxHP( ) );
        ADDWORD    ( pak, thisclient->Stats->HP );
        ADDDWORD   ( pak, 0x01000000 );
        ADDDWORD   ( pak, 0x0000000f );
        ADDWORD    ( pak, 0x1388 );
        thisclient->Party->party->SendToMembers( &pak, thisclient );
    }
	BEGINPACKET( pak, 0x721 );
    ADDWORD    ( pak, 0x0022 );
    ADDWORD    ( pak, 0x0002 );
    ADDWORD    ( pak, 0x0000 );
    thisclient->client->SendPacket( &pak );
    //Log( MSG_DEBUG, "Packet 0x721 sent");
    RESETPACKET( pak, 0x753 );
    ADDWORD    ( pak, thisclient->clientid );			// USER ID
    //Log( MSG_DEBUG, "User ID added");
    ADDWORD    ( pak, thisclient->Stats->HP );		// CURRENT HP
    //Log( MSG_DEBUG, "Current HP added");
    ADDWORD    ( pak, thisclient->Stats->MP );		// CURRENT MP
    //Log( MSG_DEBUG, "Current MP added");
    ADDDWORD   ( pak, thisclient->CharInfo->Exp );				// CURRENT EXP
    ADDDWORD   ( pak, 0x00000000 );						// LVL EXP (UNSUSED)
    //Log( MSG_DEBUG, "Current XP added");
    //Log( MSG_DEBUG, "Basic info added");
    // thanks to StrikeX to post this source
        //[economy]
        /*
    ADDWORD    ( pak, 0x0063 );  // World Rate
    ADDBYTE    ( pak, 0x70 );
    ADDBYTE    ( pak, 0x69 );
    ADDBYTE    ( pak, 0x68 );
    ADDBYTE    ( pak, 0x67 );
    ADDWORD    ( pak, 0x0062 );  // Town rate
    ADDBYTE    ( pak, 0x61 );  // misc rate
    ADDBYTE    ( pak, 0x32 );  //1
    ADDBYTE    ( pak, 0x32 );  //2
    ADDBYTE    ( pak, 0x32 );  //3
    ADDBYTE    ( pak, 0x32 );  //4
    ADDBYTE    ( pak, 0x32 );  //5
    ADDBYTE    ( pak, 0x32 );  //6
    ADDBYTE    ( pak, 0x32 );  //7
    ADDBYTE    ( pak, 0x32 );  //8
    ADDBYTE    ( pak, 0x32 );  //9
    ADDBYTE    ( pak, 0x32 );  //10
    ADDBYTE    ( pak, 0x32 );  //11
    */
    ADDWORD    ( pak, 0x0064 );    //world rate
    ADDDWORD   ( pak, 0x0C1F4B79);//0x1841f50b );
    ADDWORD    ( pak, 0x0064 );    //town rate
    ADDDWORD   ( pak, 0x3232cd50 );
    ADDDWORD   ( pak, 0x32323235 );
    ADDDWORD   ( pak, 0x35323232 );
    //Log( MSG_DEBUG, "rates added");
    CMap* map = MapList.Index[thisclient->Position->Map];
    //Log( MSG_DEBUG, "position added");
    if(map->allowpvp!=0)
        ADDWORD(pak, 0x0001)//player vs player map
    else
        ADDWORD(pak, 0x0000)//non player vs player map
    ADDWORD    (pak, 0x0000 );//??
    // Map Time
    ADDDWORD( pak, map->MapTime );
    //ADDBYTE    ( pak, 0xde );// (new)
    //ADDWORD    ( pak, 0x0008 );//this change something in the mapicon (time) (new)
    if(map->allowpvp==1)
    {
        ADDWORD(pak, 0x0000 );//red icon (map)
        ADDWORD(pak, 0x0005 );//red icon (map)
    } // pvp all vs all
    else if(map->allowpvp==2) // pvp group vs group
    {
        /*ADDWORD(pak, thisclient->Clan->clanid );*/
        ADDWORD(pak, 51);
    }
    else
    {
        ADDWORD(pak, 0x0002 );//white icon (map)
        ADDWORD(pak, 0x0000 );//white icon (map)
    }
    thisclient->client->SendPacket( &pak );
    //Log( MSG_DEBUG, "Sent 0x753 packet");
    // Sort out weight stuff, make user not able to run if overweight
    int weight = ( thisclient->GetCurrentWeight() / thisclient->GetMaxWeight() ) * 100;
    if(weight>110)
        thisclient->Status->CanAttack = false;
    else
        thisclient->Status->CanAttack = true;
    if(weight>100)
        thisclient->Status->CanRun = false;
    else
        thisclient->Status->CanRun = true;

    thisclient->Stats->Move_Speed = thisclient->GetMoveSpeed( );
    RESETPACKET( pak, 0x762 );
    ADDWORD    ( pak, thisclient->clientid );
    ADDBYTE    ( pak, weight );
    thisclient->client->SendPacket( &pak );
    // set speed
	RESETPACKET(pak, 0x782 );
	ADDWORD    ( pak, thisclient->clientid );
	ADDBYTE    ( pak, thisclient->Status->Stance );
	ADDWORD    ( pak, thisclient->Stats->Mspd_base );
	SendToVisible( &pak, thisclient );
    thisclient->CleanPlayerVector( );
	thisclient->Session->inGame = true;
	thisclient->Session->Respawned = 0;
	//Log( MSG_DEBUG, "Completed DoID");
	return true;
}

// Move Characters in map
bool CWorldServer::pakMoveChar( CPlayer* thisclient, CPacket* P )
{
    if( thisclient->Shop->open || (!thisclient->Ride->Drive && thisclient->Ride->Ride) || !thisclient->Status->CanMove )
        return true;
    thisclient->UpdatePosition( );
    thisclient->Position->lastMoveTime = clock();
    if( thisclient->Status->Stance == SITTING )
        thisclient->Status->Stance = RUNNING;
    ClearBattle( thisclient->Battle );
    thisclient->Battle->target = GETWORD((*P), 0x00 );
    thisclient->Position->destiny.x = GETFLOAT((*P), 0x02 )/100;
    thisclient->Position->destiny.y = GETFLOAT((*P), 0x06 )/100;
    if(thisclient->Ride->Drive) //update the destination for anyone riding in the back of my cart
    {
        CPlayer* otherclient = GServer->GetClientByCID( thisclient->Ride->charid );
        if(otherclient != NULL)
        {
            otherclient->Stats->Move_Speed = thisclient->Stats->Move_Speed;
            otherclient->Position->destiny.x = GETFLOAT((*P), 0x02 )/100;
            otherclient->Position->destiny.y = GETFLOAT((*P), 0x06 )/100;
            otherclient->UpdatePosition( );
            //hmm not sending an update packet regarding otherclient are we? Do we need a packet here?
            BEGINPACKET( pak1, 0x79a );
            ADDWORD    ( pak1, otherclient->clientid );		// USER ID
            ADDWORD    ( pak1, otherclient->Battle->target );		// TARGET
            //LMA: it's in fact the distance from current to destiny and not the base speed...
            ADDWORD    ( pak1, (DWORD) (distance(otherclient->Position->current,otherclient->Position->destiny)*100));
            //ADDWORD    ( pak, thisclient->Stats->Move_Speed );	// MSPEED
            ADDFLOAT   ( pak1, GETFLOAT((*P), 0x02 ) );	// POSITION X
            ADDFLOAT   ( pak1, GETFLOAT((*P), 0x06 ) );	// POSITION Y
            ADDWORD    ( pak1, GETWORD((*P), 0x0a ) );		// POSITION Z (NOT USED)
            SendToVisible( &pak1, otherclient );
        }
    }
    BEGINPACKET( pak, 0x79a );
    ADDWORD    ( pak, thisclient->clientid );		// USER ID
    ADDWORD    ( pak, thisclient->Battle->target );		// TARGET
    //LMA: it's in fact the distance from current to destiny and not the base speed...
    ADDWORD    ( pak, (DWORD) (distance(thisclient->Position->current,thisclient->Position->destiny)*100));
    //ADDWORD    ( pak, thisclient->Stats->Move_Speed );	// MSPEED
    ADDFLOAT   ( pak, GETFLOAT((*P), 0x02 ) );	// POSITION X
    ADDFLOAT   ( pak, GETFLOAT((*P), 0x06 ) );	// POSITION Y
    ADDWORD    ( pak, GETWORD((*P), 0x0a ) );		// POSITION Z (NOT USED)
    SendToVisible( &pak, thisclient );
    //Log(MSG_DEBUG,"Recieved move command and set destiny to X: %f Y: %f.",thisclient->Position->destiny.x,thisclient->Position->destiny.y);
	return true;
}

// Stop Character movement
bool CWorldServer::pakStopChar( CPlayer* thisclient, CPacket* P )
{
    ClearBattle( thisclient->Battle );
	thisclient->Position->destiny.x = GETFLOAT((*P), 0x00 )/100;
    thisclient->Position->destiny.y = GETFLOAT((*P), 0x04 )/100;
    thisclient->Position->current=thisclient->Position->destiny;
	BEGINPACKET( pak, 0x770 );
	ADDWORD    ( pak, thisclient->clientid );		// USER ID
	ADDFLOAT   ( pak, thisclient->Position->destiny.x*100 );	// POSITION X
	ADDFLOAT   ( pak, thisclient->Position->destiny.y*100 );	// POSITION Y
	ADDWORD    ( pak, GETWORD((*P), 0x08 ) );		// POSITION Z (NOT USED)
	SendToVisible( &pak, thisclient );
	return true;
}

// Spawn NPC
bool CWorldServer::pakSpawnNPC( CPlayer* thisclient, CNPC* thisnpc )
{
	//Log(MSG_DEBUG,"spawning NPC type %i at X: %f Y: %f.",thisnpc->npctype,thisnpc->pos.x,thisnpc->pos.y);
	BEGINPACKET( pak, 0x791 );
    ADDWORD( pak, thisnpc->clientid );
	ADDFLOAT( pak, thisnpc->pos.x*100 );
    ADDFLOAT( pak, thisnpc->pos.y*100 );
    ADDWORD( pak, 0xcdcd );
    ADDWORD( pak, 0xcdcd );
    ADDWORD( pak, 0xcdcd );
    ADDWORD( pak, 0xcdcd );
	ADDBYTE( pak, 0x00 );
    ADDWORD( pak, 0x0000 );
	ADDWORD( pak, 0x0000 );
	ADDWORD( pak, 0x03e8 );
	ADDWORD( pak, 0x0000 );
	ADDWORD( pak, 0x0001 );
	ADDWORD( pak, 0x0000 );//Buffs
	ADDWORD( pak, 0x0000 );//Buffs
	ADDWORD( pak, 0x0000 );//buffs
	ADDWORD( pak, thisnpc->npctype );
    if(thisnpc->thisnpc->dialogid != 0)
    {
        ADDWORD( pak, thisnpc->thisnpc->dialogid );
    }
    else
    {// fixed by tomiz [npc dialogs fixed [still not all]]
         unsigned int factor = 900;
        //if (thisnpc->npctype >= 1000 && thisnpc->npctype <=1041 || thisnpc->npctype >= 1043 && thisnpc->npctype <=1084 || thisnpc->npctype >= 1086 && thisnpc->npctype <=1119 || thisnpc->npctype >= 1131 && thisnpc->npctype <=1199 || thisnpc->npctype >= 1207 && thisnpc->npctype <=1299) factor=900;
       	//else if (thisnpc->npctype >= 1200 && thisnpc->npctype <=1203) factor=896; // event npc
        //else if (thisnpc->npctype == 1042 ) factor=899;  // Storage Adventure Plain -> Fabrizio - Junon Clan Field -> Nell
        //else if (thisnpc->npctype == 1081 ) factor=300;
        //else if (thisnpc->npctype == 1085 ) factor=901;
        //else if (thisnpc->npctype == 1205 ) factor=901;  //santa
        //else if (thisnpc->npctype == 1206 ) factor=1019;  //Loelsch
        //else if (thisnpc->npctype == 1120 ) factor=896;  // dunno if that dialog are corect 1120 [Clan Clerk] Regina
        //else if (thisnpc->npctype == 1204 ) factor=897;  // event npc another warp to zant dialog npc 1203 [Event Info] Lucielle Fete
        //else if (thisnpc->npctype == 1473 ) factor=1457; // should be ok 1473 Melendino adventure plain
        //else if (thisnpc->npctype == 1752 ) factor=1528; // Clan Merchant Aliche Patt ver 141
        //else if (thisnpc->npctype >= 1122 && thisnpc->npctype <=1130) factor=905;
        //else if (thisnpc->npctype == 1502 ) factor=1198;  //santa
        //else if (thisnpc->npctype >= 1503 && thisnpc->npctype <=1599) factor=1210;
        //else if (thisnpc->npctype >= 1750 && thisnpc->npctype <=1755 || !thisnpc->npctype == 1752 ) factor=1000; //should be ok
        ADDWORD( pak, thisnpc->npctype - factor );
    }
	ADDFLOAT( pak, thisnpc->dir );
    //if(thisnpc->npctype == 1115)
    //{
    //    ADDBYTE( pak, GServer->Config.Cfmode ); // Burland Clan Field open/close
    //    ADDBYTE ( pak, 0 );
    //}
    //else
    //{
        if(thisnpc->thisnpc->eventid != 0)
        {
            ADDWORD (pak, thisnpc->thisnpc->eventid);
        }
        else
        {
            ADDWORD( pak, 0 );
        }
    //}
    thisclient->client->SendPacket( &pak );
	return true;
}

// Changes stance
bool CWorldServer::pakChangeStance( CPlayer* thisclient, CPacket* P )
{
 /*    #define ATTACKING 1
       #define WALKING 2
       #define RUNNING 3
       #define DRIVING 4
       #define SITTING
       run-walk-run stancenum == 0
       sit-stand-sit stancenum == 1
       drive-no drive-drive == 2
*/
    if(thisclient->Shop->open)
        return true;
	BYTE stancenum = GETBYTE((*P),0x00);
	BYTE newstancenum = stancenum;
	switch (stancenum)
	{
           case 0:
                if(thisclient->Status->Stance == RUNNING) //change 3 to 2 running to walking
                {
                     newstancenum = 2;
                     thisclient->Status->Stance = WALKING;
                }
                else if(thisclient->Status->Stance == WALKING) // Running
                {
                    newstancenum = 3;
                    thisclient->Status->Stance = RUNNING;
                }
                break;
           case 1:
                if (thisclient->Status->Stance == RUNNING||thisclient->Status->Stance == WALKING)//>Status->Stance!=DRIVING && thisclient->Status->Stance>0x01)
                {
                    newstancenum = 1;
                    thisclient->Status->Stance = SITTING;
                }
                else if (thisclient->Status->Stance == SITTING)//(thisclient->Status->Stance<0x04)
                {
                     newstancenum = 3;
                     thisclient->Status->Stance = RUNNING;
                }
                break;
           case 2:
                if (thisclient->Status->Stance==RUNNING || thisclient->Status->Stance==WALKING) //getting in a cart
                {// Clean Buff
                    newstancenum = 4;
                    thisclient->Status->Stance = DRIVING;
                    thisclient->Ride->Ride = false;
                    thisclient->Ride->Drive = true;
                    thisclient->Ride->charid = 0;
                }
                else if (thisclient->Status->Stance==DRIVING) //getting out of cart
                {// Clean Buff
                    newstancenum = 3;
                    thisclient->Status->Stance = RUNNING;
                    thisclient->Ride->Ride = false;
                    thisclient->Ride->Drive = false;
                    thisclient->Ride->charid = 0;
                }
                break;
           default:
                newstancenum = 3;
                thisclient->Status->Stance = RUNNING;
                break;
    }
//	if(!thisclient->Status->CanMove)
//	   thisclient->Status->Stance = RUNNING;
    if (!thisclient->Status->CanRun && newstancenum == 3) {
        newstancenum = 2;
        thisclient->Status->Stance = WALKING;
    }
	thisclient->Stats->Move_Speed = thisclient->GetMoveSpeed( );
	BEGINPACKET( pak, 0x782 );
	ADDWORD( pak, thisclient->clientid );
	ADDBYTE( pak, newstancenum );
	//ADDWORD( pak, thisclient->Stats->Move_Speed );
	SendToVisible( &pak, thisclient );

	//Log( MSG_INFO, "Stancenum %i newstancenum %i Stance %i", stancenum, newstancenum, thisclient->Status->Stance);
	return true;
}

// Spawn Drop
bool CWorldServer::pakSpawnDrop( CPlayer* thisclient, CDrop* thisdrop )
{
	BEGINPACKET( pak, 0x7a6 );
	ADDFLOAT( pak, thisdrop->pos.x*100 );
	ADDFLOAT( pak, thisdrop->pos.y*100 );
	if (thisdrop->type==1)
    {
		// -- ZULY --
		ADDWORD( pak, 0xccdf );//0xccccccdf );
		ADDDWORD( pak, thisdrop->amount );
		ADDWORD( pak, thisdrop->clientid );
		ADDWORD( pak, 0x0000 );
		ADDWORD( pak, 0x5f90 );
	}
    else
    {
		// -- ITEM --
		ADDWORD( pak, BuildItemHead( thisdrop->item ) );
		ADDDWORD( pak, thisdrop->amount );
		ADDWORD( pak, thisdrop->clientid );
		ADDDWORD( pak, BuildItemData( thisdrop->item ) );
	}
	thisclient->client->SendPacket( &pak );
	return true;
}

// Player Left
void CWorldServer::pakClearUser( CPlayer* thisclient )
{
	BEGINPACKET( pak, 0x794 );
	ADDWORD( pak, thisclient->clientid );
	SendToVisible( &pak, thisclient, false );
}

// Drop items on map
bool CWorldServer::pakDoDrop( CPlayer* thisclient, CPacket* P )
{
	BYTE itemid = GETBYTE((*P), 0x0);
	if(!CheckInventorySlot(thisclient, itemid ))
	   return false;
	DWORD amount = GETDWORD((*P), 0x1);
	if (itemid == 0)
    {
		if ( amount<1 ) return true;
		if ( thisclient->CharInfo->Zulies < amount ) return true;
		CDrop* thisdrop = new CDrop;
		assert(thisdrop);
		thisdrop->clientid = GetNewClientID();
		thisdrop->type = 1; // ZULY
		thisdrop->pos = RandInCircle( thisclient->Position->current, 3 );
		thisdrop->posMap = thisclient->Position->Map;
		thisdrop->droptime = time(NULL);
		thisdrop->amount = amount;
		thisdrop->owner = 0;
		CMap* map = MapList.Index[thisdrop->posMap];
		map->AddDrop( thisdrop );
		thisclient->CharInfo->Zulies -= amount;
		BEGINPACKET( pak, 0x71d );
		ADDQWORD( pak, thisclient->CharInfo->Zulies );
		thisclient->client->SendPacket( &pak );
	}
    else
    {
		CDrop* thisdrop = new CDrop;
		assert(thisdrop);
		thisdrop->clientid = GetNewClientID();
		thisdrop->type = 2; // ITEM
		thisdrop->pos = RandInCircle( thisclient->Position->current, 3 );
		thisdrop->posMap = thisclient->Position->Map;
		thisdrop->droptime = time(NULL);
		thisdrop->amount = amount;
		thisdrop->item = thisclient->items[itemid];
		thisdrop->item.count = amount;
		thisdrop->owner = 0;
		CMap* map = MapList.Index[thisdrop->posMap];
		map->AddDrop( thisdrop );
        // fixed by tomiz [item count drop correctly and dissaper from inventory]
        if(thisclient->items[itemid].itemtype >=10 && thisclient->items[itemid].itemtype <= 13)
        {
            if(thisclient->items[itemid].count<amount) return true;
           thisclient->items[itemid].count -= amount;
           if(thisclient->items[itemid].count <= 0) ClearItem(thisclient->items[itemid]);
        }
        else
        {
           ClearItem(thisclient->items[itemid]);
        }
        thisclient->UpdateInventory( itemid );
	}
	return true;
}

// Picks up item
bool CWorldServer::pakPickDrop( CPlayer* thisclient, CPacket* P )
{
    try
    {
        if(thisclient->Shop->open)
            return true;
        thisclient->RestartPlayerVal( );
    	WORD dropid = GETWORD((*P), 0x00);
    	CDrop* thisdrop = GetDropByID( dropid, thisclient->Position->Map );
    	if (thisdrop == NULL)
        {
            SendSysMsg( thisclient, "That is not a valid drop" );
            return true;
        }
    	if (thisdrop->item.itemnum > 250 && thisdrop->item.itemnum < 272 && thisdrop->item.itemtype == 7)//&&thisdrop->item.itemtype<174)//251/261/271/socket jewel 171Ring 172Necklace 173Earrings
    	{
            thisdrop->item.socketed = true;
            thisdrop->item.durability = 100;
            thisdrop->item.lifespan = 100;
            thisdrop->item.refine = 0;
            thisdrop->item.stats = 0;
        }
        //now find the item type for crafting
        if(thisdrop->item.itemtype > 0 && thisdrop->item.itemtype < 10)
            thisdrop->item.type = GServer->EquipList[thisdrop->item.itemtype].Index[thisdrop->item.itemnum]->type;
        if(thisdrop->item.itemtype == 10)
            thisdrop->item.type = GServer->UseList.Index[thisdrop->item.itemnum]->type;
        if(thisdrop->item.itemtype == 11)
            thisdrop->item.type = GServer->JemList.Index[thisdrop->item.itemnum]->type;
        if(thisdrop->item.itemtype == 12)
            thisdrop->item.type = GServer->NaturalList.Index[thisdrop->item.itemnum]->type;
        if(thisdrop->item.itemtype == 14)
            thisdrop->item.type = GServer->PatList.Index[thisdrop->item.itemnum]->type;

    	bool flag = false;
        BEGINPACKET( pak, 0x7a7 );
    	ADDWORD    ( pak, thisdrop->clientid );
        CPlayer* dropowner = 0;
        if( (thisdrop->owner == 0 || thisdrop->owner == thisclient->CharInfo->charid || time(NULL)-thisdrop->droptime >= 30 ) || ( thisclient->Party->party!=NULL && thisclient->Party->party == thisdrop->thisparty ))
        {
            if( thisclient->Party->party!=NULL )
            {
                unsigned int dropparty = thisclient->Party->party->Option/0x10;
                if( dropparty == 8 ) // Orderly
                {
                    unsigned int num = 0;
                    bool dpflag = false;
                    if( thisdrop->type == 1 )
                    {
                        num = thisclient->Party->party->LastZulies;
                        thisclient->Party->party->LastZulies++;
                        if( thisclient->Party->party->LastZulies>=thisclient->Party->party->Members.size() )
                            thisclient->Party->party->LastZulies = 0;
                    }
                    else
                    if( thisdrop->type == 2 )
                    {
                        num = thisclient->Party->party->LastItem;
                        thisclient->Party->party->LastItem++;
                        if( thisclient->Party->party->LastItem>=thisclient->Party->party->Members.size() )
                            thisclient->Party->party->LastItem = 0;
                    }
                    unsigned int n = 0;
                    while( !dpflag )
                    {
                        n++;
                        if( num>=thisclient->Party->party->Members.size() )
                            num = 0;
                        dropowner = thisclient->Party->party->Members.at( num );
                        if( dropowner == NULL )
                            num++;
                        else
                        {
                            dpflag = true;
                            num++;
                        }
                        if(n > 20) // not founded yet? >.>
                        {
                            dropowner = thisclient;
                            dpflag = true;
                        }
                    }
                }
                else // Equal Loot
                {
                    dropowner = thisclient;
                }
            }
            else
            {
                dropowner = thisclient;
            }
            if( thisdrop->type == 1 ) //Zulie
            {
    		    dropowner->CharInfo->Zulies += thisdrop->amount;
    		    ADDWORD( pak, 0 );
    		    ADDBYTE( pak, 0 );
    		    ADDWORD( pak, 0xccdf );
    		    ADDDWORD( pak, thisdrop->amount );
    		    dropowner->client->SendPacket( &pak );
    		    flag = true;
            }
            else
            if( thisdrop->type == 2 ) // Item
            {
                if (thisdrop->item.type == 320) //instant effect item
                {
                    RESETPACKET( pak,0x7a3 );
                    ADDWORD    ( pak, dropowner->clientid );
                    ADDWORD    ( pak, thisdrop->item.itemnum );
                    SendToVisible( &pak, dropowner );
                    flag = true;

                    switch (UseList.Index[thisdrop->item.itemnum]->useeffect[0])
                    {
                           case 16:
                                dropowner->Stats->HP += (UseList.Index[thisdrop->item.itemnum]->useeffect[1]);
                                if(dropowner->Stats->HP > dropowner->Stats->MaxHP )
                                   dropowner->Stats->HP = dropowner->Stats->MaxHP;
                                break;
                           case 17:
                                dropowner->Stats->MP += (UseList.Index[thisdrop->item.itemnum]->useeffect[1]);
                                if(dropowner->Stats->MP > dropowner->Stats->MaxMP )
                                   dropowner->Stats->MP = dropowner->Stats->MaxMP;
                                break;
                           case 76:
                                dropowner->CharInfo->stamina += (UseList.Index[thisdrop->item.itemnum]->useeffect[1]);
                                if(dropowner->CharInfo->stamina > 5000)
                                   dropowner->CharInfo->stamina = 5000;
                                break;
                           case 92:
                                if(dropowner->Clan->clanid>0)
                                {
                                dropowner->Clan->CP += (UseList.Index[thisdrop->item.itemnum]->useeffect[1]);
                                DB->QExecute( "UPDATE list_clan set cp=%i where id=%i", dropowner->Clan->CP,dropowner->Clan->clanid);
                                	RESETPACKET( pak, 0x7e0 );
    	                            ADDBYTE    ( pak, 0x5C ); //action to update clan points (charserver)
    	                            ADDWORD    ( pak, dropowner->Clan->clanid);
    	                            ADDWORD    ( pak, dropowner->clientid );
                                    ADDDWORD    ( pak, dropowner->Clan->CP );
                                    ADDWORD    ( pak, 0x00);
                                    SendISCPacket( &pak );
                                }
                                else
                                {
                                    Log( MSG_WARNING, "Player collected clanpoints but is not in a clan");
                                }
                                break;
                           default:
                                Log( MSG_WARNING, "Unknown autoconsume type: %i %i",(UseList.Index[thisdrop->item.itemnum]->usecondition[0]),(UseList.Index[thisdrop->item.itemnum]->usecondition[1]));
                                break;
                    }
                }
                else
                {
                    unsigned int tempslot = dropowner->AddItem( thisdrop->item );
                    if(tempslot != 0xffff)// we have slot
                    {
                        unsigned int slot1 = tempslot;
                        unsigned int slot2 = 0xffff;
                        if(tempslot > MAX_INVENTORY)
                        {
                            slot1 = tempslot / 1000;
                            slot2 = tempslot % 1000;
                        }
                        ADDBYTE    ( pak, 0x00 );
                        ADDBYTE    ( pak, slot1 );
                        ADDBYTE    ( pak, 0x00 );
                        ADDWORD    ( pak, BuildItemHead( dropowner->items[slot1] ) );
                        ADDDWORD   ( pak, BuildItemData( dropowner->items[slot1] ) );
                        dropowner->client->SendPacket( &pak );
                        dropowner->UpdateInventory( slot1, slot2 );
                        flag = true;
                    }
                    else
                    {
                        ADDBYTE    (pak, 0x03);
                        dropowner->client->SendPacket(&pak);
                    }
                }
            }
        }
    	else
    	{
    		ADDBYTE    (pak, 0x02);
    		thisclient->client->SendPacket(&pak);
        }
    	if( flag )
    	{
            if( thisclient->Party->party!=NULL )
            {
                unsigned int dropparty = thisclient->Party->party->Option/0x10;
                if( dropparty == 8 )
                {
                    RESETPACKET( pak, 0x7d3 );
                    ADDWORD    ( pak, dropowner->clientid );
                    if( thisdrop->type == 1 )
                    {
                        ADDWORD ( pak, 0xccdf );
            		    ADDDWORD( pak, thisdrop->amount );
                    }
                    else
                    if( thisdrop->type == 2 )
                    {
                        ADDWORD    ( pak, BuildItemHead( thisdrop->item ) );
                        ADDDWORD   ( pak, BuildItemData( thisdrop->item ) );
                    }
                    thisclient->Party->party->SendToMembers( &pak, dropowner );
                }
            }
    		CMap* map = MapList.Index[thisdrop->posMap];
    		pthread_mutex_lock( &map->DropMutex );
    		map->DeleteDrop( thisdrop );
    		pthread_mutex_unlock( &map->DropMutex );
        }
    	return true;
    }
	catch(...)
    {
       Log( MSG_ERROR, "Error in pakpickdrop");
       return false;
    }
}

// Changes equipment
bool CWorldServer::pakChangeEquip( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Shop->open)
        return true;
	WORD srcslot = GETWORD((*P), 0);
	WORD destslot = GETWORD((*P), 2);
	if(!CheckInventorySlot(thisclient, srcslot))
	   return false;
	if(!CheckInventorySlot(thisclient, destslot))
	   return false;
	if( destslot == 0 ) destslot = thisclient->GetNewItemSlot( thisclient->items[srcslot] );
	if( destslot == 0xffff ) return true;
	/*
    if( srcslot==7 || destslot==7 )
    {
        // clear the buffs if we change the weapon
        for(UINT i=0;i<15;i++)
        {
            switch(thisclient->MagicStatus[i].Buff)
            {
                case A_ATTACK:
                case A_ACCUR:
                case A_HASTE:
                case A_CRITICAL:
                    thisclient->MagicStatus[i].Duration = 0;
                break;
            }
        }
    }
    */
    if(destslot == 8) //trying to equip a shield
    {
        // first we will check if it is possible. Do we have a two handed weapon equipped?
        UINT weapontype = EquipList[WEAPON].Index[thisclient->items[7].itemnum]->type;
        switch(weapontype)
        {
            case TWO_HAND_SWORD:
            case SPEAR:
            case TWO_HAND_AXE:
            case BOW:
            case GUN:
            case LAUNCHER:
            case STAFF:
            case KATAR:
            case DOUBLE_SWORD:
            case DUAL_GUN:
            {
                //yes we do. OK reject the shield then.
                SendSysMsg( thisclient, "Cannot equip shield at this time" );
                return true;
            }
            break;
            default:
                break;
        }
    }
    CItem tmpitm;
	tmpitm = thisclient->items[srcslot];
	thisclient->items[srcslot] = thisclient->items[destslot];
	thisclient->items[destslot] = tmpitm;
//	thisclient->UpdateInventory( srcslot, destslot );
	BEGINPACKET( pak,0x7a5 );
	ADDWORD( pak, thisclient->clientid );
	ADDWORD( pak, srcslot );
	ADDDWORD( pak, BuildItemShow(thisclient->items[srcslot]));	// ITEM
	ADDWORD ( pak, thisclient->Stats->Move_Speed);
	SendToVisible( &pak, thisclient );

    if( srcslot == 7 || destslot == 7 )
    {
        // if is two hand weapon, we have to check if have shield and unequip it
        UINT weapontype = EquipList[WEAPON].Index[thisclient->items[7].itemnum]->type;
        switch(weapontype)
        {
            case TWO_HAND_SWORD:
            case SPEAR:
            case TWO_HAND_AXE:
            case BOW:
            case GUN:
            case LAUNCHER:
            case STAFF:
            case KATAR:
            case DOUBLE_SWORD:
            case DUAL_GUN:
            {
                if(thisclient->items[8].itemnum != 0)
                { // we should unequip the shield
                    UINT newslot = thisclient->GetNewItemSlot( thisclient->items[8] );
                    if(newslot == 0xffff)
                    {
                        // we have no slot for the shield, we have to change back the items
                        tmpitm = thisclient->items[destslot];
                        thisclient->items[destslot] = thisclient->items[srcslot];
                        thisclient->items[srcslot] = tmpitm;
                        SendSysMsg( thisclient, "You don't have free slot" );
                        return true;
                    }
                    thisclient->items[newslot] = thisclient->items[8];
                    ClearItem( thisclient->items[8] );
                    thisclient->UpdateInventory( newslot, 8 );
                    RESETPACKET( pak, 0x7a5);
                    ADDWORD    ( pak, thisclient->clientid );
                    ADDWORD    ( pak, 8 );
                    ADDWORD    ( pak, thisclient->items[8].itemnum );
                    ADDWORD    ( pak, BuildItemRefine( thisclient->items[8] ) );
                    ADDWORD    ( pak, thisclient->Stats->Move_Speed );
                    SendToVisible( &pak, thisclient );

               /*     STARTPACKET(pak2, 0x782, 11);
				SETWORD( pak2, 0x00,thisclient->clientid );
				SETBYTE( pak2, 0x02, thisclient->Status->Stance );
				SETWORD( pak2, 0x03, thisclient->Stats->Move_Speed  );
				SendToVisible( &pak2, thisclient );*/
                }
            }
            break;
            default:
                break;
        }
    }

    STARTPACKET(pak3,0x718,21);
	SETBYTE  ( pak3, 0x00, 2); // ITEMS TO UPDATE
	SETBYTE  ( pak3, 0x01, srcslot);
	SETWORD   ( pak3, 0x02, BuildItemHead( thisclient->items[srcslot] ) );
    SETDWORD  ( pak3, 0x04, BuildItemData( thisclient->items[srcslot] ) );
	SETBYTE    ( pak3, 0x08, destslot);
	SETWORD   ( pak3, 0x09, BuildItemHead( thisclient->items[destslot] ) );
    SETDWORD  ( pak3, 0x0b, BuildItemData( thisclient->items[destslot] ) );
	thisclient->client->SendPacket(&pak3);


	//thisclient->UpdateInventory( srcslot, destslot );
    thisclient->SetStats( );
	return true;
}

// Construct a cart/change parts
bool CWorldServer::pakChangeCart( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Shop->open)
        return true;
	WORD cartslot = GETWORD((*P), 0);
	WORD srcslot = GETWORD((*P), 0) + 135;
	WORD destslot = GETWORD((*P), 2);
	if(!CheckInventorySlot( thisclient, srcslot ))
	   return false;
	if(!CheckInventorySlot( thisclient, destslot ))
	   return false;
	if( destslot == 0 ) destslot=thisclient->GetNewItemSlot( thisclient->items[srcslot] );
	if( destslot == 0xffff ) return true;

	CItem tmpitm = thisclient->items[srcslot];
	thisclient->items[srcslot] = thisclient->items[destslot];
	thisclient->items[destslot] = tmpitm;

	BEGINPACKET( pak, 0x7ca );
	ADDWORD    ( pak, thisclient->clientid );
	ADDWORD    ( pak, cartslot);
	ADDWORD    ( pak, thisclient->items[srcslot].itemnum);
	ADDWORD    ( pak, BuildItemRefine( thisclient->items[srcslot] ) );
	ADDWORD    ( pak, thisclient->Stats->Move_Speed );
	SendToVisible( &pak, thisclient );

    thisclient->UpdateInventory( srcslot, destslot );
	thisclient->Stats->Move_Speed = thisclient->GetMoveSpeed( );
	return true;
}

// Start attacking a monster or player
bool CWorldServer::pakStartAttack( CPlayer* thisclient, CPacket* P )
{
    WORD clientid = GETWORD((*P),0x00);
    if ( thisclient->Battle->target == clientid ) return true; //no targetting yourself

    int weapontype = EquipList[WEAPON].Index[thisclient->items[7].itemnum]->type;
    if( weapontype == 231 && thisclient->items[132].count<1 ) //Bow and no arrows
        return true;
    else
    if( weapontype == 232 && thisclient->items[133].count<1 ) //Gun and no bullets
        return true;
    else
    if( weapontype == 233 && thisclient->items[134].count<1 ) //Launcher and no shells
        return true;
    else
    if( weapontype == 271 && thisclient->items[132].count<1 ) //Crossbow and no arrows
        return true;

    CMap* map = MapList.Index[thisclient->Position->Map];
    CCharacter* character = map->GetCharInMap( clientid );
    if(character == NULL) return true;
    if(character->IsMonster( ))
    {
        if(map->allowpvp == 0 && character->IsSummon( )) return true;
        if(!character->IsSummon())
            character->AddDamage((CCharacter*)thisclient, 0);
    //}
	//if(character->IsMonster())
	//{
	   // SET MONSTER HEALTH
	   BEGINPACKET( pak, 0x79f );
	   ADDWORD    ( pak, character->clientid );
	   ADDDWORD   ( pak, character->Stats->HP );
	   thisclient->client->SendPacket( &pak );
    }
    thisclient->StartAction( character, NORMAL_ATTACK, 0 );
    thisclient->Battle->contatk = true;
	return true;
}

// Goto next map through gate
bool CWorldServer::pakGate( CPlayer* thisclient, CPacket* P )
{
    thisclient->Session->inGame = false;
    word GateID = GETWORD((*P), 0x00);
    CTeleGate* thisgate = GetTeleGateByID( GateID );
    fPoint position;
    UINT map = 0;
    // I'm setting this at 50 distance from the point of teleport. Increase if you run into
    // broken telegates. We might need to dump the scale and work from that - Drakia
    if( thisgate == NULL || thisclient->Position->Map != thisgate->srcMap || distance(thisclient->Position->current, thisgate->src) > 150 )
    {
        Log( MSG_HACK, "Player %s[Map: %i X: %f Y: %f] - Gate Hacking[ID: %i]",
        thisclient->CharInfo->charname, thisclient->Position->Map,
        thisclient->Position->current.x, thisclient->Position->current.y, GateID );
        return true;
	}


	map = thisgate->destMap;
	position = thisgate->dest;

    MapList.Index[map]->TeleportPlayer( thisclient, position );
    thisclient->saveinventory();
    thisclient->quicksave();
    thisclient->Session->inGame = true;
	return true;
}

// Emotions
bool CWorldServer::pakDoEmote( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Shop->open)
        return true;
    thisclient->RestartPlayerVal( );
	BEGINPACKET( pak, 0x781 );
	ADDWORD( pak, GETWORD((*P), 0) );
	ADDWORD( pak, GETWORD((*P), 2) );
	ADDWORD( pak, thisclient->clientid );
	SendToVisible( &pak, thisclient );
	return true;
}

// This function is for increasing your stats
bool CWorldServer::pakAddStats( CPlayer* thisclient, CPacket* P )
{
	BYTE statid = GETBYTE((*P), 0);
	int statval = -1;
	int nstatval = 0;
	switch(statid)
    {
		case 0: nstatval=(int)floor((float)thisclient->Attr->Str/5); break;
		case 1: nstatval=(int)floor((float)thisclient->Attr->Dex/5); break;
		case 2: nstatval=(int)floor((float)thisclient->Attr->Int/5); break;
		case 3: nstatval=(int)floor((float)thisclient->Attr->Con/5); break;
		case 4: nstatval=(int)floor((float)thisclient->Attr->Cha/5); break;
		case 5: nstatval=(int)floor((float)thisclient->Attr->Sen/5); break;
		default:
                break;
	}
	if (thisclient->CharInfo->StatPoints>=nstatval && nstatval < ((Config.MaxStat/5)+1))
    {
		switch(statid)
        {
			case 0: statval=++thisclient->Attr->Str; break;
			case 1: statval=++thisclient->Attr->Dex; break;
			case 2: statval=++thisclient->Attr->Int; break;
			case 3: statval=++thisclient->Attr->Con; break;
			case 4: statval=++thisclient->Attr->Cha; break;
			case 5: statval=++thisclient->Attr->Sen; break;
			default:
                break;
		}
	}
	if (statval>0)
    {
		thisclient->CharInfo->StatPoints-=nstatval;
		BEGINPACKET( pak, 0x7a9 );
		ADDBYTE( pak, statid );
		ADDWORD( pak, (unsigned short)statval );
		thisclient->client->SendPacket( &pak );
	}
	thisclient->SetStats( );
	return true;
}

// Normal Chat
bool CWorldServer::pakNormalChat( CPlayer* thisclient, CPacket* P )
{
	if (P->Buffer[0]=='/')
    {
		return pakGMCommand( thisclient, P );
        //std::cout << thisclient->CharInfo->charname << ": " << P->Buffer << "\n";

    }
    else
    {
		BEGINPACKET( pak, 0x783 );
		ADDWORD( pak, thisclient->clientid );
		ADDSTRING( pak, P->Buffer );
		ADDBYTE( pak, 0 );
		SendToVisible( &pak, thisclient );
	}
	return true;
};

// Exit rose
bool CWorldServer::pakExit( CPlayer* thisclient, CPacket* P )
{
	BEGINPACKET( pak, 0x707 );
	ADDWORD( pak, 0 );
	thisclient->client->SendPacket( &pak );
	thisclient->client->isActive = false;
	return true;
}

// move skill to function keys
bool CWorldServer::pakMoveSkill ( CPlayer* thisclient, CPacket* P )
{
	BYTE slotid = GETBYTE((*P), 0x0 );
	WORD itemid = GETWORD((*P), 0x1 );
	if(slotid>47) return true;
	thisclient->quickbar[slotid] = itemid;
	BEGINPACKET( pak, 0x7aa );
	ADDBYTE( pak, slotid );
	ADDWORD( pak, itemid );
	thisclient->client->SendPacket( &pak );
	return true;
}

// User is checking up on the server
bool CWorldServer::pakPing ( CPlayer* thisclient, CPacket* P )
{
	BEGINPACKET( pak, 0x0700 );
	ADDWORD( pak, 0 );
	thisclient->client->SendPacket( &pak );
	return true;
}

// GameGuard
bool CWorldServer::pakGameGuard ( CPlayer* thisclient, CPacket* P )
{
	thisclient->lastGG = clock();
	return true;
}

// User Died
bool CWorldServer::pakUserDied ( CPlayer* thisclient, CPacket* P )
{
    thisclient->Session->inGame = false;
    thisclient->Session->Respawned = 1;
    //BYTE respawn = GETBYTE((*P),0);
    thisclient->Session->RespawnChoice = GETBYTE((*P),0);

    //PY lets try moving all this stuff into the main loop because we are currently outside of the player mutex
    //It's all in pakRespawned now.
    //thisclient->Session->inGame is just used as a toggle trigger now

    /*
    Log( MSG_INFO, "RespawnZones choise: %i", respawn );
    //1 - Current / 2 - save point/dungeon entrance
    CMap* map = MapList.Index[thisclient->Position->Map];
    CRespawnPoint* thisrespawn = NULL;
    thisclient->Stats->HP = thisclient->Stats->MaxHP * 10 / 100;
    if(respawn == 1 || map->dungeon)
    {
        if (respawn != 1) // This is a dungeon map, spawn at start
            thisrespawn = map->GetStartRespawn( );
        else
            thisrespawn = map->GetNearRespawn( thisclient );
         if(thisrespawn!=NULL)
         {
            map->TeleportPlayer( thisclient, thisrespawn->dest, false );
         }
    }
    else  // This is a field, spawn in save town
    {
        thisrespawn = GetRespawnByMap( thisclient->Position->saved );
        if(thisrespawn != NULL)
        {
            fPoint coord = thisrespawn->dest;
            MapList.Index[thisclient->Position->saved]->TeleportPlayer( thisclient, coord, false );
        }
    }

    if(thisrespawn == NULL)
    {
        fPoint coord;
        coord.x = 5200;
        coord.y = 5200;
        MapList.Index[2]->TeleportPlayer( thisclient, coord, false );
    }
	for(unsigned int i=0;i<30;i++)
	{	// Clean Buffs
        thisclient->MagicStatus[i].Duration = 0;
    }*/

	return true;
}
// User Save Town
bool CWorldServer::pakSaveTown ( CPlayer* thisclient, CPacket* P )
{
     thisclient->Position->saved = thisclient->Position->Map;
     GServer->DB->QExecute("UPDATE characters SET townid=%i WHERE id=%i",thisclient->Position->saved,thisclient->CharInfo->charid );
     return true;
}
// Shouting
bool CWorldServer::pakShout ( CPlayer* thisclient, CPacket* P )
{
	BEGINPACKET(pak, 0x0785);
	ADDSTRING  ( pak, thisclient->CharInfo->charname );
	ADDBYTE    ( pak, 0 );
	ADDSTRING  ( pak, &P->Buffer[0] );
	ADDBYTE    ( pak, 0 );
	SendToMap  ( &pak, thisclient->Position->Map );

	return true;
}

// Whispering
bool CWorldServer::pakWhisper ( CPlayer* thisclient, CPacket* P )
{
	char msgto[17];
	memset( &msgto, '\0', 17 );
	strncpy( msgto, (char*)&(*P).Buffer[0],16 );
	CPlayer* otherclient = GetClientByCharName( msgto );
	if(otherclient!=NULL)
	{
	   BEGINPACKET( pak, 0x0784 );
	   ADDSTRING( pak, thisclient->CharInfo->charname );
	   ADDBYTE( pak, 0 );
	   ADDSTRING( pak, &P->Buffer[strlen(msgto)+1] );
	   ADDBYTE( pak, 0 );
	   otherclient->client->SendPacket( &pak );
	   return true;
	}
	BEGINPACKET( pak, 0x0784 );
	ADDSTRING( pak, msgto );
	ADDBYTE( pak, 0 );
	ADDBYTE( pak, 0 );
	thisclient->client->SendPacket( &pak );
	return true;
}

// Return to Char Select
bool CWorldServer::pakCharSelect ( CPlayer* thisclient, CPacket* P )
{
    if(!thisclient->Session->inGame) return true;
    BEGINPACKET( pak, 0x707 );
	ADDWORD( pak, 0 );
	thisclient->client->SendPacket( &pak );
    thisclient->Session->inGame=false;
    RESETPACKET( pak, 0x7e1 );
    ADDBYTE    ( pak, 0xfa );
    ADDWORD    ( pak, thisclient->Session->userid );//CharInfo->charid );
    ADDBYTE    ( pak, 0x00 );
    SendISCPacket( &pak );

    for(unsigned j=0; j<thisclient->VisiblePlayers.size(); j++) {
        CPlayer* otherclient=thisclient->VisiblePlayers.at(j);
		thisclient->ClearObject(otherclient->clientid);
	}
    for(unsigned j=0; j<thisclient->VisibleMonsters.size(); j++) {
		thisclient->ClearObject(thisclient->VisibleMonsters.at(j));
	}
	for(unsigned j=0; j<thisclient->VisibleDrops.size(); j++) {
        CDrop* thisdrop = thisclient->VisibleDrops.at(j);
		thisclient->ClearObject(thisdrop->clientid);
	}
	for(unsigned j=0; j<thisclient->VisibleNPCs.size(); j++) {
        CNPC* thisnpc = thisclient->VisibleNPCs.at(j);
        thisclient->ClearObject( thisnpc->clientid );
	}

    thisclient->savedata();
    RESETPACKET( pak, 0x505 );
    ADDWORD    ( pak,  thisclient->Session->userid );
    SendISCPacket( &pak );
   	thisclient->Session->isLoggedIn = false;
    thisclient->Saved = true;
    pakClearUser( thisclient );
   	ClearClientID( thisclient->clientid );
    if(thisclient->client!=NULL) thisclient->client->isActive = false;
    return true;
}

// Buy from NPC
bool CWorldServer::pakNPCBuy ( CPlayer* thisclient, CPacket* P )
{
     //try
     //{
    if(thisclient->Shop->open)
        return true;
    WORD NPC = GETWORD((*P), 0);
	CNPC* thisnpc = GetNPCByID( NPC, thisclient->Position->Map );
	if( thisnpc == NULL )
	   return true;
	BYTE buycount = GETBYTE((*P), 2);
	BYTE sellcount = GETBYTE((*P), 3);

	//Union Shop case...
    Log(MSG_INFO,"Buying /selling from NPC %i. Buycount: %i, Sellcount: %i" ,thisnpc->npctype, buycount,sellcount);
    bool is_unionshop = false;

    //if (thisnpc->npctype == 1109 || thisnpc->npctype == 1110 || thisnpc->npctype == 1111 || thisnpc->npctype == 1112 || thisnpc->npctype == 1043)
    //{
    //   is_unionshop = true;
    //  Log(MSG_INFO,"identified as a union shop");
    //}

    switch(thisnpc->npctype)
    {
        case 1109:
        case 1110:
        case 1111:
        case 1112:
        case 1043:
            is_unionshop = true;
            Log(MSG_INFO,"identified as a union shop");
            break;
    }

	int UpointCost = 0;
	int UnionVar = thisclient->Union_s->unionvar[0];
	int TotUpointCost = 0;
	BYTE ncount = 0;
	BEGINPACKET( pak, 0x717 );
	ADDQWORD   ( pak, thisclient->CharInfo->Zulies );
	ADDBYTE    ( pak, 0x00 );
	for (int i=0; i<buycount; i++)
    {
		BYTE tabid = GETBYTE((*P), 8+(i*4));
		BYTE itemid = GETBYTE((*P), 9+(i*4));  //position in shop tab
		WORD count = GETWORD((*P), 10+(i*4));
        //Log( MSG_WARNING, "Buying item %i. ID %i, count %i", i, itemid, count);
		unsigned sellid = 0;
		switch(tabid)
		{
            case 0:
                sellid = thisnpc->thisnpc->tab1;
            break;
            case 1:
                sellid = thisnpc->thisnpc->tab2;
            break;
            case 2:
                sellid = thisnpc->thisnpc->tab3;
            break;
            case 3:
                sellid = thisnpc->thisnpc->specialtab;
            break;
            default:
                sellid = 0;
        }
        if(SellList.Index[sellid]==NULL)
        { // invalid tab
            //Log( MSG_WARNING, "Bad tab ID");
            continue;
        }
		int tmpcount = count;
		while (tmpcount > 0)
        {
			CItem thisitem;
			thisitem.itemnum = SellList.Index[sellid]->item[itemid] % 1000;
			thisitem.itemtype = SellList.Index[sellid]->item[itemid] / 1000;
			thisitem.count = count;
			//Log( MSG_WARNING, "Item purchased. type = %i. id = %i. tempcount = %i", thisitem.itemtype,thisitem.itemnum,tmpcount);

            if(thisitem.itemtype <= 9)
			{
			    UpointCost = GServer->EquipList[thisitem.itemtype].Index[thisitem.itemnum]->unionpoint;
			    thisitem.type = GServer->EquipList[thisitem.itemtype].Index[thisitem.itemnum]->type;
			    thisitem.durability = EquipList[thisitem.itemtype].Index[thisitem.itemnum]->durability;
            }
            if(thisitem.itemtype == 10)
            {
                UpointCost = GServer->UseList.Index[thisitem.itemnum]->unionpoint;
                thisitem.type = GServer->UseList.Index[thisitem.itemnum]->type;
                thisitem.durability = 0;
            }
            if(thisitem.itemtype == 11)
            {
                UpointCost = GServer->JemList.Index[thisitem.itemnum]->unionpoint;
                thisitem.type = GServer->JemList.Index[thisitem.itemnum]->type;
                thisitem.durability = 0;
            }
            if(thisitem.itemtype == 12)
            {
                UpointCost = GServer->NaturalList.Index[thisitem.itemnum]->unionpoint;
                thisitem.type = GServer->NaturalList.Index[thisitem.itemnum]->type;
                thisitem.durability = 0;
            }
            if(thisitem.itemtype == 14)
            {
                UpointCost = GServer->PatList.Index[thisitem.itemnum]->unionpoint;
                thisitem.type = GServer->PatList.Index[thisitem.itemnum]->type;
                thisitem.durability = GServer->PatList.Index[thisitem.itemnum]->durability;
            }
			if(is_unionshop && UpointCost == 0)
	        {
                ncount++;
                Log( MSG_WARNING, "Item has no price in Server");
                tmpcount = 0;
                continue;    //this item has no price so skip it
            }
            if(is_unionshop && thisclient->Union_s->unionvar[UnionVar] < UpointCost)
			{
                ncount++;
                Log( MSG_WARNING, "You cannot afford this item");
                tmpcount = 0;
                continue;    //can't afford the item so don't bother adding it
            }
            //Log( MSG_WARNING, "Item purchased. type = %i. id = %i", thisitem.itemtype,thisitem.itemnum);
			unsigned newslot = thisclient->GetNewItemSlot( thisitem );
			if ( newslot == 0xffff )
            {
                 ncount -= 1;
                 Log( MSG_WARNING, "failed to find free slot");
                 break;
            }
			int thisslotcount = 999 - thisclient->items[newslot].count;
			//Log( MSG_WARNING, "this slot count = %i", thisslotcount);
			//if ( thisslotcount > tmpcount )
            //{
            //    thisslotcount = tmpcount;
            //}
            //Log( MSG_WARNING, "this slot count = %i", thisslotcount);
			tmpcount -= thisslotcount;
			thisitem.count += thisclient->items[newslot].count;
			thisitem.refine = 0;
			thisitem.lifespan = 100;
			thisitem.appraised = true;
			thisitem.socketed = false;
			thisitem.stats = 0;
			if(is_unionshop) //make sure all union shop items come with extra stats
			{
                if(thisitem.itemtype <= 9)
                    thisitem.stats = GServer->RandNumber(1,299);
            }
			thisitem.gem = 0;
			thisclient->items[newslot] = thisitem;
			ADDBYTE  ( pak, newslot );
			ADDWORD  ( pak, BuildItemHead( thisclient->items[newslot] ) );
			ADDDWORD ( pak, BuildItemData( thisclient->items[newslot] ) );

    		switch(thisitem.itemtype)
    		{
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 8:
                case 9:
                case 14:
                {
                    float price = 0;
                    UINT quality = 0;
                    UINT bprice = 0;
                    if(thisitem.itemtype<10 )
                    {
                        quality = EquipList[thisitem.itemtype].Index[thisitem.itemnum]->quality;
                        bprice = EquipList[thisitem.itemtype].Index[thisitem.itemnum]->price;
                    }
                    else
                    {
                        quality = PatList.Index[thisitem.itemnum]->quality;
                        bprice = PatList.Index[thisitem.itemnum]->price;
                    }
                    price = quality;
                    price += 0x32; // town rate
                    price *= bprice;
                    price += 0.5;
                    price /= 100;
                    price = (float)round(price);
                    //Log( MSG_WARNING, "Item bought: itemnum %i, itemtype %i, itemcount %i, price %0.0f", thisitem.itemnum, thisitem.itemtype, thisitem.count, price);
                    if(is_unionshop)
                    {
                        thisclient->Union_s->unionvar[UnionVar] -= UpointCost;
                        if(UnionVar == 9)
                        {
                            Log( MSG_WARNING, "Union Shop Item bought: UnionID %i, itemnum %i, itemtype %i, itemcount %i, price %i", UnionVar, thisitem.itemnum, thisitem.itemtype, thisitem.count, UpointCost);
                            GServer->DB->QExecute("UPDATE accounts SET ktpoints=%i WHERE id=%i AND password='%s'",
                                thisclient->Union_s->unionvar[UnionVar],thisclient->Session->userid, thisclient->Session->password);
                            Log(MSG_DEBUG,"KTPoints updated and saved to the database");
                            Log( MSG_WARNING, "item Purchased successfully");
                        }

                    }
                    else
                        thisclient->CharInfo->Zulies -= (long int)price;
                }
                break;
                case 10:
                case 12:
                {
                    // this values should be the same as packet 753
                    //Log( MSG_WARNING, "Type %i item selected", thisitem.itemtype);
                    BYTE values[11] = {0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32};
                    UINT type = 0;
                    UINT bprice = 0;
                    UINT pricerate = 0;
                    UINT pvalue = 0;
                    if(thisitem.itemtype == 10)
                    {
                        type = UseList.Index[thisitem.itemnum]->type;
                        bprice = UseList.Index[thisitem.itemnum]->price;
                        pricerate = UseList.Index[thisitem.itemnum]->pricerate;
                        pvalue = UseList.Index[thisitem.itemnum]->pricevalue;
                    }
                    else
                    {
                        type = NaturalList.Index[thisitem.itemnum]->type;
                        bprice = NaturalList.Index[thisitem.itemnum]->price;
                        pricerate = NaturalList.Index[thisitem.itemnum]->pricerate;
                        pvalue = NaturalList.Index[thisitem.itemnum]->pricevalue;
                    }
                    unsigned int value = 0;
                    float price = 0;
                    bool flag;
                    if(type<421)
                        if(type<311)
                            flag = false;
                        else
                            if(type>312)
                                flag = false;
                            else
                                flag = true;
                    else
                        if(type<=428)
                            flag = true;
                        else
                            if(type<311)
                                flag = false;
                            else
                                flag = true;
                    if(flag)
                    {
                        value = pvalue;
                        if(value>=11)
                            value ^= 0xffffffff;
                        else
                            value = values[value];
                        value -= 0x32;
                        value *= pricerate;
                        price = value * 0.001;
                        price += 1;
                        price *= bprice;
                        price += 0.5;
                        price = (float)floor(price);
                        //Log( MSG_WARNING, "Item bought: itemnum %i, itemtype %i, itemcount %i, price %0.0f, flag %i", thisitem.itemnum, thisitem.itemtype, thisitem.count, price, flag);
                        if(is_unionshop)
                        {
                            thisclient->Union_s->unionvar[UnionVar] -= (UpointCost * count);

                            TotUpointCost -= (UpointCost * count);
                            if(UnionVar == 9)
                            {
                                Log( MSG_WARNING, "Union Shop Item bought: UnionID %i, itemnum %i, itemtype %i, itemcount %i, price %i", UnionVar, thisitem.itemnum, thisitem.itemtype, thisitem.count, UpointCost);
                                GServer->DB->QExecute("UPDATE accounts SET ktpoints=%i WHERE id=%i AND password='%s'",
                                    thisclient->Union_s->unionvar[UnionVar],thisclient->Session->userid, thisclient->Session->password);
                                Log(MSG_DEBUG,"KTPoints updated and saved to the database");
                                Log( MSG_WARNING, "item Purchased successfully");
                            }
                            //Log( MSG_WARNING, "item Purchased successfully");
                        }
                        else
                            thisclient->CharInfo->Zulies -= (long int)price * count;
                    }
                    else
                    {
                        price = pricerate;
                        value = 0x61 - 0x32; // misc rate - 0x32
                        price *= value;
                        price *= 0.001;
                        price += 1;
                        price *= bprice;
                        price += 0.5;
                        price = (float)floor(price);
                		//Log( MSG_WARNING, "Item bought: itemnum %i, itemtype %i, itemcount %i, price %0.0f, flag %i", thisitem.itemnum, thisitem.itemtype, thisitem.count, price, flag);
                    	if(is_unionshop)
                        {
                            thisclient->Union_s->unionvar[UnionVar] -= (UpointCost * count);
                            //Log( MSG_WARNING, "Union Shop Item bought: UnionID %i, itemnum %i, itemtype %i, itemcount %i, price %i", UnionVar, thisitem.itemnum, thisitem.itemtype, thisitem.count, UpointCost);
                            TotUpointCost -= (UpointCost * count);
                            if(UnionVar == 9)
                            {
                                Log( MSG_WARNING, "Union Shop Item bought: UnionID %i, itemnum %i, itemtype %i, itemcount %i, price %i", UnionVar, thisitem.itemnum, thisitem.itemtype, thisitem.count, UpointCost);
                                GServer->DB->QExecute("UPDATE accounts SET ktpoints=%i WHERE id=%i AND password='%s'",
                                    thisclient->Union_s->unionvar[UnionVar],thisclient->Session->userid, thisclient->Session->password);
                                Log(MSG_DEBUG,"KTPoints updated and saved to the database");
                                Log( MSG_WARNING, "item Purchased successfully");
                            }
                            //Log( MSG_WARNING, "item Purchased successfully");
                        }
                        else
                            thisclient->CharInfo->Zulies -= (long int)price * count;
                    }
                }
                break;
                case 7:
                case 11:
                case 13:
                {
                    float price = 0;
                    UINT bprice = 0;
                    UINT pricerate;
                    if(thisitem.itemtype==7)
                    {
                        pricerate = EquipList[7].Index[thisitem.itemnum]->pricerate;
                        bprice = EquipList[7].Index[thisitem.itemnum]->price;
                    }
                    else
                    {
                        switch(thisitem.itemtype)
                        {
                            case 11:
                                pricerate = JemList.Index[thisitem.itemnum]->pricerate;
                                bprice = JemList.Index[thisitem.itemnum]->price;
                            break;
                            case 13:continue;
                        }
                    }
                    price = pricerate;
                    unsigned int value = 0x61 - 0x32; // misc rate - 0x32
                    price *= value;
                    price *= 0.001;
                    price += 1;
                    price *= bprice;
                    price += 0.5;
                    price = (float)round(price);
                    if(thisitem.itemtype == 7)
                        price = (float)round(bprice * 1.3);
            		//Log( MSG_WARNING, "Item bought: itemnum %i, itemtype %i, itemcount %i, price %0.0f", thisitem.itemnum, thisitem.itemtype, thisitem.count, price);
                	if(is_unionshop)
                    {
                        thisclient->Union_s->unionvar[UnionVar] -= UpointCost;
                        //Log( MSG_WARNING, "Union Shop Item bought: UnionID %i, itemnum %i, itemtype %i, itemcount %i, price %i", UnionVar, thisitem.itemnum, thisitem.itemtype, thisitem.count, UpointCost);
                        TotUpointCost -= UpointCost;
                        if(UnionVar == 9)
                        {
                            Log( MSG_WARNING, "Union Shop Item bought: UnionID %i, itemnum %i, itemtype %i, itemcount %i, price %i", UnionVar, thisitem.itemnum, thisitem.itemtype, thisitem.count, UpointCost);
                            GServer->DB->QExecute("UPDATE accounts SET ktpoints=%i WHERE id=%i AND password='%s'",
                                thisclient->Union_s->unionvar[UnionVar],thisclient->Session->userid, thisclient->Session->password);
                            Log(MSG_DEBUG,"KTPoints updated and saved to the database");
                            Log( MSG_WARNING, "item Purchased successfully");
                        }
                        //Log( MSG_WARNING, "item Purchased successfully");
                    }
                    else
                        thisclient->CharInfo->Zulies -= (long int)price*count;
                }
                break;
                default:
                    Log( MSG_WARNING, "Invalid Item Type: %i", thisitem.itemtype );
                break;
            }
			ncount++;
			Log( MSG_WARNING, "item count: %i", ncount );
		}
		BEGINPACKET(pak1, 0x720 );
        ADDWORD(pak1, thisclient->Union_s->unionvar[0] );
        ADDDWORD(pak1, TotUpointCost);
        thisclient->client->SendPacket( &pak1 );
	}
	for (int i=0; i<sellcount; i++)
    {
		BYTE slotid = GETBYTE((*P), 8+(buycount*4)+(i*3));
		WORD count = GETWORD((*P), 9+(buycount*4)+(i*3));
		CItem thisitem = thisclient->items[slotid];
		thisitem.count = count;
		switch(thisitem.itemtype)
		{
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 8:
            case 9:
            case 14:
            {
                float price = 0;
                price = 7.142857E-05F * 5000;
                if(thisitem.itemtype<10)
                {
                    price *= EquipList[thisitem.itemtype].Index[thisitem.itemnum]->price;
                }
                else
                {
                    price *= PatList.Index[thisitem.itemnum]->price;
                }
                price *= thisitem.durability + 0xc8;
                price *= 40;
                price *= 0xc8 - 0x62; //town rate
                price *= 1.000000E-06;
                price = (float)floor(price);
    			//Log( MSG_WARNING, "Item Sold: itemnum %i, itemtype %i, itemcount %i, price %0.0f", thisitem.itemnum, thisitem.itemtype, thisitem.count, price);
        		thisclient->CharInfo->Zulies += (long int)price*count;
            }
            break;
            case 10:
            case 12:
            {
                // this values are the same from packet 753
                BYTE values[11] = {0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32};
                UINT type = 0;
                UINT bprice = 0;
                UINT pricerate = 0;
                UINT pvalue = 0;
                if(thisitem.itemtype==10)
                {
                   type = UseList.Index[thisitem.itemnum]->type;
                   bprice = UseList.Index[thisitem.itemnum]->price;
                   pricerate = UseList.Index[thisitem.itemnum]->pricerate;
                   pvalue = UseList.Index[thisitem.itemnum]->pricevalue;
                }
                else
                {
                   type = NaturalList.Index[thisitem.itemnum]->type;
                   bprice = NaturalList.Index[thisitem.itemnum]->price;
                   pricerate = NaturalList.Index[thisitem.itemnum]->pricerate;
                   pvalue = NaturalList.Index[thisitem.itemnum]->pricevalue;
                }
                unsigned int value = 0;
                float price = 0;
                bool flag;
                if(type<421)
                {
                    if(type<311)
                        flag = false;
                    else
                        if(type>312)
                            flag = false;
                        else
                            flag = true;
                }
                else
                {
                    if(type<=428)
                        flag = true;
                    else
                        if(type<311)
                            flag = false;
                        else
                            flag = true;
                }
                if(flag)
                {
                    value = pvalue;
                    if(value>=11)
                        value ^= 0xffffffff;
                    else
                        value = values[value];
                    value -= 0x32;
                    value *= pricerate;
                    value += 1000;
                    value *= bprice;
                    value *= (200 - 0x62); //town rate ( 100)
                    price = value * 5.555555555555556E-06;
                    price = (float)floor(price);
                	//Log( MSG_WARNING, "Item Sold: itemnum %i, itemtype %i, itemcount %i, price %0.0f", thisitem.itemnum, thisitem.itemtype, thisitem.count, price);
                    thisclient->CharInfo->Zulies += (long int)price*count;
                }
                else
                {
                    price = pricerate;
                    value = 0x61 - 0x32; // misc rate -0x32
                    price *= value;
                    price += 1000;
                    price *= bprice;
                    price *= (200 - 0x62); //town rate ( 100)
                    price *= 5.555555555555556E-06;
                    price = (float)floor(price);
                	//Log( MSG_WARNING, "Item Sold: itemnum %i, itemtype %i, itemcount %i, price %0.0f", thisitem.itemnum, thisitem.itemtype, thisitem.count, price);
                    thisclient->CharInfo->Zulies += (long int)price*count;
                }
            }
            break;
            case 7:
            case 11:
            case 13:
            {
                float price = 0;
                UINT bprice = 0;
                UINT pricerate = 0;
                switch(thisitem.itemtype)
                {
                    case 7:
                        pricerate = EquipList[thisitem.itemtype].Index[thisitem.itemnum]->pricerate;
                        bprice = EquipList[thisitem.itemtype].Index[thisitem.itemnum]->price;
                    break;
                    case 11:
                        pricerate = JemList.Index[thisitem.itemnum]->pricerate;
                        bprice = JemList.Index[thisitem.itemnum]->price;
                    break;
                    case 13:continue;//can we sell quest items? :S

                }
                price = pricerate;
                price *= 0x61 - 0x32;   // misc rate -0x32
                price += 1000;
                price *= bprice;
                price *= (200 - 0x62); //town rate ( 100)
                price *= 5.555555555555556E-06;
                price = (float)floor(price);
                if(thisitem.itemtype == 7)
                    price = (float)floor(bprice * 0.5555508);
        		//Log( MSG_WARNING, "Item Sold: itemnum %i, itemtype %i, itemcount %i, price %0.0f", thisitem.itemnum, thisitem.itemtype, thisitem.count, price);
            	thisclient->CharInfo->Zulies += (long int)price*count;
            }
            break;
            default:
                Log( MSG_WARNING, "Invalid Item Type: %i", thisitem.itemtype );
                break;
        }
        thisclient->items[slotid].count	-= count;
        if( thisclient->items[slotid].count <=0 )
    		ClearItem( thisclient->items[slotid] );
		ADDBYTE( pak, slotid );
		ADDWORD( pak, BuildItemHead( thisclient->items[slotid] ) );
		ADDDWORD( pak, BuildItemData( thisclient->items[slotid] ) );
		ncount++;
	}
	SETQWORD( pak, 0, thisclient->CharInfo->Zulies );
	SETBYTE( pak, 8, ncount );
	thisclient->client->SendPacket( &pak );
	thisclient->saveinventory();
	return true;
    //}
    //__seh_except(info, context)
    //{
    //   Log( MSG_ERROR, "Error in pakNPCBuy");
    //   return false;
    //}
    //__seh_end
}



// Trade action
bool CWorldServer::pakTradeAction ( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Shop->open)
        return true;
	CPacket pak;
	BYTE action = GETBYTE( (*P), 0 );
	thisclient->Trade->trade_target = GETWORD( (*P), 1 );
	CPlayer* otherclient = GetClientByID( thisclient->Trade->trade_target, thisclient->Position->Map );
	if (otherclient == NULL) return true;
	switch(action)
    {
		case 0:
			// REQUEST TRADE
			RESETPACKET( pak, 0x7c0 );
			ADDBYTE( pak, 0 );
			ADDWORD( pak, thisclient->clientid );
			ADDBYTE( pak, 0 );
			otherclient->client->SendPacket( &pak ); // send the request packet to the other player with action zero
			thisclient->Trade->trade_status = 2; // requesting trade.
			otherclient->Trade->trade_status = 1; // other client needs to respond
			break;
		case 1:
			// ACCEPT TRADE
			RESETPACKET( pak, 0x7c0 );
			ADDBYTE( pak, 1 );
			ADDWORD( pak, thisclient->clientid );
			ADDBYTE( pak, 0 );
			otherclient->client->SendPacket( &pak ); // send a trade accept packet
			thisclient->Trade->trade_status = 3; // set both trade status bits to 3 (trade window open for both players)
			otherclient->Trade->trade_status = 3;
			for(int i=0; i<11; i++) thisclient->Trade->trade_count[i] = 0;
			for(int i=0; i<10; i++) thisclient->Trade->trade_itemid[i] = 0;
			for(int i=0; i<11; i++) otherclient->Trade->trade_count[i] = 0;
			for(int i=0; i<10; i++) otherclient->Trade->trade_itemid[i] = 0;
			break;
        case 2:  // REJECT TRADE
		case 3:  // CANCEL TRADE
            // reject and cancel both do the same thing
			RESETPACKET( pak, 0x7c0 );
			ADDBYTE( pak, 3 );
			ADDWORD( pak, thisclient->clientid );
			ADDBYTE( pak, 0 );
			otherclient->client->SendPacket( &pak ); // send packet to cancel trade
			thisclient->Trade->trade_target = 0;  // remove trade targets from both clients.
			otherclient->Trade->trade_target = 0;
			thisclient->Trade->trade_status = 0;  // set trade status to 0 for both clients
			thisclient->Trade->trade_status = 0;
			break;
		case 4:
            // CHECK READY
			RESETPACKET( pak, 0x7c0 );
			ADDBYTE( pak, 4 );
			ADDWORD( pak, thisclient->clientid );
			ADDBYTE( pak, 0 );
			otherclient->client->SendPacket( &pak ); // send trade locked packet to other client
			thisclient->Trade->trade_status = 4;    // set MY OWN trade status to locked
			break;
        case 5:
            // UNCHECK READY
            // seems we can't do this right now
            break;
		case 6:
            // TRADE DONE
			if (thisclient->Trade->trade_status == 6)
				thisclient->Trade->trade_status = 4;
			else
				thisclient->Trade->trade_status = 6;
			if (otherclient->Trade->trade_status == 6)
            {
				RESETPACKET( pak, 0x7c0 );
				// Complete the trade
				ADDBYTE( pak, 6 );
				ADDWORD( pak, otherclient->clientid );
				ADDBYTE( pak, 0 );
				thisclient->client->SendPacket( &pak );
				RESETPACKET( pak, 0x7c0 );
				ADDBYTE( pak, 6 );
				ADDWORD( pak, thisclient->clientid );
				ADDBYTE( pak, 0 );
				otherclient->client->SendPacket( &pak );

				// Update the zuly
				thisclient->CharInfo->Zulies -= thisclient->Trade->trade_count[0x0a];
				otherclient->CharInfo->Zulies -= otherclient->Trade->trade_count[0x0a];
				thisclient->CharInfo->Zulies += otherclient->Trade->trade_count[0x0a];
				otherclient->CharInfo->Zulies += thisclient->Trade->trade_count[0x0a];

				unsigned tucount = 0;
				unsigned oucount = 0;

				// Begin this clients inventory update
				BEGINPACKET( pakt, 0x717 );
				ADDQWORD( pakt, thisclient->CharInfo->Zulies );
				ADDBYTE( pakt, 0 );

				// Begin the other clients inventory update
				BEGINPACKET( pako, 0x717 );
				ADDQWORD( pako, otherclient->CharInfo->Zulies );
				ADDBYTE( pako, 0 );

				for (unsigned i=0; i<10; i++)
                {
					if(thisclient->Trade->trade_count[i] > 0)
                    {
						CItem thisitem = thisclient->items[thisclient->Trade->trade_itemid[i]];
						unsigned newslot = otherclient->GetNewItemSlot( thisitem );
						if(newslot==0xffff) continue;
						thisclient->items[thisclient->Trade->trade_itemid[i]].count -= thisclient->Trade->trade_count[i];
						if( thisclient->items[thisclient->Trade->trade_itemid[i]].count<=0)
      						ClearItem(thisclient->items[thisclient->Trade->trade_itemid[i]]);
						otherclient->items[newslot]=thisitem;
						otherclient->items[newslot].count = thisclient->Trade->trade_count[i];
						ADDBYTE( pakt, (unsigned char)thisclient->Trade->trade_itemid[i] );
						ADDWORD( pakt, BuildItemHead( thisclient->items[thisclient->Trade->trade_itemid[i]] ) );
						ADDDWORD( pakt, BuildItemData( thisclient->items[thisclient->Trade->trade_itemid[i]] ) );
						ADDBYTE( pako, newslot );
						ADDWORD( pako, BuildItemHead( otherclient->items[newslot] ) );
						ADDDWORD( pako, BuildItemData( otherclient->items[newslot] ) );
						tucount++;
						oucount++;
					}
					if(otherclient->Trade->trade_count[i] > 0)
                    {
						CItem thisitem = otherclient->items[otherclient->Trade->trade_itemid[i]];
						unsigned newslot = thisclient->GetNewItemSlot( thisitem );
						if(newslot==0xffff) continue;
						otherclient->items[otherclient->Trade->trade_itemid[i]].count -= otherclient->Trade->trade_count[i];
						if( otherclient->items[otherclient->Trade->trade_itemid[i]].count<=0 )
      						ClearItem( otherclient->items[otherclient->Trade->trade_itemid[i]] );
						thisclient->items[newslot]=thisitem;
						thisclient->items[newslot].count = otherclient->Trade->trade_count[i];
						ADDBYTE( pako, (unsigned char)otherclient->Trade->trade_itemid[i] );
						ADDWORD( pako, BuildItemHead( otherclient->items[otherclient->Trade->trade_itemid[i]] ) );
						ADDDWORD( pako, BuildItemData( otherclient->items[otherclient->Trade->trade_itemid[i]] ) );
						ADDBYTE( pakt, newslot );
						ADDWORD( pakt, BuildItemHead( thisclient->items[newslot] ) );
						ADDDWORD( pakt, BuildItemData( thisclient->items[newslot] ) );
						tucount++;
						oucount++;
					}
				}

				// Update itemcount and send
				SETBYTE( pakt, 8, tucount );
				SETBYTE( pako, 8, oucount );
				thisclient->client->SendPacket( &pakt );
				otherclient->client->SendPacket( &pako );
				thisclient->Trade->trade_status=0;
				otherclient->Trade->trade_status=0;
				thisclient->saveinventory();
				otherclient->saveinventory();
			}
			break;
        case 7:
            // TRADE BUSY
            break;
        case 8:
            // TRADE TOO FAR
            break;
        case 9:
            // NOT A VALID TARGET
            break;
        case 10:
            // OUT OF INVENTORY
            break;
        case 11:
            //
        default:
            break;
	}

	return true;
}

// Trade action
bool CWorldServer::pakTradeAdd ( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Shop->open)
        return true;
	BYTE islot = GETBYTE((*P),0);
	WORD slotid = GETWORD((*P),1);
	DWORD count = GETDWORD((*P),3);
	CPlayer* otherclient = GetClientByID( thisclient->Trade->trade_target, thisclient->Position->Map );
	if (otherclient == NULL) return true;
	BEGINPACKET( pak, 0x7c1 );
	ADDBYTE( pak, islot );
	if( islot == 0x0a )
    {
		ADDWORD( pak, 0xccdf );//0xccccccdf );
		ADDDWORD( pak, count );
		thisclient->Trade->trade_count[islot] = count;
	}
    else
    {
        if(islot>0x0a)
            return false;
		if( count != 0 )
        {
            if(count>thisclient->items[slotid].count)
                return false;
			thisclient->Trade->trade_count[islot] = count;
			thisclient->Trade->trade_itemid[islot] = slotid;
			CItem tmpitem = thisclient->items[slotid]; tmpitem.count = count;
			ADDWORD( pak, BuildItemHead( tmpitem ) );
			ADDDWORD( pak, BuildItemData( tmpitem ) );
		}
        else
        {
			thisclient->Trade->trade_count[islot] = 0;
			thisclient->Trade->trade_itemid[islot] = 0;
			ADDDWORD( pak, 0 );
			ADDDWORD( pak, 0 );
		}
	}
	otherclient->client->SendPacket( &pak );
	return true;
}


// Attack skill
bool CWorldServer::pakStartSkill ( CPlayer* thisclient, CPacket* P )
{

    if( thisclient->Shop->open || thisclient->Status->Muted!=0xff )
        return true;
    fPoint thispoint;
    unsigned int skillid;
    UINT targetid = GETWORD( (*P), 0 );
    BYTE skillnum = GETBYTE( (*P), 2 );//skill inventory number
    if(thisclient->Session->codedebug) //Debug code
    {
       SendPM(thisclient, "Skill went to pakStartSkill. Skill number = %i", skillnum);
    }
    if(skillnum >= MAX_SKILL)
    {
        Log( MSG_HACK, "Invalid Skill id %i for %s ", skillnum, thisclient->CharInfo->charname );
        return false;
    }
    if (skillnum > 29)
    {
         skillid = thisclient->askill[skillnum - 30] + thisclient->askilllvl[skillnum - 30];
    }
    else
    {
         skillid = thisclient->bskills[skillnum];
    }
    CMap* map = MapList.Index[thisclient->Position->Map];
    CCharacter* character = map->GetCharInMap( targetid );
    if(character == NULL) return true;

	if(character->IsMonster())
	{
	   BEGINPACKET( pak, 0x79f );
	   ADDWORD( pak, character->clientid );
	   ADDWORD( pak, character->Stats->HP );
	   ADDWORD( pak, 0 );
	   thisclient->client->SendPacket( &pak );
    }
	CSkills* thisskill = GetSkillByID( skillid );
	if(thisskill == NULL)
	   return true;
    if(thisclient->Session->codedebug) //Debug code
    {
       SendPM(thisclient, "Skill type = %i target = %i",thisskill->skilltype, thisskill->target);
    }
    if(!thisclient->canUseSkill(thisskill))
    {
        SendPM(thisclient, "Sorry. You cannot use that skill");
        return true;
    }
	if(thisskill->target == 9 && !character->IsDead())
	{
        ClearBattle( thisclient->Battle );
        return true;
    }
    //if( isSkillTargetFriendly( thisskill ) )
    //{
    //    if(thisclient->Session->codedebug) //Debug code
    //    {
    //       SendPM(thisclient, "Target is friendly. Action = SKILL_BUFF");
    //    }
    //    thisclient->StartAction( character, SKILL_BUFF, skillid );
    //}
    //else
    //{
    switch(thisskill->skilltype)
    {
        case 3: case 6:
            if(thisclient->Session->codedebug) //Debug code
            {
                SendPM(thisclient, "Target is UN-friendly. Action = SKILL_ATTACK");
            }
            thisclient->StartAction( character, SKILL_ATTACK, skillid );
            break;
        case 9: case 11: case 13:
            if(thisclient->Session->codedebug) //Debug code
            {
                SendPM(thisclient, "Target is either friendly or unfriedly. Action = SKILL_BUFF");
                SendPM(thisclient, "My id = %i target id = %i",thisclient->clientid, character->clientid);
            }
            thisclient->StartAction( character, SKILL_BUFF, skillid );
            break;
        case 20: // resurrect
            ClearBattle( thisclient->Battle );
            if(thisskill->target == 9)
        	{
                if(character->IsDead())
                {
                    character->Stats->HP = (int)character->GetMaxHP()/10;
                }
                return true;
            }
            break;
        default:
            SendPM(thisclient, "Unhandled skill request");
            break;
    }
    //}
	return true;
}

// Self skills
bool CWorldServer::pakSkillSelf( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Session->codedebug) //Debug code
    {
       char buffer[200];
       sprintf ( buffer, "Skill went to pakSkillSelf" );
       SendPM(thisclient, buffer);
    }
    if( thisclient->Shop->open || thisclient->Status->Muted!=0xff || !thisclient->Status->CanCastSkill)
        return true;
    unsigned int skillid;
    BYTE num = GETBYTE((*P),0);
    if(num >= MAX_SKILL)
    {
        Log( MSG_HACK, "Invalid Skill id %i for %s ", num, thisclient->CharInfo->charname );
        return false;
    }
    if (num > 29)
    {
         skillid = thisclient->askill[num-30]+thisclient->askilllvl[num-30];
    }
    else
    {
         skillid = thisclient->bskills[num];
    }
	CSkills* thisskill = GetSkillByID( skillid );
	if(thisskill == NULL)
	   return true;
    if(thisclient->Session->codedebug) //Debug code
    {
       char buffer[200];
       sprintf ( buffer, "Skill type = %i target = %i",thisskill->skilltype,thisskill->target);
       SendPM(thisclient, buffer);
    }
    if(!thisclient->canUseSkill(thisskill))
    {
        SendPM(thisclient, "Sorry. You cannot use that skill");
        return true;
    }
	unsigned int skilltarget = thisskill->target;
    unsigned int skillrange = thisskill->aoeradius;

	if( thisskill->aoe == 0 )
	{
        if(thisclient->Session->codedebug) //Debug code
        {
           SendPM(thisclient, "Skill aoe is 0. Action = BUFF_SELF");
        }
        thisclient->StartAction( NULL, BUFF_SELF, skillid );
    }
    else
    {
        if(isSkillTargetFriendly( thisskill ))
        {
            if(thisclient->Session->codedebug) //Debug code
            {
               SendPM(thisclient, "Skill aoe is 1 and target is friendly. Action = BUFF_AOE");
            }
            thisclient->StartAction( NULL, BUFF_AOE, skillid );
        }
        else
        {
            if(thisclient->Session->codedebug) //Debug code
            {
               SendPM(thisclient, "Skill aoe is 1 and target is UN-friendly. Action = SKILL_AOE");
            }
            thisclient->StartAction( NULL, SKILL_AOE, skillid );
        }
    }
    return true;
}

// Aoe Skill
bool CWorldServer::pakSkillAOE( CPlayer* thisclient, CPacket* P)
{
    if(thisclient->Session->codedebug) //Debug code
    {
       char buffer[200];
       sprintf ( buffer, "Skill went to pakSkillAOE" );
       SendPM(thisclient, buffer);
    }

    if( thisclient->Shop->open || thisclient->Status->Muted != 0xff || !thisclient->Status->CanCastSkill) return true;
    BYTE num = GETBYTE( (*P), 0 );
    thisclient->Position->skilltargetpos.x = P->GetFloat(1)/100; //these set an absolute aoe center. not a monster.
    thisclient->Position->skilltargetpos.y = P->GetFloat(5)/100;
    if(thisclient->Session->codedebug) //Debug code
    {
       SendPM(thisclient, "target X = %f target Y = %f",thisclient->Position->skilltargetpos.x,thisclient->Position->skilltargetpos.y );
    }

    //arnold
    if(num >= MAX_SKILL)
    {
        Log( MSG_HACK, "Invalid Skill id %i for %s ", num, thisclient->CharInfo->charname );
        return false;
    }
    unsigned int skillid;
    if (num > 29)
    {
         skillid = thisclient->askill[num-30] + thisclient->askilllvl[num-30];
    }
    else
    {
         skillid = thisclient->bskills[num];
    }
    CSkills* thisskill = GetSkillByID( skillid );
    if(thisskill == NULL) return true;
    if(thisclient->Session->codedebug) //Debug code
    {
       char buffer[200];
       sprintf ( buffer, "Skill type = %i target = %i",thisskill->skilltype,thisskill->target);
       SendPM(thisclient, buffer);
    }
    if(!thisclient->canUseSkill(thisskill))
    {
        SendPM(thisclient, "Sorry. You cannot use that skill");
        return true;
    }
    if(thisskill->aoe == 1)
    {
        if(isSkillTargetFriendly( thisskill ))
        {
            if(thisclient->Session->codedebug) //Debug code
            {
               SendPM(thisclient, "Skill aoe is 1 and target is friendly. Action = nothing");
            }
            //cout << "Friendly skill: " << thisclient->Battle->skillid << endl;
        }
        else
        {
            if(thisclient->Session->codedebug) //Debug code
            {
               SendPM(thisclient, "Skill aoe is 1 and target is UN-friendly. Action = AOE_TARGET");
            }
            thisclient->StartAction( NULL , AOE_TARGET, skillid );
        }
    }
    else
    {
        if(thisclient->Session->codedebug) //Debug code
        {
            SendPM(thisclient, "Skill aoe is 0. Action = nothing");
        }
        Log( MSG_INFO, "no aoe, skillid = %i ", thisclient->Battle->skillid);
    }
    return true;
}

// Consumible Items
bool CWorldServer::pakUseItem ( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Shop->open)
        return true;
    BYTE slot = GETBYTE((*P),0);
    if(!CheckInventorySlot( thisclient, slot))
        return false;
    if( thisclient->items[slot].count<=0 )
        return true;
    CUseInfo* thisuse = GetUseItemInfo( thisclient, slot);
    if(thisuse == NULL)
    {
        Log(MSG_WARNING,"[%i]Invalid Item, Item: %i. - Type: %i",
        thisclient->clientid, thisclient->items[slot].itemnum,
        thisclient->items[slot].itemtype);
        return true;
    }
    bool flag = false;
    switch(thisuse->usescript)
    {
        case 1: // Food
        {
            thisclient->UsedItem->usevalue = thisuse->usevalue;
            thisclient->UsedItem->usetype = thisuse->usetype;
            thisclient->UsedItem->userate = 15;
            thisclient->UsedItem->used = 0;
            BEGINPACKET( pak,0x7a3 );
            ADDWORD    ( pak, thisclient->clientid );
            ADDWORD    ( pak, thisuse->itemnum );
            SendToVisible( &pak, thisclient );
            flag = true;
            Log(MSG_WARNING, "Food item used. type %i Value %i", thisuse->usetype, thisuse->usevalue );
        }
        break;
        case 2: // Return Scroll
        {
            BEGINPACKET( pak,0x7a3 );
            ADDWORD    ( pak,thisclient->clientid );
            ADDWORD    ( pak, thisuse->itemnum );
            ADDBYTE    ( pak,slot );
            thisclient->client->SendPacket( &pak );
            //thisclient->items[slot].count -= 1;
            //if( thisclient->items[slot].count == 0 )
            //    ClearItem( thisclient->items[slot] );
            fPoint thispoint;
            thispoint.x = floor( (double)thisuse->usevalue/10000 );
            thispoint.y = floor( (double)(thisuse->usevalue%10000) );
            TeleportTo ( thisclient, thisuse->usetype, thispoint );
            flag = true;
        }
        break;
        case 3: // Charm Scroll
        {
	        CSkills* thisskill = GetSkillByID( thisuse->usetype );
            if(thisskill == NULL)
            {
                Log(MSG_WARNING, "Char %s tried to use invalid scroll type: %i", thisclient->CharInfo->charname, thisuse->usetype );
                delete thisuse;
          	    return true;
            }
        	int skilltarget = thisskill->target;
            int skillrange = thisskill->aoeradius;
        	if( thisskill->aoe == 0 )
        	{
                thisclient->StartAction( NULL,BUFF_SELF,thisuse->usetype );
            }
            else
            {
                if(isSkillTargetFriendly( thisskill ))
                {
                    thisclient->StartAction( NULL,BUFF_AOE,thisuse->usetype );
                }
                else
                {
                    thisclient->StartAction( NULL,SKILL_AOE,thisuse->usetype );
                }
            }
            flag = true;
        }
        break;
        case 4: // Dance Scroll | FireCrackers | Emotion
        {
            //Start Animation
            BEGINPACKET( pak, 0x7b2 );
            ADDWORD    ( pak, thisclient->clientid );
            ADDWORD    ( pak, thisuse->usevalue );
            SendToVisible( &pak, thisclient );
            //Finish Animation
            RESETPACKET( pak, 0x7bb );
            ADDWORD    ( pak, thisclient->clientid );
            SendToVisible( &pak, thisclient );
            //????
            RESETPACKET( pak, 0x7b9);
            ADDWORD    ( pak, thisclient->clientid);
            ADDWORD    ( pak, thisuse->usevalue );
	        SendToVisible( &pak, thisclient );
            flag = true;
        }
        break;
        case 12: //Dance scrolls
        {
            CSkills* thisskill = GetSkillByID( thisuse->usetype );
            if(thisskill == NULL)
            {
                Log(MSG_WARNING, "Char %s tried to use invalid Dance scroll type: %i", thisclient->CharInfo->charname, thisuse->usetype );
                delete thisuse;
          	    return true;
            }
            //Log(MSG_INFO, "Char %s used a Dance scroll type: %i", thisclient->CharInfo->charname, thisuse->usetype );
            int skilltarget = thisskill->target;
            int skillrange = thisskill->aoeradius;
            flag = true;
            //Log(MSG_INFO, "Sending skill request. AOE range = %i", skillrange);
            if(skillrange > 0 ) //AOE effect
            {
                thisclient->StartAction( NULL,BUFF_AOE,thisuse->usetype );
            }
            else
            {
                thisclient->StartAction( NULL,BUFF_SELF,thisuse->usetype );
            }
            flag = true;
        }
        break;
        case 13: // Fireworks
        {
            CSkills* thisskill = GetSkillByID( thisuse->usetype );
            if(thisskill == NULL)
            {
                Log(MSG_WARNING, "Char %s tried to use invalid Dance scroll type: %i", thisclient->CharInfo->charname, thisuse->usetype );
                delete thisuse;
          	    return true;
            }
            //Log(MSG_INFO, "Char %s used a Dance scroll type: %i", thisclient->CharInfo->charname, thisuse->usetype );
            int skilltarget = thisskill->target;
            int skillrange = thisskill->aoeradius;
            flag = true;
            Log(MSG_INFO, "Sending skill request. AOE range = %i", skillrange);
            if(skillrange > 0 ) //AOE effect
            {
                thisclient->StartAction( NULL,BUFF_AOE,thisuse->usetype );
            }
            else
            {
                Log(MSG_INFO, "Char %s used an invalid firework type: %i", thisclient->CharInfo->charname, thisuse->usetype );
            }
            flag = true;
        }
        break;
        case 5:  // summon
        case 11: // Summon ownerless
        {
            CNPCData* thisnpc = GetNPCDataByID( thisuse->usevalue );
            if(thisnpc == NULL)
            {
                Log( MSG_WARNING,"[%i]NPCDATA NOT Founded: %i.",
                                    thisclient->clientid,thisuse->usevalue );
                delete thisuse;
                return true;
            }
            //Start Animation
            BEGINPACKET( pak, 0x7b2 );
            ADDWORD    ( pak, thisclient->clientid );
            ADDWORD    ( pak, thisuse->usetype );
            ADDBYTE    ( pak, 6 );
            SendToVisible( &pak, thisclient );
            //Finish Animation
            RESETPACKET( pak, 0x7bb );
            ADDWORD    ( pak, thisclient->clientid );
            SendToVisible( &pak, thisclient );
            //????
            RESETPACKET( pak, 0x7b9);
            ADDWORD    ( pak, thisclient->clientid);
            ADDWORD    ( pak, thisuse->usetype );
	        SendToVisible( &pak, thisclient );
	        // Add our Mob to the mobs list
           	fPoint position = RandInCircle( thisclient->Position->current, 5 );
           	CMap* map = MapList.Index[thisclient->Position->Map];
           	int owner = 0;
           	if(thisuse->usescript == 5) owner = thisclient->clientid;
           	map->AddMonster( thisuse->usevalue, position, owner,0,1 );
            flag = true;
        }
        break;
        case 6: // Snowball
        {
            WORD clientid = GETWORD((*P),2);
            fPoint thispoint;
            CMap* map = MapList.Index[thisclient->Position->Map];
            CCharacter* character = map->GetCharInMap( clientid );
            if(character == NULL) return true;
            thisclient->StartAction( character, SKILL_BUFF, thisuse->usevalue );
            flag = true;
        }
        break;
        case 7: // scrolls [damage,maxhp,...]
        {
	        CSkills* thisskill = GetSkillByID( thisuse->usetype );
            if(thisskill == NULL)
            {
                Log(MSG_WARNING, "Char %s tried to use invalid scroll type: %i", thisclient->CharInfo->charname, thisuse->usetype );
                delete thisuse;
          	    return true;
            }
        	int skilltarget = thisskill->target;
            int skillrange = thisskill->aoeradius;
        	if( thisskill->aoe == 0 )
        	{
                thisclient->StartAction( NULL, BUFF_SELF, thisuse->usetype );
            }
            else
            {
                if(isSkillTargetFriendly( thisskill ))
                {
                    thisclient->StartAction( NULL, BUFF_AOE, thisuse->usetype );
                }
                else
                {
                    thisclient->StartAction( NULL, SKILL_AOE, thisuse->usetype );
                }
            }
            flag = true;
        }
        break;
        case 10: // Skill Book
        {
            flag = LearnSkill( thisclient, thisuse->usevalue );
        }
        break;
        case 14: // Fairy scroll
        {
            GServer->Config.ScrollFairy ++; //increase count of scroll fairies by one
            int oldFairyMax = GServer->Config.FairyMax;
            GServer->Config.FairyMax = (int)ceil((float)GServer->ClientList.size() / 50.0) + GServer->Config.ScrollFairy; //recalculate the maximum number of fairies
            if( oldFairyMax < GServer->Config.FairyMax ) // if we increased the fairy max we need to make a dummy fairy to hold the space or we will crash the server
            {
                CFairy* thisfairy = new (nothrow) CFairy;
                thisfairy->LastTime = clock();
                thisfairy->assigned = 0;
                thisfairy->ListIndex = 0;
                thisfairy->WaitTime = GServer->Config.FairyWait;
                GServer->FairyList.push_back( thisfairy );
            }
            for (int i=0; i<Config.FairyMax; i++)     // Now we check all fairies to find an unasigned one
            {
                if(FairyList.at(i)->assigned == false) // we found an empty fairy so let's assign it
                {
                    FairyList.at(i)->ListIndex = 0;
			        FairyList.at(i)->LastTime = clock();
			        FairyList.at(i)->assigned = true;
			        FairyList.at(i)->scroll = true;                  // Scroll value set to true. this IS a scroll buff fairy
			        thisclient->Fairy = true;
			        thisclient->FairyListIndex = i;                 // FairyList index number of our actual fairy
			        DoFairyStuff(thisclient, 1);                    // spawn fairy to target
			        thisclient->SetStats();
			        flag = true;
			        break;
                }
            }

            break;
        }
    }
    if(flag == true)
    {
        BEGINPACKET( pak,0x7a3 );
        ADDWORD    ( pak, thisclient->clientid );
        ADDWORD    ( pak, thisuse->itemnum );
        ADDBYTE    ( pak, slot );
        thisclient->client->SendPacket( &pak );
        thisclient->items[slot].count -= 1;
        if( thisclient->items[slot].count <= 0 )
            ClearItem( thisclient->items[slot] );
        thisclient->saveinventory();
    }
    delete thisuse;
    return true;
}

// Level UP Skill
bool  CWorldServer::pakLevelUpSkill( CPlayer *thisclient, CPacket* P )
{
    CSkills* thisskill;
    CSkills* nextskill;
    char rs = 0;
    char rl = 0;
    int pos = GETBYTE ((*P),0);
    // Check that skill is valid
    if (pos > 59)
    { // Passive Skill - ID + 60
         thisskill = GetSkillByID((thisclient->pskill[pos-60])+(thisclient->pskilllvl[pos-60]));
         nextskill = GetSkillByID(((thisclient->pskill[pos-60])+(thisclient->pskilllvl[pos-60]))+1);
    }
    else if (pos > 29)
    { // Active Skill - ID + 30
         thisskill = GetSkillByID((thisclient->askill[pos-30])+(thisclient->askilllvl[pos-30]));
         nextskill = GetSkillByID(((thisclient->askill[pos-30])+(thisclient->askilllvl[pos-30]))+1);
    }
    else return true;
    // Make sure skill is found
    if (thisskill == NULL || nextskill == NULL) return true;
    if(thisskill->skillid != nextskill->skillid) return true; //if skillid is different then we have gone off the end of the skill levels

    // Check SP requirement
    if (thisclient->CharInfo->SkillPoints < nextskill->sp) {
        BEGINPACKET( pak, 0x7b1 );
        ADDBYTE( pak, 0x02 );
        thisclient->client->SendPacket( &pak );
        return true;
    }

    // Check zuly requirement
    if (thisclient->CharInfo->Zulies < nextskill->zuly) {
        BEGINPACKET( pak, 0x7b1 );
        ADDBYTE( pak, 0x01 );
        thisclient->client->SendPacket( &pak );
        return true;
    }

    // Check both stat requirements.
    bool fail = false;
    for (char i = 0; i < 2; i++)
    {
        switch (nextskill->req[i])
        {
            case sLevel:
                if (nextskill->reqam[i] > thisclient->Stats->Level) fail = true;
            break;
            case sStrength:
                if (nextskill->reqam[i] > thisclient->Attr->Str) fail = true;
            break;
            case sDexterity:
                if (nextskill->reqam[i] > thisclient->Attr->Dex) fail = true;
            break;
            case sIntelligence:
                if (nextskill->reqam[i] > thisclient->Attr->Int) fail = true;
            break;
            case sConcentration:
                if (nextskill->reqam[i] > thisclient->Attr->Con) fail = true;
            break;
            case sCharm:
                if (nextskill->reqam[i] > thisclient->Attr->Cha) fail = true;
            break;
            case sSensibility:
                if (nextskill->reqam[i] > thisclient->Attr->Sen) fail = true;
            break;
            default:
                break;
        }
    }

    if (fail)
	{
        BEGINPACKET( pak, 0x7b1 );
        ADDBYTE( pak, 0x03 );
        thisclient->client->SendPacket( &pak );
        return true;
    }

    // Check class requirement
    bool passClass = false;
    int nocheck = 4; // Used to check if no lvl check
    for (char i = 0; i < 4; i++)
    {
      if (nextskill->c_class[i]>0)
      {
        switch(nextskill->c_class[i])
        {
            case cSoldierJob:
                 if((thisclient->CharInfo->Job)/100==1)passClass = true;
                 break;
            case cMuseJob:
                 if((thisclient->CharInfo->Job)/100==2)passClass = true;
                 break;
            case cHawkerJob:
                 if((thisclient->CharInfo->Job)/100==3)passClass = true;
                 break;
            case cDealerJob:
                 if((thisclient->CharInfo->Job)/100==4)passClass = true;
                 break;
            case cKnightJob:
                 if(thisclient->CharInfo->Job==121)passClass = true;
                 break;
            case cChampionJob:
                 if(thisclient->CharInfo->Job==122)passClass = true;
                 break;
            case cMageJob:
                 if(thisclient->CharInfo->Job==221)passClass = true;
                 break;
            case cClericJob:
                 if(thisclient->CharInfo->Job==222)passClass = true;
                 break;
            case cRaiderJob:
                 if(thisclient->CharInfo->Job==321)passClass = true;
                 break;
            case cScoutJob:
                 if(thisclient->CharInfo->Job==322)passClass = true;
                 break;
            case cBourgeoisJob:
                 if(thisclient->CharInfo->Job==421)passClass = true;
                 break;
            case cArtisanJob:
                 if(thisclient->CharInfo->Job==422)passClass = true;
                 break;
            default:
                break;
        }
        if (passClass) break;
      } else
        nocheck--;
    }
    // Player isn't the required class/job
    if (!passClass && nocheck > 0)
    {
        BEGINPACKET( pak, 0x7b1 );
        ADDBYTE( pak, 0x04 );
        thisclient->client->SendPacket( &pak );
        return true;
    }
    if(thisclient->Session->codedebug) //Debug code
    {
         char buffer[200];
         sprintf ( buffer, "Passed check for class" );
         SendPM(thisclient, buffer);
    }
    // Check required skills/skill levels
    for (char j = 0; j < 3 ; j++)
    {
        if(nextskill->rskill[j]>0)
        {
            rs++;
            for (char i = 0; i<30;i++)
            {
                // Subtract 1 because our characters levels are actually off by 1
                // Check passive skill
                if ( ( thisclient->pskill[i] == nextskill->rskill[j] ) &&
                   ( thisclient->pskilllvl[i] >= nextskill->lskill[j] - 1 ) )
                {
                    rl++;
                    break; // No use continueing for the rest of the for loop, right?
                }
                // Check Active Skill
                if ( ( thisclient->askill[i] == nextskill->rskill[j] ) &&
                   ( thisclient->askilllvl[i] >= nextskill->lskill[j] - 1 ) )
                {
                    rl++;
                    break; // No need to continue inner loop
                }
            }
        }
    }

    if(rl != rs)
    {
        BEGINPACKET( pak, 0x7b1 );
        ADDBYTE( pak, 0x05 );
        thisclient->client->SendPacket( &pak );
        return true;
    }

    if (pos > 59) thisclient->pskilllvl[pos-60] += 1;
    else if (pos > 29) thisclient->askilllvl[pos-30] += 1;
    thisclient->CharInfo->SkillPoints -= nextskill->sp;
    thisclient->CharInfo->Zulies -= nextskill->zuly;

    BEGINPACKET( pak, 0x7b1 );
    ADDBYTE( pak, 0x00 );
    ADDBYTE( pak, GETBYTE ((*P),0) );
    ADDWORD( pak, GETWORD ((*P),1) );
    ADDWORD( pak, thisclient->CharInfo->SkillPoints );
    thisclient->client->SendPacket( &pak );
    thisclient->SetStats();
    return true;
}

// Equip bullets arrows and cannons
bool CWorldServer::pakEquipABC ( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Shop->open)
        return true;
    BYTE itemslot = GETBYTE((*P),0);
    int slot = ((itemslot-32)/4)+72;
    int dest = 0;
    int type = (itemslot-32)%4;
    if(!CheckInventorySlot( thisclient, slot))
        return false;
    if(itemslot>3)
    {
        dest = type+132;
    }
    else
    {
        slot = itemslot + 132;
        dest = thisclient->GetNewItemSlot( thisclient->items[slot] );
        if(dest==0xffff)
            return true;
        type=300;
    }
	CItem tmpitm = thisclient->items[slot];
	thisclient->items[slot] =thisclient->items[dest];
	thisclient->items[dest] = tmpitm;

	thisclient->UpdateInventory( dest, slot );
    BEGINPACKET( pak, 0x7ab );
    ADDWORD    ( pak, thisclient->clientid );
    unsigned int effect = ( thisclient->items[dest].itemnum * 32 ) + type;
    ADDWORD    ( pak, effect );
    SendToVisible( &pak, thisclient );
    thisclient->Stats->Attack_Power = thisclient->GetAttackPower( );
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Craft item  (Template by Arnold)  (Crafting modifications by: Killerfly)	Fixed for irose by: Arnold	//
// Recoded for osProse by PurpleYouko                                                                   //
//////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CWorldServer::pakCraft( CPlayer* thisclient, CPacket* P )
{
	if(thisclient->Shop->open==true)
        return true;
	CItem item;
	UINT quality = 0;
	int	m = 0;

	// determine the item number and type
	item.itemnum = (GETWORD((*P), 2));
	item.itemtype = (GETBYTE((*P), 0x1));

	//get material used lookup number
	int	materialnumber = 0;
	if(item.itemtype < 10)
	{
        materialnumber = EquipList[item.itemtype].Index[item.itemnum]->material;
    }
    else
    {
        switch(item.itemtype)
        {
            case 11:materialnumber = JemList.Index[item.itemnum]->material;break;
            case 14:materialnumber = PatList.Index[item.itemnum]->material;break;
            default:
                break;
        }
    }
	if(thisclient->Session->codedebug)
	{
       SendPM(thisclient, "Attempting to craft an item. type = %i. id = %i",item.itemtype, item.itemnum);
       SendPM(thisclient, "Material number = %i",materialnumber);
    }
	//check material slots before we start making the new item
	if(ProductList.Index[materialnumber]->matType != 0) // recipe has an item type listed rather than a specific item
    {
        WORD material= GETWORD((*P), 4);
        UINT matid = thisclient->items[material].itemnum;
        quality = NaturalList.Index[matid]->quality;
        if(thisclient->Session->codedebug)
    	{
           SendPM(thisclient, "Recipe recquires an item with type = %i.",ProductList.Index[materialnumber]->matType);
           SendPM(thisclient, "Type of material in slot = %i",thisclient->items[material].type);
        }
        if(ProductList.Index[materialnumber]->matType != thisclient->items[material].type)
        {
            if(thisclient->Session->codedebug)
        	{
               SendPM(thisclient, "Rejected as mat types do not match");
            }
            return true; //item in the slot is the wrong type
        }
    }
    m=0;
    for(char used=4; used != 12; used +=2)
    {
        WORD material= GETWORD((*P), used);//gets inventory location
        if(thisclient->Session->codedebug)
    	{
           SendPM(thisclient, "Slot number = %i", material);
           SendPM(thisclient, "Recipe recquires an item with type = %i. id = %i",ProductList.Index[materialnumber]->itemtype[m],ProductList.Index[materialnumber]->itemid[m]);
           SendPM(thisclient, "Type of material in slot = %i. id = %i",thisclient->items[material].itemtype,thisclient->items[material].itemnum);
           SendPM(thisclient, "Material count required = %i", ProductList.Index[materialnumber]->amount[m]);
           SendPM(thisclient, "Material count in slot = %i", thisclient->items[material].count);
        }
        if(!CheckInventorySlot( thisclient, material))
        {
            SendPM(thisclient, "Crafting Error 0: Missing or incorrect material in inventory slot.");
            return true;
        }
        if (material != 0)
        {
            if(ProductList.Index[materialnumber]->matType != 0 && m == 0) //only checked for the first item in the recipe
            {
                if(thisclient->items[material].type != ProductList.Index[materialnumber]->matType)
                {
                    SendPM(thisclient, "Crafting Error %i 1: Server and Client crafting recipes do not match",m);
                    return true; // item type does not match recipe
                }
            }
            else
            {
                if(thisclient->items[material].itemtype != ProductList.Index[materialnumber]->itemtype[m])
                {
                    SendPM(thisclient, "Crafting Error %i 2: Server and Client crafting recipes do not match",m);
                    return true; // item type does not match recipe
                }
                if(thisclient->items[material].itemnum != ProductList.Index[materialnumber]->itemid[m])
                {
                    SendPM(thisclient, "Crafting Error %i 3: Server and Client crafting recipes do not match",m);
                    return true; // item id does not match recipe
                }
            }
            if(thisclient->items[material].count < ProductList.Index[materialnumber]->amount[m])
            {
                SendPM(thisclient, "Crafting Error %i 4: Server and Client crafting recipes do not match",m);
                return true; //not enough of the required item
            }
        }
        m += 1;
    }
    if(thisclient->Session->codedebug)
   	{
        SendPM(thisclient, "Item cleared the checks and will be created");
    }

	// item durability randomizer
	int lowest = thisclient->Attr->Con/ 10 + 17;
	int highest = thisclient->Attr->Con / 10 + 70;
	int range = (highest - lowest) + 1;
	item.durability = lowest+int(range*rand()/(RAND_MAX + 1.0));

	// stats randomizer
	int changeofstatslow = thisclient->Attr->Sen / 13 + 10;
	int changeofstatshigh = thisclient->Attr->Sen / 13 + 50;
	int changeofstatsrange = (changeofstatshigh-changeofstatslow)+1;
	if (changeofstatslow+int(changeofstatsrange*rand()/(RAND_MAX + 1.0)) > 50)
    {
    	int statslowget = 1;
    	int statshighget = 256;
    	int setstatrange=(statshighget-statslowget)+1;
      	item.stats = statslowget + int(setstatrange*rand()/(RAND_MAX + 1.0));
    	item.appraised = 1;
	}
    else
    {
        item.stats = 0;
        item.appraised = 0;
	}
	item.socketed = 0;
	item.gem = 0;
	item.lifespan = 100; //Its new so 100%
	item.refine = 0;
	item.count = 1;


    unsigned newslot= thisclient->GetNewItemSlot( item );
	if (newslot !=0xffff)
    {
        //removes material items from the slots
        item.count +=(thisclient->items[newslot].count);
		thisclient->items[newslot] = item;
		m=0;
		for(char used=4; used != 12; used +=2)
        {
            WORD material= GETWORD((*P), used);//gets inventory location
            if (material != 0)
            {
		        thisclient->items[material].count -= ProductList.Index[materialnumber]->amount[m];
    	        m += 1;
		        if (thisclient->items[material].count <=0)
                {
			        ClearItem(thisclient->items[material]);
                }
            }
        }

        BEGINPACKET( pak, 0x07d8);
        ADDWORD( pak, thisclient->clientid );
        ADDWORD( pak, 0x0100);
        ADDWORD( pak, item.itemnum);// item id not shifted
        thisclient->client->SendPacket(&pak);

        RESETPACKET( pak, 0x07af);
        ADDBYTE( pak, 0x00);
        ADDWORD( pak, newslot);

        // Make craft bars
        int bar1 = item.durability * 9;
        int bar2 = changeofstatsrange * 9;
        int bar3 = item.durability + changeofstatsrange * 6;
        int bar4 = item.durability + changeofstatsrange + bar3 / 3;

        ADDWORD( pak, bar1);//progress bar1 0 is empty 0x0400 is full bar
        ADDWORD( pak, bar2);//progress bar2 0 is empty 0x0400 is full bar
        if ((GETWORD((*P),  8))==0){ ADDWORD( pak, 0x99a0);}else{ ADDWORD( pak, bar3);}//progress bar3 0 is empty 0x0400 is full bar
        if ((GETWORD((*P), 10))==0){ ADDWORD( pak, 0x99a0);}else{ ADDWORD( pak, bar4);}//progress bar4 0 is empty 0x0400 is full bar
        ADDWORD(pak, BuildItemHead(item));

     if (item.itemtype == 11)
     {
	     ADDWORD( pak, item.count);// amount
	     ADDWORD( pak, 0x0000);
     }
     else
     {
	     ADDDWORD(pak, BuildItemData(item));
     }
        int crafting_exp = item.durability + changeofstatsrange * (thisclient->Stats->Level/ 5);
		thisclient->CharInfo->Exp += crafting_exp;//  add exp
		thisclient->client->SendPacket(&pak);
		if(!thisclient->CheckPlayerLevelUP( )){
        RESETPACKET( pak, 0x79b );
        ADDDWORD   ( pak, thisclient->CharInfo->Exp );
        ADDWORD    ( pak, thisclient->CharInfo->stamina );
        ADDWORD    ( pak, 0 );
        thisclient->client->SendPacket( &pak );}
     }
     else
     {
         BEGINPACKET (pak, 0x702);
         ADDSTRING(pak, "No free slot !");
         ADDBYTE(pak, 0);
         thisclient->client->SendPacket(&pak);
     }
     thisclient->saveinventory();
     return true;
}


bool CWorldServer::pakModifiedItemDone( CPlayer* thisclient, CPacket* P )
{
     DWORD result = GETDWORD((*P), 0x00 );
     BEGINPACKET( pak, 0x07d8);
     ADDWORD( pak, thisclient->clientid );
     ADDDWORD( pak, result);
     SendToVisible( &pak , thisclient);
     return true;

}



// Identify Item
bool CWorldServer::pakidentify( CPlayer* thisclient, CPacket* P)
{
    WORD itemslot = GETWORD ((*P),0);
    if(!CheckInventorySlot( thisclient, itemslot))
        return false;
    thisclient->items[itemslot].appraised = true;
    BEGINPACKET( pak, 0x7ba );
    ADDWORD    ( pak, itemslot );
    ADDBYTE    ( pak, 0x00 );
    thisclient->client->SendPacket( &pak );
    return true;
}

// Show Storge Items
bool CWorldServer::pakStorage( CPlayer* thisclient, CPacket* P)
{
    BYTE action = GETBYTE((*P),0);
    switch(action)
    {
        case 0x00:
        {
            UINT nstorageitems = thisclient->Getnstorageitems(thisclient);
            Log( MSG_INFO, "Number of items in storage: %i ", nstorageitems);
            BEGINPACKET( pak, 0x7ad );
            ADDBYTE    ( pak, 0x00 );
            ADDBYTE    ( pak, nstorageitems ); //numero de items
            UINT counter = 0;
            for(int i=0;i<160;i++)
            {
           		if( thisclient->storageitems[i].itemtype !=0 && counter < 144) //packet can only handle 144 items
           		{
                    ADDBYTE    ( pak, i );
                  	ADDWORD   ( pak, BuildItemHead( thisclient->storageitems[i] ) );
               		ADDDWORD   ( pak, BuildItemData( thisclient->storageitems[i] ) );
               		counter ++;
                }
            }
            ADDQWORD( pak, thisclient->CharInfo->Storage_Zulies );
            thisclient->client->SendPacket( &pak );
        }
        break;
        default:
            Log( MSG_INFO, "Storage unknow action: %i ", action);
    }
    return true;
}

// Change Storage (Deposit/Withdraw items)
bool CWorldServer::pakChangeStorage( CPlayer* thisclient, CPacket* P)
{
  /* Packet for this function
     ===========================
     [BYTE] Action
     [BYTE] Item Slot
     [WORD] Item Head
     [DWORD] Item Body
     [BYTE] Unk (0x00)

  */
    BYTE action = GETBYTE((*P),0);
    switch(action)
    {
        case 0x00: //Deposit
        {
            int itemslot = (int)GETBYTE((*P),1);
            CItem clientitem = GetItemByHeadAndData( GETWORD((*P), 2), GETDWORD((*P), 4) );

            if(!CheckInventorySlot( thisclient, itemslot ))
                return false;
            CItem newitem = thisclient->items[itemslot];
            //if(newitem == NULL)
            //    return true;
            // Set the newitem's count to the count from the client for slot search
            newitem.count = clientitem.count;

            Log(MSG_INFO, "New Item: %i %i", newitem.itemtype, newitem.itemnum);
            // find an empty or matching slot depending on new item type
            int newslot = thisclient->GetNewStorageItemSlot ( newitem );
            if(newslot == 0xffff)
                return true;
            if(newitem.itemtype >= 10 && newitem.itemtype <= 12) //is it a stackable type
            {
                int count = clientitem.count;
                if(count > thisclient->items[itemslot].count)
                    count = thisclient->items[itemslot].count; //stops players transferring more than they actually have
                newitem.count = count;

                if (thisclient->storageitems[newslot].count > 0)
                    thisclient->storageitems[newslot].count += newitem.count; //add the new items to the storage slot
                else
                    thisclient->storageitems[newslot] = newitem;

                thisclient->items[itemslot].count -= count; //delete the items from inventory slot
                if(thisclient->items[itemslot].count <= 0)
                    ClearItem(thisclient->items[itemslot]);
            }
            else
            {
                // non-stackable
                ClearItem(thisclient->items[itemslot]);
                thisclient->storageitems[newslot] = newitem;
            }
            BEGINPACKET( pak, 0x7ae );
            ADDWORD    ( pak, itemslot );
            ADDWORD    ( pak, newslot );
            ADDWORD    ( pak, BuildItemHead( thisclient->items[itemslot] ) );
    		ADDDWORD   ( pak, BuildItemData( thisclient->items[itemslot] ) );
            ADDWORD    ( pak, BuildItemHead( thisclient->storageitems[newslot] ) );
            ADDDWORD   ( pak, BuildItemData( thisclient->storageitems[newslot] ) );
    		ADDQWORD   ( pak, thisclient->CharInfo->Zulies );
            ADDBYTE    ( pak, 0x00 );
            thisclient->client->SendPacket( &pak );
            //thisclient->nstorageitems++;  //this is pointless and serves no purpose
        }
        break;//thanks to anon for post that this break was missing
        case 0x01: //Withdraw
        {
            BYTE storageslot = GETBYTE((*P),1);
            CItem clientitem = GetItemByHeadAndData( GETWORD((*P), 2), GETDWORD((*P), 4) );

            if(storageslot >= 160)
            {
                Log( MSG_HACK, "Invalid storage slot %i from %s", storageslot, thisclient->Session->username );
                return false;
            }
            CItem newitem = thisclient->storageitems[storageslot];
            newitem.count = clientitem.count;

            int newslot= thisclient->GetNewItemSlot ( newitem );
            if (newslot == 0xffff)
                return true;

            if(newitem.itemtype > 9 && newitem.itemtype < 14)
            {
                WORD count = clientitem.count;
                if( count > thisclient->storageitems[storageslot].count )
                    count = thisclient->storageitems[storageslot].count;
                newitem.count = count;

                if (thisclient->items[newslot].count > 0)
                    thisclient->items[newslot].count += newitem.count;
                else
                    thisclient->items[newslot] = newitem;

                thisclient->storageitems[storageslot].count -= count;
                if(thisclient->storageitems[storageslot].count<=0)
                    ClearItem(thisclient->storageitems[storageslot]);
            }
            else
            {
                ClearItem(thisclient->storageitems[storageslot]);
                thisclient->items[newslot] = newitem;
            }

            BEGINPACKET( pak, 0x7ae );
            ADDWORD    ( pak, newslot );
            ADDWORD    ( pak, storageslot );
            ADDWORD    ( pak, BuildItemHead( thisclient->items[newslot] ) );
    		ADDDWORD   ( pak, BuildItemData( thisclient->items[newslot] ) );
            ADDWORD    ( pak, BuildItemHead( thisclient->storageitems[storageslot] ) );
            ADDDWORD   ( pak, BuildItemData( thisclient->storageitems[storageslot] ) );
    		ADDQWORD   ( pak, thisclient->CharInfo->Zulies );
            ADDBYTE    ( pak, 0x00 );
            thisclient->client->SendPacket( &pak );
            //thisclient->nstorageitems--; //this is pointless and serves no purpose
        }
        break;
        default:
            Log( MSG_INFO, "Storage unknow action: %i ", action);
    }
    thisclient->saveinventory();
    thisclient->savestorage();
    return true;
}

// Deposit/Widthdraw zulies
bool CWorldServer::pakStoreZuly( CPlayer* thisclient, CPacket* P)
{
    BYTE action = GETBYTE ((*P), 0 );
    QWORD zuly = GETQWORD ((*P), 1 );
    switch(action)
    {
        case 0x10://deposit'
        {
            if(zuly > thisclient->CharInfo->Zulies)
                return true;
            thisclient->CharInfo->Zulies -= zuly;
            thisclient->CharInfo->Storage_Zulies += zuly;
            BEGINPACKET( pak, 0x7da );
            ADDQWORD   ( pak, thisclient->CharInfo->Zulies );
            ADDQWORD   ( pak, thisclient->CharInfo->Storage_Zulies );
            ADDBYTE    ( pak, 0x00 );
            thisclient->client->SendPacket( &pak );
        }
        break;
        case 0x11://withdraw
        {
            if(zuly > thisclient->CharInfo->Storage_Zulies )
                return true;
            thisclient->CharInfo->Zulies += zuly;
            thisclient->CharInfo->Storage_Zulies -= zuly;
            BEGINPACKET( pak, 0x7da );
            ADDQWORD   ( pak, thisclient->CharInfo->Zulies );
            ADDQWORD   ( pak, thisclient->CharInfo->Storage_Zulies );
            ADDBYTE    ( pak, 0x00 );
            thisclient->client->SendPacket( &pak );
        }
        break;
        default:
        {
            Log( MSG_INFO, "Storage unknow action: %i ", action);
            break;
        }
    }
    thisclient->saveinventory();
    thisclient->savestorage();
    return true;
}

// Open Shop
bool CWorldServer::pakOpenShop( CPlayer* thisclient, CPacket* P )
{
//Log( MSG_INFO, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x ", GETBYTE((*P),0), GETBYTE((*P),1), GETBYTE((*P),2), GETBYTE((*P),3), GETBYTE((*P),4), GETBYTE((*P),5), GETBYTE((*P),6), GETBYTE((*P),7), GETBYTE((*P),8), GETBYTE((*P),9), GETBYTE((*P),10), GETBYTE((*P),11), GETBYTE((*P),12), GETBYTE((*P),13), GETBYTE((*P),14), GETBYTE((*P),15), GETBYTE((*P),16), GETBYTE((*P),17), GETBYTE((*P),18), GETBYTE((*P),19), GETBYTE((*P),20), GETBYTE((*P),21), GETBYTE((*P),22), GETBYTE((*P),23), GETBYTE((*P),24) );
    if( thisclient->Shop->open )
        return true;
    BYTE nselling = GETBYTE((*P),0);
    BYTE nbuying = GETBYTE((*P),1);
    if(nselling>30 || nbuying>30)
        return true;
    int nchar = ((nselling + nbuying) * 11 )+2;
    strncpy(thisclient->Shop->name ,(char*)&(*P).Buffer[nchar] , P->Size-nchar );
    thisclient->Shop->Selling = nselling;
    thisclient->Shop->Buying = nbuying;
    for(int i=0;i<nselling;i++)
    {
        int n=(i*11)+2;
        BYTE slot =  GETBYTE((*P),n);
        if(!CheckInventorySlot( thisclient, slot))
            return false;
        thisclient->Shop->SellingList[i].slot = slot;
        if( thisclient->items[slot].itemtype>9 && thisclient->items[slot].itemtype<14 )
            thisclient->Shop->SellingList[i].count = GETWORD((*P),n+3);
        else
            thisclient->Shop->SellingList[i].count = 1;
        thisclient->Shop->SellingList[i].price = GETDWORD((*P),n+7);
    }
    for(int i=0;i<nbuying;i++)
    {
        unsigned int n=(nselling*11)+2+(i*11);
        BYTE slot = GETBYTE((*P),n);
        thisclient->Shop->BuyingList[slot].slot = slot;
        DWORD head = GETWORD((*P),n+1);
        DWORD data = GETDWORD((*P),n+3);
        CItem thisitem = GetItemByHeadAndData( head, data );
        thisclient->Shop->BuyingList[slot].item = thisitem;
        if( thisitem.itemtype > 9 && thisitem.itemtype < 14 )
            thisclient->Shop->BuyingList[slot].count = GETWORD((*P),n+3);
        else
            thisclient->Shop->BuyingList[slot].count = 1;
        thisclient->Shop->BuyingList[slot].price = GETDWORD((*P),n+7);
    }
    BEGINPACKET( pak, 0x796 );
    ADDWORD    ( pak, thisclient->clientid );
    ADDFLOAT   ( pak, thisclient->Position->current.x );
    ADDFLOAT   ( pak, thisclient->Position->current.y );
    ADDWORD    ( pak, 0x9057 );//>???
    SendToVisible( &pak, thisclient );

    RESETPACKET( pak, 0x7c2 );
    ADDWORD    ( pak, thisclient->clientid );
    ADDWORD    ( pak, thisclient->Shop->ShopType );
    ADDSTRING  ( pak, thisclient->Shop->name );
    ADDBYTE    ( pak, 0x00 );
    SendToVisible( &pak, thisclient );
    thisclient->Shop->open = true;
    return true;
}

// Show Shop to other players
bool CWorldServer::pakShowShop( CPlayer* thisclient, CPacket* P )
{
    WORD otherclientid = GETWORD((*P),0);
    CPlayer* otherclient = GetClientByID ( otherclientid, thisclient->Position->Map );
    if(otherclient == NULL)
        return true;
    BEGINPACKET( pak, 0x7c4 );
    ADDBYTE    ( pak, otherclient->Shop->Selling );
    ADDBYTE    ( pak, otherclient->Shop->Buying );
    for(unsigned int i = 0; i<otherclient->Shop->Selling;i++)
    {
        CItem thisitem =  otherclient->items[otherclient->Shop->SellingList[i].slot];
        thisitem.count = otherclient->Shop->SellingList[i].count;
        ADDBYTE     ( pak, i );
        ADDWORD    ( pak, BuildItemHead( thisitem ) );
        ADDDWORD    ( pak, BuildItemData( thisitem ) );
        ADDDWORD    ( pak, otherclient->Shop->SellingList[i].price );
    }
    for(unsigned int i = 0; i<30;i++)
    {
        if(otherclient->Shop->BuyingList[i].count>0)
        {
            CItem thisitem = otherclient->Shop->BuyingList[i].item;
            ADDBYTE     ( pak, i );
            ADDWORD    ( pak, BuildItemHead( thisitem ) );
            ADDDWORD    ( pak, BuildItemData( thisitem ) );
            ADDDWORD    ( pak, otherclient->Shop->BuyingList[i].price );
        }
    }
    ADDBYTE    ( pak, 0x00 );
    thisclient->client->SendPacket( &pak );
    return true;
}

// Buy From Shop
bool CWorldServer::pakBuyShop( CPlayer* thisclient, CPacket* P )
{
    // Log( MSG_INFO, "Size:%04x", P->Size );
    // Log( MSG_INFO, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x ", GETBYTE((*P),0), GETBYTE((*P),1), GETBYTE((*P),2), GETBYTE((*P),3), GETBYTE((*P),4), GETBYTE((*P),5), GETBYTE((*P),6), GETBYTE((*P),7), GETBYTE((*P),8), GETBYTE((*P),9), GETBYTE((*P),10), GETBYTE((*P),11), GETBYTE((*P),12), GETBYTE((*P),13), GETBYTE((*P),14), GETBYTE((*P),15), GETBYTE((*P),16), GETBYTE((*P),17), GETBYTE((*P),18), GETBYTE((*P),19), GETBYTE((*P),20), GETBYTE((*P),21), GETBYTE((*P),22), GETBYTE((*P),23), GETBYTE((*P),24) );

    WORD otherclientid = GETWORD((*P),0);
    BYTE action = GETBYTE((*P),2);
    switch(action)
    {
        case 0x01://check this
        {
            CPlayer* otherclient = GetClientByID( otherclientid, thisclient->Position->Map );
            if( otherclient == NULL )
                return true;
            BYTE slot = GETBYTE((*P),3);
            unsigned int count = 0;
            unsigned int invslot = otherclient->Shop->SellingList[slot].slot;
            CItem newitem =  otherclient->items[invslot];
            if(otherclient->items[invslot].itemtype>9 &&
                    otherclient->items[invslot].itemtype<14)
                count = GETWORD((*P),6);
            else
                count = 1;
            if( count > otherclient->Shop->SellingList[slot].count )
                return true;
            newitem.count = count;
            if( thisclient->CharInfo->Zulies<(otherclient->Shop->SellingList[slot].price*count) )
                return true;
            unsigned int newslot = thisclient->GetNewItemSlot ( newitem );
            if(newslot==0xffff)
                return true;
            thisclient->CharInfo->Zulies -= (otherclient->Shop->SellingList[slot].price*count);
            otherclient->CharInfo->Zulies += (otherclient->Shop->SellingList[slot].price*count);
            if(otherclient->items[invslot].itemtype>9 &&
                    otherclient->items[invslot].itemtype<14)
            {
                if(otherclient->items[invslot].count<=count)
                {
                     ClearItem(otherclient->items[invslot])
                     otherclient->Shop->SellingList[slot].slot = 0;
                     otherclient->Shop->SellingList[slot].count = 0;
                     otherclient->Shop->SellingList[slot].price = 0;
                }
                else
                {
                    if(otherclient->Shop->SellingList[slot].count<=count)
                    {
                        otherclient->Shop->SellingList[slot].slot = 0;
                        otherclient->Shop->SellingList[slot].count = 0;
                        otherclient->Shop->SellingList[slot].price = 0;
                    }
                    else
                    {
                        otherclient->Shop->SellingList[slot].count -= count;
                    }
                    otherclient->items[invslot].count-=count;
                }
            }
            else
            {
                ClearItem( otherclient->items[invslot] )
                otherclient->Shop->SellingList[slot].slot = 0;
                otherclient->Shop->SellingList[slot].count = 0;
                otherclient->Shop->SellingList[slot].price = 0;
            }
            if(thisclient->items[newslot].count!=0)
                thisclient->items[newslot].count += newitem.count;
            else
                thisclient->items[newslot] = newitem;
            //update inventory (buyer)
            BEGINPACKET( pak, 0x7c7 );
            ADDQWORD   ( pak, thisclient->CharInfo->Zulies );
            ADDBYTE    ( pak, 0x01 ); //buy action
            ADDBYTE    ( pak, newslot );
            ADDWORD   ( pak, BuildItemHead( thisclient->items[newslot] ) );
            ADDDWORD   ( pak, BuildItemData( thisclient->items[newslot] ) );
            thisclient->client->SendPacket( &pak );

            //update inventory (seller)
            RESETPACKET( pak, 0x7c7 );
            ADDQWORD   ( pak, otherclient->CharInfo->Zulies );
            ADDBYTE    ( pak, 0x01 ); //buy action
            ADDBYTE    ( pak, invslot );
            ADDWORD   ( pak, BuildItemHead( otherclient->items[invslot] ) );
            ADDDWORD   ( pak, BuildItemData( otherclient->items[invslot] ) );
            otherclient->client->SendPacket( &pak );

            //update shop
            RESETPACKET( pak, 0x7c6 );
            ADDWORD    ( pak, otherclient->clientid );
            ADDBYTE    ( pak, 0x05 );
            ADDBYTE    ( pak, 0x01 );
            ADDBYTE    ( pak, slot );
            if(otherclient->Shop->SellingList[slot].count<=0)
            {
               ADDDWORD ( pak, 0x00000000 );
               ADDDWORD ( pak, 0x00000000 );
            }
            else
            {
               ADDWORD ( pak, BuildItemHead( otherclient->items[invslot] ));
               ADDDWORD ( pak, BuildItemData( otherclient->items[invslot] ));
            }
            SendToVisible( &pak, otherclient );
        }
        break;
        default:
            Log( MSG_WARNING, "Buy unknow action: %i", action );
    }
    return true;
}

// Sell in Shop
bool CWorldServer::pakSellShop( CPlayer* thisclient, CPacket* P )
{
     //Log( MSG_INFO, "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x ", GETBYTE((*P),0), GETBYTE((*P),1), GETBYTE((*P),2), GETBYTE((*P),3), GETBYTE((*P),4), GETBYTE((*P),5), GETBYTE((*P),6), GETBYTE((*P),7), GETBYTE((*P),8), GETBYTE((*P),9), GETBYTE((*P),10), GETBYTE((*P),11), GETBYTE((*P),12), GETBYTE((*P),13), GETBYTE((*P),14), GETBYTE((*P),15), GETBYTE((*P),16), GETBYTE((*P),17), GETBYTE((*P),18), GETBYTE((*P),19), GETBYTE((*P),20), GETBYTE((*P),21), GETBYTE((*P),22), GETBYTE((*P),23), GETBYTE((*P),24) );

    WORD otherclientid = GETWORD((*P),0);
    BYTE action = GETBYTE((*P),2);
    switch(action)
    {
        case 0x01:
        {
            CPlayer* otherclient = GetClientByID( otherclientid, thisclient->Position->Map );
            if( otherclient == NULL )
                return true;
            unsigned int count = 0;
            BYTE invslot = GETBYTE((*P),3);
            BYTE slot = GETBYTE((*P),4);
            if(!CheckInventorySlot( thisclient, slot))
                return false;
            CItem newitem =  thisclient->items[invslot];
            if(thisclient->items[invslot].itemtype>9 && thisclient->items[invslot].itemtype<14)
                count = GETWORD((*P),7);
            else
                count = 1;
            newitem.count = count;
            if( otherclient->CharInfo->Zulies<(otherclient->Shop->BuyingList[slot].price*count) )
                return true;
            unsigned int newslot = otherclient->GetNewItemSlot ( newitem );
            if( newslot==0xffff )
                return true;
            if( thisclient->items[invslot].count<count )
                return true;
            thisclient->CharInfo->Zulies += (otherclient->Shop->BuyingList[slot].price*count);
            otherclient->CharInfo->Zulies -= (otherclient->Shop->BuyingList[slot].price*count);
            if(thisclient->items[invslot].itemtype>9 &&
                    thisclient->items[invslot].itemtype<14)
            {
                if(thisclient->items[invslot].count<=count)
                {
                    ClearItem( thisclient->items[invslot] );
                    if(count>=otherclient->Shop->BuyingList[slot].count)
                    {
                         ClearItem( otherclient->Shop->BuyingList[slot].item );
                         otherclient->Shop->BuyingList[slot].slot = 0;
                         otherclient->Shop->BuyingList[slot].count = 0;
                         otherclient->Shop->BuyingList[slot].price = 0;
                    }
                    else
                    {
                         otherclient->Shop->BuyingList[slot].count -= count;
                    }
                }
                else
                {
                    if(otherclient->Shop->BuyingList[slot].count<=count)
                    {
                         ClearItem( otherclient->Shop->BuyingList[slot].item );
                         otherclient->Shop->BuyingList[slot].slot = 0;
                         otherclient->Shop->BuyingList[slot].count = 0;
                         otherclient->Shop->BuyingList[slot].price = 0;
                    }
                    else
                    {
                        otherclient->Shop->BuyingList[slot].count -= count;
                    }
                    thisclient->items[invslot].count-=count;
                }
            }
            else
            {
                ClearItem( thisclient->items[invslot] )
                ClearItem( otherclient->Shop->BuyingList[slot].item );
                otherclient->Shop->BuyingList[slot].slot = 0;
                otherclient->Shop->BuyingList[slot].count = 0;
                otherclient->Shop->BuyingList[slot].price = 0;
            }
            if(otherclient->items[newslot].count!=0)
                otherclient->items[newslot].count += newitem.count;
            else
                otherclient->items[newslot] = newitem;

            //update inventory (seller)
            BEGINPACKET( pak, 0x7c7 );
            ADDQWORD   ( pak, thisclient->CharInfo->Zulies );
            ADDBYTE    ( pak, 0x01 );
            ADDBYTE    ( pak, invslot );
            ADDWORD   ( pak, BuildItemHead( thisclient->items[invslot] ) );
            ADDDWORD   ( pak, BuildItemData( thisclient->items[invslot] ) );
            thisclient->client->SendPacket( &pak );

            //update inventory (buyer)
            RESETPACKET( pak, 0x7c7 );
            ADDQWORD   ( pak, otherclient->CharInfo->Zulies );
            ADDBYTE    ( pak, 0x01 );
            ADDBYTE    ( pak, newslot );
            ADDWORD   ( pak, BuildItemHead( otherclient->items[newslot] ) );
            ADDDWORD   ( pak, BuildItemData( otherclient->items[newslot] ) );
            otherclient->client->SendPacket( &pak );

            //update shop
            CItem thisitem = otherclient->Shop->BuyingList[slot].item;
            RESETPACKET( pak, 0x7c6 );
            ADDWORD    ( pak, otherclient->clientid );
            ADDBYTE    ( pak, 0x07 );
            ADDBYTE    ( pak, 0x01 );
            ADDBYTE    ( pak, slot );
            ADDWORD   ( pak, BuildItemHead( thisitem ) );
            ADDDWORD   ( pak, BuildItemData( thisitem ) );
            SendToVisible( &pak, otherclient );
        }
        break;
        default:
            Log( MSG_WARNING, "Sell unknow action: %i", action );
    }
    return true;
}

// Close Shop
bool CWorldServer::pakCloseShop( CPlayer* thisclient, CPacket* P )
{
    BEGINPACKET( pak, 0x7c3 );
    ADDWORD    ( pak, thisclient->clientid );
    ADDBYTE    ( pak, 0x00 );
    SendToVisible( &pak, thisclient );
    thisclient->Shop->open = false;
    for(unsigned int j=0;j<30;j++)
    {
        thisclient->Shop->SellingList[j].slot = 0;
        thisclient->Shop->SellingList[j].count = 0;
        thisclient->Shop->SellingList[j].price = 0;
        thisclient->Shop->BuyingList[j].slot = 0;
        thisclient->Shop->BuyingList[j].count = 0;
        thisclient->Shop->BuyingList[j].price = 0;
        ClearItem( thisclient->Shop->BuyingList[j].item );

    }
    return true;
}

// Modified item (put gem, refine, Drill )
bool CWorldServer::pakModifiedItem( CPlayer* thisclient, CPacket* P )
{
     printf("[DEBUG]: ");
     for (int i = 0;i<(P->Size-6);i++)
     {
         printf("%i ",GETBYTE((*P),i));
     }
     printf("\n");
    if(thisclient->Shop->open==true)
        return true;
    BYTE action = GETBYTE((*P),0);
    switch(action)
    {
        case 0x01://Gemming
        {
            BYTE destslot = GETBYTE((*P),1);
            BYTE srcslot = GETBYTE((*P),2);
            if(!CheckInventorySlot( thisclient, destslot))
                return false;
            if(!CheckInventorySlot( thisclient, srcslot))
                return false;
            if( thisclient->items[srcslot].count<=0 )
            {
                BEGINPACKET( pak, 0x7bc );
                ADDBYTE    ( pak, 0x12 ); // dont have requerid material
                ADDBYTE    ( pak, 0x00 );
                thisclient->client->SendPacket( &pak );
                return true;
            }
            if( thisclient->items[destslot].gem!=0 )
            {
                BEGINPACKET( pak, 0x7bc );
                ADDBYTE    ( pak, 0x02 ); //no socket available
                ADDBYTE    ( pak, 0x00 );
                thisclient->client->SendPacket( &pak );
                return true;
            }
            thisclient->items[destslot].gem = thisclient->items[srcslot].itemnum;
            thisclient->items[destslot].stats = thisclient->items[srcslot].itemnum;
            thisclient->items[srcslot].count--;
            if(thisclient->items[srcslot].count<1)
                ClearItem( thisclient->items[srcslot] );
            BEGINPACKET( pak, 0x7bc );
            ADDBYTE    ( pak, 0x01 );//gemming success
            ADDBYTE    ( pak, 0x02 );
            ADDBYTE    ( pak, destslot );
            ADDWORD   ( pak, BuildItemHead( thisclient->items[destslot] ) );
            ADDDWORD   ( pak, BuildItemData( thisclient->items[destslot] ) );
            ADDBYTE    ( pak, srcslot );
            ADDWORD   ( pak, BuildItemHead( thisclient->items[srcslot] ) );
            ADDDWORD   ( pak, BuildItemData( thisclient->items[srcslot] ) );
            thisclient->client->SendPacket( &pak );
            thisclient->SetStats( );
            thisclient->saveinventory();
        }
        break; //case 0x02 ( Surprise gift box )
        case 0x02: //itemdivide by user
        case 0x03: //itemdivide by npc
        {
            BYTE slot = GETBYTE((*P),3);
            if(!CheckInventorySlot( thisclient, slot))
            {
                SendPM(thisclient, "Sorry! Checkinventory returned false for slot %i", slot);
                return true;
            }
            BEGINPACKET( pak, 0x7bc )
            ADDBYTE    ( pak, 0x07 );//successful
            ADDBYTE    ( pak, 0x01 );
            CItem splititem;
            char updateteller = 0;
            UINT material_lookup_number = STB_ITEM[(thisclient->items[slot].itemtype)-1].rows[thisclient->items[slot].itemnum][14];
            UINT CraftLevel = STB_ITEM[(thisclient->items[slot].itemtype)-1].rows[thisclient->items[slot].itemnum][13];
            SendPM(thisclient, "Material lookup number = %i Craft Level = %i", material_lookup_number,CraftLevel);

            //first item
            int matType = ProductList.Index[material_lookup_number]->matType;
            int item1 = ProductList.Index[material_lookup_number]->itemid[0];
            int itemtype1 = ProductList.Index[material_lookup_number]->itemtype[0];
            int itemcount1 = ProductList.Index[material_lookup_number]->amount[0];
            int itemcount2 = ProductList.Index[material_lookup_number]->amount[1];
            int itemcount3 = ProductList.Index[material_lookup_number]->amount[2];
            int itemcount4 = ProductList.Index[material_lookup_number]->amount[3];
            unsigned slot1 = 0;
            unsigned slot2 = 0;
            unsigned slot3 = 0;
            unsigned slot4 = 0;
            if(matType != 0)
            {
                // we have to find one of the correct item types rather than just a specific item. Seems to be related to craft skill level
                SendPM(thisclient, "item matType = %i", matType);
                splititem.itemtype = 12; // always seems to be a natural item here
                // Search the natural list and return the nth item in the list where n is the craft level of the item
                splititem.itemnum = GetMatIDfromRecipe (CraftLevel, matType);
                if(splititem.itemnum == 0)
                {
                  SendPM(thisclient, "Item number returned as zero");
                  return true;
                }
                SendPM(thisclient, "Item number = %i type = %i", splititem.itemnum, splititem.itemtype);
            }
            else
            {
                splititem.itemtype = itemtype1;
                splititem.itemnum = item1;
                //need to adjust the count according to some rules
            }
            splititem.count = itemcount1;
            SendPM(thisclient, "Item count = %i", splititem.count);
            splititem.appraised = false;
            splititem.durability = 0;
            splititem.gem = 0;
            splititem.lifespan = 0;
            splititem.refine = 0;
            splititem.socketed = 0;
            splititem.stats = 0;
            slot1 = thisclient->GetNewItemSlot( splititem );
            if (slot1 != 0xffff)
            {
                splititem.count += (thisclient->items[slot1].count);
                thisclient->items[slot1] = splititem;
                ADDBYTE    ( pak, slot1);
                ADDWORD    ( pak, BuildItemHead( thisclient->items[slot1] ) );
                ADDDWORD   ( pak, BuildItemData( thisclient->items[slot1] ) );
                updateteller += 1;
            }
            else
            {
                thisclient->items[slot1].count -= itemcount1;
                if(thisclient->items[slot1].count < 1)
                    ClearItem( thisclient->items[slot1] );
                SendPM(thisclient, "Not enough free slots");
                return true;
            }

            //second item
            SendPM(thisclient, "Second item now");
            splititem.itemnum = ProductList.Index[material_lookup_number]->itemid[1];
            splititem.itemtype = ProductList.Index[material_lookup_number]->itemtype[1];
            splititem.count = ProductList.Index[material_lookup_number]->amount[1];
            splititem.appraised = false;
            splititem.durability = 0;
            splititem.gem = 0;
            splititem.lifespan = 0;
            splititem.refine = 0;
            splititem.socketed = 0;
            splititem.stats = 0;
            SendPM(thisclient, "Item number = %i type = %i", splititem.itemnum, splititem.itemtype);
            slot2 = thisclient->GetNewItemSlot( splititem );
            if (slot2 != 0xffff)
            {
                splititem.count +=(thisclient->items[slot2].count);
                thisclient->items[slot2] = splititem;
                ADDBYTE    ( pak, slot2);
                ADDWORD    ( pak, BuildItemHead( thisclient->items[slot2] ) );
                ADDDWORD   ( pak, BuildItemData( thisclient->items[slot2] ) );
                updateteller += 1;
            }
            else
            {
                thisclient->items[slot1].count -= itemcount1;
                if(thisclient->items[slot1].count < 1)
                    ClearItem( thisclient->items[slot1] );
                thisclient->items[slot2].count -= itemcount2;
                if(thisclient->items[slot2].count < 1)
                    ClearItem( thisclient->items[slot2] );
                SendPM(thisclient, "Not enough free slots");
                return true;
            }

            //third item (if it exists)
            if(ProductList.Index[material_lookup_number]->amount[2] !=0 )
            {
                SendPM(thisclient, "Third item now");
                splititem.itemnum = ProductList.Index[material_lookup_number]->itemid[2];
                splititem.itemtype = ProductList.Index[material_lookup_number]->itemtype[2];
                splititem.count = ProductList.Index[material_lookup_number]->amount[2];
                splititem.appraised = false;
                splititem.durability = 0;
                splititem.gem = 0;
                splititem.lifespan = 0;
                splititem.refine = 0;
                splititem.socketed = 0;
                splititem.stats = 0;
                SendPM(thisclient, "Item number = %i type = %i", splititem.itemnum, splititem.itemtype);
                slot3 = thisclient->GetNewItemSlot( splititem );
                if (slot3 != 0xffff)
                {
                    splititem.count +=(thisclient->items[slot3].count);
                    thisclient->items[slot3] = splititem;
                    ADDBYTE    ( pak, slot3);
                    ADDWORD    ( pak, BuildItemHead( thisclient->items[slot3] ) );
                    ADDDWORD   ( pak, BuildItemData( thisclient->items[slot3] ) );
                    updateteller += 1;
                }
                else
                {
                    thisclient->items[slot1].count -= itemcount1;
                    if(thisclient->items[slot1].count < 1)
                        ClearItem( thisclient->items[slot1] );
                    thisclient->items[slot2].count -= itemcount2;
                    if(thisclient->items[slot2].count < 1)
                        ClearItem( thisclient->items[slot2] );
                    thisclient->items[slot3].count -= itemcount3;
                    if(thisclient->items[slot3].count < 1)
                        ClearItem( thisclient->items[slot3] );
                    SendPM(thisclient, "Not enough free slots");
                    return true;
                }
            }

            //fourth item
            if(ProductList.Index[material_lookup_number]->amount[3] !=0 )
            {
                splititem.itemnum = ProductList.Index[material_lookup_number]->itemid[3];
                splititem.itemtype = ProductList.Index[material_lookup_number]->itemtype[3];
                splititem.count = ProductList.Index[material_lookup_number]->amount[3];
                splititem.appraised = false;
                splititem.durability = 0;
                splititem.gem = 0;
                splititem.lifespan = 0;
                splititem.refine = 0;
                splititem.socketed = 0;
                splititem.stats = 0;
                slot4 = thisclient->GetNewItemSlot( splititem );
                if (slot4 !=0xffff)
                {
                    splititem.count +=(thisclient->items[slot4].count);
                    thisclient->items[slot4] = splititem;
                    ADDBYTE    ( pak, slot4);
                    ADDWORD    ( pak, BuildItemHead( thisclient->items[slot4] ) );
                    ADDDWORD   ( pak, BuildItemData( thisclient->items[slot4] ) );
                    updateteller += 1;
                }
                else
                {
                    thisclient->items[slot1].count -= itemcount1;
                    if(thisclient->items[slot1].count < 1)
                        ClearItem( thisclient->items[slot1] );
                    thisclient->items[slot2].count -= itemcount2;
                    if(thisclient->items[slot2].count < 1)
                        ClearItem( thisclient->items[slot2] );
                    thisclient->items[slot3].count -= itemcount3;
                    if(thisclient->items[slot3].count < 1)
                        ClearItem( thisclient->items[slot3] );
                    thisclient->items[slot4].count -= itemcount4;
                    if(thisclient->items[slot4].count < 1)
                        ClearItem( thisclient->items[slot4] );
                    SendPM(thisclient, "Not enough free slots");
                    return true;
                }
            }

            /*
            for(unsigned int i=0;i<STB_ITEM[11].rowcount;i++)
            {
                if (STB_ITEM[11].rows[i][4] == ProductList.Index[material_lookup_number]->item[0])
                {
                    splititem.itemtype = 12;
                    splititem.itemnum = i;
                    splititem.count = ProductList.Index[material_lookup_number]->amount[0];
                    if(splititem.count > 1)
                    {
                        splititem.count/=2;
                    }
                    splititem.appraised = false;
                    splititem.durability = 0;
                    splititem.gem = 0;
                    splititem.lifespan = 0;
                    splititem.refine = 0;
                    splititem.socketed = 0;
                    splititem.stats = 0;
                    unsigned newslot = thisclient->GetNewItemSlot( splititem );
                    if (newslot !=0xffff)
                    {
                        splititem.count +=(thisclient->items[newslot].count);
                        thisclient->items[newslot] = splititem;
                        ADDBYTE    ( pak,newslot);
                        ADDWORD   ( pak, BuildItemHead( thisclient->items[newslot] ) );
                        ADDDWORD   ( pak, BuildItemData( thisclient->items[newslot] ) );
                        updateteller+=1;
                    }
                    break;
                }
            }
            for (char teller = 1; teller<4;teller++)
            {
                if (ProductList.Index[material_lookup_number]->amount[teller]>0)
                {
                    splititem.count = ProductList.Index[material_lookup_number]->amount[teller];
                    if(splititem.count > 1)
                    {
                        splititem.count /= 2;
                    }
                    splititem.itemtype = (ProductList.Index[material_lookup_number]->item[teller])/1000;
                    splititem.itemnum  = (ProductList.Index[material_lookup_number]->item[teller])-(1000*splititem.itemtype);
                    splititem.appraised = false;
                    splititem.durability = 0;
                    splititem.gem = 0;
                    splititem.lifespan = 0;
                    splititem.refine = 0;
                    splititem.socketed = 0;
                    splititem.stats = 0;
                    unsigned newslot = thisclient->GetNewItemSlot( splititem );
                    if (newslot !=0xffff)
                    {
                        splititem.count += (thisclient->items[newslot].count);
                        thisclient->items[newslot] = splititem;
                        ADDBYTE    ( pak,newslot);
                        ADDWORD   ( pak, BuildItemHead( thisclient->items[newslot] ) );
                        ADDDWORD   ( pak, BuildItemData( thisclient->items[newslot] ) );
                        updateteller += 1;
                    }
                }
            }
            */
            thisclient->items[slot].count -= 1;
            ADDBYTE    ( pak,slot);
            if (thisclient->items[slot].count <=0)
            {
                ClearItem(thisclient->items[slot]);
                ADDWORD   ( pak,0);
                ADDDWORD   ( pak,0);
            }
            else
            {
                ADDWORD   ( pak, BuildItemHead( thisclient->items[slot] ) );
                ADDDWORD   ( pak, BuildItemData( thisclient->items[slot] ) );
            }
            updateteller += 1;
            SETBYTE(pak,1,updateteller);
            thisclient->client->SendPacket( &pak );
            thisclient->saveinventory();
        }
        break;
        case 0x04://NPC Refine
        case 0x05://Player Refine
        {
            BYTE item = GETBYTE((*P),3); //slot number
            BYTE material1 = GETBYTE((*P),4); //slot number
            int itemtype = thisclient->items[item].itemtype;
            int itemnum = thisclient->items[item].itemnum;
            if( thisclient->Session->codedebug )
            {
               SendPM(thisclient, "Item: %i Material: %i",item, material1  );
            }
            if(!CheckInventorySlot( thisclient, item))
                return false;
            if(!CheckInventorySlot( thisclient, material1))
                return false;
            //compare material1 with refinetype from equiplist
            int refinetype = GServer->EquipList[itemtype].Index[itemnum]->refinetype;
            int refineitem = GServer->ProductList.Index[refinetype]->item[0];
            int refinecount = GServer->ProductList.Index[refinetype]->amount[0];
            if( thisclient->Session->codedebug )
            {
               SendPM(thisclient, "Refineitem needed for this item: %i",refineitem );
            }
            //if(refineitem != material1)
            //    return false;
            if(thisclient->items[item].count<1 || thisclient->items[material1].count < refinecount)
            {
                BEGINPACKET( pak, 0x7bc );
                ADDBYTE    ( pak, 0x12 );
                ADDBYTE    ( pak, 0x00 );
                thisclient->client->SendPacket( &pak );
                return true;
            }
            unsigned int nextlevel = ( thisclient->items[item].refine / 16 ) + 1;
            if( nextlevel > 9 )
                return true;//if a client were able to try and upgrade an lvl 9 grade item this would probebly lockup this client

            thisclient->items[material1].count -= refinecount;
            if ((thisclient->items[material1].count) < 1)
            ClearItem( thisclient->items[material1] );


            bool success = true;
            srand( time(NULL));
            unsigned int prefine = rand()%100;
            int refinechance = upgrade[nextlevel];

            if( GServer->EquipList[itemtype].Index[itemnum]->raretype != 0 )
                refinechance += GServer->Config.Rare_Refine;
            if( prefine > refinechance)
                success = false;

            BEGINPACKET( pak, 0x7bc )
            if( success )
            {
                thisclient->items[item].refine = nextlevel*16;
                thisclient->items[item].durability += nextlevel;
                ADDBYTE    ( pak, 0x10 );//successful
            }
            else
            {
                if(GServer->Config.KillOnFail || nextlevel > 5)
                {
                    ClearItem( thisclient->items[item] );
                }
                else
                {
                    thisclient->items[item].refine = (nextlevel-2)*16;
                    thisclient->items[item].durability -= 2;
                }
                ADDBYTE    ( pak, 0x11 );//Fail
            }
            {ADDBYTE    ( pak, 0x04 );}
            ADDBYTE    ( pak, material1 );
            ADDWORD   ( pak, BuildItemHead( thisclient->items[material1] ) );
            ADDDWORD   ( pak, BuildItemData( thisclient->items[material1] ) );
            ADDBYTE    ( pak, item );
            ADDWORD   ( pak, BuildItemHead( thisclient->items[item] ) );
            ADDDWORD   ( pak, BuildItemData( thisclient->items[item] ) );
            ADDBYTE    ( pak, 0x00 );
            ADDDWORD   ( pak, 0x002f0000 );
            ADDDWORD   ( pak, 0x00000017 );
            thisclient->client->SendPacket( &pak );
            thisclient->saveinventory();
        }
        break;
        case 0x06: // Drill
        {
            BYTE material = GETBYTE((*P), 1);
            BYTE item = GETBYTE((*P), 3);
            int itemnum = 0;
            if(!CheckInventorySlot( thisclient, item))
                return false;
            if(!CheckInventorySlot( thisclient, material))
                return false;
            //Log(MSG_INFO,"client has %i drills in slot %i",thisclient->items[material].count,material);
            if( thisclient->items[material].count <= 0 )
            {
                BEGINPACKET( pak, 0x7bc );
                ADDBYTE    ( pak, 0x12 );
                ADDBYTE    ( pak, 0x00 );
                thisclient->client->SendPacket( &pak );
                return true;
            }
            else
            {
                //find the item number
                itemnum = thisclient->items[material].itemnum;
                //Log(MSG_INFO,"Item number = %i",itemnum);
            }
            //already drilled
            if(thisclient->items[item].socketed)
            {
                BEGINPACKET( pak, 0x7bc );
                ADDBYTE    ( pak, 0x23 );
                ADDBYTE    ( pak, 0x00 );
                thisclient->client->SendPacket( &pak );
               return true;
            }
            //if( thisclient->items[item].socketed ) return true;//Show message
            thisclient->items[material].count -= 1;
            //thisclient->items[item].socketed = true;
            if( thisclient->items[material].count <= 0 )
                ClearItem(thisclient->items[material]);

            //LMA: Adding some probability there :)
            int success = RandNumber(0,100);
            //Log(MSG_INFO,"Drill succes? %i / %i",success,UseList.Index[itemnum]->useeffect[1]);
            if(success > UseList.Index[itemnum]->useeffect[1])
            {
                //fail
                thisclient->items[item].socketed = false;
                BEGINPACKET( pak, 0x7bc );
                ADDBYTE    ( pak, 0x21 );
                ADDBYTE    ( pak, 0x01 );
                ADDBYTE    ( pak, material);
                ADDDWORD   ( pak, BuildItemHead( thisclient->items[material] ) );
                ADDDWORD   ( pak, BuildItemData( thisclient->items[material] ) );
                thisclient->client->SendPacket(&pak);
            }
            else
            {
                // success
                thisclient->items[item].socketed = true;
                BEGINPACKET( pak, 0x7bc );
                ADDBYTE    ( pak, 0x20 );
                ADDBYTE    ( pak, 0x02 );
                ADDBYTE    ( pak, material);
                ADDWORD    ( pak, BuildItemHead( thisclient->items[material] ) );
                ADDDWORD   ( pak, BuildItemData( thisclient->items[material] ) );
                ADDBYTE    ( pak, item );
                ADDWORD    ( pak, BuildItemHead( thisclient->items[item] ) );
                ADDDWORD   ( pak, BuildItemData( thisclient->items[item] ) );
                thisclient->client->SendPacket(&pak);
            }
            //Log(MSG_INFO,"client now has %i drills in slot %i",thisclient->items[material].count,material);
        }
        thisclient->saveinventory();
        break;
        default:
            Log( MSG_WARNING,"Modified Item unknown action: %i", action);
    }
    return true;
}

// Repair hammer
bool CWorldServer::pakRepairHammer( CPlayer* thisclient, CPacket* P )
{
     Log( MSG_INFO, "Repairhammer. %02x %02x %02x %02x", GETBYTE((*P),0), GETBYTE((*P),1), GETBYTE((*P),2),GETBYTE((*P),3) );
     UINT repairhammer = GETBYTE((*P),0);
     UINT repairitem = GETBYTE((*P),2);
     if (thisclient->items[repairhammer].count < 1)
        return true;
     thisclient->items[repairhammer].count -= 1;
     if (thisclient->items[repairhammer].count < 1)
        ClearItem( thisclient->items[repairhammer] );
     thisclient->items[repairitem].durability -= 2;
     thisclient->items[repairitem].lifespan=100;
     BEGINPACKET  ( pak, 0x7cb );
     ADDBYTE      ( pak, 0x02 );
     ADDBYTE      ( pak, repairhammer);
     ADDWORD   ( pak, BuildItemHead( thisclient->items[repairhammer] ));
     ADDDWORD   ( pak, BuildItemData( thisclient->items[repairhammer] ));
     ADDBYTE      ( pak, repairitem);
     ADDWORD   ( pak, BuildItemHead( thisclient->items[repairitem] ));
     ADDDWORD   ( pak, BuildItemData( thisclient->items[repairitem] ));
     thisclient->client->SendPacket( &pak );
     thisclient->saveinventory();
     return true;
}
// Repair npc
bool CWorldServer::pakRepairItem( CPlayer* thisclient, CPacket* P )
{
    BYTE action = GETBYTE((*P),0);
    switch(action)
    {
        case 0x61: //Ronk
        case 0x3d:
        case 0x39:
        case 0x1c:
        case 0x08:
        case 0x74:
        case 0x89:
        case 0x12: // Raffle
        case 0x43: //NPC Repair Item / Town
        {
            BYTE slot = GETBYTE((*P),2);
            if(!CheckInventorySlot( thisclient, slot)) return false;
            if(thisclient->items[slot].count<1) return true;
            //Log( MSG_INFO,"Item socketed?: %i", thisclient->items[slot].socketed);
            thisclient->items[slot].lifespan = 100;
            //Log( MSG_INFO,"Item socketed?: %i", thisclient->items[slot].socketed);
            //Still TODO: find where prices of storage and repair are and add it to the code.
            BEGINPACKET( pak, 0x7cd );
            ADDQWORD   ( pak, thisclient->CharInfo->Zulies );
            ADDBYTE    ( pak, 0x01 );
            ADDBYTE    ( pak, slot );
            ADDWORD   ( pak, BuildItemHead( thisclient->items[slot] ));
            ADDDWORD   ( pak, BuildItemData( thisclient->items[slot] ));
            ADDBYTE    ( pak, 0x00 );
            thisclient->client->SendPacket( &pak );
            thisclient->SetStats( );
            thisclient->saveinventory();
        }
        break;
        default:
            Log( MSG_WARNING,"Repair Item unknown action: %i", action);
            break;
    }
    return true;
}

// Ride request
bool CWorldServer::pakRideRequest( CPlayer* thisclient, CPacket* P )
{
    if(thisclient->Shop->open)
        return true;
    BYTE action = GETBYTE((*P),0);
    switch(action)
    {
        case 0x01://Ride Request
        {
            WORD tclientid = GETWORD((*P),1);
            WORD oclientid = GETWORD((*P),3);
            if( tclientid != thisclient->clientid )
                return true;
            CPlayer* otherclient = GetClientByID( oclientid, thisclient->Position->Map );
            if(otherclient == NULL)
                return true;
            BEGINPACKET( pak, 0x7dd );
            ADDBYTE    ( pak, 0x01 );
            ADDWORD    ( pak, thisclient->clientid );
            ADDWORD    ( pak, oclientid );
            ADDFLOAT   ( pak, thisclient->Position->current.x*100 );
            ADDFLOAT   ( pak, thisclient->Position->current.y*100 );
            otherclient->client->SendPacket( &pak );
        }
        break;
        case 0x02://Accept
        {
            WORD oclientid = GETWORD((*P),1);
            WORD tclientid = GETWORD((*P),3);
            if( tclientid != thisclient->clientid )
                return true;
            CPlayer* otherclient = GetClientByID( oclientid, thisclient->Position->Map );
            if(otherclient == NULL)
                return true;
            BEGINPACKET( pak, 0x796 );
            ADDWORD    ( pak, tclientid );
            ADDFLOAT   ( pak, thisclient->Position->current.x*100 );
            ADDFLOAT   ( pak, thisclient->Position->current.y*100 );
            ADDWORD    ( pak, 0x0000 );
            SendToVisible( &pak, otherclient );

            RESETPACKET( pak, 0x7dd );
            ADDBYTE    ( pak, 0x02 );
            ADDWORD    ( pak, oclientid );
            ADDWORD    ( pak, tclientid );
            SendToVisible( &pak, otherclient );
            thisclient->Ride->Ride = true;
            thisclient->Ride->Drive = false;
            thisclient->Ride->charid = otherclient->CharInfo->charid;
            otherclient->Ride->Ride = true;
            otherclient->Ride->Drive = true;
            otherclient->Ride->charid = thisclient->CharInfo->charid;
        }
        break;
        case 0x03://Denied
        {
            WORD oclientid = GETWORD((*P),1);
            WORD tclientid = GETWORD((*P),3);
            if( tclientid != thisclient->clientid )
                return true;
            CPlayer* otherclient = GetClientByID( oclientid, thisclient->Position->Map );
            if(otherclient == NULL)
                return true;
            BEGINPACKET( pak, 0x7dd );
            ADDBYTE    ( pak, 0x03 );
            ADDWORD    ( pak, oclientid );
            ADDWORD    ( pak, tclientid );
            otherclient->client->SendPacket( &pak );
        }
        break;
    }
	return true;
}

bool CWorldServer::pakWeight( CPlayer* thisclient, CPacket* P )
{
    BYTE weight = GETBYTE((*P),0) & 0xff;
    if(weight>110)
        thisclient->Status->CanAttack = false;
    else
        thisclient->Status->CanAttack = true;
    if(weight>100)
        thisclient->Status->CanRun = false;
    else
        thisclient->Status->CanRun = true;
    thisclient->Stats->Move_Speed = thisclient->GetMoveSpeed( );
    BEGINPACKET( pak, 0x762 );
    ADDWORD    ( pak, thisclient->clientid );
    ADDBYTE    ( pak, weight );
    thisclient->client->SendPacket( &pak );
    return true;
}

// Show Monster HP or Player Regeneration
bool CWorldServer::pakShowHeal( CPlayer* thisclient, CPacket* P )
{
    WORD clientid = GETWORD((*P),0);
    CCharacter* character = MapList.Index[thisclient->Position->Map]->GetCharInMap( clientid );
    if(character == NULL) return true;
    if(character->IsMonster())
    {
    	// SET MONSTER HEALTH
    	BEGINPACKET( pak, 0x79f );
    	ADDWORD( pak, character->clientid );
    	ADDWORD( pak, character->Stats->HP );
    	ADDWORD( pak, 0 );
        thisclient->client->SendPacket( &pak );
        //thisclient->Battle->contatk = false;
    }
    //thisclient->Battle->target = clientid;
    return true;
}

// Disconnect char
bool CWorldServer::pakCharDSClient( CPlayer* thisclient, CPacket* P )
{
    if(!thisclient->Session->isLoggedIn) return true;
    BYTE action = GETBYTE((*P),0);
    switch(action)
    {
        case 1:
        {
            unsigned int userid = GETDWORD((*P), 1 );
            CPlayer* otherclient = GetClientByUserID( userid );
            if(otherclient==NULL)
            {
                Log(MSG_WARNING, "userid '%s' not found online", userid );
                return true;
            }
            otherclient->client->isActive = false;

        }
        break;
        default:
                break;
    }
    return true;
}

// Pack Printscreen
bool CWorldServer::pakPrintscreen( CPlayer* thisclient, CPacket* P )
{
    BEGINPACKET( pak, 0x7eb );
    ADDWORD    ( pak, thisclient->Session->userid );
    ADDWORD    ( pak, 0x0302 );
    ADDWORD    ( pak, 0x2d17 );
    thisclient->client->SendPacket( &pak );
    return true;
}

// CharServer Connected
bool CWorldServer::pakCSReady ( CPlayer* thisclient, CPacket* P )
{
	if(thisclient->Session->isLoggedIn) return false;
	if(GETDWORD((*P),0) != Config.WorldPass )
    {
        Log( MSG_HACK, "CharServer Tried to connect WorldServer with wrong password ");
        return true;
    }

	thisclient->Session->isLoggedIn=true;
	return true;
}

// CharServer - Disconnect User
bool CWorldServer::pakCSCharSelect ( CPlayer* thisclient, CPacket* P )
{
    if(!thisclient->Session->isLoggedIn) return false;
	Log( MSG_INFO, "Char server requested client kill" );
	DWORD userid = GETDWORD( (*P), 0 );
	CPlayer* otherclient = GetClientByUserID( userid );
	if(otherclient != NULL)
	{
        if(otherclient->client==NULL) return true;
        otherclient->client->isActive = false;
    }
	Log( MSG_INFO, "Client killed" );
	return true;
}

bool CWorldServer::pakItemMall( CPlayer* thisclient, CPacket* P )
{
    return true;
}
