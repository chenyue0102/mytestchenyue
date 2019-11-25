import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Canvas{
    id:countDown;
    objectName: "root";
    visible: true;
    width:90;
    height:90;
    antialiasing:true;
    property int sectorWidth:7;//扇形宽度

    property string backgroundColor:"#f5ecd6";
    property string foregroundColor1:"#ff6f6a";
    property string textColor:"#4a4a4a";
    property int totalValue:0;
    property int curValue:0;
    property string font:"normal 40px 'Noto Sans S Chinese Medium'";
    property bool autoCountDown:false;//自动倒计时到0

    function countDownChanged()
    {
        checkStartTimer();
        countDown.requestPaint();
    }

    function checkStartTimer()
    {
        console.log("checkStartTimer");
        if (totalValue > 0 && curValue > 0 && autoCountDown)
        {
            console.log("checkStartTimer running");
            timerCountDown.running = true;
        }
    }

    onAutoCountDownChanged:countDownChanged();
    onTotalValueChanged:countDownChanged();
    onCurValueChanged: checkStartTimer();

    Timer{
        id:timerCountDown;
        interval: 1000;
        repeat: false;
        running: false;
        onTriggered:{
            var newValue = parent.curValue - 1;
            if (newValue >= 0 && autoCountDown)
            {
                parent.curValue = newValue;
                parent.requestPaint();
            }
            else
            {
                running = false;
            }
        }
    }

    //弧度to角度
    function radian2angle(radian)
    {
        return 2 * Math.PI / 360;
    }
    //角度to弧度
    function angle2radian(angle)
    {
        return 2 * Math.PI * angle / 360;
    }

    onPaint: {
        var radius = width / 2;
        var centerX = width / 2;
        var centerY = height / 2;
        var rotateAngle = -90;//起始点旋转角度
        var degree = totalValue == 0 ? 0 : 360.0 * curValue / totalValue;

        var ctx = countDown.getContext("2d");
        ctx.fillStyle ="#ff0000";
        ctx.clearRect(0, 0, width, height);

        ctx.lineWidth = sectorWidth;

        //已经消耗的弧
        ctx.strokeStyle=backgroundColor;
        ctx.beginPath();
        if (0 == degree)
        {
            ctx.arc(centerX, centerY, radius - sectorWidth,
                    angle2radian(0),angle2radian(360), false);
        }
        else
        {
            ctx.arc(centerX, centerY, radius - sectorWidth,
                    angle2radian(0 + rotateAngle + degree),angle2radian(0 + rotateAngle), false);
        }
        ctx.stroke();
        ctx.closePath();

        //画还剩的弧
        ctx.beginPath();
        ctx.strokeStyle=foregroundColor1;
        ctx.arc(centerX, centerY, radius - sectorWidth,
                angle2radian(0 + rotateAngle), angle2radian(degree + rotateAngle), false);
        ctx.stroke();
        ctx.closePath();

        //绘制文字
        ctx.fillStyle = textColor;
        ctx.font =font;
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(String(curValue), centerX, centerY);

        ctx.restore();
    }

}

