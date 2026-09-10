# mod-individual-progression-announce

Per-player **Individual Progression** announcement at login, companion to
[mod-individual-progression](https://github.com/Zerathane/mod-individual-progression)
(the AzerothCore playerbots-era fork by Zerathane et al.).

Instead of the static "Individual Progression: enabled" message every player
gets, each player sees **their own progression level** at login, optionally
with the state name and the next content gate:

```
Individual Progression: level 3 (Blackwing Lair cleared) - next: Ahn'Qiraj war effort
```

## Requirements

- [mod-individual-progression](https://github.com/Zerathane/mod-individual-progression) must be installed and enabled (uses its public API).

## Installation

1. Place the module under the `modules` directory of your AzerothCore source.
2. Copy `conf/individual_progression_announce.conf.dist` to the same name
   without `.dist` in your server config directory (or let the module system
   place it and edit the copy).
3. Re-run CMake and build (`make -j<N> && make install`). Bots and excluded
   accounts stay silent — only normal accounts get the message.

## Configuration

```
IndividualProgression.AnnounceStyle = 1
```
* 0 = plain level
* 1 = level + cleared-state name (default)
* 2 = level + state name + next content gate

## Notes

* Progression source: mod-individual-progression's own API
  (`GetPlayerProgressionFromQuests`), i.e. exactly what `.ip get` reports.
* Works for every progression state 0-18 with a graceful fallback if the
  level has no named entry.
* AGPL v3, same as AzerothCore.