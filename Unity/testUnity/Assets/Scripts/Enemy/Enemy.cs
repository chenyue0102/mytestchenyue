using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour, IDamageable
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

    private GameObject alarmSign;

    [Header("attack")]
    public float attackRange, skillRange;
    public float attackRate;
    protected float nextAttack = 0;

    [Header("health")]
    public float health;
    public bool isDead;

    public virtual void Init()
    {
        targetPoint = pointA;
        anim = GetComponent<Animator>();
        alarmSign = transform.GetChild(0).gameObject;
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
        if (isDead)
        {
            return;
        }
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
    
    public virtual void Attack()
    {
        Debug.Log("Attack");
        if (Vector2.Distance(transform.position, targetPoint.position) < attackRange)
        {
            if (Time.time > nextAttack)
            {
                anim.SetTrigger("attack");
                nextAttack = Time.time + attackRange;
            }
        }
    }

    public virtual void SkillAttack()
    {
        if (Vector2.Distance(transform.position, targetPoint.position) < skillRange)
        {
            if (Time.time > nextAttack)
            {
                anim.SetTrigger("skill");
                nextAttack = Time.time + attackRange;
            }
        }
    }

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
        StartCoroutine(OnAlaram());
    }

    IEnumerator OnAlaram()
    {
        alarmSign.SetActive(true);
        //第一个layer 第一个动画的片段长度
        yield return new WaitForSeconds(alarmSign.GetComponent<Animator>().GetCurrentAnimatorClipInfo(0)[0].clip.length);
        alarmSign.SetActive(false);
    }

    public void GetHit(float damage)
    {
        health -= damage;
        if (health < 1)
        {
            health = 0;
            isDead = true;
            anim.SetBool("dead", isDead);
        }
        else
        {
            anim.SetTrigger("hit");
        }
    }
}
