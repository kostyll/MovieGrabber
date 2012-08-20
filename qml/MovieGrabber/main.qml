// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: emoticonsWindow
    width: 360
    height: 360

    Rectangle {
        anchors.fill: parent
        anchors.margins: 20

        GridView {
            id: gridView
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 10
            anchors.topMargin: 10
            width: parent.width
            height: parent.height
            cellHeight: 200
            cellWidth: 200
            model: listModel

            delegate:
                Rectangle {
                id: imageBox
                width: 180
                height: 180

                Image {
                    width: 160
                    height: 160
                    anchors.centerIn: imageBox
                    source: imageSource
                    smooth: true
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //emoticonsWindow.visible = false
                            movieLoader.source = "MovieDescription.qml"
                            movieSelector.showMovieDescription()
                        }
                    }
                }
            }
        }
    }

    Loader {
        id: movieLoader
    }

    ListModel {
        id: listModel
    }

    Component.onCompleted: {
        for (var i = 1; i< 6; i++)
        {
            listModel.append({imageSource: "qrc:///Images/emoticon_" + i + ".jpg"})
        }
    }
}
