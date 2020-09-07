using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Enemy : MonoBehaviour
{
    public EnemyBaseState currentState;
    public float speed;
    public Transform pointA, pointB;
    public Transform targetPoint;
    public List<Transform> attackList = new List<Transform>();
    public GameObject checkArea;
    public Animator anim;
    public int animState = 0;
    public PatrolState patrolState = new PatrolState();
    public AttachState attachState = new AttachState();

    [Header("attack")]
    public float attackRange, skillRange;
    public float attackRate;
    protected float nextAttack = 0;

    public virtual void Init()
    {
        targetPoint = pointA;
        anim = GetComponent<Animator>();
    }

    private void Awake()
    {
        Init();
    }

    // Start is called before the first frame update
    void Start()
    {
        TransitionToState(patrolState);
    }

    // Update is called once per frame
    void Update()
    {
        currentState.OnUpdate(this);
        anim.SetInteger("state", animState);
    }

    public void TransitionToState(EnemyBaseState state)
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

    public abstract void Attack();

    public abstract void SkillAttack();

    public void OnTriggerStay2D(Collider2D collision)//停留在区域中
    {
        if (!attackList.Contains(collision.transform))
        {
            attackList.Add(collision.transform);
        }
    }

    public void OnTriggerExit2D(Collider2D collision)//离开区域
    {
        attackList.Remove(collision.transform);
    }

    public void OnTriggerEnter2D(Collider2D collision)
    {

    }

}
