// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 1280
    height: 800

    Image {
        id: previousArrow
        width: 36
        height: 36
        source: "qrc:///Images/previous.png"
        smooth: true
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle {
        width: 1200
        height: 740
        anchors.fill: parent
        anchors.margins: 30
        color: "#DfDfDf"

        Text {
            id: movieTitle
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
            text: "The boy in the Striped Pajamas"
            font.bold: true
            font.pointSize: 20
        }

        Image {
            id: movieImage
            anchors.top: movieTitle.bottom
            anchors.topMargin: 20
            anchors.left: previousArrow.right
            anchors.leftMargin: 20
            width: parent.width / 2
            height: parent.height / 2
            source: "qrc:///Images/moviePicture.jpg"
        }

        Image {
            id: ratingCount
            anchors.left: movieImage.right
            anchors.top: movieTitle.bottom
            anchors.leftMargin: 10
            anchors.topMargin: 10
            smooth: true
            width: 32
            height: 32
            source: "qrc:///Images/rating.png"
        }

        Text {
            id: description
            anchors.left: movieImage.right
            anchors.leftMargin: 10
            anchors.top: ratingCount.bottom
            anchors.topMargin: 100
            width: parent.width / 2 - 20
            wrapMode: Text.WordWrap
            text: qsTr("Set during World War II, a story seen through the innocent eyes of Bruno, the eight-year-old son of the commandant at a concentration camp, whose forbidden friendship with a Jewish boy on the other side of the camp fence has startling and unexpected consequences. ")
        }

//        Rectangle {
//            id: commentsBox
//            anchors.top: movieImage.bottom
//            anchors.topMargin: 20
//            anchors.left: parent.left
//            anchors.leftMargin: 20
//            height: 50
//            width: parent.width
//            color: "#DfDfDf"

//            Text {
//                text: "Comments"
//                anchors.left: commentsBox.left
//                anchors.leftMargin: 20
//            }
//        }
    }

    Image {
        id: nextArrow
        anchors.right: parent.right
        source: "qrc:///Images/next.png"
        smooth: true
        anchors.verticalCenter: parent.verticalCenter
    }
}
