// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/s4.hpp"

namespace xsk::gsc::s4
{

extern std::array<std::pair<u16, char const*>, meth_count> const meth_list
{{
//  { 0x80AD, "disableplayeruse" },
//  { 0x8276, "enableplayeruse" },
    { 0x809B, "delete" },
    { 0x80AD, "hudoutlinedisableforclient" },
    { 0x8126, "getcurrentweapon" },
    { 0x817B, "gettagorigin" },
    { 0x817E, "tagexists" },
    { 0x81A5, "hide" },
    { 0x81B8, "iprintlnbold" },
    { 0x820C, "linkto" },
    { 0x8226, "makeunusable" },
    { 0x8227, "makeuseable" },
    { 0x8276, "playlocalsound" },
    { 0x8277, "playloopsound" },
    { 0x8291, "controlturreton" },
    { 0x82F7, "setclientomnvar" },
    { 0x8306, "setcursorhint" },
    { 0x830A, "setdefaultdroppitch" },
    { 0x832C, "sethintstring" },
    { 0x8351, "setmodel" },
    { 0x8358, "setnodeploy" },
    { 0x83C4, "show" },
    { 0x83C9, "showpart" },
    { 0x83CB, "showtoplayer" },
    { 0x83F1, "stoploopsound" },
    { 0x8401, "switchtoweaponimmediate" },
    { 0x841F, "usebuttonpressed" },
    { 0x8428, "usinggamepad" },
    { 0x84A9, "setplayermusicstate" },
    { 0x84B2, "allowmounttop" },
    { 0x84B3, "allowmountside" },
    { 0x84C7, "sethudtutorialmessage" },
    { 0x84C8, "clearhudtutorialmessage" },
    { 0x84CF, "setuserange" },
    { 0x84D0, "setuseholdduration" },
    { 0x84D5, "setusefov" },
    { 0x84D6, "sethintdisplayfov" },
    { 0x8580, "sethintrequiresholding" },
    { 0x85A4, "setasgametypeobjective" },
}};

} // namespace xsk::gsc::s4
