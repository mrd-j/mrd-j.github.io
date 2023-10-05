// powerup.c 蛤蟆功加力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
    int skill;

    if (target != me)
        return notify_fail("你只能用蛤蟆功来提升自己的战斗力。\n");

    if ((int)me->query("neili") < 100 )
        return notify_fail("你的内力不够。\n");

    if ((int)me->query_temp("powerup"))
        return notify_fail("你已经在运功中了。\n");

    skill = me->query_skill("hamagong", 1);
    me->add("neili", -90);
    me->receive_damage("qi", 0);

    message_combatd(HIR "$N" HIR "微一凝神，运起蛤蟆功，全"
                        "身骨节发出一阵爆豆般的声响！\n" NOR, me);

    me->add_temp("apply/attack", skill / 3);
    me->add_temp("apply/defense", skill / 3);
    me->set_temp("powerup", 1);

    me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill/3 :), skill);

    if (me->is_fighting()) me->start_busy(1 + random(3));

    return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
            me->add_temp("apply/attack", -amount);
            me->add_temp("apply/defense", -amount);
            me->delete_temp("powerup");
            tell_object(me, "你的蛤蟆功运行完毕，将内力收回丹田。\n");
        }
}
