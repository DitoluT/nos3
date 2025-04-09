#include "cfe.h"
#include "cfe_tbl_filedef.h"

#include "sc_tbldefs.h"      /* defines SC table headers */
#include "sc_platform_cfg.h" /* defines table buffer size */
#include "sc_msgdefs.h"      /* defines SC command code values */
#include "sc_msgids.h"       /* defines SC packet msg ID's */
#include "sc_msg.h"          /* defines SC message structures */

/* Command Includes */
#include "cam_app.h"
#include "generic_radio_app.h"
#include "sample_app.h"

/* Custom table structure, modify as needed to add desired commands */
typedef struct
{
    SC_RtsEntryHeader_t hdr1;
    SAMPLE_Config_cmd_t cmd1;
    SC_RtsEntryHeader_t hdr2;
    GENERIC_RADIO_Proximity_cmd_t cmd2;
    SC_RtsEntryHeader_t hdr3;
    CAM_NoArgsCmd_t cmd3;
} SC_RtsStruct026_t;

/* Define the union to size the table correctly */
typedef union
{
    SC_RtsStruct026_t rts;
    uint16            buf[SC_RTS_BUFF_SIZE];
} SC_RtsTable026_t;

/* Helper macro to get size of structure elements */
#define SC_MEMBER_SIZE(member) (sizeof(((SC_RtsStruct026_t *)0)->member))

/* Used designated intializers to be verbose, modify as needed/desired */
SC_RtsTable026_t SC_Rts026 = {    
.rts = {
        /* 1 - Sample Configuration 123 */
        .hdr1.TimeTag = 1,
        .cmd1.CmdHeader = CFE_MSG_CMD_HDR_INIT(SAMPLE_CMD_MID, SC_MEMBER_SIZE(cmd1), SAMPLE_CONFIG_CC, 0x00),
        .cmd1.DeviceCfg = CFE_MAKE_BIG32(123),

        /* 2 - Radio Proximity Run Rts5 */
        .hdr2.TimeTag = 1,
        .cmd2.CmdHeader = CFE_MSG_CMD_HDR_INIT(GENERIC_RADIO_CMD_MID, SC_MEMBER_SIZE(cmd2), GENERIC_RADIO_PROXIMITY_CC, 0x00),
        .cmd2.SCID = 0,
        .cmd2.Payload = {0x18, 0xA9, 0xC0, 0x00, 0x00, 0x05, 0x04, 0x00, 0x05, 0x00, 0x00, 0x00},

        /* 3 - CAM NOOP */ 
        .hdr3.TimeTag = 1,
        .cmd3.CmdHeader = CFE_MSG_CMD_HDR_INIT(CAM_CMD_MID, SC_MEMBER_SIZE(cmd3), CAM_NOOP_CC, 0x00),
    }
};

/* Macro for table structure */
CFE_TBL_FILEDEF(SC_Rts026, SC.RTS_TBL026, SC Example RTS_TBL026, sc_rts026.tbl)
