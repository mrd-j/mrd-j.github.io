#include <room.h>
inherit ROOM;

void create()
{
        set("short", "树林");
        set("long", @LONG
扬州郊外的树林，松枝挺拔，乔木横斜。林间小道，逶迤
随远。林中蝉鸣厮闹，鸟啼宛转，使你顿时烦意尽消。地上落
了很多树枝石块。
LONG);
        set("outdoors", "city");
        set("exits", ([
            "east" : __DIR__"jiaowai5",
            "west" : __DIR__"jiaowai7",
        ]));
        setup();
        replace_program(ROOM);
}
