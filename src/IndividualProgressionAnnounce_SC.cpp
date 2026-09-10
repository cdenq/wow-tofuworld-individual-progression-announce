/*
 * mod-individual-progression-announce — per-player progression line at login.
 *
 * Complements mod-individual-progression: instead of the static
 * "Individual Progression: enabled" message, each player gets their own
 * progression level (+ state name, + next gate, per config) on login.
 *
 * Requires mod-individual-progression to be present (uses its public API).
 */

#include "IndividualProgressionAnnounce.h"
#include "IndividualProgression.h"
#include "Chat.h"
#include "Player.h"
#include "ScriptMgr.h"

class IndividualProgressionAnnounce_Player : public PlayerScript
{
public:
    IndividualProgressionAnnounce_Player() : PlayerScript("IndividualProgressionAnnounce_Player") { }

    void OnPlayerLogin(Player* player) override
    {
        if (!sIndividualProgression->enabled)
            return;

        if (!player || !player->IsInWorld())
            return;

        if (!sIndividualProgression->isNormalAccount(player)) // bots / excluded accounts stay quiet
            return;

        uint8 prog = sIndividualProgression->GetPlayerProgressionFromQuests(player);

        uint8 style = IP_ANNOUNCE_NAMED;
        if (Optional<uint32> cfg = sConfigMgr->GetOption<uint32>("IndividualProgression.AnnounceStyle", 1, false))
            style = static_cast<uint8>(*cfg > IP_ANNOUNCE_NEXT ? IP_ANNOUNCE_NEXT : *cfg);

        std::string msg = "|cff00ff00Individual Progression:|r ";

        char const* stateName = nullptr;
        char const* nextGate = nullptr;
        for (IPAnnounceStateName const& entry : IPAnnounceStates)
        {
            if (entry.level == prog)
            {
                stateName = entry.name;
                nextGate = entry.nextGate;
                break;
            }
            if (entry.level > prog)
                break;
            stateName = entry.name;      // keep last entry below prog as fallback
            nextGate = entry.nextGate;
        }

        msg += Acore::StringFormat("level {}", prog);
        if (style >= IP_ANNOUNCE_NAMED && stateName)
            msg += Acore::StringFormat(" (|cffcccccc{}|r)", stateName);
        if (style >= IP_ANNOUNCE_NEXT && nextGate)
            msg += Acore::StringFormat(" - next: |cffcccccc{}|r", nextGate);

        ChatHandler(player->GetSession()).SendSysMessage(msg);
    }
};

// Group all custom scripts
void AddSC_IndividualProgressionAnnounce()
{
    new IndividualProgressionAnnounce_Player();
}