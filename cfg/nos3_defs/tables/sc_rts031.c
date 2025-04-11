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
#include "lc_app.h"
#include "lc_msgids.h"
#include "mgr_msgids.h"
#include "mgr_app.h"

/* 
** ********************************************************
** RTS 031 - Science Mode: Doing Science, Over CONUS Region
** ********************************************************
*/

/* Custom table structure, modify as needed to add desired commands */
typedef struct
{
    /* 1 - Manager Note: Doing Science, Over CONUS Region */
    SC_RtsEntryHeader_t hdr1;
    MGR_U8_cmd_t cmd1;
    /* 2 - Increment Science Pass Counter */
    SC_RtsEntryHeader_t hdr2;
    MGR_NoArgs_cmd_t cmd2;
    /* 3 - Turn ON Instrument */
    SC_RtsEntryHeader_t hdr3;
    SAMPLE_NoArgs_cmd_t cmd3;
    /* 4 - Reset AP 34 - Leaving CONUS Region */
    SC_RtsEntryHeader_t hdr4;
    LC_ResetAPStats_t cmd4;
    /* 5 - Enable AP 34 - Leaving CONUS Region */
    SC_RtsEntryHeader_t hdr5;
    LC_SetAPState_t cmd5;
} SC_RtsStruct031_t;

/* Define the union to size the table correctly */
typedef union
{
    SC_RtsStruct031_t rts;
    uint16            buf[SC_RTS_BUFF_SIZE];
} SC_RtsTable031_t;

/* Helper macro to get size of structure elements */
#define SC_MEMBER_SIZE(member) (sizeof(((SC_RtsStruct031_t *)0)->member))

/* Used designated intializers to be verbose, modify as needed/desired */
SC_RtsTable031_t SC_Rts031 = {    
.rts = {
        /* 1 - Manager Note: Doing Science, Over CONUS Region */
        .hdr1.TimeTag = 1,
        .cmd1.CmdHeader = CFE_MSG_CMD_HDR_INIT(MGR_CMD_MID, SC_MEMBER_SIZE(cmd1), MGR_UPDATE_SCI_STATUS_CC, 0x00),
        .cmd1.U8 = SS_SCIENCE_OVER_CONUS,
        /* 2 - Increment Science Pass Counter */
        .hdr2.TimeTag = 1,
        .cmd2.CmdHeader = CFE_MSG_CMD_HDR_INIT(MGR_CMD_MID, SC_MEMBER_SIZE(cmd2), MGR_SCI_PASS_INC_CC, 0x00),
        /* 3 - Turn ON Instrument */
        .hdr3.TimeTag = 1,
        .cmd3.CmdHeader = CFE_MSG_CMD_HDR_INIT(SAMPLE_CMD_MID, SC_MEMBER_SIZE(cmd3), SAMPLE_ENABLE_CC, 0x00),
        /* 4 - Reset AP 34 - Leaving CONUS Region */
        .hdr4.TimeTag = 1,
        .cmd4.CmdHeader = CFE_MSG_CMD_HDR_INIT(LC_CMD_MID, SC_MEMBER_SIZE(cmd4), LC_RESET_AP_STATS_CC, 0x00),
        .cmd4.APNumber = 34,
        .cmd4.Padding = 0,
        /* 5 - Enable AP 34 - Leaving CONUS Region */
        .hdr5.TimeTag = 1,
        .cmd5.CmdHeader = CFE_MSG_CMD_HDR_INIT(LC_CMD_MID, SC_MEMBER_SIZE(cmd5), LC_SET_AP_STATE_CC, 0x00),
        .cmd5.APNumber = 34,
        .cmd5.NewAPState = LC_APSTATE_ACTIVE,
    }
};

/* Macro for table structure */
CFE_TBL_FILEDEF(SC_Rts031, SC.RTS_TBL031, SC Example RTS_TBL031, sc_rts031.tbl)
