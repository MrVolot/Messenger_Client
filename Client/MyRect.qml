import QtQuick 2.0

Item
{
    property alias color: theRect.color;
    property string sender: "default";
    property string message: "default";

    Rectangle
    {
        id: theRect;
        Column{
        Text
        {
            text: message;
        }
        Text
        {
            text: sender;
        }
        }

        width: 60;
        height: 80;
    }
}
