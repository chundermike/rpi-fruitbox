#pragma once

constexpr uint32_t StatusEvent_none                { 0x00000000 };
constexpr uint32_t StatusEvent_selCodeChange       { 0x00000001 };
constexpr uint32_t StatusEvent_playqueueChange     { 0x00000002 };
constexpr uint32_t StatusEvent_nowPlayingChange    { 0x00000004 };
constexpr uint32_t StatusEvent_timerChange         { 0x00000008 };
constexpr uint32_t StatusEvent_creditsChange       { 0x00000010 };
constexpr uint32_t StatusEvent_songStart           { 0x00000020 };
constexpr uint32_t StatusEvent_songStop            { 0x00000040 };
constexpr uint32_t StatusEvent_autoPlayModeChange  { 0x00000080 };
constexpr uint32_t StatusEvent_loopModeChange      { 0x00000100 };
constexpr uint32_t StatusEvent_freeplayModeChange  { 0x00000200 };
constexpr uint32_t StatusEvent_volumeChange        { 0x00000400 };
constexpr uint32_t StatusEvent_buttonChanged       { 0x00000800 };
constexpr uint32_t StatusEvent_pageMoveLeftInit    { 0x00001000 };
constexpr uint32_t StatusEvent_pageMoveRightInit   { 0x00002000 };
constexpr uint32_t StatusEvent_oneSecondChange     { 0x00004000 };
constexpr uint32_t StatusEvent_songLoad            { 0x00008000 };
constexpr uint32_t StatusEvent_songUnload          { 0x00010000 };
constexpr uint32_t StatusEvent_muteChange          { 0x00020000 };
constexpr uint32_t StatusEvent_newArtwork          { 0x00040000 };
constexpr uint32_t StatusEvent_songPauseChange     { 0x00080000 };
constexpr uint32_t StatusEvent_chooseSong          { 0x00100000 };
constexpr uint32_t StatusEvent_songVideoShow       { 0x00200000 };
constexpr uint32_t StatusEvent_songVideoStart      { 0x00400000 };
constexpr uint32_t StatusEvent_songVideoStop       { 0x00800000 };
constexpr uint32_t StatusEvent_flagChange          { 0x01000000 };
constexpr uint32_t StatusEvent_initEmpty           { 0x80000000 };

constexpr uint32_t StatusEvent_status {
  StatusEvent_initEmpty
};

constexpr uint32_t StatusEvent_joystick {
  StatusEvent_none
};

constexpr uint32_t StatusEvent_TouchSong {
  StatusEvent_none
};

constexpr uint32_t StatusEvent_bitmap {
  StatusEvent_none
};

constexpr uint32_t StatusEvent_pages {
  StatusEvent_pageMoveLeftInit |
  StatusEvent_pageMoveRightInit
};

constexpr uint32_t StatusEvent_init {
  StatusEvent_initEmpty |
  StatusEvent_oneSecondChange |
  StatusEvent_selCodeChange |
  StatusEvent_playqueueChange |
  StatusEvent_timerChange |
  StatusEvent_creditsChange |
  StatusEvent_songStop |
  StatusEvent_autoPlayModeChange |
  StatusEvent_loopModeChange |
  StatusEvent_freeplayModeChange |
  StatusEvent_volumeChange |
  StatusEvent_buttonChanged
};

