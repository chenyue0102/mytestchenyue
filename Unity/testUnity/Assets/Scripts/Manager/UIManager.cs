using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    public static UIManager instance;


    public GameObject healthBar;
    public GameObject pauseMenu;
    public GameObject gameOverPanel;
    public Slider bossHealthBar;
    public void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
        //DontDestroyOnLoad
    }

    public void UpdateHealth(float currentHealth)
    {
        healthBar.transform.GetChild(0).gameObject.SetActive(currentHealth >= 1);
        healthBar.transform.GetChild(1).gameObject.SetActive(currentHealth >= 2);
        healthBar.transform.GetChild(2).gameObject.SetActive(currentHealth >= 3);
    }

    public void PauseGame()
    {
        pauseMenu.SetActive(true);

        Time.timeScale = 0;//暂停游戏
    }
    
    public void ResumeGame()
    {
        pauseMenu.SetActive(false);
        Time.timeScale = 1;
        string testMsg = "{\"msgId\":100}";
        MessageBriage.GetInstance().OnAppMessage(testMsg);
    }

    public void SetBossMaxHealth(float health)
    {
         bossHealthBar.maxValue = health;
        bossHealthBar.value = health;
    }

    public void SetBossCurrentHealth(float health)
    {
         bossHealthBar.value = health;
    }

    public void setGameOverPanelVisible(bool visible)
    {
        gameOverPanel.SetActive(visible);
    }


}
