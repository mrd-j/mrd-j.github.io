#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "阴阳塔" NOR);
        set("long", HIB @LONG
这是地狱中最高的一座塔，高约三百余尺，共有十八级。相传塔顶
住有神兽朱雀，这个传言也不知是真是假。
LONG NOR
        );

        set("exits", ([
              "up"   : __DIR__"yinyangta12",
              "down" : __DIR__"yinyangta10",
        ]));
        
        set("objects",([
        ]));
        
        setup();
        replace_program(ROOM);
}
