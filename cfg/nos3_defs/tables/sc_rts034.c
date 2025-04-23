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
#include "generic_eps_app.h"
#include "generic_eps_msgids.h"
#include "sample_app.h"
#include "lc_app.h"
#include "lc_msgids.h"
#include "mgr_msgids.h"
#include "mgr_app.h"

/* 
** ********************************************************
** RTS 034 - Science Mode: Idle Science, Left CONUS Region
** ********************************************************
*/

/* Custom table structure, modify as needed to add desired commands */
typedef struct
{
    /* 1 - Manager Note: Stop Science, Left CONUS Region */
    SC_RtsEntryHeader_t hdr1;
    MGR_U8_cmd_t cmd1;
    /* 2 - Disable Instrument Switch on EPS*/
    SC_RtsEntryHeader_t hdr2;
    GENERIC_EPS_Switch_cmd_t cmd2;
    /* 3 - Disable Instrument Application */
    SC_RtsEntryHeader_t hdr3;
    SAMPLE_NoArgs_cmd_t cmd3;
    /* 4 - Reset AP 31 - Do Science, Entering CONUS Region */
    SC_RtsEntryHeader_t hdr4;
    LC_ResetAPStats_t cmd4;
    /* 5 - Enable AP 31 - Do Science, Entering CONUS Region */
    SC_RtsEntryHeader_t hdr5;
    LC_SetAPState_t cmd5;
} SC_RtsStruct034_t;

/* Define the union to size the table correctly */
typedef union
{
    SC_RtsStruct034_t rts;
    uint16            buf[SC_RTS_BUFF_SIZE];
} SC_RtsTable034_t;

/* Helper macro to get size of structure elements */
#define SC_MEMBER_SIZE(member) (sizeof(((SC_RtsStruct034_t *)0)->member))

/* Used designated intializers to be verbose, modify as needed/desired */
SC_RtsTable034_t SC_Rts034 = {    
.rts = {
        /* 1 - Manager Note: Idle Science, Left CONUS Region */
        .hdr1.TimeTag = 1,
        .cmd1.CmdHeader = CFE_MSG_CMD_HDR_INIT(MGR_CMD_MID, SC_MEMBER_SIZE(cmd1), MGR_UPDATE_SCI_STATUS_CC, 0x00),
        .cmd1.U8 = SS_NO_SCIENCE_LEFT_CONUS,
        /* 2 - Disable Instrument Switch on EPS*/
        .hdr2.TimeTag = 1,
        .cmd2.CmdHeader = CFE_MSG_CMD_HDR_INIT(SAMPLE_CMD_MID, SC_MEMBER_SIZE(cmd2), GENERIC_EPS_SWITCH_CC, 0x00),
        .cmd2.SwitchNumber = 0,
        .cmd2.State = 0x00,
        /* 3 - Disable Instrument Application */
        .hdr3.TimeTag = 1,
        .cmd3.CmdHeader = CFE_MSG_CMD_HDR_INIT(SAMPLE_CMD_MID, SC_MEMBER_SIZE(cmd3), SAMPLE_DISABLE_CC, 0x00),
        /* 4 - Reset AP 31 - Do Science, Entering CONUS Region */
        .hdr4.TimeTag = 1,
        .cmd4.CmdHeader = CFE_MSG_CMD_HDR_INIT(LC_CMD_MID, SC_MEMBER_SIZE(cmd4), LC_RESET_AP_STATS_CC, 0x00),
        .cmd4.APNumber = 31,
        .cmd4.Padding = 0,
        /* 5 - Enable AP 31 - Do Science, Entering CONUS Region */
        .hdr5.TimeTag = 1,
        .cmd5.CmdHeader = CFE_MSG_CMD_HDR_INIT(LC_CMD_MID, SC_MEMBER_SIZE(cmd5), LC_SET_AP_STATE_CC, 0x00),
        .cmd5.APNumber = 31,
        .cmd5.NewAPState = LC_APSTATE_ACTIVE,
    }
};

/* Macro for table structure */
CFE_TBL_FILEDEF(SC_Rts034, SC.RTS_TBL034, SC Example RTS_TBL034, sc_rts034.tbl)
