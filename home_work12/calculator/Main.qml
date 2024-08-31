import QtQuick 2.5
import QtQuick.Layouts 2.5
import QtQuick.Controls 2.15

Window {
    id: mainFrame
    width: 300
    height: 480
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width




    visible: true
    title: qsTr("Calculator")

    function  doCalculate(op1, op, op2){
        var op1Num = op1*1
        var op2Num = op2*1
        var result
        switch(op){
        case "+":
            result = op1Num + op2Num
            break
        case "-":
            result = op1Num - op2Num
            break
        case "/":
            result = op1Num / op2Num
            break
        case "*":
            result = op1Num * op2Num
            break
        }
        backEndLoger.writeData("Calculate %1 %2 %3 = %4".arg(op1Num).arg(op).arg(op2Num).arg(result))
        return result
    }


    property string oper: ""
    property string oper1: ""
    property string oper2: ""


    signal buttonHendlerSignal(var buttonPressed1)
    onButtonHendlerSignal:{
        switch (buttonPressed1) {
          case "+":
              if(oper1 !== ""){
              oper = "+"
              }
              break;
          case "-":
              if(oper1 !== ""){
                oper = "-"
              }
              break;
          case "/":
              if(oper1 !== ""){
                oper = "/"
              }
              break;
          case "*":
              if(oper1 !== ""){
                  oper = "*"
              }
              break;
          case "=":
              if(oper2 !== ""){
                    oper1 = doCalculate(oper1, oper, oper2)
                    oper2 = ""
                    oper = ""
              }
              break;
          default:
              if(oper === "" ){
              oper1 = oper1 + buttonPressed1
              }else{
                oper2 = oper2 + buttonPressed1
              }
              break;
          }
        if(buttonPressed1==="C"){
            display.text =""
            oper1 = ""
            oper=""
            oper2=""
        }else{
            display.text = "%1\n%2\n%3".arg(oper1).arg(oper).arg(oper2)
            backEndLoger.writeData("Key pressed %1 number on display %2".arg(buttonPressed1)
                                   .arg(oper === "" ? oper1: oper2))

        }
    }
    GridLayout {
        id: gridLayout
        visible: true
        anchors.fill: parent
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        rows: 2
        columns: 1
        layer.enabled: false
        transformOrigin: Item.Center
        clip: false


        Rectangle {
            id: rectangle
            width: 300
            height: 120
            color: "#C3C8F5"
            radius: 5
            border.color: "#1e010202"
            border.width: 10
            Layout.margins: 0
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            clip: true

            TextArea {
                id: display
                color: "#2800da"
                width: 300
                height: 120
                horizontalAlignment: Text.AlignRight
                cursorVisible: false
                textMargin: 5
                font.pointSize: 18
                //hoverEnabled: true
                placeholderTextColor: "#350e0e"
                selectedTextColor: "#e63d0c"
                text: qsTr("")
                wrapMode: Text.WrapAnywhere

            }
        }

        RowLayout {
            id: rowLayout
            width: 100
            height: 100

            Grid {

                id: gridDigitButton
                width: parent.width
                height: parent.height
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.margins: 10
                Layout.fillWidth: false
                spacing: 4
                rows: 4
                columns: 3
                ListModel {
                    id: digiKey

                    ListElement {text_button: "1"; id_button: 1}
                    ListElement {text_button: "2"; id_button: 2}
                    ListElement {text_button: "3"; id_button: 3}
                    ListElement {text_button: "4"; id_button: 4}
                    ListElement {text_button: "5"; id_button: 5}
                    ListElement {text_button: "6"; id_button: 6}
                    ListElement {text_button: "7"; id_button: 7}
                    ListElement {text_button: "8"; id_button: 8}
                    ListElement {text_button: "9"; id_button: 9}
                    ListElement {text_button: "0"; id_button: 0}
                    ListElement {text_button: "C"; id_button: 0}
                    ListElement {text_button: "="; id_button: 0}
                }
                Repeater {
                    id: repeeter
                    model: digiKey

                    Button {
                        id: button
                        required property string text_button
                        required property string id_button
                        property var dspl: display
                        text: text_button               //qsTr("" + index)
                        icon.color: "#e2000000"
                        height: 60
                        width: 60
                        onClicked: {
                            buttonHendlerSignal(text_button)
                        }
                    }
                }
            }

            Grid {
                id: grid1
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                rows: 4
                Layout.margins: 10
                Layout.fillWidth: false
                spacing: 4
                columns: 1
                ListModel {
                    id: operKey
                    ListElement {text_button: "+"; id_button: 1}
                    ListElement {text_button: "-"; id_button: 2}
                    ListElement {text_button: "*"; id_button: 3}
                    ListElement {text_button: "/"; id_button: 4}
                }
                Repeater {
                    id: repeeterOperKey
                    model: operKey

                    Button {
                        id: buttonOper
                        required property string text_button
                        required property string id_button
                        property var dspl: display
                        text: text_button               //qsTr("" + index)
                        icon.color: "#e2000000"
                        height: 60
                        width: 60
                        onClicked: {
                            buttonHendlerSignal(text_button)
                        }

                    }


                }
            }
        }

    }



}
