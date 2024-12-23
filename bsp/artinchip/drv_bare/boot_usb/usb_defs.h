/*
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _USB_DEFS_H_
#define _USB_DEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* USB constants */

/* Device and/or Interface Class codes */
#define USB_CLASS_PER_INTERFACE 0 /* for DeviceClass */
#define USB_CLASS_AUDIO         1
#define USB_CLASS_COMM          2
#define USB_CLASS_HID           3
#define USB_CLASS_PRINTER       7
#define USB_CLASS_MASS_STORAGE  8
#define USB_CLASS_HUB           9
#define USB_CLASS_DATA          10
#define USB_CLASS_VENDOR_SPEC   0xff

#define MSC_SUBCLASS_SCSI      0x06 /* SCSI transparent */
#define MSC_PROTOCOL_BULK_ONLY 0x50 /* Bulk only transport */

/* some HID sub classes */
#define USB_SUB_HID_NONE 0
#define USB_SUB_HID_BOOT 1

/* some UID Protocols */
#define USB_PROT_HID_NONE     0
#define USB_PROT_HID_KEYBOARD 1
#define USB_PROT_HID_MOUSE    2

/* Sub STORAGE Classes */
#define US_SC_RBC  1 /* Typically, flash devices */
#define US_SC_8020 2 /* CD-ROM */
#define US_SC_QIC  3 /* QIC-157 Tapes */
#define US_SC_UFI  4 /* Floppy */
#define US_SC_8070 5 /* Removable media */
#define US_SC_SCSI 6 /* Transparent */
#define US_SC_MIN  US_SC_RBC
#define US_SC_MAX  US_SC_SCSI

/* STORAGE Protocols */
#define US_PR_CB   1    /* Control/Bulk w/o interrupt */
#define US_PR_CBI  0    /* Control/Bulk/Interrupt */
#define US_PR_BULK 0x50 /* bulk only */

/* USB types */
#define USB_TYPE_STANDARD (0x00 << 5)
#define USB_TYPE_CLASS    (0x01 << 5)
#define USB_TYPE_VENDOR   (0x02 << 5)
#define USB_TYPE_RESERVED (0x03 << 5)

/* USB recipients */
#define USB_RECIP_DEVICE    0x00
#define USB_RECIP_INTERFACE 0x01
#define USB_RECIP_ENDPOINT  0x02
#define USB_RECIP_OTHER     0x03

/* USB directions */
#define USB_DIR_OUT 0
#define USB_DIR_IN  0x80

enum usb_device_speed {
    USB_SPEED_UNKNOWN = 0, /* enumerating */
    USB_SPEED_LOW,
    USB_SPEED_FULL,     /* usb 1.1 */
    USB_SPEED_HIGH,     /* usb 2.0 */
    USB_SPEED_WIRELESS, /* wireless (usb 2.5) */
    USB_SPEED_SUPER,    /* usb 3.0 */
    USB_SPEED_RESERVED
};
/*
 * bmRequestType: USB Device Requests, table 9.2 USB 2.0 spec.
 * (shifted) direction/type/recipient.
 */
#define DeviceRequest ((USB_DIR_IN | USB_TYPE_STANDARD | USB_RECIP_DEVICE) << 8)

#define DeviceOutRequest \
    ((USB_DIR_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE) << 8)

#define InterfaceRequest \
    ((USB_DIR_IN | USB_TYPE_STANDARD | USB_RECIP_INTERFACE) << 8)

#define EndpointRequest \
    ((USB_DIR_IN | USB_TYPE_STANDARD | USB_RECIP_INTERFACE) << 8)

#define EndpointOutRequest \
    ((USB_DIR_OUT | USB_TYPE_STANDARD | USB_RECIP_INTERFACE) << 8)

/* Descriptor types */
#define USB_DT_DEVICE    0x01
#define USB_DT_CONFIG    0x02
#define USB_DT_STRING    0x03
#define USB_DT_INTERFACE 0x04
#define USB_DT_ENDPOINT  0x05

#define USB_DT_HID      (USB_TYPE_CLASS | 0x01)
#define USB_DT_REPORT   (USB_TYPE_CLASS | 0x02)
#define USB_DT_PHYSICAL (USB_TYPE_CLASS | 0x03)
#define USB_DT_HUB      (USB_TYPE_CLASS | 0x09)

/* Descriptor sizes per descriptor type */
#define USB_DT_DEVICE_SIZE         18
#define USB_DT_CONFIG_SIZE         9
#define USB_DT_INTERFACE_SIZE      9
#define USB_DT_ENDPOINT_SIZE       7
#define USB_DT_ENDPOINT_AUDIO_SIZE 9 /* Audio extension */
#define USB_DT_HUB_NONVAR_SIZE     7
#define USB_DT_HID_SIZE            9

/* Endpoints */
#define USB_ENDPOINT_NUMBER_MASK 0x0f /* in bEndpointAddress */
#define USB_ENDPOINT_DIR_MASK    0x80

#define USB_ENDPOINT_XFERTYPE_MASK 0x03 /* in bmAttributes */
#define USB_ENDPOINT_XFER_CONTROL  0
#define USB_ENDPOINT_XFER_ISOC     1
#define USB_ENDPOINT_XFER_BULK     2
#define USB_ENDPOINT_XFER_INT      3

/* usb string index define */
#define USB_STRING_LANGID_INDEX    0x00
#define USB_STRING_MFC_INDEX       0x01
#define USB_STRING_PRODUCT_INDEX   0x02
#define USB_STRING_SERIAL_INDEX    0x03
#define USB_STRING_CONFIG_INDEX    0x04
#define USB_STRING_INTERFACE_INDEX 0x05
#define USB_STRING_OS_INDEX        0x06
#define USB_STRING_MAX             USB_STRING_OS_INDEX

/* USB Packet IDs (PIDs) */
#define USB_PID_UNDEF_0  0xf0
#define USB_PID_OUT      0xe1
#define USB_PID_ACK      0xd2
#define USB_PID_DATA0    0xc3
#define USB_PID_UNDEF_4  0xb4
#define USB_PID_SOF      0xa5
#define USB_PID_UNDEF_6  0x96
#define USB_PID_UNDEF_7  0x87
#define USB_PID_UNDEF_8  0x78
#define USB_PID_IN       0x69
#define USB_PID_NAK      0x5a
#define USB_PID_DATA1    0x4b
#define USB_PID_PREAMBLE 0x3c
#define USB_PID_SETUP    0x2d
#define USB_PID_STALL    0x1e
#define USB_PID_UNDEF_F  0x0f

/* Standard requests */
#define USB_REQ_GET_STATUS        0x00
#define USB_REQ_CLEAR_FEATURE     0x01
#define USB_REQ_SET_FEATURE       0x03
#define USB_REQ_SET_ADDRESS       0x05
#define USB_REQ_GET_DESCRIPTOR    0x06
#define USB_REQ_SET_DESCRIPTOR    0x07
#define USB_REQ_GET_CONFIGURATION 0x08
#define USB_REQ_SET_CONFIGURATION 0x09
#define USB_REQ_GET_INTERFACE     0x0A
#define USB_REQ_SET_INTERFACE     0x0B
#define USB_REQ_SYNCH_FRAME       0x0C

/* HID requests */
#define USB_REQ_GET_REPORT   0x01
#define USB_REQ_GET_IDLE     0x02
#define USB_REQ_GET_PROTOCOL 0x03
#define USB_REQ_SET_REPORT   0x09
#define USB_REQ_SET_IDLE     0x0A
#define USB_REQ_SET_PROTOCOL 0x0B

/* Device features */
#define USB_FEAT_HALT   0x00
#define USB_FEAT_WAKEUP 0x01
#define USB_FEAT_TEST   0x02

/* Test modes */
#define USB_TEST_MODE_J            0x01
#define USB_TEST_MODE_K            0x02
#define USB_TEST_MODE_SE0_NAK      0x03
#define USB_TEST_MODE_PACKET       0x04
#define USB_TEST_MODE_FORCE_ENABLE 0x05

/* "pipe" definitions */

#define PIPE_ISOCHRONOUS 0
#define PIPE_INTERRUPT   1
#define PIPE_CONTROL     2
#define PIPE_BULK        3
#define PIPE_DEVEP_MASK  0x0007ff00

#define USB_ISOCHRONOUS 0
#define USB_INTERRUPT   1
#define USB_CONTROL     2
#define USB_BULK        3

/* USB-status codes: */
#define USB_ST_ACTIVE     0x1         /* TD is active */
#define USB_ST_STALLED    0x2         /* TD is stalled */
#define USB_ST_BUF_ERR    0x4         /* buffer error */
#define USB_ST_BABBLE_DET 0x8         /* Babble detected */
#define USB_ST_NAK_REC    0x10        /* NAK Received*/
#define USB_ST_CRC_ERR    0x20        /* CRC/timeout Error */
#define USB_ST_BIT_ERR    0x40        /* Bitstuff error */
#define USB_ST_NOT_PROC   0x80000000L /* Not yet processed */

/*************************************************************************
 * Hub defines
 */

/*
 * Hub request types
 */

#define USB_RT_HUB  (USB_TYPE_CLASS | USB_RECIP_DEVICE)
#define USB_RT_PORT (USB_TYPE_CLASS | USB_RECIP_OTHER)

/*
 * Hub Class feature numbers
 */
#define C_HUB_LOCAL_POWER  0
#define C_HUB_OVER_CURRENT 1

/*
 * Port feature numbers
 */
#define USB_PORT_FEAT_CONNECTION     0
#define USB_PORT_FEAT_ENABLE         1
#define USB_PORT_FEAT_SUSPEND        2
#define USB_PORT_FEAT_OVER_CURRENT   3
#define USB_PORT_FEAT_RESET          4
#define USB_PORT_FEAT_POWER          8
#define USB_PORT_FEAT_LOWSPEED       9
#define USB_PORT_FEAT_HIGHSPEED      10
#define USB_PORT_FEAT_C_CONNECTION   16
#define USB_PORT_FEAT_C_ENABLE       17
#define USB_PORT_FEAT_C_SUSPEND      18
#define USB_PORT_FEAT_C_OVER_CURRENT 19
#define USB_PORT_FEAT_C_RESET        20
#define USB_PORT_FEAT_TEST           21

/*
 * Changes to Port feature numbers for Super speed,
 * from USB 3.0 spec Table 10-8
 */
#define USB_SS_PORT_FEAT_U1_TIMEOUT     23
#define USB_SS_PORT_FEAT_U2_TIMEOUT     24
#define USB_SS_PORT_FEAT_C_LINK_STATE   25
#define USB_SS_PORT_FEAT_C_CONFIG_ERROR 26
#define USB_SS_PORT_FEAT_BH_RESET       28
#define USB_SS_PORT_FEAT_C_BH_RESET     29

/* wPortStatus bits */
#define USB_PORT_STAT_CONNECTION  0x0001
#define USB_PORT_STAT_ENABLE      0x0002
#define USB_PORT_STAT_SUSPEND     0x0004
#define USB_PORT_STAT_OVERCURRENT 0x0008
#define USB_PORT_STAT_RESET       0x0010
#define USB_PORT_STAT_POWER       0x0100
#define USB_PORT_STAT_LOW_SPEED   0x0200
#define USB_PORT_STAT_HIGH_SPEED  0x0400 /* support for EHCI */
#define USB_PORT_STAT_SUPER_SPEED 0x0600 /* faking support to XHCI */
#define USB_PORT_STAT_SPEED_MASK \
    (USB_PORT_STAT_LOW_SPEED | USB_PORT_STAT_HIGH_SPEED)

/*
 * Changes to wPortStatus bit field in USB 3.0
 * See USB 3.0 spec Table 10-11
 */
#define USB_SS_PORT_STAT_LINK_STATE  0x01e0
#define USB_SS_PORT_STAT_POWER       0x0200
#define USB_SS_PORT_STAT_SPEED       0x1c00
#define USB_SS_PORT_STAT_SPEED_5GBPS 0x0000

/* wPortChange bits */
#define USB_PORT_STAT_C_CONNECTION  0x0001
#define USB_PORT_STAT_C_ENABLE      0x0002
#define USB_PORT_STAT_C_SUSPEND     0x0004
#define USB_PORT_STAT_C_OVERCURRENT 0x0008
#define USB_PORT_STAT_C_RESET       0x0010

/*
 * Changes to wPortChange bit fields in USB 3.0
 * See USB 3.0 spec Table 10-12
 */
#define USB_SS_PORT_STAT_C_BH_RESET     0x0020
#define USB_SS_PORT_STAT_C_LINK_STATE   0x0040
#define USB_SS_PORT_STAT_C_CONFIG_ERROR 0x0080

/* wHubCharacteristics (masks) */
#define HUB_CHAR_LPSM     0x0003
#define HUB_CHAR_COMPOUND 0x0004
#define HUB_CHAR_OCPM     0x0018

/*
 * Hub Status & Hub Change bit masks
 */
#define HUB_STATUS_LOCAL_POWER 0x0001
#define HUB_STATUS_OVERCURRENT 0x0002

#define HUB_CHANGE_LOCAL_POWER 0x0001
#define HUB_CHANGE_OVERCURRENT 0x0002

#define USB_REQUEST_DIR_SHIFT 7U /* Bits 7: Request dir */
#define USB_REQUEST_DIR_OUT \
    (0U << USB_REQUEST_DIR_SHIFT) /*Bit 7=0: Host-to-device*/
#define USB_REQUEST_DIR_IN \
    (1U << USB_REQUEST_DIR_SHIFT) /*Bit 7=1: Device-to-host*/
#define USB_REQUEST_DIR_MASK \
    (1U << USB_REQUEST_DIR_SHIFT) /*Bit 7=1: Direction bit*/
#define USB_REQUEST_TYPE_SHIFT 5U /* Bits 5:6: Request type */
#define USB_REQUEST_STANDARD   (0U << USB_REQUEST_TYPE_SHIFT)
#define USB_REQUEST_CLASS      (1U << USB_REQUEST_TYPE_SHIFT)
#define USB_REQUEST_VENDOR     (2U << USB_REQUEST_TYPE_SHIFT)
#define USB_REQUEST_RESERVED   (3U << USB_REQUEST_TYPE_SHIFT)
#define USB_REQUEST_TYPE_MASK  (3U << USB_REQUEST_TYPE_SHIFT)

#define USB_REQUEST_RECIPIENT_SHIFT     0U /* Bits 0:4: Recipient */
#define USB_REQUEST_RECIPIENT_DEVICE    (0U << USB_REQUEST_RECIPIENT_SHIFT)
#define USB_REQUEST_RECIPIENT_INTERFACE (1U << USB_REQUEST_RECIPIENT_SHIFT)
#define USB_REQUEST_RECIPIENT_ENDPOINT  (2U << USB_REQUEST_RECIPIENT_SHIFT)
#define USB_REQUEST_RECIPIENT_OTHER     (3U << USB_REQUEST_RECIPIENT_SHIFT)
#define USB_REQUEST_RECIPIENT_MASK      (3U << USB_REQUEST_RECIPIENT_SHIFT)

/* USB Standard Request Codes */
#define USB_REQUEST_GET_STATUS          0x00
#define USB_REQUEST_CLEAR_FEATURE       0x01
#define USB_REQUEST_SET_FEATURE         0x03
#define USB_REQUEST_SET_ADDRESS         0x05
#define USB_REQUEST_GET_DESCRIPTOR      0x06
#define USB_REQUEST_SET_DESCRIPTOR      0x07
#define USB_REQUEST_GET_CONFIGURATION   0x08
#define USB_REQUEST_SET_CONFIGURATION   0x09
#define USB_REQUEST_GET_INTERFACE       0x0A
#define USB_REQUEST_SET_INTERFACE       0x0B
#define USB_REQUEST_SYNCH_FRAME         0x0C
#define USB_REQUEST_SET_ENCRYPTION      0x0D
#define USB_REQUEST_GET_ENCRYPTION      0x0E
#define USB_REQUEST_RPIPE_ABORT         0x0E
#define USB_REQUEST_SET_HANDSHAKE       0x0F
#define USB_REQUEST_RPIPE_RESET         0x0F
#define USB_REQUEST_GET_HANDSHAKE       0x10
#define USB_REQUEST_SET_CONNECTION      0x11
#define USB_REQUEST_SET_SECURITY_DATA   0x12
#define USB_REQUEST_GET_SECURITY_DATA   0x13
#define USB_REQUEST_SET_WUSB_DATA       0x14
#define USB_REQUEST_LOOPBACK_DATA_WRITE 0x15
#define USB_REQUEST_LOOPBACK_DATA_READ  0x16
#define USB_REQUEST_SET_INTERFACE_DS    0x17

/* bEndpointAddress in Endpoint Descriptor */
#define USB_ENDPOINT_DIRECTION_MASK 0x80
#define USB_ENDPOINT_OUT(addr)      ((addr) | 0x00)
#define USB_ENDPOINT_IN(addr)       ((addr) | 0x80)

/* USB endpoint direction and number. */
#define USB_EP_DIR_MASK 0x80U
#define USB_EP_DIR_IN   0x80U
#define USB_EP_DIR_OUT  0x00U

/** Get endpoint index (number) from endpoint address */
#define USB_EP_GET_IDX(ep) ((ep) & ~USB_EP_DIR_MASK)
/** Get direction from endpoint address */
#define USB_EP_GET_DIR(ep) ((ep)&USB_EP_DIR_MASK)
/** Get endpoint address from endpoint index and direction */
#define USB_EP_GET_ADDR(idx, dir) ((idx) | ((dir)&USB_EP_DIR_MASK))
/** True if the endpoint is an IN endpoint */
#define USB_EP_DIR_IS_IN(ep) (USB_EP_GET_DIR(ep) == USB_EP_DIR_IN)
/** True if the endpoint is an OUT endpoint */
#define USB_EP_DIR_IS_OUT(ep) (USB_EP_GET_DIR(ep) == USB_EP_DIR_OUT)

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_SHIFT       0
#define USB_ENDPOINT_TYPE_CONTROL     (0 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_ENDPOINT_TYPE_ISOCHRONOUS (1 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_ENDPOINT_TYPE_BULK        (2 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_ENDPOINT_TYPE_INTERRUPT   (3 << USB_ENDPOINT_TYPE_SHIFT)
#define USB_ENDPOINT_TYPE_MASK        (3 << USB_ENDPOINT_TYPE_SHIFT)

#define USB_ENDPOINT_SYNC_SHIFT              2
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION (0 << USB_ENDPOINT_SYNC_SHIFT)
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS       (1 << USB_ENDPOINT_SYNC_SHIFT)
#define USB_ENDPOINT_SYNC_ADAPTIVE           (2 << USB_ENDPOINT_SYNC_SHIFT)
#define USB_ENDPOINT_SYNC_SYNCHRONOUS        (3 << USB_ENDPOINT_SYNC_SHIFT)
#define USB_ENDPOINT_SYNC_MASK               (3 << USB_ENDPOINT_SYNC_SHIFT)

#define USB_ENDPOINT_USAGE_SHIFT             4
#define USB_ENDPOINT_USAGE_DATA              (0 << USB_ENDPOINT_USAGE_SHIFT)
#define USB_ENDPOINT_USAGE_FEEDBACK          (1 << USB_ENDPOINT_USAGE_SHIFT)
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK (2 << USB_ENDPOINT_USAGE_SHIFT)
#define USB_ENDPOINT_USAGE_MASK              (3 << USB_ENDPOINT_USAGE_SHIFT)

#define USB_ENDPOINT_MAX_ADJUSTABLE (1 << 7)

/* wMaxPacketSize in Endpoint Descriptor */
#define USB_MAXPACKETSIZE_SHIFT                        0
#define USB_MAXPACKETSIZE_MASK                         (0x7ff << USB_MAXPACKETSIZE_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT 11
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_NONE  (0 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_ONE   (1 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_TWO   (2 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)
#define USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_MASK  (3 << USB_MAXPACKETSIZE_ADDITIONAL_TRANSCATION_SHIFT)

#ifdef __cplusplus
}
#endif

#endif /*_USB_DEFS_H_ */
