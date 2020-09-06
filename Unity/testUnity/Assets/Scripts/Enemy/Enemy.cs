using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    public EnemyBaseState currentState;
    public float speed;
    public Transform pointA, pointB;
    public Transform targetPoint;
    public List<Transform> attachList = new List<Transform>();
    public GameObject checkArea;
    private PatrolState patrolState = new PatrolState();
    // Start is called before the first frame update
    void Start()
    {
        targetPoint = pointA;
        TranslateState(patrolState);
    }

    // Update is called once per frame
    void Update()
    {
        patrolState.OnUpdate(this);
    }

    public void TranslateState(EnemyBaseState state)
    {
        currentState = state;
        currentState.OnEnterState(this);
    }

    public void MoveToTarget()
    {
        transform.position = Vector2.MoveTowards(transform.position, targetPoint.position, speed * Time.deltaTime);
        FilpDirection();
    }

    public void FilpDirection()
    {
        if (transform.position.x < targetPoint.position.x)
        {
            transform.rotation = Quaternion.Euler(0, 0, 0);
        }
        else
        {
            transform.rotation = Quaternion.Euler(0, 180, 0);
        }
    }

    public void SwitchPoint()
    {
        if (Mathf.Abs(transform.position.x - pointA.position.x) < Mathf.Abs(transform.position.x - pointB.position.x))
        {
            targetPoint = pointB;
        }
        else
        {
            targetPoint = pointA;
        }
    }

    public virtual void Attack()
    {

    }

    public virtual void SkillAttack()
    {

    }

    public void OnTriggerStay2D(Collider2D collision)//停留在区域中
    {
        if (!attachList.Contains(collision.transform))
        {
            attachList.Add(collision.transform);
        }
    }

    public void OnTriggerExit2D(Collider2D collision)//离开区域
    {
        attachList.Remove(collision.transform);
    }

    public void OnTriggerEnter2D(Collider2D collision)
    {

    }

}
