inherit ROOM;
void create()
{
    set("short", "戈壁");
    set("long", @LONG
戈壁平坦如镜，和沙漠上的沙丘起伏全然不同，只见一片
平沙，凝眸远眺，只觉天地相接，万籁无声，身当此境，不禁
也生栗栗之感，顿觉大千无限，一己渺小异常。
LONG);
    set("outdoors", "shenfeng");
    set("exits", ([
        "east" : __DIR__"caoyuan4",
        "west" : "/d/xiyu/nanjiang1",
        "south" : "/d/xiyu/nanjiang2",
        "southwest" : "/d/xiyu/nanjiang2",
    ]));

    setup();
    replace_program(ROOM);
}
