#include <room.h>
inherit ROOM;

void create()
{
        set("short", "密林");
        set("long", @LONG
扬州郊外的茂密树林，阴森可怖。抬头不见天日。这里也
是扬州命案发生最多的地方。鸟兽蛇虫游荡不穷。
LONG);
        set("outdoors", "city");
        set("exits", ([
            "east"  : __DIR__"jiaowai8",
            "west"  : __DIR__"jiaowai10",
        ]));
        set("objects", ([
            __DIR__"obj/shuzhi": 2,
            "/clone/beast/dushe" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
