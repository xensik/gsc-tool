// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW8.hpp"

namespace IW8
{

auto opcode_size(opcode id) -> std::uint32_t
{
    switch (id)
    {
    case opcode::OP_02: // -- 1
    case opcode::OP_06: // -- 1
    case opcode::OP_09: // -- 1
    case opcode::OP_0A: // -- 1
    case opcode::OP_0C: // -- 1
    case opcode::OP_0D: // -- 1
    case opcode::OP_0F: // -- 1
    case opcode::OP_10: // -- 1
    case opcode::OP_11: // -- 1
    case opcode::OP_notify: // -- 1
    case opcode::OP_15: // -- 1
    case opcode::OP_1A: // -- 1
    case opcode::OP_24: // -- 1
    case opcode::OP_26: // -- 1
    case opcode::OP_27: // -- 1
    case opcode::OP_2A: // -- 1
    case opcode::OP_endon: // -- 1
    case opcode::OP_2D: // -- 1
    case opcode::OP_2E: // -- 1
    case opcode::OP_2F: // -- 1
    case opcode::OP_31: // -- 1
    case opcode::OP_36: // -- 1
    case opcode::OP_37: // -- 1
    case opcode::OP_39: // -- 1
    case opcode::OP_3A: // -- 1
    case opcode::OP_3B: // -- 1
    case opcode::OP_3D: // -- 1
    case opcode::OP_3E: // -- 1
    case opcode::OP_3F: // -- 1
    case opcode::OP_40: // -- 1
    case opcode::OP_41: // -- 1
    case opcode::OP_42: // -- 1
    case opcode::OP_43: // -- 1
    case opcode::OP_4A: // -- 1
    case opcode::OP_4B: // -- 1
    case opcode::OP_4D: // -- 1
    case opcode::OP_4E: // -- 1
    case opcode::OP_53: // -- 1
    case opcode::OP_54: // -- 1
    case opcode::OP_57: // -- 1
    case opcode::OP_58: // -- 1
    case opcode::OP_59: // -- 1
    case opcode::OP_5A: // -- 1
    case opcode::OP_5B: // -- 2
    case opcode::OP_5C: // -- 1
    case opcode::OP_5D: // -- 1 wait maybe
    case opcode::OP_waittill: // -- 1
    case opcode::OP_61: // -- 1
    case opcode::OP_64: // -- 1
    case opcode::OP_67: // -- 1
    case opcode::OP_69: // -- 1
    case opcode::OP_6A: // -- 1
    case opcode::OP_6C: // -- 1
    case opcode::OP_6F: // -- 1
    case opcode::OP_73: // -- 1
    case opcode::OP_76: // -- 1
    case opcode::OP_77: // -- 1
    case opcode::OP_78: // -- 1
    case opcode::OP_79: // -- 1
    case opcode::OP_7C: // -- 1
    case opcode::OP_7D: // -- 1
    case opcode::OP_85: // -- 1
    case opcode::OP_87: // -- 1
    case opcode::OP_88: // -- 1
    case opcode::OP_8B: // -- 1
    case opcode::OP_8F: // -- 1
    case opcode::OP_90: // -- 1
    case opcode::OP_95: // -- 1
    case opcode::OP_97: // -- 1
    case opcode::OP_99: // -- 1
    case opcode::OP_9A: // -- 1
    case opcode::OP_9B: // -- 1
    case opcode::OP_9C: // -- 1
    case opcode::OP_9D: // -- 1
    case opcode::OP_9E: // -- 1
    case opcode::OP_9F: // -- 1
    case opcode::OP_A2: // -- 1
    case opcode::OP_A3: // -- 1
    case opcode::OP_A4: // -- 1
    case opcode::OP_A5: // -- 1
    case opcode::OP_A7: // -- 1
    case opcode::OP_A8: // -- 1
        return 1;
    case opcode::OP_01: // -- 2
    case opcode::OP_03: // -- 2
    case opcode::OP_14: // -- 2
    case opcode::OP_16: // -- 2
    case opcode::OP_28: // -- 2
    case opcode::OP_30: // -- 2
    case opcode::OP_34: // -- 2
    case opcode::OP_44: // -- 2
    case opcode::OP_45: // -- 2
    case opcode::OP_46: // -- 2
    case opcode::OP_47: // -- 2
    case opcode::OP_51: // -- 2
    case opcode::OP_52: // -- 2
    case opcode::OP_GetAnimTree: // -- 2
    case opcode::OP_63: // -- 2
    case opcode::OP_68: // -- 2
    case opcode::OP_6B: // -- 2
    case opcode::OP_71: // -- 2
    case opcode::OP_74: // -- 2
    case opcode::OP_8C: // -- 2
    case opcode::OP_8E: // -- 2
    case opcode::OP_93: // -- 2
    case opcode::OP_A1: // -- 2
    case opcode::OP_A6: // -- 2 not fixed size?
    case opcode::OP_B9: // -- 2
    case opcode::OP_BA: // -- 2
    case opcode::OP_BB: // -- 2
    case opcode::OP_BC: // -- 2
    case opcode::OP_BD: // -- 2 not fixed size?
        return 2;
    case opcode::OP_0B: // -- 3
    case opcode::OP_0E: // -- 3
    case opcode::OP_19: // -- 3
    case opcode::OP_1B: // -- 3
    case opcode::OP_1C: // -- 3
    case opcode::OP_1D: // -- 3
    case opcode::OP_1E: // -- 3
    case opcode::OP_1F: // -- 3
    case opcode::OP_20: // -- 3
    case opcode::OP_21: // -- 3
    case opcode::OP_22: // -- 3
    case opcode::OP_32: // -- 3
    case opcode::OP_50: // -- 3
    case opcode::OP_55: // -- 3
    case opcode::OP_endswitch: // -- 3
    case opcode::OP_66: // -- 3
    case opcode::OP_72: // -- 3
    case opcode::OP_7E: // -- 3
    case opcode::OP_7F: // -- 3
    case opcode::OP_80: // -- 3
    case opcode::OP_81: // -- 3
    case opcode::OP_82: // -- 3
    case opcode::OP_83: // -- 3
        return 3;
    case opcode::OP_23: // -- 4
    case opcode::OP_33: // -- 4
    case opcode::OP_4F: // -- 4
    case opcode::OP_60: // -- 4 far function
    case opcode::OP_75: // -- 4 far function
    case opcode::OP_84: // -- 4
    case opcode::OP_89: // -- 4
    case opcode::OP_92: // -- 4 far function
    case opcode::OP_96: // -- 4 far function
    case opcode::OP_98: // -- 4
    case opcode::OP_A9: // -- 4
    case opcode::OP_AA: // -- 4
    case opcode::OP_AB: // -- 4
    case opcode::OP_AC: // -- 4
    case opcode::OP_B1: // -- 4
    case opcode::OP_B2: // -- 4
    case opcode::OP_B3: // -- 4
    case opcode::OP_B4: // -- 4
        return 4;
    case opcode::OP_04: // -- 5 field variable
    case opcode::OP_05: // -- 5 far thread
    case opcode::OP_07: // -- 5 field variable
    case opcode::OP_08: // -- 5 field variable
    case opcode::OP_17: // -- 5 far thread
    case opcode::OP_18: // -- 5 field variable
    case opcode::OP_25: // -- 5 field variable
    case opcode::OP_29: // -- 5
    case opcode::OP_2C: // -- 5 field variable
    case opcode::OP_35: // -- 5
    case opcode::OP_38: // -- 5 field variable
    case opcode::OP_3C: // -- 5 field variable
    case opcode::OP_48: // -- 5
    case opcode::OP_49: // -- 5
    case opcode::OP_4C: // -- 5 field variable
    case opcode::OP_GetString: // -- 5
    case opcode::OP_65: // -- 5 far thread
    case opcode::OP_6D: // -- 5 field variable
    case opcode::OP_6E: // -- 5
    case opcode::OP_70: // -- 5
    case opcode::OP_GetIString: // -- 5
    case opcode::OP_7B: // -- 5 field variable
    case opcode::OP_86: // -- 5
    case opcode::OP_8A: // -- 5 far thread
    case opcode::OP_8D: // -- 5 field variable
    case opcode::OP_94: // -- 5
    case opcode::OP_AD: // -- 5
    case opcode::OP_AE: // -- 5
    case opcode::OP_AF: // -- 5
    case opcode::OP_B0: // -- 5
    case opcode::OP_B5: // -- 5
    case opcode::OP_B6: // -- 5
    case opcode::OP_B7: // -- 5
    case opcode::OP_B8: // -- 5
        return 5;
    case opcode::OP_A0: // -- 6
        return 6;
    case opcode::OP_GetAnimation: // -- 9
        return 9;
    case opcode::OP_GetVector: // -- 13
        return 13;
    default:
        GSC_LOG_ERROR("Couldn't resolve instruction size for 0x%hhX!", id);
        return 0;
    }
}

} // namespace IW8
