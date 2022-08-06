import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls
import QtQuick.Layouts 1.12

Rectangle
{
    property int contactId: -1
    property string contactName: ""



    Connections{
        target: mainWindowClass
        ignoreUnknownSignals: true
        function onUpdateChat(sender, messageArg){
            myModel.append({msg:messageArg, sndr: sender, col:"green"})
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
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        ColumnLayout{
            Text{
                text:"Settings"
            }

            RowLayout{
                Image{
                    source: "profile.png"
                    sourceSize.width: 30
                    sourceSize.height: 30
                }
                Text{
                    text:"UserName"
                }
            }
        }
        Rectangle{
            width: parent.width
            height: 23
            anchors.bottom: parent.bottom
            color:"#f08080"
            border.color:"red"
            Row{
                anchors.centerIn: parent
                Image{
                    source: "logout.png"
                    sourceSize.width: 17
                    sourceSize.height: 17

                }
                Text{
                    text: "Logout"
                }
            }

            MouseArea {
                anchors.fill: parent;

                onClicked:{
                    popup.destroy();
                    mainWindow.onLogout();
                }
            }
        }
    }
    ListModel {
        id: listModel


        ListElement {
            mytext: "Vadym"
        }
        ListElement {
            mytext: "Kyrylo"
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
                                    contactId = index;
                                    contactNameInChat.text = mytext;
                                    contactName = contactNameInChat.text;
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




        ListModel {
            id:  myModel;
        }

        Component
        {
            id: myRectComp;

            MyRect
            {
                color: col;
                message: msg;
                sender: sndr;
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
















            ListView {
                id: listView
                model: myModel;
                delegate: myRectComp;
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 100
                readonly property bool sentByMe: index % 2 == 0

                anchors.right: sentByMe ? listView.contentItem.right : undefined
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
                            mainWindow.sendMessage(contactName, txtMessage.text);
                            myModel.append({msg:txtMessage.text, sndr: "sender", col:"lightgrey"})
                        }
                    }
                }
            }
        }
    }
}
