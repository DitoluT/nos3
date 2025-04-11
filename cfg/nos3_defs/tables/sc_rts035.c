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
#include "mgr_msgids.h"
#include "mgr_app.h"

/* 
** ********************************************************
** RTS 035 - Science Mode: Idle Science, Left HI Region
** ********************************************************
*/

/* Custom table structure, modify as needed to add desired commands */
typedef struct
{
    SC_RtsEntryHeader_t hdr1;
    MGR_U8_cmd_t cmd1;
} SC_RtsStruct035_t;

/* Define the union to size the table correctly */
typedef union
{
    /* 1 - Manager Note: Stop Science, Left HI Region */
    SC_RtsEntryHeader_t hdr1;
    MGR_U8_cmd_t cmd1;
    /* 2 - Turn OFF Instrument */
    SC_RtsEntryHeader_t hdr2;
    SAMPLE_NoArgs_cmd_t cmd2;
    /* 3 - Reset AP 31 - Do Science, Entering HI Region */
    SC_RtsEntryHeader_t hdr3;
    LC_ResetAPStats_t cmd3;
    /* 4 - Enable AP 31 - Do Science, Entering HI Region */
    SC_RtsEntryHeader_t hdr4;
    LC_SetAPState_t cmd4;
} SC_RtsTable035_t;

/* Helper macro to get size of structure elements */
#define SC_MEMBER_SIZE(member) (sizeof(((SC_RtsStruct035_t *)0)->member))

/* Used designated intializers to be verbose, modify as needed/desired */
SC_RtsTable035_t SC_Rts035 = {    
.rts = {
        /* 1 - Manager Note: Idle Science, Left HI Region */
        .hdr1.TimeTag = 1,
        .cmd1.CmdHeader = CFE_MSG_CMD_HDR_INIT(MGR_CMD_MID, SC_MEMBER_SIZE(cmd1), MGR_UPDATE_SCI_STATUS_CC, 0x00),
        .cmd1.U8 = SS_NO_SCIENCE_LEFT_HI,
        /* 2 - Turn OFF Instrument */
        .hdr2.TimeTag = 1,
        .cmd2.CmdHeader = CFE_MSG_CMD_HDR_INIT(SAMPLE_CMD_MID, SC_MEMBER_SIZE(cmd2), SAMPLE_DISABLE_CC, 0x00),
        /* 3 - Reset AP 32 - Do Science, Entering HI Region */
        .hdr3.TimeTag = 1,
        .cmd3.CmdHeader = CFE_MSG_CMD_HDR_INIT(LC_CMD_MID, SC_MEMBER_SIZE(cmd3), LC_RESET_AP_STATS_CC, 0x00),
        .cmd3.APNumber = 32,
        .cmd3.Padding = 0,
        /* 4 - Enable AP 32 - Do Science, Entering HI Region */
        .hdr4.TimeTag = 1,
        .cmd4.CmdHeader = CFE_MSG_CMD_HDR_INIT(LC_CMD_MID, SC_MEMBER_SIZE(cmd4), LC_SET_AP_STATE_CC, 0x00),
        .cmd4.APNumber = 32,
        .cmd4.NewAPState = LC_APSTATE_ACTIVE,
    }
};

/* Macro for table structure */
CFE_TBL_FILEDEF(SC_Rts035, SC.RTS_TBL035, SC Example RTS_TBL035, sc_rts035.tbl)
