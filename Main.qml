import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Counter 1.0
import QtCore
import RandomNumberGenerator 1.0
import FileHandler 1.0
import DatabaseManager 1.0

Window {
    id: mainPage
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property var backgroundImages: [
        "assets/background1.jpg",
        "assets/background3.jpg",
        "assets/background4.jpg",
        "assets/background5.jpg",
        "assets/background6.jpg",
        "assets/background7.jpg",
        "assets/background8.jpg"
    ]

    property int randomNumber: 0
    property var counterValues: []

    Settings{
        id: settings
        property int savedCounter: 0
        property string savedBackground: backgroundImages[0]
    }

    Counter{
        id: counter
        count: settings.savedCounter
        onCountChanged: {
            settings.savedCounter = counter.count
        }
    }

    FileHandler{
        id: fileHandler
        onFileError: {
            console.log("Error: "+ message)
        }
        onFileSaved: {
//            console.log("File saved successfully")
        }
        onFileLoaded: {
//            console.log("File loaded successfully")
            textEdit.text = data
        }
    }

    RandomNumberGenerator{
        id: random
    }

    DatabaseManager{
        id: dbManager
        onErrorOccurred: {
            console.log("Error: "+ error)
        }
    }

    Component.onCompleted: {
        if(dbManager.initializeDatabase("counter.db")){
            console.log("Database initialised successfully!")
        }
    }

    Rectangle{
        id: counterDisplayRect
        width: 200
        height: 200
        color: "lightblue"
        border.color: "black"
        border.width: 2
        radius: 10
        anchors.fill: parent

        Image {
            id: bgImage
            source: backgroundImages[Math.floor(Math.random()*backgroundImages.length)]
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
        }

        Text{
            id: counterDisplayText
            text: qsTr("Count: ")+ counter.count
            font.pixelSize: 30
            anchors.centerIn: parent
            color: "white"

            Behavior on color {
                ColorAnimation {
                    duration: 350
                    easing.type: Easing.InOutQuad
                }
            }
        }

        Text {
            id: randomNumberText
            text: qsTr("Random number: ") + randomNumber
            anchors{
                top: counterDisplayText.bottom
                topMargin: 10
                horizontalCenter: counterDisplayText.horizontalCenter
            }
            color: "white"
        }
    }

    Rectangle{
        id: textEditRect
        width: 400
//        height: 400
        opacity: 0.5	// 50% opacity
        radius: 8
        anchors{
            left: parent.left
            leftMargin: 10
            top: parent.top
            topMargin: 10
            bottom: parent.bottom
            bottomMargin: 10
        }

        TextEdit{
            id: textEdit
            anchors.fill: parent
            anchors.margins: 10
            text: ""
            color: "black"
            wrapMode: TextEdit.Wrap
        }
    }

    Rectangle{
        id: dbTextEditRect
//        width: 400
        height: 320
        opacity: 0.5	// 50% opacity
        radius: 8
        anchors{
            left: textEditRect.right
            leftMargin: 20
            right: parent.right
            rightMargin: 10
            top: parent.top
            topMargin: 10
            bottom: parent.bottom
            bottomMargin: 10
        }

        TextEdit{
            id: dbTextEdit
            anchors.fill: parent
            anchors.margins: 10
            text: ""
            color: "black"
            wrapMode: TextEdit.Wrap
        }
    }

    Button{
        id: incrementButton
        text: "Increment"
        anchors{
            right: parent.right
            rightMargin: 10
            bottom: parent.bottom
            bottomMargin: 10
        }

        onClicked: {
            counter.increment()
            bgImage.source = backgroundImages[counter.count % backgroundImages.length]

            //            counterDisplayText.color =  "black" // This is to trigger the color animation

        }
        onPressAndHold: counter.increment()

        SequentialAnimation{
            NumberAnimation{
                to: { 1.2; duration: 100}
                easing.type: Easing.InOutQuad
            }
            NumberAnimation{
                to: { 1.0; duration: 100}
                easing.type: Easing.InOutQuad
            }
        }
    }

    Button{
        id: decrementButton
        text: "Decrement"
        anchors{
            right: incrementButton.left
            leftMargin: 7
            bottom: incrementButton.bottom
        }

        onClicked: {
            counter.decrement()
            counterValues.push(counter.count)
        }

        SequentialAnimation{
            NumberAnimation{
                to: { 1.2; duration: 100}
                easing.type: Easing.InOutQuad
            }
            NumberAnimation{
                to: { 1.0; duration: 100}
                easing.type: Easing.InOutQuad
            }
        }
    }

    Button{
        id: loadButton
        text: "Load Data"
        anchors{
            right: decrementButton.left
            leftMargin: 7
            bottom: decrementButton.bottom
        }
        onClicked: {
            let fileName = "counter.txt"
            fileHandler.loadFromFile(fileName)
        }
    }


    // a timer to be triggering the color animation instead of button clicks
    Timer{
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            counterDisplayText.color =  "black"
            secondTimer.start()
            randomNumber = random.generateRandomNumber(0, 1000)
            let fileName = "counter.txt"
            fileHandler.saveToFile(fileName, counterValues)
            fileHandler.loadFromFile(fileName)
            var values = dbManager.fetchAllCounterValues()
            dbTextEdit.text = "DB Values: " + values.join(", ")
        }
    }

    //a second timer to togle the color back to white
    Timer{
        id: secondTimer
        interval: 2000
        onTriggered: {
            counterDisplayText.color =  "white"
            counter.increment()
            counterValues.push(counter.count)
            dbManager.insertCounterValue(counter.count)
            bgImage.source = backgroundImages[counter.count % backgroundImages.length]
        }
    }
}

