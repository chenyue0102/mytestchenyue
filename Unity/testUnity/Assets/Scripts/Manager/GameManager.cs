using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    private static string HEALTH_NAME = "playerHealth";
    public static GameManager instance;

    public PlayerController player;
    public bool gameOver;
    public List<Enemy> liveEnemy = new List<Enemy>();

    private Door doorExit;

    public void Awake()
    {
        if (null == instance)
        {
            instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
        doorExit = FindObjectOfType<Door>();
        player = FindObjectOfType<PlayerController>();
    }

    public void GameOver()
    {
        gameOver = true;
        UIManager.instance.setGameOverPanelVisible(true);
    }

    public void RestartScene()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    public void addEnemy(Enemy enemy)
    {
        liveEnemy.Add(enemy);
    }

    public void removeEnemy(Enemy enemy)
    {
        liveEnemy.Remove(enemy);
        if (liveEnemy.Count == 0)
        {
            doorExit.OpenDoor();
        }
    }

    public void NextLevel()
    {
        SaveData();
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void QuitGame()
    {
        Application.Quit();
    }

    public float LoadHealth()
    {
        if (!PlayerPrefs.HasKey(HEALTH_NAME))
        {
            PlayerPrefs.SetFloat(HEALTH_NAME, 3F);
        }
        return PlayerPrefs.GetFloat(HEALTH_NAME);
    }

    public void SaveData()
    {
        PlayerPrefs.SetFloat(HEALTH_NAME, player.health);
        //PlayerPrefs.Save();
    }
}
