/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 2;       
static const unsigned int snap      = 10; //32      
static const int showbar            = 1;       
static const int topbar             = 1;  
static const char *fonts[]          = { "Exo2-Regular:pixelsize=14:autohint=auto"
					"Font Awesome 5 Free:pixelsize=12:autohint=1", 
    		                        "Font Awesome 5 Brands:pixelsize=12:autohint=1", 
					"Font Awesome 5 Free:pixelsize=12:style=solid:autohint=1"};
static const char dmenufont[]       = "Exo2-Regular:size=14";

static const char col_bg[]          = "#1a1b26";
static const char col_fg[]          = "#a9b1d6";
static const char col_border[]      = "#444b6a";
static const char col_sfg[]         = "#bb9af7";
static const char col_sbg[]         = "#32344a";
static const char col_sborder[]     = "#787c99";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_fg, col_bg, col_border },
    [SchemeSel]  = { col_fg, col_sbg,  col_sborder  }
};

/* tagging */
static const char *tags[] = {"", "", "", "", "", ""};


static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Firefox",  NULL,       NULL,       1 << 2,	         0,           -1 },
    { "Code",     NULL,	      NULL,	  2,    	         0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.53; /* master area [0.05..0.95] */
static const int nmaster     = 1;    
static const int resizehints = 1;

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    
    { "[M]",      monocle },
    { "[\\]",     dwindle  },
    { "[@]",      spiral  },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)						\
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },




#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg, "-nf", col_fg, "-sb", col_sbg, "-sf", col_sfg, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *roficmd[]  = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *firefox[] = {"firefox", NULL};
static const char *wallpaper[] = {"gen-wallpaper", NULL};


static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,	                    XK_w,      spawn,          {.v = firefox} },
    { MODKEY|ShiftMask,	            XK_w,      spawn,          {.v = wallpaper} },
    { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY | ShiftMask,           XK_p,      spawn,          {.v = roficmd} },
    { MODKEY,                       XK_Return, spawn,          SHCMD(TERMINAL " -e tmux new-session -s 'Default'") },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY | ShiftMask,           XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,	                    XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
    { MODKEY | ShiftMask,           XK_r,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY | ShiftMask,           XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY | ShiftMask,           XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY | ShiftMask,           XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY | ShiftMask,           XK_period, tagmon,         {.i = +1 } },
    { ControlMask,                  XK_Insert, spawn,          SHCMD("ss") },
    { MODKEY,                       XK_F6,     spawn,          SHCMD("playerctl previous; mocp -r") },
    { MODKEY,                       XK_F7,     spawn,          SHCMD("playerctl play-pause; mocp -G") },
    { MODKEY,                       XK_F8,     spawn,          SHCMD("playerctl next; mocp -f") },
    { MODKEY,                       XK_F9,     spawn,          SHCMD("amixer sset Master 1%-;killsleep") },
    { MODKEY,                       XK_F10,    spawn,          SHCMD("amixer sset Master 1%+;killsleep")},
    {MODKEY | ControlMask,          XK_r,      spawn,          SHCMD("rst")},
    {MODKEY | ControlMask,          XK_p,      spawn,          SHCMD("kpwr")},
    TAGKEYS(XK_1,                      0)
    TAGKEYS(XK_2,                      1)
    TAGKEYS(XK_3,                      2)
    TAGKEYS(XK_4,                      3)
    TAGKEYS(XK_5,                      4)
    TAGKEYS(XK_6,                      5)
    TAGKEYS(XK_7,                      6)
    TAGKEYS(XK_8,                      7)
    TAGKEYS(XK_9,                      8)
    {
        MODKEY | ShiftMask,             XK_e,      quit,           {0}
    },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

