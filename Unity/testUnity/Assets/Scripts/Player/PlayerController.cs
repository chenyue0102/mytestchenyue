using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour,IDamageable
{
    private Rigidbody2D rb;
    private Animator anim;
    private FixedJoystick joystick;

    public float speed;
    public float jumpForce;

    [Header("Ground Check")]
    public Transform groundCheck;
    public float checkRadius;
    public LayerMask groundLayer;

    [Header("States Check")]
    public bool isGround;
    public bool isJump;
    public bool canJump;

    [Header("Game Object")]
    public GameObject gameObjectJump;
    public GameObject gameObjectLand;

    [Header("Attack")]
    public GameObject bombObject;
    public float nextAttack = 0.0f;
    public float attackRate;

    [Header("Health")]
    public float health;
    public bool isDead;

    private List<Transform> bombs = new List<Transform>();

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        health = GameManager.instance.LoadHealth();
        UIManager.instance.UpdateHealth(health);
        joystick = FindObjectOfType<FixedJoystick>();

        MessageBriage.GetInstance().RegMsg(100, OnMessageBomb);
    }

    void OnMessageBomb(int msgId, string msgText)
    {
        Debug.LogFormat("OnMessageBomb msgId:{0} msgText:{1}", new object[] { msgId, msgText });
        Attack();
    }

    // Update is called once per frame
    void Update()
    {
        if (isDead)
        {
            return;
        }
        CheckInput();
    }

    //固定周期执行，初始值为0.02秒
    private void FixedUpdate()
    {
        if (isDead)
        {
            rb.velocity = Vector2.zero;//速度设置成0
            return;
        }
        PhysicsCheck();
        Movement();
        Jump();
    }

    public void Attack()
    {
        if (Time.time > nextAttack)
        {
            Vector2 position = new Vector2();
            position.y = transform.position.y;
            position.x = transform.GetChild(1).transform.position.x;
            Instantiate(bombObject, position, bombObject.transform.rotation);
            nextAttack = Time.time + attackRate;
        }
    }

    void Movement()
    {
        //float horizontalInput = Input.GetAxis("Horizontal");//-1.0 ~ 1.0 包含小数
        //float horizontalInput = Input.GetAxisRaw("Horizontal");//-1.0 ~ 1.0  不包含小数
        float horizontalInput = joystick.Horizontal;
        if (horizontalInput > 0)
        {
            horizontalInput = 1;
        }else if (horizontalInput < 0)
        {
            horizontalInput = -1;
        }
        if (0.0f == horizontalInput)
        {
            horizontalInput = Input.GetAxisRaw("Horizontal");
        }
        rb.velocity = new Vector2(horizontalInput * speed, rb.velocity.y);

        if (0 != horizontalInput)
        {
            transform.localScale = new Vector3(horizontalInput, 1, 1);
        }
    }

    void CheckInput()
    {
        if (Input.GetButtonDown("Jump") && isGround)
        {
            canJump = true;
        }
        if (Input.GetKeyDown(KeyCode.B))
        {
            Attack();
        }
        if (Input.GetKeyDown(KeyCode.N))
        {
            KickBomb();
        }
        //0 left 1 right 2 middle
        if (Input.GetMouseButton(0))
        {
            Vector3 mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            Vector2 mousePos2D = new Vector2(mousePos.x, mousePos.y);
            RaycastHit2D hit = Physics2D.Raycast(mousePos2D, Vector2.zero);
           
            if (null != hit.collider)
            {
                Debug.Log("Hit " + hit.collider.gameObject.name);
            }
        }
    }

    public void JoystickJump()
    {
        canJump = true;
        Jump();
    }

    public void Jump()
    {
        if (canJump)
        {
            rb.velocity = new Vector2(rb.velocity.x, jumpForce);
            canJump = false;
            isJump = true;
            rb.gravityScale = 4;//重力
            gameObjectJump.SetActive(true);
            gameObjectJump.transform.position = transform.position + new Vector3(0, -0.1f, 0);
        }
    }

    void PhysicsCheck()
    {
        isGround = Physics2D.OverlapCircle(groundCheck.position, checkRadius, groundLayer);
        if (isGround)
        {
            rb.gravityScale = 1;
            isJump = false;
        }
    }

    public void OnDrawGizmos()
    {
        Gizmos.DrawWireSphere(groundCheck.position, checkRadius);
    }

    public void landFX()
    {
        gameObjectLand.SetActive(true);
        gameObjectLand.transform.position = transform.position + new Vector3(0, -1.0f, 0);
    }

    public void GetHit(float damage)
    {
        if (!anim.GetCurrentAnimatorStateInfo(1).IsName("Hit"))
        {
            health -= damage;
            if (health < 1)
            {
                health = 0;
                isDead = true;
                anim.SetBool("dead", isDead);
                GameManager.instance.GameOver();
            }
            else
            {
                anim.SetTrigger("hit");
            }
            UIManager.instance.UpdateHealth(health);
        }
    }

    public void KickBomb()
    {
        if (bombs.Count > 0)
        {
            Transform nearestBomb = bombs[0];
            for (int i = 1; i < bombs.Count; i++)
            {
                Transform kickBomb = bombs[i];
                if (Mathf.Abs(transform.position.x - kickBomb.position.x) < Mathf.Abs(transform.position.x - nearestBomb.position.x))
                {
                    nearestBomb = transform;
                }
            }
            int dir = transform.position.x < nearestBomb.position.x ? 1 : -1;
            nearestBomb.GetComponent<Rigidbody2D>().AddForce(new Vector2(dir, 0.5f) * 5, ForceMode2D.Impulse);
        }
    }

    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Bomb"))
        {
            bombs.Add(collision.transform);
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        bombs.Remove(collision.transform);
    }

    public void OnAppMessage(string msg)
    {
        Debug.Log(msg);
        Attack();
    }
}
