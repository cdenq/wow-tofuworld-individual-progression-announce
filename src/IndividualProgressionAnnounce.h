/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INDIVIDUAL_PROGRESSION_ANNOUNCE_H
#define INDIVIDUAL_PROGRESSION_ANNOUNCE_H

#include "Define.h"

class Player;

enum IPAnnounceStyle
{
    IP_ANNOUNCE_PLAIN   = 0,  // "Individual Progression: level 3"
    IP_ANNOUNCE_NAMED   = 1,  // "Individual Progression: level 3 (Blackwing Lair cleared)"
    IP_ANNOUNCE_NEXT    = 2,  // NAMED + next gate hint
};

struct IPAnnounceStateName
{
    uint8 level;
    char const* name;
    char const* nextGate;
};

// Ordered by level; level 0 = fresh classic start.
constexpr IPAnnounceStateName IPAnnounceStates[] =
{
    {  0, "Classic start - nothing cleared yet",       "Molten Core" },
    {  1, "Molten Core cleared",                       "Onyxia" },
    {  2, "Onyxia cleared",                            "Blackwing Lair" },
    {  3, "Blackwing Lair cleared",                    "Ahn'Qiraj war effort" },
    {  4, "Pre-AQ content unlocked",                   "AQ war effort" },
    {  5, "AQ war effort done",                        "Ahn'Qiraj raids" },
    {  6, "AQ gates open",                             "Naxxramas" },
    {  7, "Naxxramas 40 cleared",                      "Outlands journey" },
    {  8, "Pre-TBC",                                   "Karazhan / Gruul / Magtheridon" },
    {  9, "TBC tier 1 cleared",                        "Serpentshrine / Tempest Keep" },
    { 10, "TBC tier 2 cleared",                        "Hyjal Summit / Black Temple" },
    { 12, "Sunwell Plateau cleared",                   "Naxxramas (WotLK)" },
    { 13, "WotLK Naxx / EoE / OS cleared",             "Ulduar" },
    { 14, "Ulduar cleared",                            "Trial of the Crusader" },
    { 15, "Trial of the Crusader cleared",             "Icecrown Citadel" },
    { 16, "Icecrown Citadel cleared",                  "Ruby Sanctum" },
    { 17, "Ruby Sanctum cleared",                      "..." },
};

#endif // INDIVIDUALPROGRESSION_ANNOUNCE_H