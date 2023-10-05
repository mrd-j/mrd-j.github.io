// SKILL liuyang-zhang.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([    "action" : "$N一招「落日熔金」，左掌叠于右掌之上，劈向$n",
    "force" : 100,
        "attack": 2,
    "dodge" : 30,
        "parry" : 1,
    "damage": 5,
    "lvl"   : 0,
    "skill_name" : "落日熔金",
    "damage_type" : "瘀伤"
]),
([    "action" : "$N一招「安禅制毒龙」，面色凝重，双掌轻飘飘地拍向$n",
    "force" : 130,
        "attack": 8,
    "dodge" : 25,
        "parry" : 3,
    "damage": 30,
    "lvl"   : 20,
    "skill_name" : "安禅制毒龙",
    "damage_type" : "内伤"
]),
([    "action" : "$N一招「日斜归路晚霞明」，双掌幻化一片掌影，将$n笼罩于内。",
    "force" : 160,
        "attack": 12,
    "dodge" : 43,
        "parry" : 4,
    "damage": 35,
    "lvl"   : 30,
    "skill_name" : "日斜归路晚霞明",
    "damage_type" : "瘀伤"
]),

([    "action" : "$N一招「阳关三叠」，向$n的$l连击三掌",
    "force" : 210,
        "attack": 15,
    "dodge" : 55,
        "parry" : 8,
    "damage": 50,
    "lvl"   : 40,
    "skill_name" : "阳关三叠",
        "damage_type" : "瘀伤"
]),
([    "action" : "$N一招「阳春一曲和皆难」，只见一片掌影攻向$n",
    "force" : 250,
        "attack": 22,
    "dodge" : 52,
        "parry" : 0,
    "damage": 30,
    "lvl"   : 60,
    "skill_name" : "阳春一曲和皆难",
    "damage_type" : "瘀伤"
]),

([    "action" : "$N双掌平挥，一招「云霞出海曙」击向$n",
    "force" : 300,
        "attack": 23,
    "dodge" : 65,
        "parry" : 11,
    "damage": 50,
    "lvl"   : 80,
    "skill_name" : "云霞出海曙",
        "damage_type" : "瘀伤"
]),
([    "action" : "$N一招「白日参辰现」，只见一片掌影攻向$n",
    "force" : 310,
        "attack": 28,
    "dodge" : 63,
        "parry" : 5,
    "damage": 80,
    "lvl"   : 100,
    "skill_name" : "白日参辰现",
    "damage_type" : "内伤"
]),

([    "action" : "$N左掌虚晃，右掌一记「云霞出薛帷」击向$n的头部",
    "force" : 330,
        "attack": 25,
    "dodge" : 77,
    "damage": 90,
        "parry" : 12,
    "lvl"   : 120,
    "skill_name" : "云霞出薛帷",
        "damage_type" : "瘀伤"
]),
([    "action" : "$N施出「青阳带岁除」，右手横扫$n的$l，左手攻向$n的胸口",
    "force" : 360,
        "attack": 31,
    "dodge" : 80,
        "parry" : 15,
    "damage": 100,
    "lvl"   : 140,
    "skill_name" : "青阳带岁除",
        "damage_type" : "瘀伤"
]),
([    "action" : "$N施出「阳歌天钧」，双掌同时击向$n的$l",
    "force" : 400,
        "attack": 32,
    "dodge" : 81,
        "parry" : 10,
    "damage": 130,
    "lvl"   : 160,
    "skill_name" : "阳歌天钧",
        "damage_type" : "瘀伤"
]),
([      "action": "$N凝神静气，使出极招"RED" 天山六阳之极意 "NOR"",
        "force"  : (int)this_player()->query_skill("force", 1)/2 + random((int)this_player()->query_skill("force", 1)),
        "attack" : (int)this_player()->query_skill("strike", 1)/4 + random((int)this_player()->query_skill("strike", 1)/2),
        "dodge"  : (int)this_player()->query_skill("dodge", 1)/6 + random((int)this_player()->query_skill("force", 1)/3),
        "parry"  : (int)this_player()->query_skill("parry", 1)/6 + random((int)this_player()->query_skill("parry", 1)/3),
        "damage" : (int)this_player()->query_skill("force", 1)/4 + random((int)this_player()->query_skill("strike", 1)/2),
        "lvl"    : 200,
        "skill_name" : "极意",
        "damage_type": "瘀伤"
])
});

int valid_enable(string usage)
{
    return usage == "parry" || usage == "strike" || usage == "throwing";
}

int valid_combine(string combo)
{
    return combo == "zhemei-shou";
}

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("练天山六阳掌必须空手。\n");

        if (me->query("str") < 30)
                return notify_fail("你先天膂力不足，无法学习刚猛的天山六阳掌。\n");

        if ((int)me->query_skill("force") < 130)
                return notify_fail("你的内功火候不够，无法练天山六阳掌。\n");

    if ((int)me->query("max_neili") < 1000)
        return notify_fail("你的内力太弱，无法练天山六阳掌。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的基本掌法火候不够，无法练天山六阳掌。\n");

    if ((int)me->query_skill("strike", 1) < (int)me->query_skill("liuyang-zhang", 1))
        return notify_fail("你的基本掌法水平有限，无法领会更高深的天山六阳掌。\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level = (int) me->query_skill("liuyang-zhang",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 90)
        return notify_fail("你的体力太低了。\n");
    if ((int)me->query("neili") < 80)
        return notify_fail("你的内力不够练天山六阳掌。\n");

    me->receive_damage("qi", 81);
    me->add("neili", -73);
    return 1;
}

mixed hit_ob(object me, object target)
{
        int ly, zm, bm, bh, lb;
        int count_damage, count_attack;
        int i, n;
        ly = me->query_skill("liuyang-zhang", 1);
        zm = me->query_skill("zhemei-shou", 1);
        bm = me->query_skill("beiming-shengong", 1);
        bh = me->query_skill("bahuang-gong", 1);
        lb = me->query_skill("lingbo-weibu", 1);
        count_damage = bm / 10 + bh / 10;
        count_attack = lb / 5;

        if (me->query("family/family_name") == "逍遥派" || me->query("family/family_name") == "灵鹫宫")
        {
            if (random(2) && me->query("neili") > 200 && ! me->query_temp("is_attacking"))
            {
                message_vision(HIY "\n天山六阳掌,炉火纯青！\n" NOR, me, target);
                n = 1;
                if (random(zm) > 100) n += 1;
                me->add("neili", -n * 30);
                me->set_temp("is_attacking", 1);
                if (me->query_skill_mapped("force") == "beiming-shengong" ||
                    me->query_skill_mapped("force") == "bahuang-gong")
                    me->add_temp("apply/damage", count_damage);
                if (me->query_skill_mapped("dodge") == "lingbo-weibu")
                    me->add_temp("apply/attack", count_attack);
                for (i = 0; i < n; i++)
                {
                    COMBAT_D->do_attack(me, target, 0, 0);
                }
                me->delete_temp("is_attacking");
                if (me->query_skill_mapped("force") == "beiming-shengong" ||
                    me->query_skill_mapped("force") == "bahuang-gong")
                    me->add_temp("apply/damage", -count_damage);
                if (me->query_skill_mapped("dodge") == "lingbo-weibu")
                    me->add_temp("apply/attack", -count_attack);

            }
        }
}

string perform_action_file(string action)
{
    return __DIR__"liuyang-zhang/" + action;
}
