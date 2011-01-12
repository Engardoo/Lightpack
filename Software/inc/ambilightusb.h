/*
 * ambilightusb.h
 *
 *  Created on: 26.07.2010
 *      Author: Mike Shatohin (brunql)
 *     Project: Lightpack
 *
 *  Lightpack is very simple implementation of the backlight for a laptop
 *
 *  Copyright (c) 2010, 2011 Mike Shatohin, mikeshatohin [at] gmail.com
 *
 *  Lightpack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Lightpack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef AMBILIGHTUSB_H
#define AMBILIGHTUSB_H

#include <QtGui>

#include "timeevaluations.h"

#include "settings.h"

#include "../FirmwareUSB/usbconfig.h"  /* For device VID, PID, vendor name and product name */
#include "hiddata.h"    /* USB HID */

#include "../CommonHeaders/commands.h"   /* CMD defines */
#include "../CommonHeaders/RGB.h"        /* Led defines */

#include "ledcolors.h"


class AmbilightUsb : public QObject
{
    Q_OBJECT

public:
    AmbilightUsb(QObject *parent = 0);
    ~AmbilightUsb();        

public:
    bool openDevice();
    bool deviceOpened();
    QString hardwareVersion();
    QString firmwareVersion();
    void offLeds();

public slots:
    void updateColors(LedColors colors);
    void setUsbSendDataTimeoutMs(double usb_send_data_timeout_secs);
    void setTimerOptions(int prescallerIndex, int outputCompareRegValue);
    void setColorDepth(int colorDepth);
    void smoothChangeColors(int smoothly_delay);

signals:
    void openDeviceSuccess(bool isSuccess);
    void writeBufferToDeviceSuccess(bool isSuccess);
    void readBufferFromDeviceSuccess(bool isSuccess);


private:
    bool readDataFromDevice();
    bool readDataFromDeviceWithCheck();
    bool writeBufferToDevice();
    bool writeBufferToDeviceWithCheck();
    bool tryToReopenDevice();
    QString usbErrorMessage(int errCode);

    usbDevice_t *ambilightDevice;


    char read_buffer[1 + 0x20];    /* 0x00-ReportID, 0x01..0x20-data */
    char write_buffer[1 + 0x20];   /* 0x00-ReportID, 0x01..0x20-data */


    // Settings:
    int usb_send_data_timeout_ms;
};

#endif // AMBILIGHTUSB_H