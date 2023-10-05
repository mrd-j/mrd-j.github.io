// huashan-xinfa.c 华山心法

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "henshan-xinfa" ||
               force == "zixia-shengong" ||
               force == "songshan-xinfa" ||
               force == "hanbing-zhenqi" ||
               force == "zhenyue-jue";
}

int valid_learn(object me)
{
    return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("华山心法只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
    return SKILL_D(__DIR__"huashan-xinfa/") + func;
}
