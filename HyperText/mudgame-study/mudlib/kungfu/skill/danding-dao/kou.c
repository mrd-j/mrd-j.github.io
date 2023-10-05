#include <ansi.h>
#include <combat.h>

#define KOU "「" HIM "环环相扣" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
    object weapon;
    int damage;
    string msg;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/danding-dao/kou"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(KOU "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对，难以施展" KOU "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，难以施展" KOU "。\n");

        if ((int)me->query_skill("danding-dao", 1) < 80)
                return notify_fail("你的丹碇刀法还不到家，难以施展" KOU "。\n");

        if (me->query_skill_mapped("blade") != "danding-dao")
                return notify_fail("你没有激发丹碇刀法，难以施展" KOU "。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的真气不够，难以施展" KOU "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

    msg = HIM "$N" HIM "刀法忽然一变，时而削，时而砍，时而劈，挥舞如风，转瞬"
              "即至劈向$n" HIM "！\n" NOR;

        ap = me->query_skill("blade");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
    {
        damage = ap / 2 + random(ap / 2);
                me->add("neili", -100);
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "结果$n" HIR "一个不留神，被刀锋扫"
                                           "到，鲜血四溅，痛彻心肺！\n" NOR);
        me->start_busy(2);
    } else
    {
        msg += CYN "可是$p" CYN "凝神聚气，护住门户，无论$P"
                       CYN "怎样变招，始终奈何不得。\n" NOR;
                me->add("neili", -50);
        me->start_busy(3);
    }
    message_combatd(msg, me, target);

    return 1;
}
