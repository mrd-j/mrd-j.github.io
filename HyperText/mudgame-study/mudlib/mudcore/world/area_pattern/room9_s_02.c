// room9_s_01.c
// 房間型式, 有9格, 出口為south, 編號1

#include <ansi.h>

int isAreaPattern() { return 1; }

string getName() { return "房子[9格], 出口[南], 藍底亮白框 "; }

// icon樣子
private mapping getIcon()
{
    mapping icon = ([
        0: ({ BBLU+HIW"╔="NOR, BBLU+HIW"=="NOR, BBLU+HIW"=╗"NOR }),
        1: ({ BBLU+HIW"║ "NOR, BBLU+HIW"  "NOR, BBLU+HIW" ║"NOR }),
        2: ({ BBLU+HIW"╚="NOR, BBLU+HIW"门"NOR, BBLU+HIW"=╝"NOR }),
    ]);

    return icon;
}

// block設定
private mapping getBlock()
{
    mapping block = ([
        0: ({1, 1, 1}),
        1: ({1, 0, 1}),
        2: ({1, 0, 1}),
    ]);

    return block;
}

mapping getMapStyle()
{
    mapping style = ([
        "icon": getIcon(),
        "block": getBlock(),
    ]);

    return style;
}
