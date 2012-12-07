// Props to ExJam for this code :D Ported to OSpRose by Drakia
#define QUESTREWD(reward) int QUEST_REWD_ ## reward (class CWorldServer* server, class CPlayer* client, byte* raw)
typedef int (*fpQuestRewd)(class CWorldServer*, class CPlayer*, byte*);
#define GETREWDDATA(rewd) STR_REWD_ ## rewd * data = (STR_REWD_ ## rewd *)raw

QUESTREWD(000);QUESTREWD(001);QUESTREWD(002);
QUESTREWD(003);QUESTREWD(004);QUESTREWD(005);
QUESTREWD(006);QUESTREWD(007);QUESTREWD(008);
QUESTREWD(009);QUESTREWD(010);QUESTREWD(011);
QUESTREWD(012);QUESTREWD(013);QUESTREWD(014);
QUESTREWD(015);QUESTREWD(016);QUESTREWD(017);
QUESTREWD(018);QUESTREWD(019);QUESTREWD(020);
QUESTREWD(021);QUESTREWD(022);QUESTREWD(023);
QUESTREWD(024);QUESTREWD(025);QUESTREWD(026);
QUESTREWD(027);QUESTREWD(028);QUESTREWD(029);
QUESTREWD(030);

struct STR_REWD_000 {
	dword iQuestSN;
	byte btOp;
};

struct STR_REWD_001 {
	dword uiItemSN;
	union {
		byte btOp;
		word nOp;
	};
	word nDupCNT;
	byte btPartyOpt;
};

struct STR_REWD_002 
{
	dword iDataCnt;
	STR_QUEST_DATA* CheckData;
};

struct STR_REWD_003 
{
	dword iDataCnt;              //pos 0x00
	dword iType;                 //pos 0x04
	dword iValue;                //pos 0x08
	byte btOp;                   //pos 0x0c
    //this (below original code) is just plain wrong
    //dword iDataCnt;
	//STR_ABIL_DATA* CheckData;
	//byte btPartyOpt;
};

struct STR_REWD_004 {
	dword iDataCnt;
	STR_QUEST_DATA* CheckData;
};

struct STR_REWD_005 
{
	byte btTarget;            // pos 0x00
    //union 
    //{
	//	byte btEquation;      // pos 0x02 apparently should be 0x01
	//	word nEquation;
	//};
	byte btEquation;          // pos 0x01
	word nEquation;           // pos 0x02
	int iValue;               // pos 0x04
	dword iItemSN;            // pos 0x06
	union 
    {
		byte btPartyOpt;      // pos 0x0a
		word nPartyOpt;
	};
	word nItemOpt;            // pos 0x0c
};

struct STR_REWD_006 {
	dword iPercentOfHP;
	dword iPercentOfMP;
	byte btPartyOpt;
};

struct STR_REWD_007 {
	dword iZoneSN;
	dword iX;
	dword iY;
	byte btPartyOpt;
};

struct STR_REWD_008 {
	dword iMonsterSN;
	dword iHowMany;
	union {
		byte btWho;
		int iWho;
	};
	dword iZoneSN;
	dword iX;
	dword iY;
	dword iRange;
	dword iTeamNo;
};

struct STR_REWD_009 {
	word shNameLen;
	string szNextTriggerSN;
};

struct STR_REWD_010 {
};

struct STR_REWD_011 
{
	union	
    {
		byte btWho;
		word usWho;
	};
	word nVarNo;
	dword iValue;
	byte btOp;
};

struct STR_REWD_012 {
	union 
    {
		byte btMsgType;
		int iMsgType;
	};
	dword iStrID;
};

struct STR_REWD_013 {
	union {
		byte btWho;
		int iWho;
	};
	dword iSec;
	word nNameLength;
	string szTriggerName;
	dword m_HashNextTrigger;
};

struct STR_REWD_014 
{
	union 
    {
		byte btOp;
		int iOp;
	};
	dword iSkillNo;
};

struct STR_REWD_015 {
	word nSN;
	byte btOp;
};

struct STR_REWD_016 {
	word nGroupSN;
};

struct STR_REWD_017 {
};

struct STR_REWD_018 {
	dword iStrID;
	word nCnt;
	string Data;
};

struct STR_REWD_019 
{
	word nZoneNo;           //pos 0x00
	word nTeamNo;           //pos 0x02
	word nTriggerLength;    //pos 0x04 This is definitely NOT the length of the following name. PY
	string TriggerName;     //pos 0x06 + nTriggerlength more bytes. Name always appears to be 17 bytes long
	//dword m_HashTrigger;
    word m_HashTrigger;     //pos 0x17 only has 2 bytes not 4. PY
};

struct STR_REWD_020 
{
	byte btNoType;
};

struct STR_REWD_021 {
	dword iX;
	dword iY;
};

struct STR_REWD_022 {
	word nZonNo;
	byte btOp;
};

struct STR_REWD_023 
{
};

struct STR_REWD_024 {
	int iMONEY;
	byte btOP;
};

struct STR_REWD_025 {
	short nPOINT;
	byte btOP;
};

struct STR_REWD_026 {
	word nSkillNo;
	byte btOP;
};

struct STR_REWD_027 {
	short nCONT;
	byte btOP;
};

struct STR_REWD_028 {
	dword iRange;
	word nZoneNo;
	dword iX;
	dword iY;
};

struct STR_REWD_029 {
    word strLen;
    string LuaName;
};

struct STR_REWD_030 //reset skills
{
       
};
