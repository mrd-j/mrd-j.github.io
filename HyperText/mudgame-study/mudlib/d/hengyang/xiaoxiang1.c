inherit ROOM;

void create()
{
    set("short", "小巷");
    set("long", @LONG
这是衡阳城内一条偏僻的小巷，平时很少有人来，只见这
条小巷弯弯曲曲不知道通向何处。
LONG);
        set("outdoors", "hengyang");

    set("exits", ([
            "south"  : __DIR__"xiaoxiang2",
            "north"  : __DIR__"hengyang2",
    ]));

    setup();
    replace_program(ROOM);
}
