package com.xixi.observe.entity;

import com.wf.captcha.*;
import com.wf.captcha.base.Captcha;
import lombok.Data;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.LoggerFactory;

import java.awt.*;
import java.util.Objects;

@Data
public class LoginProperties {
    private static final org.slf4j.Logger logger = LoggerFactory.getLogger(LoginProperties.class);
    private LoginCode loginCode;

    public Captcha getCaptcha(){
        if (Objects.isNull(loginCode)){
            loginCode = new LoginCode();
            if (Objects.isNull(loginCode.getCodeType())){
                loginCode.setCodeType(LoginCode.LoginCodeEnum.ARITHMETIC);
            }
        }
        return switchCaptcha(loginCode);
    }

    private Captcha switchCaptcha(LoginCode loginCode){
        Captcha captcha = null;
        synchronized (this){
            switch(loginCode.getCodeType()){
                case ARITHMETIC:
                    captcha = new FixedArithmeticCaptcha(loginCode.getWidth(), loginCode.getHeight());
                    captcha.setLen(loginCode.getLength());
                    break;
                case CHINESE:
                    captcha = new ChineseCaptcha(loginCode.getWidth(), loginCode.getHeight());
                    captcha.setLen(loginCode.getLength());
                    break;
                case CHINESE_GIF:
                    captcha = new ChineseGifCaptcha(loginCode.getWidth(), loginCode.getHeight());
                    captcha.setLen(loginCode.getLength());
                    break;
                case GIF:
                    captcha = new GifCaptcha(loginCode.getWidth(), loginCode.getHeight());
                    captcha.setLen(loginCode.getLength());
                    break;
                case SPEC:
                    captcha = new SpecCaptcha(loginCode.getWidth(), loginCode.getHeight());
                    captcha.setLen(loginCode.getLength());
                    break;
                default:
                    logger.warn("unknown code type:" + loginCode.getCodeType());
                    break;
            }
        }
        if (StringUtils.isNotBlank(loginCode.getFontName())){
            captcha.setFont(new Font(loginCode.getFontName(), Font.PLAIN, loginCode.getFontSize()));
        }
        return captcha;
    }

    static class FixedArithmeticCaptcha extends ArithmeticCaptcha{
        public FixedArithmeticCaptcha(int width, int height){
            super(width, height);
        }

        @Override
        protected char[] alphas(){
            // 生成随机数字和运算符
            int n1 = num(1, 10), n2 = num(1, 10);
            int opt = num(3);

            // 计算结果
            int res = new int[]{n1 + n2, n1 - n2, n1 * n2}[opt];
            // 转换为字符运算符
            char optChar = "+-x".charAt(opt);

            this.setArithmeticString(String.format("%s%c%s=?", n1, optChar, n2));
            this.chars = String.valueOf(res);

            return chars.toCharArray();
        }
    }
}
