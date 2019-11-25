import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import "./" as Live

Rectangle{
    id:waitModuleResult;
    objectName: "root";
    visible: true;
    width:1500;
    height:1125;
    color: "#10ff0000";

    property color scoreContainerBackgroundColor:"#fff2f1";
    property color headImageBorderColor:"#ff504a";
    property string headImagePath:'';
    property int personalPoint:0;
    property int groupContribute:0;
    property int corretCount:0;
    property int totalCount:0;
    property int cangwuScore:0;
    property int bihaiScore:0;
    property bool cangwuLeadIconVisible:false;
    property bool bihaiLeadIconVisible:false;

    //设置实际分辨率
    function setContainerSize(w, h){
        waitModuleResult.scale = w / waitModuleResult.width;
    }

    function setModuleSummaryMyInfo(leadSecond, headImagePath, myTeamType)
    {
        countDown.curValue = countDown.totalValue = leadSecond;
        waitModuleResult.headImagePath = headImagePath;
        //1红队 2蓝队
        if (1 == myTeamType)
        {
            waitModuleResult.scoreContainerBackgroundColor = "#fff2f1";
            headImageBorderColor = "#ff504a";
        }
        else
        {
            waitModuleResult.scoreContainerBackgroundColor = "#eff5ff";
            headImageBorderColor = "#84bbff";
        }
    }
    function setModuleSummary(personalPoint, groupContribute, corretCount, totalCount, cangwuScore, bihaiScore)
    {
        waitModuleResult.personalPoint = personalPoint;
        waitModuleResult.groupContribute = groupContribute;
        waitModuleResult.corretCount = corretCount;
        waitModuleResult.totalCount = totalCount;
        waitModuleResult.cangwuScore = cangwuScore;
        waitModuleResult.bihaiScore = bihaiScore;
        if (cangwuScore > bihaiScore)
        {
            cangwuLeadIconVisible = true;
            bihaiLeadIconVisible = false;
        }
        else if (bihaiScore > cangwuScore)
        {
            cangwuLeadIconVisible = false;
            bihaiLeadIconVisible = true;
        }
        else
        {
            cangwuLeadIconVisible = false;
            bihaiLeadIconVisible = false;
        }
    }

    function test()
    {
        setModuleSummaryMyInfo(30, "./headimg.png", 2);
        setModuleSummary(1,2,3,4,5,6);
    }

    Component.onCompleted: {
        test();
    }

    Rectangle{
        id:mainPage;
        color:"#ffffff";
        width:1320;
        height:1000;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;

        Live.CountDown{
            id:countDown;
            totalValue: 0;
            curValue: 0;
            autoCountDown: true;
            anchors.left: parent.left;
            anchors.leftMargin: 57;
            anchors.top: parent.top;
            anchors.topMargin: 38;
        }
        Text{
            id:tipSecondText;
            font.pixelSize: 76;
            font.family: 'Noto Sans S Chinese Bold';
            text: qsTr("好棒哦，提前0秒完成");
            property int leadSeconds:0;

            anchors.top: parent.top;
            anchors.topMargin: 96;
            anchors.horizontalCenter: parent.horizontalCenter;

            onLeadSecondsChanged: {
                tipSecondText.text = qsTr("好棒哦，提前") + tipSecondText + qsTr("秒完成");
            }
        }

        //积分区域
        Rectangle{
            id:scoreContainer;
            width:1036;
            height:158;
            radius: 79;
            color:waitModuleResult.scoreContainerBackgroundColor;

            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 234;

            //头像和边框
            Rectangle{
                id:headImageContainer;
                width:120;
                height:120;
                color:waitModuleResult.headImageBorderColor;
                radius: width / 2;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: 19;

                Image{
                    id:headImage;
                    width:110;
                    height:110;
                    visible: false;
                    source: waitModuleResult.headImagePath;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    anchors.verticalCenter: parent.verticalCenter;
                }
                //图片的掩码
                Rectangle{
                    id:roundMask;
                    visible: false;
                    width:headImage.width;
                    height:headImage.height;
                    radius:headImage.width / 2;
                    color:"black";
                }
                OpacityMask{
                    id:maskImage;
                    anchors.fill: headImage;
                    source:headImage;
                    maskSource:roundMask;
                }
            }

            Text{
                id:answerRightTip;
                text:qsTr("答对题目");
                font.pixelSize: 28;
                font.family: 'Noto Sans S Chinese Medium';
                color: "#4a4a4a";
                anchors.top: parent.top;
                anchors.topMargin: 37;
                anchors.left: parent.left;
                anchors.leftMargin: 247;
            }
            Text
            {
                id:teamScoreTip;
                text:qsTr("战队得分");
                font:answerRightTip.font;
                color: answerRightTip.color;
                anchors.top: answerRightTip.top;
                anchors.left: parent.left;
                anchors.leftMargin: 521;
            }
            Text{
                id:myScoreTip;
                text:qsTr("个人得分");
                font:answerRightTip.font;
                color: answerRightTip.color;
                anchors.top: answerRightTip.top;
                anchors.left: parent.left;
                anchors.leftMargin: 778;
            }
            Image{
                id:answerRightIcon;
                source: "./answerRight.png";

                anchors.top: parent.top;
                anchors.topMargin: 80;
                anchors.left: parent.left;
                anchors.leftMargin: 222;
            }
            Text{
                id:answerRightCount;
                font.pixelSize: 36;
                font.family: 'Noto Sans S Chinese Medium';
                color: "#4a4a4a";
                text:waitModuleResult.corretCount;
                anchors.verticalCenter: answerRightIcon.verticalCenter;
                anchors.left: answerRightIcon.right;
                anchors.leftMargin: 7;
            }
            Text{
                id:answerTotalCount;
                font.pixelSize: 22;
                font.family: 'Noto Sans S Chinese Regular';
                color: "#666666";
                text:qsTr("(共") + waitModuleResult.totalCount + qsTr("题)");
                anchors.verticalCenter: answerRightIcon.verticalCenter;
                anchors.left: answerRightCount.right;
                anchors.leftMargin: 7;
            }
            Image{
                id:teamScoreIcon;
                source: "./power.png";
                width:40;
                height:40;
                anchors.verticalCenter: answerRightIcon.verticalCenter;
                anchors.left: parent.left;
                anchors.margins: 474;
            }
            Text{
                id:teamScore;
                font:answerRightCount.font;
                anchors.verticalCenter: answerRightIcon.verticalCenter;
                anchors.left: teamScoreIcon.right;
                anchors.leftMargin: 7;
                color:answerRightCount.color;
                text:waitModuleResult.groupContribute;
            }
            Text{
                font:answerTotalCount.font;
                color:answerTotalCount.color;
                anchors.verticalCenter: answerRightIcon.verticalCenter;
                anchors.left: teamScore.right;
                anchors.leftMargin: 7;
                text:qsTr("战队火力值");
            }
            Image{
                id:persionalIcon;
                source: "./score.png";
                width:40;
                height: 40;
                anchors.verticalCenter: answerRightIcon.verticalCenter;
                anchors.left: parent.left;
                anchors.leftMargin: 772;
            }

            Text{
                id:persionalScore;
                font:answerRightCount.font;
                color:answerRightCount.color;
                text:waitModuleResult.personalPoint;
                anchors.verticalCenter: answerRightIcon.verticalCenter;
                anchors.left: persionalIcon.right;
                anchors.leftMargin: 7;
            }
            Text{
                font:answerTotalCount.font;
                color:answerTotalCount.color;
                anchors.verticalCenter: answerRightIcon.verticalCenter;
                anchors.left: persionalScore.right;
                anchors.leftMargin: 7;
                text:qsTr("积分");
            }
        }

        //pk区域
        Rectangle{
            id:pkContainer;
            height:500;
            anchors.top: scoreContainer.bottom;
            anchors.topMargin: 58;
            anchors.left: parent.left;
            anchors.leftMargin: 86;
            anchors.right: parent.right;
            anchors.rightMargin: 86;
            //color:"#2000ff00";

            Rectangle{
                id:bihaiTeamContainer;
                width:264+38;
                anchors.left: parent.left;
                anchors.top: parent.top;

                Image{
                    id:bihaiTeamLead;
                    source: "./leadIcon.png";
                    anchors.top: parent.top;
                    anchors.right: parent.right;
                    visible: waitModuleResult.bihaiLeadIconVisible;
                }
                Image{
                    id:bihaiTeamIcon;
                    width:264;
                    height:292;
                    source: "./team2.png";
                    anchors.horizontalCenter: parent.horizontalCenter;
                    anchors.top: parent.top;
                    anchors.topMargin: 59;
                }
                Text{
                    id:bihaiTeamScore;
                    text:waitModuleResult.bihaiScore;
                    height:50;
                    anchors.top: bihaiTeamIcon.bottom;
                    anchors.topMargin: 30;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    font.family: 'Noto Sans S Chinese Medium';
                    font.pixelSize: 50;
                    color: "#006dff";
                    verticalAlignment:Text.AlignVCenter;
                }

                Text{
                    height: 50;
                    anchors.top: bihaiTeamScore.bottom;
                    anchors.topMargin: 3;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    text:qsTr("火力值");
                    font.family: 'Noto Sans S Chinese Medium';
                    font.pixelSize: 28;
                    color: "#006dff";
                    leftPadding: 40;
                    //将image放入text中，一起居中对齐
                    Image{
                        id:bihaiPowerIcon;
                        source: './power.png';
                    }
                }
            }


            Rectangle{
                id:cangwuTeamContainer;
                width:bihaiTeamContainer.width;
                height: bihaiTeamContainer.height;
                anchors.top: parent.top;
                anchors.right:  parent.right;

                Image{
                    id:cangwuTeamLead;
                    source: "./leadIcon.png";
                    anchors.top: parent.top;
                    anchors.right: parent.right;
                    visible: waitModuleResult.cangwuLeadIconVisible
                }
                Image{
                    id:cangwuTeamIcon;
                    width:264;
                    height:292;
                    source: "./team1.png";
                    anchors.horizontalCenter: parent.horizontalCenter;
                    anchors.top: parent.top;
                    anchors.topMargin: 59;
                }

                Text{
                    id:cangwuTeamScore;
                    text:waitModuleResult.cangwuScore;
                    height:50;
                    anchors.top: cangwuTeamIcon.bottom;
                    anchors.topMargin: 30;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    font.family: 'Noto Sans S Chinese Medium';
                    font.pixelSize: 50;
                    color: "#ff1a12";
                    verticalAlignment:Text.AlignVCenter;
                }
                Text{
                    height: 50;
                    anchors.top: cangwuTeamScore.bottom;
                    anchors.topMargin: 3;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    text:qsTr("火力值");
                    font.family: 'Noto Sans S Chinese Medium';
                    font.pixelSize: 28;
                    color: "#ff1a12";
                    leftPadding: 40;
                    //将image放入text中，一起居中对齐
                    Image{
                        id:cangwuPowerIcon;
                        source: './power.png';
                    }
                }
            }
        }
    }
}

