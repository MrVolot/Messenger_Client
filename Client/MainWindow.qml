import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls

ApplicationWindow {
    title: "Messenger"
    id: mainWindow
    visible: true
    minimumWidth: 800
    minimumHeight: 600
    property bool register: true
    property bool loading: false
    function onLogout(){
        stack.push(registerWindow);
    }
    Connections{
        target: mainWindowClass
        function onLoginSuccess(){
            register = false;
            loading = false;
            stack.push(messengerWindow);
        }
    }
    StackView {
        id: stack
        initialItem: registerWindow
        anchors.fill: parent
        pushEnter: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: 200
            }
        }
        pushExit: Transition {
            PropertyAnimation {
                property: "opacity"
                from: 1
                to:0
                duration: 200
            }
        }
    }
    Component {
        id: registerWindow


        RegisterDialog{
                anchors.centerIn: parent
        }
    }
    Component {
        id: messengerWindow
        MessengerDialog{

        }
    }
    AnimatedImage {
        id: animation
        visible: loading
        source: "loading.gif"
        width: 200
        height:200
        anchors{
            centerIn: parent
        }
        speed: 1
    }
}
