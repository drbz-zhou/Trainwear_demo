import QtQuick 2.3

import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    id: window
    width: 1618
    height: 1000
    title: qsTr("Body Suit Demo")
    visibility: Qt.Window

    signal viewClicked(string first)
    signal setDemoMenuState(int state)

    Image {
        id: matrix_1;
        objectName: "matrix_1"
        source: "image://matrix_provider_1/id"
        width: window.width*0.38/2//height/2
        height: window.height*0.16
        anchors.left: parent.left
        anchors.top: parent.top

        cache: false;
        asynchronous : false
        opacity: 0.8

        function updateGrid(){
            matrix_1.source = ""; // this line clears image cache so that new image is loaded
            matrix_1.source = "image://matrix_provider_1/id";
        }
    }

    Image {
        id: matrix_2;
        objectName: "matrix_2"
        source: "image://matrix_provider_2/id"
        width: window.width*0.38/2//height/2
        height: window.height*0.16
        anchors.left: matrix_1.left
        anchors.top: matrix_1.bottom

        cache: false;
        asynchronous : false
        opacity: 0.8

        function updateGrid(){
            matrix_2.source = ""; // this line clears image cache so that new image is loaded
            matrix_2.source = "image://matrix_provider_2/id";
        }
    }

    Image {
        id: matrix_3;
        objectName: "matrix_3"
        source: "image://matrix_provider_3/id"
        width: window.width*0.38/2//height/2
        height: window.height*0.16
        anchors.left: matrix_2.left
        anchors.top: matrix_2.bottom

        cache: false;
        asynchronous : false
        opacity: 0.8

        function updateGrid(){
            matrix_3.source = ""; // this line clears image cache so that new image is loaded
            matrix_3.source = "image://matrix_provider_3/id";
        }
    }

    Image {
        id: matrix_4
        x: -2
        y: 0
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 20
        cache: false
        objectName: "matrix_4"
        asynchronous: false
        source: "image://matrix_provider_4/id"
        anchors.top: matrix_3.bottom
        opacity: 0.8
        anchors.left: parent.left

        function updateGrid(){
            matrix_4.source = ""; // this line clears image cache so that new image is loaded
            matrix_4.source = "image://matrix_provider_4/id";
        }
    }

    Image {
        id: matrix_5
        x: 9
        y: 7
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 0
        cache: false
        objectName: "matrix_5"
        asynchronous: false
        source: "image://matrix_provider_5/id"
        anchors.top: matrix_4.bottom
        opacity: 0.8
        anchors.left: parent.left

        function updateGrid(){
            matrix_5.source = ""; // this line clears image cache so that new image is loaded
            matrix_5.source = "image://matrix_provider_5/id";
        }
    }

    Image {
        id: matrix_6
        x: -4
        y: -3
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 0
        cache: false
        objectName: "matrix_6"
        asynchronous: false
        source: "image://matrix_provider_6/id"
        anchors.top: matrix_5.bottom
        opacity: 0.8
        anchors.left: parent.left

        function updateGrid(){
            matrix_6.source = ""; // this line clears image cache so that new image is loaded
            matrix_6.source = "image://matrix_provider_6/id";
        }
    }

    Image {
        id: matrix_7
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 0
        anchors.leftMargin: window.width*0.005
        cache: false
        objectName: "matrix_7"
        asynchronous: false
        source: "image://matrix_provider_7/id"
        anchors.top: parent.top
        opacity: 0.8
        anchors.left: matrix_1.right

        function updateGrid(){
            matrix_7.source = ""; // this line clears image cache so that new image is loaded
            matrix_7.source = "image://matrix_provider_7/id";
        }
    }

    Image {
        id: matrix_8
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 0
        anchors.leftMargin: window.width*0.005
        cache: false
        objectName: "matrix_8"
        asynchronous: false
        source: "image://matrix_provider_8/id"
        anchors.top: matrix_7.bottom
        opacity: 0.8
        anchors.left: matrix_2.right

        function updateGrid(){
            matrix_8.source = ""; // this line clears image cache so that new image is loaded
            matrix_8.source = "image://matrix_provider_8/id";
        }
    }

    Image {
        id: matrix_9
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 0
        anchors.leftMargin: window.width*0.005
        cache: false
        objectName: "matrix_9"
        asynchronous: false
        source: "image://matrix_provider_9/id"
        anchors.top: matrix_8.bottom
        opacity: 0.8
        anchors.left: matrix_3.right

        function updateGrid(){
            matrix_9.source = ""; // this line clears image cache so that new image is loaded
            matrix_9.source = "image://matrix_provider_9/id";
        }
    }

    Image {
        id: matrix_10
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 20
        anchors.leftMargin: window.width*0.005
        cache: false
        objectName: "matrix_10"
        asynchronous: false
        source: "image://matrix_provider_10/id"
        anchors.top: matrix_9.bottom
        opacity: 0.8
        anchors.left: matrix_4.right

        function updateGrid(){
            matrix_10.source = ""; // this line clears image cache so that new image is loaded
            matrix_10.source = "image://matrix_provider_10/id";
        }
    }

    Image {
        id: matrix_11
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 0
        anchors.leftMargin: window.width*0.005
        cache: false
        objectName: "matrix_11"
        asynchronous: false
        source: "image://matrix_provider_11/id"
        anchors.top: matrix_10.bottom
        opacity: 0.8
        anchors.left: matrix_5.right

        function updateGrid(){
            matrix_11.source = ""; // this line clears image cache so that new image is loaded
            matrix_11.source = "image://matrix_provider_11/id";
        }
    }

    Image {
        id: matrix_12
        width: window.width*0.38/2
        height: window.height*0.16
        anchors.topMargin: 0
        anchors.leftMargin: window.width*0.005
        cache: false
        objectName: "matrix_12"
        asynchronous: false
        source: "image://matrix_provider_12/id"
        anchors.top: matrix_11.bottom
        opacity: 0.8
        anchors.left: matrix_6.right

        function updateGrid(){
            matrix_12.source = ""; // this line clears image cache so that new image is loaded
            matrix_12.source = "image://matrix_provider_12/id";
        }
    }

    Image {
        id: plot_1;
        objectName: "plot_1"
        source: "image://plot_Provider_1/id"
        width: window.width*0.61
        height: window.height
        anchors.right: parent.right
        anchors.top: parent.top
        cache: false;
        asynchronous : false
        opacity: 1

        function updatePlot(){
            plot_1.source = ""; // this line clears image cache so that new image is loaded
            plot_1.source = "image://plot_Provider_1/id";
        }
    }



}

