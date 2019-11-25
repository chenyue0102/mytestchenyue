import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import "./" as Live

Rectangle{
    id:test;
    width:200;
    height:100;
    Row{
        Image{
            id:img;
            width:100;
            height:100;
            source: "./headimg.png";

            NumberAnimation on opacity{
                running: false;
                loops: Animation.Infinite;
                from:1;
                to:0;
                duration: 1000;
            }
        }
        Image{
            id:img2;
            source: "./team1.png";
            visible: false;
        }

        ShaderEffect{
            id:shaderImg;
            property variant src:img;
            property variant src2:img2;
            opacity: 0.5;
            property real myOpacity:0.8;
            property real myScale:0.9;
            onMyOpacityChanged: {
                //console.log(shaderImg.myOpacity);
            }

            width:100;
            height:100;
            vertexShader: "
                uniform highp mat4 qt_Matrix;
                attribute highp vec4 qt_Vertex;
                attribute highp vec2 qt_MultiTexCoord0;
                varying highp vec2 coord;
                void main(){
                    coord = qt_MultiTexCoord0;
                    gl_Position = qt_Matrix * qt_Vertex;
                }
            ";
            fragmentShader: "
                varying highp vec2 coord;
                uniform sampler2D src;
                uniform sampler2D src2;
                uniform lowp float qt_Opacity;
                uniform lowp float myOpacity;
                uniform lowp float myScale;
                void main(){
                    highp vec2 tmpVec2 = coord / myScale;
                    highp vec4 tmpColor;
                    if (tmpVec2.x <= 1.0 && tmpVec2.y <= 1.0)
                    {
                        lowp vec4 tex = texture2D(src, tmpVec2);
                        tmpColor = vec4(tex.r, tex.g, tex.b, myOpacity);
                    }
                    else
                    {
                        tmpColor = vec4(0.0, 0.0, 0.0, 0.0);
                    }
                    gl_FragColor = tmpColor * 0.5 + texture2D(src2, coord) * 0.5;
                }
            ";
            NumberAnimation on myOpacity{
                running: true;
                loops: Animation.Infinite;
                from:1;
                to:0;
                duration: 1000;
            }
        }
    }
}

