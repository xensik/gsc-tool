// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW8_HPP_
#define _GSC_IW8_HPP_

#include <utils.hpp>

#include "resolver.hpp"

namespace IW8
{

enum class opcode : std::uint8_t
{
    OP_01 = 0x01, // -- 2
    OP_02 = 0x02, // -- 1
    OP_03 = 0x03, // -- 2
    OP_04 = 0x04, // -- 5 field variable
    OP_05 = 0x05, // -- 5 far thread
    OP_06 = 0x06, // -- 1
    OP_07 = 0x07, // -- 5 field variable
    OP_08 = 0x08, // -- 5 field variable
    OP_09 = 0x09, // -- 1
    OP_0A = 0x0A, // -- 1
    OP_0B = 0x0B, // -- 3
    OP_0C = 0x0C, // -- 1
    OP_0D = 0x0D, // -- 1
    OP_0E = 0x0E, // -- 3
    OP_0F = 0x0F, // -- 1
    OP_10 = 0x10, // -- 1
    OP_11 = 0x11, // -- 1
    OP_notify = 0x12, // -- 1
    OP_GetVector = 0x13, // -- 13
    OP_14 = 0x14, // -- 2
    OP_15 = 0x15, // -- 1
    OP_16 = 0x16, // -- 2
    OP_17 = 0x17, // -- 5 far thread
    OP_18 = 0x18, // -- 5 field variable
    OP_19 = 0x19, // -- 3
    OP_1A = 0x1A, // -- 1
    OP_1B = 0x1B, // -- 3
    OP_1C = 0x1C, // -- 3
    OP_1D = 0x1D, // -- 3
    OP_1E = 0x1E, // -- 3
    OP_1F = 0x1F, // -- 3
    OP_20 = 0x20, // -- 3
    OP_21 = 0x21, // -- 3
    OP_22 = 0x22, // -- 3
    OP_23 = 0x23, // -- 4
    OP_24 = 0x24, // -- 1
    OP_25 = 0x25, // -- 5 field variable
    OP_26 = 0x26, // -- 1
    OP_27 = 0x27, // -- 1
    OP_28 = 0x28, // -- 2
    OP_29 = 0x29, // -- 5
    OP_2A = 0x2A, // -- 1
    OP_endon = 0x2B, // -- 1
    OP_2C = 0x2C, // -- 5 field variable
    OP_2D = 0x2D, // -- 1
    OP_2E = 0x2E, // -- 1
    OP_2F = 0x2F, // -- 1
    OP_30 = 0x30, // -- 2
    OP_31 = 0x31, // -- 1
    OP_32 = 0x32, // -- 3
    OP_33 = 0x33, // -- 4
    OP_34 = 0x34, // -- 2
    OP_35 = 0x35, // -- 5
    OP_36 = 0x36, // -- 1
    OP_37 = 0x37, // -- 1
    OP_38 = 0x38, // -- 5 field variable
    OP_39 = 0x39, // -- 1
    OP_3A = 0x3A, // -- 1
    OP_3B = 0x3B, // -- 1
    OP_3C = 0x3C, // -- 5 field variable
    OP_3D = 0x3D, // -- 1
    OP_3E = 0x3E, // -- 1
    OP_3F = 0x3F, // -- 1
    OP_40 = 0x40, // -- 1
    OP_41 = 0x41, // -- 1
    OP_42 = 0x42, // -- 1
    OP_43 = 0x43, // -- 1
    OP_44 = 0x44, // -- 2
    OP_45 = 0x45, // -- 2
    OP_46 = 0x46, // -- 2
    OP_47 = 0x47, // -- 2
    OP_48 = 0x48, // -- 5
    OP_49 = 0x49, // -- 5
    OP_4A = 0x4A, // -- 1
    OP_4B = 0x4B, // -- 1
    OP_4C = 0x4C, // -- 5 field variable
    OP_4D = 0x4D, // -- 1
    OP_4E = 0x4E, // -- 1
    OP_4F = 0x4F, // -- 4
    OP_50 = 0x50, // -- 3
    OP_51 = 0x51, // -- 2
    OP_52 = 0x52, // -- 2
    OP_53 = 0x53, // -- 1
    OP_54 = 0x54, // -- 1
    OP_55 = 0x55, // -- 3
    OP_endswitch = 0x56, // -- 3
    OP_57 = 0x57, // -- 1
    OP_58 = 0x58, // -- 1
    OP_59 = 0x59, // -- 1
    OP_5A = 0x5A, // -- 1
    OP_5B = 0x5B, // -- 2
    OP_5C = 0x5C, // -- 1
    OP_5D = 0x5D, // -- 1 wait maybe
    OP_waittill = 0x5E, // -- 1
    OP_GetString = 0x5F, // -- 5
    OP_60 = 0x60, // -- 4 far function
    OP_61 = 0x61, // -- 1
    OP_GetAnimTree = 0x62, // -- 2
    OP_63 = 0x63, // -- 2
    OP_64 = 0x64, // -- 1
    OP_65 = 0x65, // -- 5 far thread
    OP_66 = 0x66, // -- 3
    OP_67 = 0x67, // -- 1
    OP_68 = 0x68, // -- 2
    OP_69 = 0x69, // -- 1
    OP_6A = 0x6A, // -- 1
    OP_6B = 0x6B, // -- 2
    OP_6C = 0x6C, // -- 1
    OP_6D = 0x6D, // -- 5 field variable
    OP_6E = 0x6E, // -- 5
    OP_6F = 0x6F, // -- 1
    OP_70 = 0x70, // -- 5
    OP_71 = 0x71, // -- 2
    OP_72 = 0x72, // -- 3
    OP_73 = 0x73, // -- 1
    OP_74 = 0x74, // -- 2
    OP_75 = 0x75, // -- 4 far function
    OP_76 = 0x76, // -- 1
    OP_77 = 0x77, // -- 1
    OP_78 = 0x78, // -- 1
    OP_79 = 0x79, // -- 1
    OP_GetIString = 0x7A, // -- 5
    OP_7B = 0x7B, // -- 5 field variable
    OP_7C = 0x7C, // -- 1
    OP_7D = 0x7D, // -- 1
    OP_7E = 0x7E, // -- 3
    OP_7F = 0x7F, // -- 3
    OP_80 = 0x80, // -- 3
    OP_81 = 0x81, // -- 3
    OP_82 = 0x82, // -- 3
    OP_83 = 0x83, // -- 3
    OP_84 = 0x84, // -- 4
    OP_85 = 0x85, // -- 1
    OP_86 = 0x86, // -- 5
    OP_87 = 0x87, // -- 1
    OP_88 = 0x88, // -- 1
    OP_89 = 0x89, // -- 4
    OP_8A = 0x8A, // -- 5 far thread
    OP_8B = 0x8B, // -- 1
    OP_8C = 0x8C, // -- 2
    OP_8D = 0x8D, // -- 5 field variable
    OP_8E = 0x8E, // -- 2
    OP_8F = 0x8F, // -- 1
    OP_90 = 0x90, // -- 1
    OP_GetAnimation = 0x91, // -- 9
    OP_92 = 0x92, // -- 4 far function
    OP_93 = 0x93, // -- 2
    OP_94 = 0x94, // -- 5
    OP_95 = 0x95, // -- 1
    OP_96 = 0x96, // -- 4 far function
    OP_97 = 0x97, // -- 1
    OP_98 = 0x98, // -- 4
    OP_99 = 0x99, // -- 1
    OP_9A = 0x9A, // -- 1
    OP_9B = 0x9B, // -- 1
    OP_9C = 0x9C, // -- 1
    OP_9D = 0x9D, // -- 1
    OP_9E = 0x9E, // -- 1
    OP_9F = 0x9F, // -- 1
    OP_A0 = 0xA0, // -- 6
    OP_A1 = 0xA1, // -- 2
    OP_A2 = 0xA2, // -- 1
    OP_A3 = 0xA3, // -- 1
    OP_A4 = 0xA4, // -- 1
    OP_A5 = 0xA5, // -- 1
    OP_A6 = 0xA6, // -- 2 not fixed size?
    OP_A7 = 0xA7, // -- 1
    OP_A8 = 0xA8, // -- 1
    OP_A9 = 0xA9, // -- 4
    OP_AA = 0xAA, // -- 4
    OP_AB = 0xAB, // -- 4
    OP_AC = 0xAC, // -- 4
    OP_AD = 0xAD, // -- 5
    OP_AE = 0xAE, // -- 5
    OP_AF = 0xAF, // -- 5
    OP_B0 = 0xB0, // -- 5
    OP_B1 = 0xB1, // -- 4
    OP_B2 = 0xB2, // -- 4
    OP_B3 = 0xB3, // -- 4
    OP_B4 = 0xB4, // -- 4
    OP_B5 = 0xB5, // -- 5
    OP_B6 = 0xB6, // -- 5
    OP_B7 = 0xB7, // -- 5
    OP_B8 = 0xB8, // -- 5
    OP_B9 = 0xB9, // -- 2
    OP_BA = 0xBA, // -- 2
    OP_BB = 0xBB, // -- 2
    OP_BC = 0xBC, // -- 2
    OP_BD = 0xBD, // -- 2 not fixed size?
    OP_Count = 0xBE,
};

auto opcode_size(opcode op) -> std::uint32_t;

} // namespace IW8

#endif // _GSC_IW8_HPP_
