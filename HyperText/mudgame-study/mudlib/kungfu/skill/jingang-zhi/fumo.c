// fumo.c  金刚伏魔决

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        // object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/jingang-zhi/fumo"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「金刚伏魔诀」只能在战斗中对对手使用。\n");

        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("你必须空手才能使用「金刚伏魔诀」！\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("jingang-zhi", 1) < 150)
                return notify_fail("你的大力金刚指修为不够，目前不能使用「金刚伏魔诀」！\n");

        if ((me->query_skill_mapped("force") != "hunyuan-yiqi") && (me->query_skill_mapped("force") != "yijinjing") && (me->query_skill_mapped("force") != "luohan-fumogong"))
                return notify_fail("你现在没有激发少林内功为内功，难以施展「金刚伏魔诀」。\n");

        if (me->query("neili") < 400)
                return notify_fail("你的真气不够，无法使用「金刚伏魔诀」！\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("你没有激发大力金刚指，不能使用「金刚伏魔诀」！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "眼中闪过一道青光，汇聚全身功力，右手食指弹出一道"
              HIY "劲气，划空而过，如同流星一般击向$n" + HIY "！\n" NOR;

        ap = me->query_skill("finger") + me->query_skill("force");
        dp = target->query_skill("dodge") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                me->add("neili", -300);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                    HIR "只见$p" HIR "一声惨叫，已被点中胸口要穴，"
                                    "$p" HIR "只觉得胸口气血汹涌，全身气血"
                                    "倒流，哇的一声吐出一口鲜血，苦不堪言！\n" NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$N" CYN "的企图，轻轻"
                       CYN "向后飘出数丈，躲过了这一致命的一击！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
