// Room: /d/pk/turen12.c

#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", HIR "戮人场" NOR);
    set("long", @LONG
这里阴森恐怖，地上到处是残肢碎尸，无处不是暗红色的血滴。你心中
忐忑不安，万分警惕，不知道从哪里就会窜出一个黑影。
LONG
    );
    set("exits", ([
        "northeast"  : __DIR__"turen10",
        "west"  : __DIR__"turen11",
        "north" : __DIR__"turen9",
    ]));

    setup();
        replace_program(ROOM);
}
