package com.xixi.observe.listener;

import com.xixi.observe.dao.PrivateKeyDao;
import com.xixi.observe.entity.PrivateKey;
import com.xixi.observe.util.TokenUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.context.support.WebApplicationContextUtils;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;
import java.sql.Timestamp;
import java.util.logging.Logger;
@WebListener
public class MyListener implements ServletContextListener {
    @Autowired
    PrivateKeyDao privateKeyDao;

    @Override
    public void contextInitialized(ServletContextEvent event){
        //解决ServletContextListener中privateKeyDao为null
        WebApplicationContextUtils.getRequiredWebApplicationContext(event.getServletContext())
                .getAutowireCapableBeanFactory().autowireBean(this);
        //初始化
        long time = System.currentTimeMillis();
        Timestamp enableTime = new Timestamp(time);
        PrivateKey privateKey = privateKeyDao.getPrivateKey(enableTime, enableTime);
        if (null == privateKey){
            System.exit(-1);
        }
        String base64PrivateKey = privateKey.getPrivateKey().replace("\n", "");
        Logger.getGlobal().warning("contextInitialized:" + "exp:" + privateKey.getExpiration().toString());
        TokenUtil.getInstance().setRSAKey(base64PrivateKey, privateKey.getExpiration().getTime());
    }

    @Override
    public void contextDestroyed(ServletContextEvent event){
        //备份
    }
}
