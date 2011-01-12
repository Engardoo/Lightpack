/* Name: hiddata.h
 * Author: Christian Starkjohann
 * Creation Date: 2008-04-11
 * Tabsize: 4
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: hiddata.h 692 2008-11-07 15:07:40Z cs $
 */

/* 
 * hiddata.h
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


#ifndef __HIDDATA_H_INCLUDED__
#define __HIDDATA_H_INCLUDED__

/*
General Description:
This module implements an abstraction layer for data transfer over HID feature
requests. The implementation uses native Windows functions on Windows so that
no driver installation is required and libusb on Unix. You must link the
appropriate libraries in either case: "-lhid -lusb -lsetupapi" on Windows and
`libusb-config --libs` on Unix.
*/

/* ------------------------------------------------------------------------ */

#define USBOPEN_SUCCESS         0   /* no error */
#define USBOPEN_ERR_ACCESS      1   /* not enough permissions to open device */
#define USBOPEN_ERR_IO          2   /* I/O error */
#define USBOPEN_ERR_NOTFOUND    3   /* device not found */


// brunql
#define USB_TIMER_EXPIRED       -62

/* ------------------------------------------------------------------------ */

typedef struct usbDevice    usbDevice_t;
/* Opaque data type representing the USB device. This can be a Windows handle
 * or a libusb handle, depending on the backend implementation.
 */

/* ------------------------------------------------------------------------ */

int usbhidOpenDevice(usbDevice_t **device, int vendorID, char *vendorName, int productID, char *productName, int usesReportIDs);
/* This function opens a USB device. 'vendorID' and 'productID' are the numeric
 * Vendor-ID and Product-ID of the device we want to open. If 'vendorName' and
 * 'productName' are both not NULL, only devices with matching manufacturer-
 * and product name strings are accepted. If the device uses report IDs,
 * 'usesReportIDs' must be set to a non-zero value.
 * Returns: If a matching device has been found, USBOPEN_SUCCESS is returned
 * and '*device' is set to an opaque pointer representing the device. The
 * device must be closed with usbhidCloseDevice(). If the device has not been
 * found or opening failed, an error code is returned.
 */
void    usbhidCloseDevice(usbDevice_t *device);
/* Every device opened with usbhidOpenDevice() must be closed with this function.
 */

/* brunql edited: add timeout */
int usbhidSetReport(usbDevice_t *device, char *buffer, int len, int timeout);
/* This function sends a feature report to the device. The report ID must be
 * in the first byte of buffer and the length 'len' of the report is specified
 * including this report ID. If no report IDs are used, buffer[0] must be set
 * to 0 (dummy report ID).
 * Returns: 0 on success, an error code otherwise.
 */
int usbhidGetReport(usbDevice_t *device, int reportID, char *buffer, int *len);
/* This function obtains a feature report from the device. The requested
 * report-ID is passed in 'reportID'. The caller must pass a buffer of the size
 * of the expected report in 'buffer' and initialize the variable pointed to by
 * 'len' to the total size of this buffer. Upon successful return, the report
 * (prefixed with the report-ID) is in 'buffer' and the actual length of the
 * report is returned in '*len'.
 * Returns: 0 on success, an error code otherwise.
 */

//brunql:
int usbInterruptRead(usbDevice_t *device, char *buffer, int size, int ep);


/* ------------------------------------------------------------------------ */

#endif /* __HIDDATA_H_INCLUDED__ */