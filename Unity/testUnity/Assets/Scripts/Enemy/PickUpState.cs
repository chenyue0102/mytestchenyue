

using UnityEngine;

public class PickUpState : EnemyBaseState
{
    public override void OnEnterState(Enemy enemy)
    {
        enemy.animState = 5;
        enemy.SwitchPoint();
    }

    public override void OnUpdate(Enemy enemy)
    {
        if (!enemy.anim.GetCurrentAnimatorStateInfo(0).IsName("Idle"))
        {
            enemy.animState = 1;
            enemy.MoveToTarget();
        }
        if (Mathf.Abs(enemy.transform.position.x - enemy.targetPoint.position.x) < 0.01f)
        {
            enemy.TransitionToState(enemy.patrolState);
        }
        if (enemy.attackList.Count > 0)
        {
            enemy.TransitionToState(enemy.attachState);
        }
    }
}
