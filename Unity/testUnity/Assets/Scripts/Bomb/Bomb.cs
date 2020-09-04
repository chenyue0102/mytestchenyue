using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bomb : MonoBehaviour
{
    private Animator anim;
    private Rigidbody2D rb;
    private Collider2D coll;
    public LayerMask targeLayer;

    public float startTime;
    public float waitTime;
    public float radius;
    public float bombForce;

    // Start is called before the first frame update
    void Start()
    {
        startTime = Time.time;
        anim = GetComponent<Animator>();
        rb = GetComponent<Rigidbody2D>();
        targeLayer = GetComponent<LayerMask>();
        coll = GetComponent<Collider2D>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Time.time > startTime + waitTime)
        {
            anim.Play("BombExplotion");
        }
    }

    public void OnDrawGizmos()
    {
        Gizmos.DrawWireSphere(transform.position, radius);
    }

    void Explotion()
    {
        Collider2D[] aroundObjects = Physics2D.OverlapCircleAll(transform.position, radius, targeLayer);//检测周围物体
        //coll.enabled = false;
        //rb.gravityScale = 0;
        foreach (var item in aroundObjects)
        {
            Vector3 pos = transform.position - item.transform.position;
            item.GetComponent<Rigidbody2D>().AddForce((-pos + Vector3.up) * bombForce, ForceMode2D.Impulse);
        }
    }

    void DestroyThis()
    {
        Destroy(gameObject);
    }
}
