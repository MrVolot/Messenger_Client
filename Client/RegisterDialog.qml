import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls

Rectangle{
    id: registrationDialog
    width: 300
    height: 100
    color: "red"
    //anchors.centerIn: parent
    property bool showText: false
    Connections{
        target: mainWindowClass
        function onWrongCredentials(){
            login.credentials = false;
            password.credentials = false;
            txtPassword.placeholderText = "Wrong credentials!";
            txtPassword.text = "";
            mainWindow.loading = false;
            registrationDialog.opacity = 1.0;
        }
        function onUserExists(){
            login.credentials = false;
            password.credentials = false;
            txtPassword.placeholderText = "User already exists!";
            txtPassword.text = "";
            mainWindow.loading = false;
            registrationDialog.opacity = 1.0;
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
                selectByMouse: true
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
                selectByMouse: true
                placeholderText: "Password"
                echoMode: showText ? TextField.Normal : TextField.Password
                background:Rectangle{border.width: 1
                    color: password.credentials ? "white" : "#F29688"}
            }
            Image{
                source: "index.svg"
                sourceSize.width: 30
                sourceSize.height: parent.height
                anchors.right: parent.right
                MouseArea {
                    anchors.fill: parent;
                    onClicked:{
                        if(showText){
                            showText = false
                        }
                        else
                        {
                            showText = true
                        }
                    }
                }
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
                        mainWindowClass.loginUser(txtLogin.text, txtPassword.text);
                        registrationDialog.opacity = 0.3;
                        mainWindow.loading = true;
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
                        mainWindowClass.registerUser(txtLogin.text, txtPassword.text);
                        registrationDialog.opacity = 0.3;
                        mainWindow.loading = true;
                    }
                }
            }
        }
    }
}
