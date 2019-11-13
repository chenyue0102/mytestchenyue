import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Rectangle{
    id:questionResult;
    objectName: "root";
    visible: true;
    width:840;
    height:840;
    color: "#00ff0000";
    border.color: "#c51e1e"
    signal playFinished;
    scale: 0.8;

    Button{
        id:wrongBtn;
        text: qsTr("wrong");
        onClicked: {
            console.log("Button onClicked");
            setResultGif(false,"./wrong.gif");
        }
    }
    Button{
        text: qsTr("right");
        anchors.left:wrongBtn.right;
        onClicked: {
            console.log("Button onClicked");
            setResultGif(false,"./right.gif");
        }
    }


    //设置结果gif
    function setResultGif(win, gifPath){
        console.log("setResultGif" + win + gifPath);
        resultGif.source = gifPath;
        resultGif.currentFrame = 0;
        resultGif.playing=true;
        resultGif.paused=false;
        console.log("----------------------------------setResultGif "
                    + " status=" + resultGif.status
                    + " playing=" + resultGif.playing
                    + " paused=" + resultGif.paused
                    + " source=" + resultGif.source
                    + " currentFrame=" + resultGif.currentFrame
                    + " frameCount=" + resultGif.frameCount
                    );
        if (win)
        {
            light1.running = true;
            light2.running = true;
        }
    }

    function setResultScore(score, fireScore)
    {
        resultScore.score=score;
        resultScore.fireScore=fireScore;
        resultScore.running = true;
    }

    function test(){
        console.log("test");
        setResultGif(true,"./right.gif");
        setResultScore(100,200);
    }

    //测试代码
    Component.onCompleted: {
        //test();
    }


    Rectangle{
        id:resultScore;
        width:465;
        height:110;
        z:11;
        radius: 55;
        border.color: "#ffffff";
        opacity: 0;
        anchors.horizontalCenter: questionResult.horizontalCenter;
        property bool running:false;
        property int score:0;
        property int fireScore:0;

        SequentialAnimation{
            id:resultScoreAnimation;
            loops: 1;
            running: resultScore.running;

            PauseAnimation {
                duration: 200;
            }
            ParallelAnimation{
                PropertyAnimation{
                    target: resultScore;
                    property: "opacity";
                    from:0;
                    to:100;
                    duration: 240;
                }
                PropertyAnimation{
                    target: resultScore;
                    property:"y";
                    from:626;
                    to:602;
                    duration: 240;
                }
            }
        }

        Text{
            id:score;
            font.pixelSize:36;
            color: "#4a4a4a";
            text: "+"+parent.score;
            anchors.horizontalCenter:resultScore.horizontalCenter;
            anchors.horizontalCenterOffset: -100;
            anchors.top: resultScore.top;
            anchors.topMargin: 14;
        }
        Text{
            id:fireScore;
            font.pixelSize:36;
            color: "#4a4a4a";
            text:"+"+parent.fireScore;
            anchors.horizontalCenter: resultScore.horizontalCenter;
            anchors.horizontalCenterOffset:+100;
            anchors.top: resultScore.top;
            anchors.topMargin: 14;
        }
        Image{
            id:scoreImage;
            source: "./score.png";
            anchors.top: resultScore.top;
            anchors.topMargin: 58;
            anchors.left: resultScore.left;
            anchors.leftMargin: 80;
        }
        Text{
            id:scoreTip;
            text:qsTr("积分");
            font.pixelSize: 28;
            color:"#4a4a4a";
            anchors.top: scoreImage.top;
            anchors.topMargin: 5;
            anchors.left:scoreImage.right;
            anchors.leftMargin: 15;
        }
        Image{
            id:fireImage;
            source:"./power.png";
            anchors.top: scoreImage.top;
            anchors.left: parent.left;
            anchors.leftMargin: 240;
        }
        Text{
            text:qsTr("战队火力值");
            font.pixelSize: 28;
            color:"#4a4a4a";
            anchors.top:scoreTip.top;
            anchors.left: fireImage.right;
            anchors.leftMargin: 2;
        }
    }

    //gif
    AnimatedImage{
        id:resultGif;
        z:10;
        //source:"./test.gif";
        onCurrentFrameChanged:{
            if (currentFrame + 1 == frameCount)
            {
                playing = false;
                playFinished();
            }
        }
    }

    //背光
    Image{
        id:light1;
        source: "./light.png";
        z:9;
        //初始动画属性
        opacity: 0;
        scale: 0.7;
        rotation: 0;
        property bool running:false;

        //25帧每秒，一帧40毫秒
        SequentialAnimation {
            loops: Animation.Infinite;
            running: light1.running;
            //等待5帧
            PauseAnimation{
                duration: 200;
            }
            //动画1
            ParallelAnimation{
                PropertyAnimation{
                    target: light1;
                    property: "opacity";
                    from: 0.0;
                    to:1.0;
                    duration: 560;
                }
                PropertyAnimation{
                    target: light1;
                    property: "rotation";
                    from:0.0;
                    to:15;
                    duration: 560;
                }
                PropertyAnimation{
                    target: light1;
                    property: "scale";
                    from:0.7;
                    to:1.0;
                }
            }
            //动画2
            ParallelAnimation{
                PropertyAnimation{
                    target: light1;
                    property:"opacity";
                    from:1.0;
                    to:0.0;
                    duration: 560;
                }
                PropertyAnimation{
                    target: light1;
                    property: "rotation";
                    from:15;
                    to:30;
                    duration: 560;
                }
                PropertyAnimation{
                    target: light1;
                    property: "scale";
                    from:1.0;
                    to:0.7;
                    duration: 560;
                }
            }
            //空两帧
            PauseAnimation{
                duration: 80;
            }
        }
    }

    Image{
        id:light2;
        source: "./light.png";
        z:8;
        //初始动画属性
        opacity:0;
        rotation: 0;
        scale: 0.7;
        property bool running:false;
        SequentialAnimation{
            running: light2.running;
            loops: Animation.Infinite;
            //等待5帧,200毫秒
            PauseAnimation{
                duration: 200;
            }
            ParallelAnimation{
                PropertyAnimation{
                    target: light2;
                    property: "opacity";
                    from:0;
                    to:1;
                    duration: 560;
                }
                PropertyAnimation{
                    target: light2;
                    property: "rotation";
                    from:0;
                    to:-15;
                    duration: 560;
                }
                PropertyAnimation{
                    target: light2;
                    property: "scale";
                    from:0.7;
                    to:1;
                    duration: 560;
                }
            }
            ParallelAnimation{
                PropertyAnimation{
                    target: light2;
                    property: "opacity";
                    from:1;
                    to:0;
                    duration: 560;
                }
                PropertyAnimation{
                    target: light2;
                    property:"rotation";
                    from:-15;
                    to:-30;
                    duration: 560;
                }
                PropertyAnimation{
                    target: light2;
                    property: "scale";
                    from:1;
                    to:0.7;
                    duration: 560;
                }
            }

            PauseAnimation {
                duration: 80;
            }
        }
    }
}

