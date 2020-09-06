
using UnityEngine;

public class PatrolState : EnemyBaseState
{
    public override void OnEnterState(Enemy enemy)
    {
        enemy.SwitchPoint();
    }

    public override void OnUpdate(Enemy enemy)
    {
        if (Mathf.Abs(enemy.transform.position.x - enemy.targetPoint.position.x) < 0.01f)
        {
            enemy.SwitchPoint();
        }
        enemy.MoveToTarget();
    }
}
