import QtQuick 2.5
import QtQuick.Window 2.2
import QtMultimedia 5.6
import my.filter 1.0

Window {
    visible: true
    height: 400
    width:  600

    Camera {
        id: camera_0

    }

    MyFilter{
      id: filter_0;
      active: true
    }

    VideoOutput {
        id: video_out
        anchors.fill: parent
        source: camera_0
        filters: [filter_0]
    }


}
