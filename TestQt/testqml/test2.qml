import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.2

Rectangle{
    id:questionResult;
    objectName: "root";
    visible: true;
    width:480;
    height:320;
    color: "#00ff0000";

    Image{
        id:teamBlue;
        source: "./pic_bg blue.png";
    }
    Image{
        id:teamRed;
        source: "./pic_bg red.png";
    }
}

