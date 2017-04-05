/*-------------------------------------------------------------------------------

BARONY
File: stat.cpp
Desc: shared functions for the Stat struct within editor.exe and barony.exe

Copyright 2013-2016 (c) Turning Wheel LLC, all rights reserved.
See LICENSE for details.

-------------------------------------------------------------------------------*/

#pragma once

#include "main.hpp"
#include "game.hpp"
#include "stat.hpp"
#include "entity.hpp"
#include "items.hpp"
#include "magic/magic.hpp"

// Constructor
Stat::Stat(Sint32 sprite)
{
	this->type = NOTHING;
	strcpy(this->name, "");
	strcpy(this->obituary, language[1500]);
	this->defending = false;
	this->poisonKiller = 0;
	this->sex = static_cast<sex_t>(rand() % 2);
	this->appearance = 0;
	this->HP = 10;
	this->MAXHP = 10;
	this->OLDHP = this->HP;
	this->MP = 10;
	this->MAXMP = 10;
	this->STR = 0;
	this->DEX = 0;
	this->CON = 0;
	this->INT = 0;
	this->PER = 0;
	this->CHR = 0;
	this->EXP = 0;
	this->LVL = 1;
	this->GOLD = 0;
	this->HUNGER = 800;
	int c;
	for ( c = 0; c < std::max<real_t>(NUMPROFICIENCIES, NUMEFFECTS); c++ )
	{
		if ( c < NUMPROFICIENCIES )
		{
			this->PROFICIENCIES[c] = 0;
		}
		if ( c < NUMEFFECTS )
		{
			this->EFFECTS[c] = false;
		}
		if ( c < NUMEFFECTS )
		{
			this->EFFECTS_TIMERS[c] = 0;
		}
	}

	for ( c = 0; c < 96; c = c + 6 )
	{
		this->EDITOR_ITEMS[c] = 0;
		this->EDITOR_ITEMS[c + 1] = 0;
		this->EDITOR_ITEMS[c + 2] = 10;
		this->EDITOR_ITEMS[c + 3] = 1;
		this->EDITOR_ITEMS[c + 4] = 1;
		this->EDITOR_ITEMS[c + 5] = 100;
	}

	this->leader_uid = 0;
	this->FOLLOWERS.first = NULL;
	this->FOLLOWERS.last = NULL;
	this->stache_x1 = 0;
	this->stache_x2 = 0;
	this->stache_y1 = 0;
	this->stache_y2 = 0;
	this->inventory.first = NULL;
	this->inventory.last = NULL;
	this->helmet = NULL;
	this->breastplate = NULL;
	this->gloves = NULL;
	this->shoes = NULL;
	this->shield = NULL;
	this->weapon = NULL;
	this->cloak = NULL;
	this->amulet = NULL;
	this->ring = NULL;
	this->mask = NULL;
#if defined(HAVE_FMOD) || defined(HAVE_OPENAL)
	this->monster_sound = NULL;
#endif
	this->monster_idlevar = 1;
	this->magic_effects.first = NULL;
	this->magic_effects.last = NULL;

	if ( multiplayer != CLIENT )
	{
		setDefaultMonsterStats(this, (int)sprite);
	}
}

void setDefaultMonsterStats(Stat* stats, int sprite)
{
	switch ( sprite )
	{
		case 70:
		case (1000 + GNOME):
			stats->type = GNOME;
			stats->sex = static_cast<sex_t>(rand() % 2);
			stats->appearance = 0;
			stats->HP = 50;
			stats->MAXHP = 50;
			stats->MP = 50;
			stats->MAXMP = 50;
			stats->OLDHP = stats->HP;
			stats->STR = 2;
			stats->DEX = 0;
			stats->CON = 4;
			stats->INT = 0;
			stats->PER = 2;
			stats->CHR = -1;
			stats->EXP = 0;
			stats->LVL = 5;
			stats->RANDOMGOLD = 20;
			stats->GOLD = 40 + rand() % stats->RANDOMGOLD;
			stats->HUNGER = 900;

			stats->PROFICIENCIES[PRO_SWORD] = 35;
			stats->PROFICIENCIES[PRO_MACE] = 50;
			stats->PROFICIENCIES[PRO_AXE] = 45;
			stats->PROFICIENCIES[PRO_POLEARM] = 25;
			stats->PROFICIENCIES[PRO_RANGED] = 35;
			stats->PROFICIENCIES[PRO_SHIELD] = 35;


			stats->EDITOR_ITEMS[ITEM_SLOT_WEAPON] = 1; //Pick/Lightningstaff
			stats->EDITOR_ITEMS[ITEM_SLOT_SHIELD] = 1; //Lantern/Wooden Shield
			stats->EDITOR_ITEMS[ITEM_SLOT_CLOAK] = 1; //Cloak

			stats->EDITOR_ITEMS[ITEM_SLOT_INV_1] = 1;
			stats->EDITOR_ITEMS[ITEM_SLOT_INV_1 + ITEM_CHANCE] = 33; //Fish
			stats->EDITOR_ITEMS[ITEM_SLOT_INV_2] = 1;
			stats->EDITOR_ITEMS[ITEM_SLOT_INV_2 + ITEM_CHANCE] = 10; //Random Gems
			stats->EDITOR_ITEMS[ITEM_SLOT_INV_3] = 1;
			stats->EDITOR_ITEMS[ITEM_SLOT_INV_3 + ITEM_CHANCE] = 2; //Winny's report

			break;
		case 71:
		case (1000 + DEVIL):
			stats->type = DEVIL;
			stats->sex = static_cast<sex_t>(rand() % 2);
			stats->appearance = rand();
			strcpy(stats->name, "Baphomet");
			stats->inventory.first = NULL;
			stats->inventory.last = NULL;
			stats->HP = 1250 + 250 * numplayers;
			stats->MAXHP = stats->HP;
			stats->MP = 2000;
			stats->MAXMP = 2000;
			stats->OLDHP = stats->HP;
			stats->STR = -50;
			stats->DEX = -20;
			stats->CON = 10;
			stats->INT = 50;
			stats->PER = 500;
			stats->CHR = 50;
			stats->EXP = 0;
			stats->LVL = 30;
			stats->HUNGER = 900;

			stats->EFFECTS[EFF_LEVITATING] = true;
			stats->EFFECTS_TIMERS[EFF_LEVITATING] = 0;

			stats->PROFICIENCIES[PRO_MAGIC] = 100;
			stats->PROFICIENCIES[PRO_SPELLCASTING] = 100;

			break;
		case 62:
		case (1000 + LICH):
			stats->type = LICH;
			stats->sex = MALE;
			stats->appearance = rand();
			strcpy(stats->name, "Baron Herx");
			stats->inventory.first = NULL;
			stats->inventory.last = NULL;
			stats->HP = 1000 + 250 * numplayers;
			stats->MAXHP = stats->HP;
			stats->MP = 1000;
			stats->MAXMP = 1000;
			stats->OLDHP = stats->HP;
			stats->STR = 20;
			stats->DEX = 8;
			stats->CON = 8;
			stats->INT = 20;
			stats->PER = 80;
			stats->CHR = 50;
			stats->EXP = 0;
			stats->LVL = 25;
			stats->GOLD = 100;
			stats->HUNGER = 900;

			stats->EFFECTS[EFF_LEVITATING] = true;
			stats->EFFECTS_TIMERS[EFF_LEVITATING] = 0;

			break;
		case 48:
		case (1000 + SPIDER):
			stats->type = SPIDER;
			stats->sex = static_cast<sex_t>(rand() % 2);
			stats->appearance = rand();
			strcpy(stats->name, "");
			stats->inventory.first = NULL;
			stats->inventory.last = NULL;
			stats->HP = 50;
			stats->MAXHP = 50;
			stats->MP = 10;
			stats->MAXMP = 10;
			stats->OLDHP = stats->HP;
			stats->STR = 3;
			stats->DEX = 8;
			stats->CON = 4;
			stats->INT = -3;
			stats->PER = -3;
			stats->CHR = -1;
			stats->EXP = 0;
			stats->LVL = 5;
			stats->GOLD = 0;
			stats->HUNGER = 900;

			break;
		case 36:
		case (1000 + GOBLIN):
			stats->type = GOBLIN;
			stats->sex = static_cast<sex_t>(rand() % 2);
			stats->appearance = rand();
			strcpy(stats->name, "");
			stats->inventory.first = NULL;
			stats->inventory.last = NULL;
			stats->HP = 60;
			stats->MAXHP = 60;
			stats->MP = 20;
			stats->MAXMP = 20;
			stats->OLDHP = stats->HP;
			stats->STR = 6;
			stats->DEX = 0;
			stats->CON = 2;
			stats->INT = -1;
			stats->PER = 0;
			stats->CHR = -1;
			stats->EXP = 0;
			stats->LVL = 6;
			if ( rand() % 3 == 0 )
			{
				stats->GOLD = 10 + rand() % 20;
			}
			else
			{
				stats->GOLD = 0;
			}
			stats->HUNGER = 900;

			stats->PROFICIENCIES[PRO_SWORD] = 35;
			stats->PROFICIENCIES[PRO_MACE] = 50;
			stats->PROFICIENCIES[PRO_AXE] = 45;
			stats->PROFICIENCIES[PRO_POLEARM] = 25;
			stats->PROFICIENCIES[PRO_RANGED] = 35;
			stats->PROFICIENCIES[PRO_SHIELD] = 35;

			break;
		case 35:
		case (1000 + SHOPKEEPER):
			stats->type = SHOPKEEPER;
			stats->sex = MALE;
			stats->appearance = rand();
			strcpy(stats->name, language[158 + rand() % 26]);
			stats->inventory.first = NULL;
			stats->inventory.last = NULL;
			stats->HP = 300;
			stats->MAXHP = 300;
			stats->MP = 200;
			stats->MAXMP = 200;
			stats->OLDHP = stats->HP;
			stats->STR = 10;
			stats->DEX = 4;
			stats->CON = 10;
			stats->INT = 7;
			stats->PER = 7;
			stats->CHR = 3 + rand() % 4;
			stats->EXP = 0;
			stats->LVL = 10;
			stats->GOLD = 300 + rand() % 200;
			stats->HUNGER = 900;

			stats->FOLLOWERS.first = NULL;
			stats->FOLLOWERS.last = NULL;
			stats->PROFICIENCIES[PRO_MAGIC] = 50;
			stats->PROFICIENCIES[PRO_SPELLCASTING] = 50;
			stats->PROFICIENCIES[PRO_TRADING] = 75;
			stats->PROFICIENCIES[PRO_APPRAISAL] = 75;

			break;
		case 30:
		case (1000 + TROLL):
			stats->type = TROLL;
			stats->sex = static_cast<sex_t>(rand() % 2);
			stats->appearance = rand();
			stats->inventory.first = NULL;
			stats->inventory.last = NULL;
			stats->HP = 100 + rand() % 20;
			stats->MAXHP = stats->HP;
			stats->MP = 30;
			stats->MAXMP = 30;
			stats->OLDHP = stats->HP;
			stats->STR = 15;
			stats->DEX = -2;
			stats->CON = 5;
			stats->INT = -4;
			stats->PER = -2;
			stats->CHR = -1;
			stats->EXP = 0;
			stats->LVL = 12;
			stats->GOLD = 0;
			stats->HUNGER = 900;

			stats->EDITOR_ITEMS[ITEM_SLOT_INV_1] = 1;
			stats->EDITOR_ITEMS[ITEM_SLOT_INV_1 + ITEM_CHANCE] = 33; //Random Items

			break;
		case 27:
		case (1000 + HUMAN):
			stats->type = HUMAN;
			stats->sex = static_cast<sex_t>(rand() % 2);
			stats->appearance = rand() % 18; //NUMAPPEARANCES = 18
			strcpy(stats->name, "");
			stats->inventory.first = NULL;
			stats->inventory.last = NULL;
			stats->HP = 30 + rand() % 20;
			stats->MAXHP = stats->HP;
			stats->MP = 20 + rand() % 20;
			stats->MAXMP = stats->MP;
			stats->OLDHP = stats->HP;
			stats->STR = -1 + rand() % 4;
			stats->DEX = 4 + rand() % 4;
			stats->CON = -2 + rand() % 4;
			stats->INT = -1 + rand() % 4;
			stats->PER = -2 + rand() % 4;
			stats->CHR = -3 + rand() % 4;
			stats->EXP = 0;
			stats->LVL = 3;
			if ( rand() % 2 == 0 )
			{
				stats->GOLD = 20 + rand() % 20;
			}
			else
			{
				stats->GOLD = 0;
			}
			stats->HUNGER = 900;

			stats->PROFICIENCIES[PRO_SWORD] = 45;
			stats->PROFICIENCIES[PRO_MACE] = 35;
			stats->PROFICIENCIES[PRO_AXE] = 35;
			stats->PROFICIENCIES[PRO_POLEARM] = 45;
			stats->PROFICIENCIES[PRO_RANGED] = 40;
			stats->PROFICIENCIES[PRO_SHIELD] = 35;

			break;
		case 83:
		case (1000 + KOBOLD):
			stats->type = KOBOLD;
		case 84:
		case (1000 + SCARAB):
			stats->type = SCARAB;
		case 85:
		case (1000 + CRYSTALGOLEM):
			stats->type = CRYSTALGOLEM;
		case 86:
		case (1000 + INCUBUS):
			stats->type = INCUBUS;
		case 87:
		case (1000 + VAMPIRE):
			stats->type = VAMPIRE;
		case 88:
		case (1000 + SHADOW):
			stats->type = SHADOW;
		case 89:
		case (1000 + COCKATRICE):
			stats->type = COCKATRICE;
		case 90:
		case (1000 + INSECTOID):
			stats->type = INSECTOID;
		case 91:
		case (1000 + GOATMAN):
			stats->type = GOATMAN;
		case 92:
		case (1000 + AUTOMATON):
			stats->type = AUTOMATON;
		case 93:
		case (1000 + LICH_ICE):
			stats->type = LICH_ICE;
		case 94:
		case (1000 + LICH_FIRE):
			stats->type = LICH_FIRE;
			break;
		case 95:
		case (1000 + SKELETON):
			stats->type = SKELETON;
			stats->sex = static_cast<sex_t>(rand() % 2);
			stats->appearance = rand();
			stats->HP = 40;
			stats->MAXHP = 40;
			stats->MP = 30;
			stats->MAXMP = 30;
			stats->OLDHP = stats->HP;
			stats->STR = 1;
			stats->DEX = -1;
			stats->CON = 0;
			stats->INT = -1;
			stats->PER = 1;
			stats->CHR = -3;
			stats->EXP = 0;
			stats->LVL = 2;
			stats->GOLD = 0;
			stats->HUNGER = 900;

			stats->PROFICIENCIES[PRO_SWORD] = 35;
			stats->PROFICIENCIES[PRO_MACE] = 50;
			stats->PROFICIENCIES[PRO_AXE] = 45;
			stats->PROFICIENCIES[PRO_POLEARM] = 25;
			stats->PROFICIENCIES[PRO_RANGED] = 35;
			stats->PROFICIENCIES[PRO_SHIELD] = 35;
			break;
		case 96:
		case (1000 + RAT):
			stats->type = RAT;
			stats->sex = static_cast<sex_t>(rand() % 2);
			stats->appearance = rand();
			strcpy(stats->name, "");
			stats->inventory.first = NULL;
			stats->inventory.last = NULL;
			stats->HP = 30;
			stats->MAXHP = 30;
			stats->MP = 10;
			stats->MAXMP = 10;
			stats->OLDHP = stats->HP;
			stats->STR = 0;
			stats->DEX = 2;
			stats->CON = 1;
			stats->INT = -2;
			stats->PER = 0;
			stats->CHR = -1;
			stats->EXP = 0;
			stats->LVL = 1;
			stats->GOLD = 0;
			stats->HUNGER = 900;
			break;
		case 10:
		default:
			break;
	}
}

//void setDefaultMonsterItemSlots ( Stat* stats )
//{
//	if ( multiplayer != CLIENT )
//	{
//		switch ( stats->type )
//		{
//			case HUMAN:
//				break;
//			case RAT:
//				break;
//			case GOBLIN:
//				break;
//			case SLIME:
//				break;
//			case SCORPION:
//				break;
//			case SUCCUBUS:
//				break;
//			case TROLL:
//				break;
//			case SHOPKEEPER:
//				break;
//			case SKELETON:
//				break;
//			case MINOTAUR:
//				break;
//			case GHOUL:
//				break;
//			case DEMON:
//				break;
//			case SPIDER:
//				break;
//			case LICH:
//				break;
//			case CREATURE_IMP:
//				break;
//			case GNOME:
//
//				break;
//			case DEVIL:
//				break;
//			case KOBOLD:
//				break;
//			case SCARAB:
//				break;
//			case CRYSTALGOLEM:
//				break;
//			case INCUBUS:
//				break;
//			case VAMPIRE:
//				break;
//			case SHADOW:
//				break;
//			case COCKATRICE:
//				break;
//			case INSECTOID:
//				break;
//			case GOATMAN:
//				break;
//			case AUTOMATON:
//				break;
//			case LICH_ICE:
//				break;
//			case LICH_FIRE:
//				break;
//			default:
//				break; //This should never be reached.
//		}
//	}
//}
