import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.12

Rectangle
{
    Connections{
        target: mainWindow
        ignoreUnknownSignals: true
        function onCustomClose(){
            root.close();
        }
    }
    Popup {
        id: popup
        x: 100
        y: 100
        width: 200
        height: 300
        modal: true
        focus: true
        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        Button{
            id: logout
            text: "Logout"
            onClicked: {
                mainWindow.logout();
            }
        }
    }
    ListModel {
        id: listModel

        ListElement {
            mytext: "Kyrylo"
        }
        ListElement {
            mytext: "Vadym"
        }
    }
    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        Rectangle {
            id: contacts
            implicitWidth: 250
            SplitView.minimumWidth: 100
            SplitView.maximumWidth: 400
            color: "lightblue"

            ListView {
                id: list
                anchors.fill: parent
                model: listModel
                spacing: 3
                delegate: Component {
                    id: listDelegate

                    Item {
                        width: parent.width;
                        height: 20
                        Rectangle{
                            width: parent.width;
                            height: 20
                            color:"lightgrey"
                            Text { text: mytext }
                            MouseArea {
                                anchors.fill: parent;

                                onClicked:{
                                    console.debug("clicked:"+ index);
                                    contactNameInChat.text = mytext
                                }
                            }
                        }
                    }
                }
            }
            Button{
                anchors.bottom: parent.bottom
                width: parent.width
                text:"Settings"
                onClicked: {
                    popup.open()
                }
            }
        }
        ColumnLayout {
            id: centerItem
            SplitView.fillWidth: true
            spacing: 0
            Label {
                id: contactNameInChat
                text: "Name"
                Text{
                    anchors.bottomMargin: 10
                    anchors.leftMargin: 10
                    anchors.bottom: parent.bottom
                    text:"Offline"
                }

                Layout.fillWidth: true
                Layout.preferredHeight: 50
                height: 30
                background: Rectangle {
                    color: "lightblue"
                }
            }

            Label {
                text: "View 2"
                Layout.fillWidth: true
                Layout.fillHeight: true
                background: Rectangle {
                    color: "Grey"
                }
            }
            RowLayout{
                id: row
                width: parent.width
                height:30
                Layout.alignment: Qt.AlignBottom
                TextField{
                    id: txtMessage
                    Layout.fillWidth: true
                    width: parent.width
                    height: parent.height
                    placeholderText: "Enter a message"
                    background:Rectangle{color: "white"}
                }
                Image{
                    source: "icon.png"
                    sourceSize.width: 30
                    sourceSize.height: parent.height
                    MouseArea {
                        anchors.fill: parent;
                        onClicked:{
                            console.debug("Send message " + txtMessage.text);
                        }
                    }
                }
            }
        }
    }
}
