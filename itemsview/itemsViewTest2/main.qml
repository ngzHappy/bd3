
import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#222222"
        }

        GradientStop {
            position: 1
            color: "#000000"
        }
    }

    TreeView {

        model: itemsModel ;
        backgroundVisible: false ;
        anchors.fill: parent ;
        itemDelegate: Item {
              Text {
                  anchors.verticalCenter: parent.verticalCenter

                  text: "xxxx"
              }
          }

        rowDelegate: Rectangle{
        width: 100;
        height: 32;
        }

        TableViewColumn {
                role: "name"
                title: "Name"
            }

    }//TreeView

}//Rectangle



