// Room: /u/zqb/tiezhang/road-1.c

inherit ROOM;

void create()
{
    set("short", "黄土路");
    set("long", @LONG
你走在一条尘土飞扬的黄土路上，两旁是阴森森的树林。这里是川湘的
交界处，据说经常有土匪出没，不可久留。
LONG    );
    set("exits", ([ /* sizeof() == 2 */
        "southwest" : __DIR__"road-2",
        "northeast" : __DIR__"lx",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "tiezhang");

    setup();
    replace_program(ROOM);
}
