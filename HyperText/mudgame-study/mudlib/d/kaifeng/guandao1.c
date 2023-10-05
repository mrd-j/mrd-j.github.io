inherit ROOM;

void create()
{
    set("short", "官道");
    set("long", @LONG
这是条连接开封府与中州府的官道，由于这条路治安较好
行人也不少。西面通向开封，东面通向中州。
LONG);
    set("exits", ([
        "east":__DIR__"tokaifeng",
        "northwest":__DIR__"shulin",
    ]));
    set("outdoors", "kaifeng");
    set("no_clean_up", 0);

    setup();
    replace_program(ROOM);
}
