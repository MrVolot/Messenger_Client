import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls

Window {
    title: "Register"
    visible:true
    minimumWidth: 300
    minimumHeight: 100
    maximumWidth: 300
    maximumHeight: 100
    id: root

    Connections{
        target: registerWindow
        ignoreUnknownSignals: true
        function onCustomClose(){
            root.close();
        }

        function onWrongCredentials(){
            console.log("onCWrongCredentials()");
            login.credentials = false;
            password.credentials = false;
            txtPassword.placeholderText = "Wrong credentials!";
            txtPassword.text = "";
        }
    }

    Column{
        id: column
        anchors.fill: parent
        anchors.margins: 5
        spacing: 3
        Rectangle{
            id: login
            property bool credentials: true
            width: parent.width
            height: 25
            border.width: 1
            TextField{
                id: txtLogin
                anchors.fill: parent
                anchors.margins: 0
                anchors.centerIn: parent
                placeholderText: "Login"
                background:Rectangle{border.width: 1
                    color: login.credentials ? "white" : "#F29688"}
            }
        }

        Rectangle{
            id: password
            property bool credentials: true
            width: parent.width
            height: 25
            border.width: 1

            TextField{
                id: txtPassword
                anchors.fill: parent
                anchors.margins: 0
                placeholderText: "Register"
                background:Rectangle{border.width: 1
                    color: password.credentials ? "white" : "#F29688"}
            }
        }
        Row{
            Button {
                id: loginButton
                text: qsTr("Login")
                width: 145
                height:25
                onClicked: {
                    if(txtLogin.text!=="" && txtPassword.text!==""){
                        registerWindow.loginUser(txtLogin.text, txtPassword.text, "login");
                    }
                }
            }
            Button {
                id: registerButton
                text: qsTr("Register")
                width: 145
                height:25
                onClicked: {
                    if(txtLogin.text!=="" && txtPassword.text!==""){
                        registerWindow.loginUser(txtLogin.text, txtPassword.text, "register");
                    }
                }
            }
        }
    }

}
