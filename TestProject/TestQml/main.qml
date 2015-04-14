import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0
import test.QUINotify 1.0

Window {
    id:windowInstance
    title: UserInfo.userNickName
    width: 640
    height: 480
    visible:true
    property int currentWindowState:0
    flags:Qt.Dialog | Qt.FramelessWindowHint

    Component.onCompleted: {
    }

    onWindowStateChanged: {
        currentWindowState = windowState;
        if (windowState & Qt.WindowMaximized){
            if (systemButtonMax.visible)
            systemButtonMax.visible = false;
            systemButtonRestore.visible = true;
        }
        else{
            if (systemButtonRestore.visible){
                systemButtonMax.visible = true;
                systemButtonRestore.visible = false;
            }
        }
    }
	QUINotify{
        id:uiNotify
	}

    Connections{
        target:UserInfo
        onUserNickNameChanged:{
            console.log("onuserNickNameChanged");
        }
    }

    Rectangle {
        id:containerInstace
        border.color: "blue"
        border.width: 1
        color:"white"
        anchors.fill: parent
        focus:true
        property int lastX: 0
        property int lastY:0
        property bool isPressed:false
        Component.onCompleted: {
            systemButtonRestore.visible = false;
        }

        MouseArea{
            id:containerMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onPressed:{
                if (mouse.button == Qt.LeftButton){
                    containerInstace.lastX = mouse.x;
                    containerInstace.lastY = mouse.y;
                    containerInstace.isPressed = true;
                }
            }
            onReleased:{
                if (mouse.button == Qt.LeftButton){
                    containerInstace.lastX = 0;
                    containerInstace.lastY = 0;
                    containerInstace.isPressed = false;
                    containerInstace.mapFromItem()
                    containerMouseArea.mapToGlobal
                }
            }
            onPositionChanged:{
                if (!(currentWindowState & Qt.WindowMaximized)){
                    if (containerInstace.isPressed){
                        var nOffsetX = mouse.x - containerInstace.lastX, nOffsetY = mouse.y - containerInstace.lastY;
                        windowInstance.x += nOffsetX;
                        windowInstance.y += nOffsetY;
                    }
                }
            }

            onDoubleClicked:{
                if (mouse.button == Qt.LeftButton){
                    if (systemButtonMax.visible){
                        windowInstance.showMaximized();
                    }
                    else if (systemButtonRestore.visible){
                        windowInstance.showNormal();
                    }
                }
            }
        }

        Image{
            id:systemIcon
            //source: "file///DolphinIcon.png"
            anchors.left: parent.left
            anchors.top: parent.top
        }

        Text{
            id:systemTitle
            text : windowInstance.title
            color: "black"
            anchors.left: systemIcon.visible ? systemIcon.right : parent.left
            anchors.top : parent.top
        }

        Button {
            id:systemButtonClose
            text:qsTr("关闭")
            anchors.right: parent.right
            anchors.top: parent.top
            onClicked:
            {
                Qt.quit();
            }
        }

        Button {
            id:systemButtonMin
            text: qsTr("最小化")
            anchors.right:systemButtonMax.visible ? systemButtonMax.left : systemButtonRestore.left
            anchors.top:parent.top
            onClicked: {
                windowInstance.showMinimized();
            }
        }

        Button {
            id:systemButtonMax
            text:qsTr("最大化")
            anchors.right:systemButtonClose.left
            anchors.top:parent.top
            onClicked: {
                windowInstance.showMaximized();
            }
        }

        Button {
            id:systemButtonRestore
            text:qsTr("还原")
            anchors.right:systemButtonClose.left
            anchors.top:parent.top
            onClicked: {
                windowInstance.showNormal();
            }
        }

        Button {
            text: qsTr("Hello World")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
			onClicked: {
                uiNotify.notifyEvent(1, "kingmax");
            }
        }
    }


}
