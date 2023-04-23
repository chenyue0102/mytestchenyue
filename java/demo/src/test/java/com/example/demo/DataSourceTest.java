package com.example.demo;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DataSourceTest {
    @Autowired
    private DataSource dataSource;

    @Test
    public void setDataSourceTest()throws SQLException{
        try{
            Class.forName("com.mysql.jdbc.Driver");
            String URL = "jdbc:mysql://localhost:3306/test?useUnicode=true&serverTimeZone=Asia/Shanghai&characterEncoding=utf8&autoReconnect=true&usesSSL=false&allowMultiQueries=true&useAffectedRows=true";
            Connection connection = DriverManager.getConnection(URL,"root", "root");
            //Connection connection = dataSource.getConnection();
            System.out.println(connection != null);
            connection.close();
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
