package com.xixi.observe;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.test.context.SpringBootTest;

import java.lang.reflect.Type;

@SpringBootTest
public class TemplateTest {
    private static final Logger logger = LoggerFactory.getLogger(TemplateTest.class);

    public static class TestBase{

    }

    public static class TestA extends TestBase{
        public int a;
    }
    private interface CallFun<T extends TestBase>{
         void run(T t);
    }

    public <T extends TestBase> void callFun(String text, CallFun<T> imp, Type type){
        try{
            T t = new Gson().fromJson(text, type);
            imp.run(t);
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    @Test
    public void testTemplate(){
        String s = "{\"a\":1}";
        callFun(s, this::onFunA, new TypeToken<TestA>(){}.getType());
    }

    private void onFunA(TestA t){
        logger.warn("testa:" + t.a);
    }
}
