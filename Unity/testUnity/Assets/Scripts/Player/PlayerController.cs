using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    private Rigidbody2D rb;
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

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        CheckInput();
    }

    private void FixedUpdate()
    {
        PhysicsCheck();
        Movement();
        Jump();
    }

    public void Attack()
    {
        if (Time.time > nextAttack)
        {
            Instantiate(bombObject, transform.position, bombObject.transform.rotation);
            nextAttack = Time.time + attackRate;
        }
    }

    void Movement()
    {
        //float horizontalInput = Input.GetAxis("Horizontal");//-1.0 ~ 1.0 包含小数
        float horizontalInput = Input.GetAxisRaw("Horizontal");//-1.0 ~ 1.0  不包含小数
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
    }

    void Jump()
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
}
