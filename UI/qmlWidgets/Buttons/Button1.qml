import QtQuick 2.2

import "../Controls"

ButtonType1{

    signal buttonClicked()

    onClicked: {
        buttonClicked();
    }
}
