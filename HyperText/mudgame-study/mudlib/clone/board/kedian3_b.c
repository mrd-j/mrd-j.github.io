// /clone/board/kedian3_b.c

inherit BULLETIN_BOARD;

void create()
{
    set_name("客店留言板", ({ "board" }) );
    set("location", "/d/chengdu/kedian");
    set("board_id", "kedian3_b");
    set("long", "有有用的话就往这里说，乱灌水杀无赦。\n" );
    setup();
    set("capacity", 100);
    replace_program(BULLETIN_BOARD);
}
