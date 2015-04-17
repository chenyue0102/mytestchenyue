import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0
import test.QUINotify 1.0
import QtQuick.Layouts 1.1
import test.QContectModel 1.0
//import "Controls"

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

        Grid{
            anchors.right: parent.right
            anchors.top:parent.top
            anchors.topMargin: 30
            anchors.bottom: parent.bottom
            width:parent.width / 2
            height:parent.height
            columnSpacing:4
            rowSpacing:4
            Button {
                text: qsTr("改变标题")
                onClicked: {
                    uiNotify.notifyEvent(1, "改变标题");
                }
            }
            Button {
                text: qsTr("删除选中行")
                onClicked: {
                    var curIndex = contentList.currentIndex;
                    uiNotify.notifyEvent(2, curIndex.toString());
                }
            }
            Button {
                text: qsTr("增加行")
                onClicked: {
                    var curIndex = contentList.currentIndex;
                    uiNotify.notifyEvent(3, curIndex.toString());
                }
            }
            Button {
                text: qsTr("头像变灰")
                onClicked: {
                    var curIndex = contentList.currentIndex;
                    uiNotify.notifyEvent(4, curIndex.toString());
                }
            }
            Button {
                text: qsTr("头像变亮")
                onClicked: {
                    var curIndex = contentList.currentIndex;
                    uiNotify.notifyEvent(5, curIndex.toString());
                }
            }
            Button {
                text: qsTr("log ")
                onClicked: {
                    var curIndex = contentList.currentIndex;
                    var item = ContectModel[contentList.currentIndex];
                    console.log(typeof(item));
                    //uiNotify.notifyEvent(5, curIndex.toString());
                }
            }
        }


        ListView{
            id:contentList
            anchors.left: parent.left
            anchors.leftMargin: 4
            anchors.top: parent.top
            anchors.topMargin: 20
            width:parent.width / 2
            height:parent.height - 30
            clip:true
            focus:true;
            highlightMoveDuration: 0

            //垂直滚动条
            ScrollBar {
                id: verticalScrollBar
                width: 12; height: contentList.height
                anchors.right: contentList.right
                opacity: 0
                orientation: Qt.Vertical
                position: contentList.visibleArea.yPosition
                pageSize: contentList.visibleArea.heightRatio
            }
            //移动到滚动条上的鼠标事件
            MouseArea{
                id:verticalScrollBarMouseArea
                anchors.fill: verticalScrollBar
                hoverEnabled:true
                propagateComposedEvents:true
                onEntered: {
                    console.log("onEntered");
                    if (contentList.visibleArea.heightRatio < 1.0)
                    {
                        verticalScrollBar.opacity = 1;
                    }
                }
                onExited: {
                    console.log("onExited");
                    verticalScrollBar.opacity = 0;
                }
            }


            Connections{
                target:verticalScrollBar
                onButtonClicked:{
                    console.log(buttonName);
                }
            }

             states: State {
                name:"showScrollBar";
                when:contentList.flicking
                PropertyChanges { target: verticalScrollBar; opacity: 1 }
             }
             transitions: Transition {
                 NumberAnimation { properties: "opacity"; duration: 500; easing.type: Easing.InOutQuad }
             }

            //动画
//            addDisplaced: Transition {
//                    NumberAnimation { properties: "x,y"; duration: 300 }
//                }

            property var grayImageCache:[]
            highlight: Rectangle{
                color:"#fffdeba8"
            }
            section.property:"groupid"
            section.criteria:ViewSection.FullString
            section.delegate:sectionHeader;
            Component{
                id:sectionHeader;
                Rectangle{
                    width:parent.width
                    height:childrenRect.height
                    color:"lightsteelblue"
                    Text{
                        text:section
                    }
                }
            }

            model:ContectModel

            /*model:ListModel{
                id:contentModel
                Component.onCompleted:{
                    append({name:"张三",groupid:"0",gray:true,headImage:"file:///D:\\JJ比赛外网测试\\LobbyTheme\\HeadImage\\H00016.jpg"});
                    append({name:"李四",groupid:"0",gray:true,headImage:"file:///D:\\JJ比赛外网测试\\LobbyTheme\\HeadImage\\H00017.jpg"});
                    append({name:"朱武",groupid:"1",gray:true,headImage:"file:///D:\\JJ比赛外网测试\\LobbyTheme\\HeadImage\\H00018.jpg"});
                    append({name:"杨柳",groupid:"1",gray:true,headImage:"file:///D:\\JJ比赛外网测试\\LobbyTheme\\HeadImage\\H00019.jpg"});
                    append({name:"侯七",groupid:"2",gray:false,headImage:"file:///D:\\JJ比赛外网测试\\LobbyTheme\\HeadImage\\H00020.jpg"});
                    append({name:"马八",groupid:"2",gray:false,headImage:"file:///D:\\JJ比赛外网测试\\LobbyTheme\\HeadImage\\H00021.jpg"});
                }
            }*/
            delegate:Item{
                id:wrapper
                height:50
                width:parent.width


                Canvas{
                    property var myState:headImage + gray
                    onMyStateChanged:
                    {
                        //console.log("onMyStateChanged");
                        requestPaint();
                    }

                    id:itemHeadImage
                    height: 42
                    width: 42
                    //fillMode: Image.PreserveAspectCrop
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 4
                    //source: headImage
                    onPaint:{
                        //console.log("nickname:" + name + " gray:" + gray);
                        if (headImage == undefined)
                        {
                            console.log("headimage undefined");
                            return;
                        }


                        var ctx = getContext("2d");
                        var bDrawImage = false, bDrawGrayImage = false;
                        if (gray)
                        {
                            var grayImageFileName = headImage + ".gray";
                            if (!wrapper.ListView.view.grayImageCache.hasOwnProperty(grayImageFileName))
                            {
                                if (!wrapper.ListView.view.grayImageCache.hasOwnProperty(headImage))
                                {
                                    bDrawImage = true;
                                }
                                else
                                {
                                    var sourceImage = wrapper.ListView.view.grayImageCache[headImage];
                                    var grayImageData = ctx.createImageData(sourceImage.width, sourceImage.height);
                                    var limit = sourceImage.width * sourceImage.height * 4;
                                    for (var i = 0; i < limit; i += 4)
                                    {
                                        //(r * 11 + g * 16 + b * 5) / 32
                                        var grayvalue = (sourceImage.data[i] * 11 + sourceImage.data[i + 1] * 16 + sourceImage.data[i + 2] * 5) / 32;
                                        grayImageData.data[i] = grayImageData.data[i + 1] = grayImageData.data[i + 2] = grayvalue;
                                        grayImageData.data[i + 3] = sourceImage.data[i + 3];
                                    }
                                    wrapper.ListView.view.grayImageCache[grayImageFileName] = grayImageData;
                                    bDrawGrayImage = true;
                                }
                            }
                            else
                            {
                                bDrawGrayImage = true;
                            }
                        }
                        else
                        {
                            bDrawImage = true;
                        }

                        if (bDrawGrayImage)
                        {
                            ctx.drawImage(wrapper.ListView.view.grayImageCache[grayImageFileName], 0, 0,42,42);
                        }
                        if (bDrawImage)
                        {
                            if (wrapper.ListView.view.grayImageCache.hasOwnProperty(headImage))
                            {
                                ctx.drawImage(wrapper.ListView.view.grayImageCache[headImage], 0, 0,42,42);
                            }
                            else
                            {
                                ctx.drawImage(headImage, 0, 0,42,42);
                            }
                        }

                        ctx = null;
                    }
                    onImageLoaded:{
                        if (!wrapper.ListView.view.grayImageCache.hasOwnProperty(headImage))
                        {
                            wrapper.ListView.view.grayImageCache[headImage] = getContext("2d").createImageData(headImage);
                        }

                        requestPaint();
                    }
                    Image{
                        id:itemHeadImageBorder
                        opacity:0.5
                        visible:wrapper.ListView.isCurrentItem ? true : false;
                        source:"file:///E:\\mytestchenyue\\trunk\\TestProject\\TestQml\\PanelListBorder.png"
                    }
                 }
                Text{
                    anchors.left: itemHeadImage.right
                    anchors.leftMargin: 8
                    height:24
                    text:name
                }
                MouseArea{
                    anchors.fill:parent;
                    onClicked: {
                        wrapper.ListView.view.currentIndex = index;
                    }
                }
            }
        }
    }
}
