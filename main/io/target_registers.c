#include "target_registers.h"
 
/**
 * @brief Array of ALL BASIC REGISTERS of the UMP209 multimeter (hardcoded). 
 */
static const MultimeterRegister targetRegister[] = {
        // Instant values
        { "Phase 1-N Voltage",      "V",   0x0000, 2, 0x04, 0.001 }, // 0
        { "Phase 2-N Voltage",      "V",   0x0002, 2, 0x04, 0.001 }, // 1
        { "Phase 3-N Voltage",      "V",   0x0004, 2, 0x04, 0.001 }, // 2
        { "Phase 1-2 Voltage",      "V",   0x0006, 2, 0x04, 0.001 }, // 3
        { "Phase 2-3 Voltage",      "V",   0x0008, 2, 0x04, 0.001 }, // 4
        { "Phase 3-1 Voltage",      "V",   0x000A, 2, 0x04, 0.001 }, // 5
        { "System Voltage",         "V",   0x000C, 2, 0x04, 0.001 }, // 6

        { "Phase 1 Current",        "A",   0x000E, 2, 0x04, 0.001 }, // 7
        { "Phase 2 Current",        "A",   0x0010, 2, 0x04, 0.001 }, // 8
        { "Phase 3 Current",        "A",   0x0012, 2, 0x04, 0.001 }, // 9
        { "Neutral Current",        "A",   0x0014, 2, 0x04, 0.001 }, // 10
        { "System Current",         "A",   0x0016, 2, 0x04, 0.001 }, // 11

        { "Phase 1 Active Power",   "W",   0x0018, 4, 0x04, 0.001 }, // 12
        { "Phase 2 Active Power",   "W",   0x001C, 4, 0x04, 0.001 }, // 13
        { "Phase 3 Active Power",   "W",   0x0020, 4, 0x04, 0.001 }, // 14
        { "System Active Power",    "W",   0x0024, 4, 0x04, 0.001 }, // 15

        { "Phase 1 Apparent Power", "VA", 0x0028, 4, 0x04, 0.001 }, // 16
        { "Phase 2 Apparent Power", "VA", 0x002C, 4, 0x04, 0.001 }, // 17
        { "Phase 3 Apparent Power", "VA", 0x0030, 4, 0x04, 0.001 }, // 18
        { "System Apparent Power",  "VA", 0x0034, 4, 0x04, 0.001 }, // 19

        { "Phase 1 Reactive Power", "var", 0x0038, 4, 0x04, 0.001 }, // 20 !!
        { "Phase 2 Reactive Power", "var", 0x003C, 4, 0x04, 0.001 }, // 21
        { "Phase 3 Reactive Power", "var", 0x0040, 4, 0x04, 0.001 }, // 22
        { "System Reactive Power",  "var", 0x0044, 4, 0x04, 0.001 }, // 23

        { "Phase 1 Power Factor",   "-",   0x0048, 2, 0x04, 0.001 }, // 24 !!
        { "Phase 2 Power Factor",   "-",   0x004A, 2, 0x04, 0.001 }, // 25
        { "Phase 3 Power Factor",   "-",   0x004C, 2, 0x04, 0.001 }, // 26
        { "System Power Factor",    "-",   0x004E, 2, 0x04, 0.001 }, // 27
    
        { "Phase 1 DPF",            "-",   0x0050, 2, 0x04, 0.001 }, // 28
        { "Phase 2 DPF",            "-",   0x0052, 2, 0x04, 0.001 }, // 29
        { "Phase 3 DPF",            "-",   0x0054, 2, 0x04, 0.001 }, // 30
    
        { "Phase 1 TAN(Ø)",         "-",   0x0056, 2, 0x04, 0.001 }, // 31
        { "Phase 2 TAN(Ø)",         "-",   0x0058, 2, 0x04, 0.001 }, // 32
        { "Phase 3 TAN(Ø)",         "-",   0x005A, 2, 0x04, 0.001 }, // 33
        { "System TAN(Ø)",          "-",   0x005C, 2, 0x04, 0.001 }, // 34
    
        { "Phase 1 Voltage THD",    "%",   0x005E, 2, 0x04, 0.001 }, // 35
        { "Phase 2 Voltage THD",    "%",   0x0060, 2, 0x04, 0.001 }, // 36
        { "Phase 3 Voltage THD",    "%",   0x0062, 2, 0x04, 0.001 }, // 37
        { "Line 12 Voltage THD",    "%",   0x0064, 2, 0x04, 0.001 }, // 38
        { "Line 23 Voltage THD",    "%",   0x0066, 2, 0x04, 0.001 }, // 39
        { "Line 31 Voltage THD",    "%",   0x0068, 2, 0x04, 0.001 }, // 40
    
        { "Phase 1 Current THD",    "%",   0x006A, 2, 0x04, 0.001 }, // 41
        { "Phase 2 Current THD",    "%",   0x006C, 2, 0x04, 0.001 }, // 42
        { "Phase 3 Current THD",    "%",   0x006E, 2, 0x04, 0.001 }, // 43
        { "Neutral Current THD",    "%",   0x0070, 2, 0x04, 0.001 }, // 44
    
        { "Frequency",              "Hz",  0x0072, 2, 0x04, 0.001 }, // 45
        { "Phase Sequence",         "-",   0x0074, 2, 0x04, 0.001 }, // 46

        //DEMAND values
        { "Phase 1 current DMD",                 "A",   0x010E, 2, 0x04, 0.001 }, // 47
        { "Phase 2 current DMD",                 "A",   0x0110, 2, 0x04, 0.001 }, // 48
        { "Phase 3 current DMD",                 "A",   0x0112, 2, 0x04, 0.001 }, // 49
        { "Neutral current DMD",                 "A",   0x0114, 2, 0x04, 0.001 }, // 50
        { "System current DMD",                  "A",   0x0116, 2, 0x04, 0.001 }, // 51
        { "Phase 1 imported active power DMD",   "W",   0x0118, 4, 0x04, 0.001 }, // 52
        { "Phase 1 exported active power DMD",   "W",   0x011C, 4, 0x04, 0.001 }, // 53
        { "Phase 2 imported active power DMD",   "W",   0x0120, 4, 0x04, 0.001 }, // 54
        { "Phase 2 exported active power DMD",   "W",   0x0124, 4, 0x04, 0.001 }, // 55
        { "Phase 3 imported active power DMD",   "W",   0x0128, 4, 0x04, 0.001 }, // 56
        { "Phase 3 exported active power DMD",   "W",   0x012C, 4, 0x04, 0.001 }, // 57
        { "System imported active power DMD",    "W",   0x0130, 4, 0x04, 0.001 }, // 58
        { "System exported active power DMD",    "W",   0x0134, 4, 0x04, 0.001 }, // 59

        { "Phase 1 imported reactive power DMD", "var", 0x0160, 4, 0x04, 0.001 }, // 60
        { "Phase 1 exported reactive power DMD", "var", 0x0164, 4, 0x04, 0.001 }, // 61
        { "Phase 2 imported reactive power DMD", "var", 0x0168, 4, 0x04, 0.001 }, // 62
        { "Phase 2 exported reactive power DMD", "var", 0x016C, 4, 0x04, 0.001 }, // 63
        { "Phase 3 imported reactive power DMD", "var", 0x0170, 4, 0x04, 0.001 }, // 64
        { "Phase 3 exported reactive power DMD", "var", 0x0174, 4, 0x04, 0.001 }, // 65
        { "System imported reactive power DMD",  "var", 0x0178, 4, 0x04, 0.001 }, // 66
        { "System exported reactive power DMD",  "var", 0x017C, 4, 0x04, 0.001 }, // 67

        //MAX values
        { "Phase 1-N voltage MAX",               "V",    0x0200, 2, 0x04, 0.001 }, // 68
        { "Phase 2-N voltage MAX",               "V",    0x0202, 2, 0x04, 0.001 }, // 69
        { "Phase 3-N voltage MAX",               "V",    0x0204, 2, 0x04, 0.001 }, // 70
        { "Line 12 voltage MAX",                 "V",    0x0206, 2, 0x04, 0.001 }, // 71
        { "Line 23 voltage MAX",                 "V",    0x0208, 2, 0x04, 0.001 }, // 72
        { "Line 31 voltage MAX",                 "V",    0x020A, 2, 0x04, 0.001 }, // 73
        { "System voltage MAX",                  "V",    0x020C, 2, 0x04, 0.001 }, // 74
        { "Phase 1 current MAX",                 "A",    0x020E, 2, 0x04, 0.001 }, // 75
        { "Phase 2 current MAX",                 "A",    0x0210, 2, 0x04, 0.001 }, // 76
        { "Phase 3 current MAX",                 "A",    0x0212, 2, 0x04, 0.001 }, // 77
        { "Neutral current MAX",                 "A",    0x0214, 2, 0x04, 0.001 }, // 78
        { "System current MAX",                  "A",    0x0216, 2, 0x04, 0.001 }, // 79

        { "Phase 1 imported active power DMD MAX",     "W",    0x02B4, 4, 0x04, 0.001 }, // 80
        { "Phase 1 exported active power DMD MAX",     "W",    0x02B8, 4, 0x04, 0.001 }, // 81
        { "Phase 2 imported active power DMD MAX",     "W",    0x02BC, 4, 0x04, 0.001 }, // 82
        { "Phase 2 exported active power DMD MAX",     "W",    0x02C0, 4, 0x04, 0.001 }, // 83
        { "Phase 3 imported active power DMD MAX",     "W",    0x02C4, 4, 0x04, 0.001 }, // 84
        { "Phase 3 exported active power DMD MAX",     "W",    0x02C8, 4, 0x04, 0.001 }, // 85
        { "System imported active power DMD MAX",      "W",    0x02CC, 4, 0x04, 0.001 }, // 86
        { "System exported active power DMD MAX",      "W",    0x02D0, 4, 0x04, 0.001 }, // 87

        { "Phase 1 imported reactive power DMD MAX",   "var",  0x02F4, 4, 0x04, 0.001 }, // 88
        { "Phase 1 exported reactive power DMD MAX",   "var",  0x02F8, 4, 0x04, 0.001 }, // 89
        { "Phase 2 imported reactive power DMD MAX",   "var",  0x02FC, 4, 0x04, 0.001 }, // 90
        { "Phase 2 exported reactive power DMD MAX",   "var",  0x0300, 4, 0x04, 0.001 }, // 91
        { "Phase 3 imported reactive power DMD MAX",   "var",  0x0304, 4, 0x04, 0.001 }, // 92
        { "Phase 3 exported reactive power DMD MAX",   "var",  0x0308, 4, 0x04, 0.001 }, // 93
        { "System imported reactive power DMD MAX",    "var",  0x030C, 4, 0x04, 0.001 }, // 94
        { "System exported reactive power DMD MAX",    "var",  0x0310, 4, 0x04, 0.001 }, // 95


        //MIN values
        { "System Active power MIN",                   "W",    0x02D4, 4, 0x04, 0.001 },    // 96
        { "System Apparent power MIN",                 "VA",   0x02D8, 4, 0x04, 0.001 },    // 97
        { "System Reactive power MIN",                 "var",  0x02DC, 4, 0x04, 0.001 },    // 98
        
        // Energy values
        { "Phase 1 imported active energy",            "Wh",   0x0400, 4, 0x04, 0.001 },   //  99
        { "Phase 1 exported active energy",            "Wh",   0x0404, 4, 0x04, 0.001 },   // 101
        { "Phase 2 imported active energy",            "Wh",   0x0408, 4, 0x04, 0.001 },   // 102
        { "Phase 2 exported active energy",            "Wh",   0x040C, 4, 0x04, 0.001 },   // 103
        { "Phase 3 imported active energy",            "Wh",   0x0410, 4, 0x04, 0.001 },   // 104
        { "Phase 3 exported active energy",            "Wh",   0x0414, 4, 0x04, 0.001 },   // 105
        { "System imported active energy",             "Wh",   0x0418, 4, 0x04, 0.001 },   // 106
        { "System exported active energy",             "Wh",   0x041C, 4, 0x04, 0.001 },   // 107
        { "Phase 1 imported active energy",            "Wh",   0x0400, 4, 0x04, 0.001 },   // 108
        { "Phase 1 exported active energy",            "Wh",   0x0404, 4, 0x04, 0.001 },   // 109
        { "Phase 2 imported active energy",            "Wh",   0x0408, 4, 0x04, 0.001 },   // 110
        { "Phase 2 exported active energy",            "Wh",   0x040C, 4, 0x04, 0.001 },   // 111
        { "Phase 3 imported active energy",            "Wh",   0x0410, 4, 0x04, 0.001 },   // 112
        { "Phase 3 exported active energy",            "Wh",   0x0414, 4, 0x04, 0.001 },   // 113
        { "System imported active energy",             "Wh",   0x0418, 4, 0x04, 0.001 },   // 114
        { "System exported active energy",             "Wh",   0x041C, 4, 0x04, 0.001 },   // 115
        { "Balance of system active energy (imp-exp)", "Wh",   0x0420, 4, 0x04, 0.001 },   // 116

        { "Balance of system apparent energy (BAL-C + BAL-L)",      "VAh",  0x048C, 4, 0x04, 0.001 },   // 117
        { "Phase 1 imported capacitive reactive energy",            "varh", 0x0490, 4, 0x04, 0.001 },   // 118
        { "Phase 1 exported capacitive reactive energy",            "varh", 0x0494, 4, 0x04, 0.001 },   // 119
        { "Phase 1 imported inductive reactive energy",             "varh", 0x0498, 4, 0x04, 0.001 },   // 120
        { "Phase 1 exported inductive reactive energy",             "varh", 0x049C, 4, 0x04, 0.001 },   // 121
        { "Phase 2 imported capacitive reactive energy",            "varh", 0x04A0, 4, 0x04, 0.001 },   // 122
        { "Phase 2 exported capacitive reactive energy",            "varh", 0x04A4, 4, 0x04, 0.001 },   // 123
        { "Phase 2 imported inductive reactive energy",             "varh", 0x04A8, 4, 0x04, 0.001 },   // 124
        { "Phase 2 exported inductive reactive energy",             "varh", 0x04AC, 4, 0x04, 0.001 },   // 125

        { "Phase 3 imported capacitive reactive energy",            "varh", 0x04B0, 4, 0x04, 0.001 },   // 126
        { "Phase 3 exported capacitive reactive energy",            "varh", 0x04B4, 4, 0x04, 0.001 },   // 127
        { "Phase 3 imported inductive reactive energy",             "varh", 0x04B8, 4, 0x04, 0.001 },   // 128
        { "Phase 3 exported inductive reactive energy",             "varh", 0x04BC, 4, 0x04, 0.001 },   // 129

        { "System imported capacitive reactive energy",             "varh", 0x04C0, 4, 0x04, 0.001 },   // 130
        { "System exported capacitive reactive energy",             "varh", 0x04C4, 4, 0x04, 0.001 },   // 131
        { "System imported inductive reactive energy",              "varh", 0x04C8, 4, 0x04, 0.001 },   // 132
        { "System exported inductive reactive energy",              "varh", 0x04CC, 4, 0x04, 0.001 },   // 133

    // Experimental registers
    //{ "Balance of system capacitive reactive energy (imp-exp)", "varh", 0x04D0, 4, 0x04, 0.001 }, // 146
    //{ "Balance of system inductive reactive energy (imp-exp)",  "varh", 0x04D4, 4, 0x04, 0.001 }, // 147
    //{ "Balance of system reactive energy (BAL-C + BAL-L)",      "varh", 0x04D8, 4, 0x04, 0.001 }, // 148

};



const MultimeterRegisterSet target_register_set = {
    .registers = targetRegister,
    .size = sizeof(targetRegister) / sizeof(targetRegister[0])
};